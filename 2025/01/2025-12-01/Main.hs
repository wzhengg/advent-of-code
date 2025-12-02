module Main where

data Dir = L | R

type Rotation = (Dir, Int)

password :: [Rotation] -> Int
password =
  let start = 50
      mod100 x = x `mod` 100
      next pos (dir, dist) = case dir of
        L -> mod100 (pos - dist)
        R -> mod100 (pos + dist)
      f (count, pos) rot = (count + zeros, nextPos)
        where
          zeros = count0s pos rot
          nextPos = next pos rot
   in fst . foldl' f (0, start)

count0s :: Int -> Rotation -> Int
count0s pos (dir, dist) =
  let diff
        | L <- dir = pos
        | R <- dir = 100 - pos
      fullRotations = (dist - diff) `div` 100
      zeros
        | diff == 0 = fullRotations
        | dist >= diff = 1 + fullRotations
        | otherwise = 0
   in zeros

parseContents :: String -> [Rotation]
parseContents =
  let f ('L' : xs) = (L, dist) where dist = read xs :: Int
      f ('R' : xs) = (R, dist) where dist = read xs :: Int
      f _ = error "Invalid rotation"
   in map f . lines

main :: IO ()
main = do
  contents <- readFile "input.txt"
  putStrLn . show . password . parseContents $ contents
