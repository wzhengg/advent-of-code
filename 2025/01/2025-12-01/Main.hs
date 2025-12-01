module Main where

data Rotation = L Int | R Int

password :: [Rotation] -> Int
password =
  let start = 50
      mod100 x = x `mod` 100
      f pos rot = case rot of
        L dist -> mod100 (pos - dist)
        R dist -> mod100 (pos + dist)
   in length . filter (== 0) . scanl f start

parseContents :: String -> [Rotation]
parseContents =
  let f ('L' : xs) = L dist where dist = read xs :: Int
      f ('R' : xs) = R dist where dist = read xs :: Int
      f _ = error "Invalid rotation"
   in map f . lines

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . password . parseContents $ contents
