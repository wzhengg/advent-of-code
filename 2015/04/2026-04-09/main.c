#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// #define KEY "yzbqklnj"
#define KEY ""

typedef struct String String;
struct String {
	u8 *str;
	u64 len;
};

String md5_pad(String msg) {
	u64 align = 64;

	u64 padded_len = (msg.len+align) & (~(align-1));
	if (msg.len >= padded_len - 8) {
		padded_len = (msg.len+(2*align)) & (~(align-1));
	}

	String padded = {.str = 0, .len = 0};

	padded.str = (u8 *)malloc(padded_len * sizeof(u8));
	if (padded.str) {
		padded.len = padded_len;
		u64 padding_bytes = padded.len - msg.len - sizeof(u8) - sizeof(u64);

		memcpy(padded.str, msg.str, msg.len);
		padded.str[msg.len] = 0x80;
		memset(&padded.str[msg.len+1], 0, padding_bytes);

		padded.str[padded.len - 8] = (u8)(msg.len);
		padded.str[padded.len - 7] = (u8)(msg.len >> 8);
		padded.str[padded.len - 6] = (u8)(msg.len >> 16);
		padded.str[padded.len - 5] = (u8)(msg.len >> 24);
		padded.str[padded.len - 4] = (u8)(msg.len >> 32);
		padded.str[padded.len - 3] = (u8)(msg.len >> 40);
		padded.str[padded.len - 2] = (u8)(msg.len >> 48);
		padded.str[padded.len - 1] = (u8)(msg.len >> 56);
	}

	return padded;
}

u32 md5_F(u32 X, u32 Y, u32 Z) {
	return (X&Y) | (~X&Z);
}

u32 md5_G(u32 X, u32 Y, u32 Z) {
	return (X&Z) | (Y&~Z);
}

u32 md5_H(u32 X, u32 Y, u32 Z) {
	return X ^ Y ^ Z;
}

u32 md5_I(u32 X, u32 Y, u32 Z) {
	return Y ^ (X | ~Z);
}

u32 md5_shift(u32 X, u32 s) {
	s = s % 32;
	return (X << s) | (X >> (32-s));
}

u32 md5_r1_op(u32 X[16], u32 A, u32 B, u32 C, u32 D, u32 k, u32 s, u32 T) {
	return B + md5_shift(A + md5_F(B,C,D) + X[k] + T, s);
}

u32 md5_r2_op(u32 X[16], u32 A, u32 B, u32 C, u32 D, u32 k, u32 s, u32 T) {
	return B + md5_shift(A + md5_G(B,C,D) + X[k] + T, s);
}

u32 md5_r3_op(u32 X[16], u32 A, u32 B, u32 C, u32 D, u32 k, u32 s, u32 T) {
	return B + md5_shift(A + md5_H(B,C,D) + X[k] + T, s);
}

u32 md5_r4_op(u32 X[16], u32 A, u32 B, u32 C, u32 D, u32 k, u32 s, u32 T) {
	return B + md5_shift(A + md5_I(B,C,D) + X[k] + T, s);
}

typedef struct MD5 MD5;
struct MD5 {
	u8 out[64];
};

