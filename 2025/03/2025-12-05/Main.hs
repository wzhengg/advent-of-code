module Main where

totalJoltage :: [[Integer]] -> Integer
totalJoltage =
  let digits = 12
   in sum . map (joltage digits)

joltage :: Int -> [Integer] -> Integer
joltage 0 _ = 0
joltage digits xs =
  let n = length xs
      remaining = digits - 1
      left = take (n - remaining) xs
      max = maximum left
      right = drop 1 . dropWhile (/= max) $ xs
   in max * (10 ^ remaining) + joltage remaining right

parseContents :: String -> [[Integer]]
parseContents =
  let parseLine l = case l of
        [] -> []
        (x : xs) -> (read [x] :: Integer) : parseLine xs
   in map parseLine . lines

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . totalJoltage . parseContents $ contents
