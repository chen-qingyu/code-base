qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (p : xs) = qsort (filter (<= p) xs) ++ [p] ++ qsort (filter (> p) xs)
