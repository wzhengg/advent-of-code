module Solution where

totalJoltage :: [[Int]] -> Int
totalJoltage = sum . map joltage

joltage :: [Int] -> Int
joltage xs =
  let n = length xs
      leftMax = maximum . take (n - 1) $ xs
      right = drop 1 . dropWhile (/= leftMax) $ xs
      rightMax = maximum right
   in leftMax * 10 + rightMax

parseContents :: String -> [[Int]]
parseContents =
  let parseLine l = case l of
        [] -> []
        (x : xs) -> (read [x] :: Int) : parseLine xs
   in map parseLine . lines

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . totalJoltage . parseContents $ contents
