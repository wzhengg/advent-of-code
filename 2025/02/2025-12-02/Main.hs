module Main where

import Data.Int
import Data.List.Split

type Id = Int64

type Range = (Id, Id)

countDigits :: Id -> Int64
countDigits = ceiling . logBase 10 . fromIntegral

sumInvalidIds :: [Range] -> Int64
sumInvalidIds =
  let sumIdsInRange (start, end) = sum . filter isInvalidId $ [start .. end]
      f range acc = acc + sumIdsInRange range
   in foldr f 0

isInvalidId :: Id -> Bool
isInvalidId id =
  let maxLen = (`div` 2) . countDigits $ id
      f seqLen acc = acc || isRepeatingSeq seqLen id
   in foldr f False [1 .. maxLen]

isRepeatingSeq :: Int64 -> Id -> Bool
isRepeatingSeq seqLen id =
  let digits = countDigits id
      divisor = 10 ^ seqLen
      seq = id `mod` divisor
      isRepeating id
        | id > 0 = (id `mod` divisor == seq) && isRepeating (id `div` divisor)
        | otherwise = True
   in digits `mod` seqLen == 0 && isRepeating id && id /= seq

parseContents :: String -> [Range]
parseContents =
  let parseRange s = case splitOn "-" s of
        (x : y : []) -> (read x :: Id, read y :: Id)
        _ -> error "Invalid range"
   in map parseRange . splitOn ","

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . sumInvalidIds . parseContents $ contents
