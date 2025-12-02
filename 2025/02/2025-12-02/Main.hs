module Main where

import Data.Int
import Data.List.Split

type Range = (Int64, Int64)

sumInvalidIds :: [Range] -> Int64
sumInvalidIds =
  let sumIdsInRange (start, end) = sum . filter isInvalidId $ [start .. end]
      f range acc = acc + sumIdsInRange range
   in foldr f 0

isInvalidId :: Int64 -> Bool
isInvalidId id =
  let pow = (`div` 2) . ceiling . logBase 10 . fromIntegral $ id
      divisor = 10 ^ pow
      left = id `div` divisor
      right = id `mod` divisor
   in left == right

parseContents :: String -> [Range]
parseContents =
  let parseRange s = case splitOn "-" s of
        (x : y : []) -> (read x :: Int64, read y :: Int64)
        _ -> error "Invalid range"
   in map parseRange . splitOn ","

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . sumInvalidIds . parseContents $ contents
