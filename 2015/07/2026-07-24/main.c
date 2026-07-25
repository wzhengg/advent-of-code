#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))

typedef enum {
	GATE_SIG = 1, // # -> x
	GATE_BUF,     // x -> y
	GATE_NOT,     // NOT x -> y
	GATE_AND,     // x AND y -> z
	GATE_AND1,    // 1 AND x -> y
	GATE_OR,      // x OR y -> z
	GATE_LSHIFT,  // x LSHIFT # -> y
	GATE_RSHIFT,  // x RSHIFT # -> y
} GateType;

typedef struct Wire Wire;

typedef struct {
	GateType type;
	uint16_t signal;
} GateSignal;

typedef struct {
	GateType type;
	Wire *src;
} GateUnary;

typedef struct {
	GateType type;
	Wire *src1;
	Wire *src2;
} GateBinary;

typedef struct {
	GateType type;
	Wire *src;
	uint16_t shift;
} GateShift;

typedef union {
	GateType type;
	GateSignal signal;
	GateUnary unary;
	GateBinary binary;
	GateShift shift;
} Gate;

struct Wire {
	uint16_t id;
	uint16_t signal;
	Gate src;
};

typedef struct ListNode ListNode;
struct ListNode {
	ListNode *next;
	Wire *wire;
};

typedef struct {
	ListNode *head;
	ListNode *tail;
	int size;
} List;

static List list_new(void) {
	List queue = {0};
	return queue;
}

static void list_append(List *queue, Wire *wire) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	assert(node);
	node->next = 0;
	node->wire = wire;

	if (queue->tail) {
		queue->tail->next = node;
		queue->tail = node;
	} else {
		queue->head = queue->tail = node;
	}

	queue->size++;
}

static Wire *list_popleft(List *queue) {
	assert(queue->size > 0);
	queue->size--;

	ListNode *popped = queue->head;
	Wire *wire = popped->wire;

	queue->head = queue->head->next;
	if (!queue->head) {
		queue->tail = 0;
	}

	free(popped);

	return wire;
}

static Wire wires[26*26+26] = {0};

static uint16_t wire_id(char *id) {
	assert('a' <= *id && *id <= 'z');
	assert(!id[1] || !id[2]);

	uint16_t res = id[0] - 'a';
	if (id[1]) {
		assert('a' <= id[1] && id[1] <= 'z');
		res = (res+1) * 26 + (id[1]-'a');
	}

	assert(res < ARRAY_COUNT(wires));

	return res;
}

static uint16_t get_wire_signal(char *wire) {
	List edges[ARRAY_COUNT(wires)] = {0};
	int indegree[ARRAY_COUNT(wires)] = {0};

	for (size_t i = 0; i < ARRAY_COUNT(wires); ++i) {
		if (wires[i].src.type) {
			switch (wires[i].src.type) {
				case GATE_SIG:
					break;
				case GATE_BUF:
				case GATE_NOT:
				case GATE_AND1:
					{
						uint16_t src_id = wires[i].src.unary.src->id;
						list_append(&edges[src_id], &wires[i]);
						indegree[i] += 1;
					}
					break;
				case GATE_LSHIFT:
				case GATE_RSHIFT:
					{
						uint16_t src_id = wires[i].src.shift.src->id;
						list_append(&edges[src_id], &wires[i]);
						indegree[i] += 1;
					}
					break;
				case GATE_AND:
				case GATE_OR:
					{
						uint16_t src1_id = wires[i].src.binary.src1->id;
						uint16_t src2_id = wires[i].src.binary.src2->id;
						list_append(&edges[src1_id], &wires[i]);
						list_append(&edges[src2_id], &wires[i]);
						indegree[i] += 2;
					}
					break;
				default:
					assert(0);
			}
		}
	}

	List queue = list_new();

	for (size_t i = 0; i < ARRAY_COUNT(wires); ++i) {
		if (wires[i].src.type && !indegree[i]) {
			list_append(&queue, &wires[i]);
		}
	}

	while (queue.size) {
		Wire *wire = list_popleft(&queue);

		switch (wire->src.type) {
			case GATE_SIG:
				wire->signal = wire->src.signal.signal;
				break;
			case GATE_BUF:
				wire->signal = wire->src.unary.src->signal;
				break;
			case GATE_NOT:
				wire->signal = ~(wire->src.unary.src->signal);
				break;
			case GATE_AND:
				wire->signal = (wire->src.binary.src1->signal) & (wire->src.binary.src2->signal);
				break;
			case GATE_AND1:
				wire->signal = (uint16_t)1 & wire->src.unary.src->signal;
				break;
			case GATE_OR:
				wire->signal = (wire->src.binary.src1->signal) | (wire->src.binary.src2->signal);
				break;
			case GATE_LSHIFT:
				wire->signal = (wire->src.shift.src->signal) << (wire->src.shift.shift);
				break;
			case GATE_RSHIFT:
				wire->signal = (wire->src.shift.src->signal) >> (wire->src.shift.shift);
				break;
			default:
				assert(0);
		}

		for (ListNode *node = edges[wire->id].head; node; node = node->next) {
			--indegree[node->wire->id];
			if (!indegree[node->wire->id]) {
				list_append(&queue, node->wire);
			}
		}
	}

	return wires[wire_id(wire)].signal;
}

int main(void) {
	FILE *fp = fopen("input.txt", "r");
	assert(fp);

	char line[32];
	while (fgets(line, sizeof(line), fp)) {
		uint16_t sig, shift;
		char src1[3], src2[3], dst[3];

		Wire wire = {0};

		if (sscanf(line, "%hu AND %s -> %s", &sig, src1, dst) == 3) {
			assert(sig == 1);
			wire.src.type = GATE_AND1;
			wire.src.unary.src = &wires[wire_id(src1)];
		} else if (sscanf(line, "%s AND %s -> %s", src1, src2, dst) == 3) {
			wire.src.type = GATE_AND;
			wire.src.binary.src1 = &wires[wire_id(src1)];
			wire.src.binary.src2 = &wires[wire_id(src2)];
		} else if (sscanf(line, "%s OR %s -> %s", src1, src2, dst) == 3) {
			wire.src.type = GATE_OR;
			wire.src.binary.src1 = &wires[wire_id(src1)];
			wire.src.binary.src2 = &wires[wire_id(src2)];
		} else if (sscanf(line, "NOT %s -> %s", src1, dst) == 2) {
			wire.src.type = GATE_NOT;
			wire.src.unary.src = &wires[wire_id(src1)];
		} else if (sscanf(line, "%s RSHIFT %hu -> %s", src1, &shift, dst) == 3) {
			wire.src.type = GATE_RSHIFT;
			wire.src.shift.src = &wires[wire_id(src1)];
			wire.src.shift.shift = shift;
		} else if (sscanf(line, "%s LSHIFT %hu -> %s", src1, &shift, dst) == 3) {
			wire.src.type = GATE_LSHIFT;
			wire.src.shift.src = &wires[wire_id(src1)];
			wire.src.shift.shift = shift;
		} else if (sscanf(line, "%hu -> %s", &sig, dst) == 2) {
			wire.src.type = GATE_SIG;
			wire.src.signal.signal = sig;
		} else if (sscanf(line, "%s -> %s", src1, dst) == 2) {
			wire.src.type = GATE_BUF;
			wire.src.unary.src = &wires[wire_id(src1)];
		} else {
			assert(0);
		}

		wire.id = wire_id(dst);
		wires[wire.id] = wire;
	}

	assert(feof(fp) && !ferror(fp));

	printf("%hu\n", get_wire_signal("a"));

	return 0;
}
