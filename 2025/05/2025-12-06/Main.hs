module Main where

import Data.List.Split

type Range = (Integer, Integer)

countFreshIds :: [Range] -> [Integer] -> Integer
countFreshIds ranges ids = foldr f 0 ids
  where
    f id acc | isFreshId ranges id = acc + 1 | otherwise = acc

isFreshId :: [Range] -> Integer -> Bool
isFreshId ranges id = foldr f False ranges
  where
    f (start, end) acc = acc || start <= id && id <= end

parseContents :: String -> ([Range], [Integer])
parseContents s =
  let parts = span (/= "") . lines $ s
      ranges = fst parts
      ranges' = map parseRange ranges
        where
          parseRange s = case splitOn "-" s of
            (x : y : []) -> (read x :: Integer, read y :: Integer)
            _ -> error "Invalid range"
      ids = drop 1 (snd parts)
      ids' = map (\x -> read x :: Integer) ids
   in (ranges', ids')

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . uncurry countFreshIds . parseContents $ contents
