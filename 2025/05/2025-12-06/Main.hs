module Main where

import Data.List
import Data.List.Split

type Range = (Integer, Integer)

countIds :: [Range] -> Integer
countIds =
  let f (start, end) acc = acc + (end - start + 1)
   in foldr f 0 . mergeRanges

mergeRanges :: [Range] -> [Range]
mergeRanges [] = []
mergeRanges ranges =
  let f range [] = [range]
      f range@(start, end) acc@(x : xs)
        | start <= end' = (start', max end end') : xs
        | otherwise = range : acc
        where
          (start', end') = x
   in foldr f [] . reverse . sort $ ranges

parseContents :: String -> [Range]
parseContents s =
  let ranges = takeWhile (/= "") . lines $ s
      ranges' = map parseRange ranges
      parseRange s = case splitOn "-" s of
        (x : y : []) -> (read x :: Integer, read y :: Integer)
        _ -> error "Invalid range"
   in ranges'

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . countIds . parseContents $ contents
