czyPierwotna :: (Int,Int,Int) -> Bool
czyPierwotna (a,b,c)
    | gcd a b == 1 && gcd a c == 1 && gcd b c == 1 = True
    | otherwise = False

for1 :: Int -> Int -> Int -> (Int, Int)
for1 m n k
    | 2*m*(m+n) == k = (m,n)
    | m == k = for1 (n+1) (n+1) k
    | n <= k = for1 (m+1) n k
    | otherwise = (0, 0)

liczABC :: (Int, Int) -> (Int, Int, Int)
liczABC (m,n)
    | m == 0 || n == 0 || m*m - n*n == 0 = (0,0,0)
    | otherwise = (m*m-n*n, 2*m*n, m*m+n*n)

szukajTrojkiPitagorejskiej :: Int -> (Int, Int, Int)
szukajTrojkiPitagorejskiej n
    | (b) == (0,0,0) && n > 1 = szukajTrojkiPitagorejskiej (n-1)
    | c = (b)
    | not (c) = szukajTrojkiPitagorejskiej (n-1)
    | otherwise = (0,0,0)
    where a = for1 1 1 n
          b = liczABC a
          c = czyPierwotna (b)
