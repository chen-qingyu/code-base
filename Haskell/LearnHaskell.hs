-- 9223372036854775807
_ = maxBound :: Int

-- -9223372036854775808
_ = minBound :: Int

-- [1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576]
_ = [2 ^ n | n <- [0 .. 20], 2 ^ n > 1000]

fac :: Integer -> Integer
fac n = product [1 .. n]

trd :: (a, b, c) -> c
trd (_, _, c) = c

quickSort :: Ord a => [a] -> [a]
quickSort [] = []
quickSort (p : xs) = quickSort lesser ++ [p] ++ quickSort greater
  where
    lesser = filter (< p) xs
    greater = filter (>= p) xs

qsort :: (Ord a) => [a] -> [a]
qsort [] = []
qsort (x : xs) =
  let smallerSorted = qsort [a | a <- xs, a <= x]
      biggerSorted = qsort [a | a <- xs, a > x]
   in smallerSorted ++ [x] ++ biggerSorted
