module Main where

import Data.List

data Op = Add | Mul

data Problem = Problem Op Integer

grandTotal :: [[Integer]] -> [Op] -> Integer
grandTotal rows ops =
  let problems =
        let f Add = Problem Add 0
            f Mul = Problem Mul 1
         in map f ops
      solved =
        let f probs row = map g (zip probs row)
            g pair = case pair of
              ((Problem Add x), y) -> Problem Add (x + y)
              ((Problem Mul x), y) -> Problem Mul (x * y)
         in foldl' f problems rows
   in foldl' (\z (Problem _ x) -> z + x) 0 solved

parseContents :: String -> ([[Integer]], [Op])
parseContents s =
  let lines' = lines s
      rows = map parseNums . init $ lines'
      ops = parseOps . last $ lines'
   in (rows, ops)

parseNums :: String -> [Integer]
parseNums = map (\x -> read x :: Integer) . words

parseOps :: String -> [Op]
parseOps =
  let f '+' = Add
      f '*' = Mul
   in map f . filter (/= ' ')

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . uncurry grandTotal . parseContents $ contents