MD5 md5_foo(String msg) {
	u32 A = 0x67452301;
	u32 B = 0xefcdab89;
	u32 C = 0x98badcfe;
	u32 D = 0x10325476;

	u32 *M = (u32 *)msg.str;
	u32 block_count = msg.len / 64;

	for (u32 i = 0; i < block_count; ++i) {

		u32 X[16];
		for (u32 j = 0; j < 16; ++j) {
			X[j] = M[i*16+j];
		}

		u32 AA = A;
		u32 BB = B;
		u32 CC = C;
		u32 DD = D;

		// Round 1
		A = md5_r1_op(X, A,B,C,D, 0, 7, 0xd76aa478);
		D = md5_r1_op(X, D,A,B,C, 1, 12, 0xe8c7b756);
		C = md5_r1_op(X, C,D,A,B, 2, 17, 0x242070db);
		B = md5_r1_op(X, B,C,D,A, 3, 22, 0xc1bdceee);
		A = md5_r1_op(X, A,B,C,D, 4, 7, 0xf57c0faf);
		D = md5_r1_op(X, D,A,B,C, 5, 12, 0x4787c62a);
		C = md5_r1_op(X, C,D,A,B, 6, 17, 0xa8304613);
		B = md5_r1_op(X, B,C,D,A, 7, 22, 0xfd469501);
		A = md5_r1_op(X, A,B,C,D, 8, 7, 0x698098d8);
		D = md5_r1_op(X, D,A,B,C, 9, 12, 0x8b44f7af);
		C = md5_r1_op(X, C,D,A,B, 10, 17, 0xffff5bb1);
		B = md5_r1_op(X, B,C,D,A, 11, 22, 0x895cd7be);
		A = md5_r1_op(X, A,B,C,D, 12, 7, 0x6b901122);
		D = md5_r1_op(X, D,A,B,C, 13, 12, 0xfd987193);
		C = md5_r1_op(X, C,D,A,B, 14, 17, 0xa679438e);
		B = md5_r1_op(X, B,C,D,A, 15, 22, 0x49b40821);

		// Round 2
		A = md5_r2_op(X, A,B,C,D, 1, 5, 0xf61e2562);
		D = md5_r2_op(X, D,A,B,C, 6, 9, 0xc040b340);
		C = md5_r2_op(X, C,D,A,B, 11, 14, 0x265e5a51);
		D = md5_r2_op(X, B,C,D,A, 0, 20, 0xe9b6c7aa);
		A = md5_r2_op(X, A,B,C,D, 5, 5, 0xd62f105d);
		D = md5_r2_op(X, D,A,B,C, 10, 9, 0x2441453);
		C = md5_r2_op(X, C,D,A,B, 15, 14, 0xd8a1e681);
		D = md5_r2_op(X, B,C,D,A, 4, 20, 0xe7d3fbc8);
		A = md5_r2_op(X, A,B,C,D, 9, 5, 0x21e1cde6);
		D = md5_r2_op(X, D,A,B,C, 14, 9, 0xc33707d6);
		C = md5_r2_op(X, C,D,A,B, 3, 14, 0xf4d50d87);
		D = md5_r2_op(X, B,C,D,A, 8, 20, 0x455a14ed);
		A = md5_r2_op(X, A,B,C,D, 13, 5, 0xa9e3e905);
		D = md5_r2_op(X, D,A,B,C, 2, 9, 0xfcefa3f8);
		C = md5_r2_op(X, C,D,A,B, 7, 14, 0x676f02d9);
		D = md5_r2_op(X, B,C,D,A, 12, 20, 0x8d2a4c8a);

		// Round 3
		A = md5_r3_op(X, A,B,C,D, 5, 4, 0xfffa3942);
		D = md5_r3_op(X, D,A,B,C, 8, 11, 0x8771f681);
		C = md5_r3_op(X, C,D,A,B, 11, 16, 0x6d9d6122);
		B = md5_r3_op(X, B,C,D,A, 14, 23, 0xfde5380c);
		A = md5_r3_op(X, A,B,C,D, 1, 4, 0xa4beea44);
		D = md5_r3_op(X, D,A,B,C, 4, 11, 0x4bdecfa9);
		C = md5_r3_op(X, C,D,A,B, 7, 16, 0xf6bb4b60);
		B = md5_r3_op(X, B,C,D,A, 10, 23, 0xbebfbc70);
		A = md5_r3_op(X, A,B,C,D, 13, 4, 0x289b7ec6);
		D = md5_r3_op(X, D,A,B,C, 0, 11, 0xeaa127fa);
		C = md5_r3_op(X, C,D,A,B, 3, 16, 0xd4ef3085);
		B = md5_r3_op(X, B,C,D,A, 6, 23, 0x4881d05);
		A = md5_r3_op(X, A,B,C,D, 9, 4, 0xd9d4d039);
		D = md5_r3_op(X, D,A,B,C, 12, 11, 0xe6db99e5);
		C = md5_r3_op(X, C,D,A,B, 15, 16, 0x1fa27cf8);
		B = md5_r3_op(X, B,C,D,A, 2, 23, 0xc4ac5665);

		// Round 4
		A = md5_r4_op(X, A,B,C,D, 0, 6, 0xf4292244);
		D = md5_r4_op(X, D,A,B,C, 7, 10, 0x432aff97);
		C = md5_r4_op(X, C,D,A,B, 14, 15, 0xab9423a7);
		B = md5_r4_op(X, B,C,D,A, 5, 21, 0xfc93a039);
		A = md5_r4_op(X, A,B,C,D, 12, 6, 0x655b59c3);
		D = md5_r4_op(X, D,A,B,C, 3, 10, 0x8f0ccc92);
		C = md5_r4_op(X, C,D,A,B, 10, 15, 0xffeff47d);
		B = md5_r4_op(X, B,C,D,A, 1, 21, 0x85845dd1);
		A = md5_r4_op(X, A,B,C,D, 8, 6, 0x6fa87e4f);
		D = md5_r4_op(X, D,A,B,C, 15, 10, 0xfe2ce6e0);
		C = md5_r4_op(X, C,D,A,B, 6, 15, 0xa3014314);
		B = md5_r4_op(X, B,C,D,A, 13, 21, 0x4e0811a1);
		A = md5_r4_op(X, A,B,C,D, 4, 6, 0xf7537e82);
		D = md5_r4_op(X, D,A,B,C, 11, 10, 0xbd3af235);
		C = md5_r4_op(X, C,D,A,B, 2, 15, 0x2ad7d2bb);
		B = md5_r4_op(X, B,C,D,A, 9, 21, 0xeb86d391);

		A += AA;
		B += BB;
		C += CC;
		D += DD;
	}

	MD5 md5;

	u32 *out = (u32 *)md5.out;
	out[0] = D;
	out[1] = C;
	out[2] = B;
	out[3] = A;

	return md5;
}

int main(void) {
	String key = {.str = (u8 *)KEY, .len = strlen(KEY)};
	String foo = md5_pad(key);
	MD5 bar = md5_foo(foo);

	for (u32 i = 0; i < 16; ++i) {
		printf("%02x", bar.out[i]);
	}

	return 0;
}
