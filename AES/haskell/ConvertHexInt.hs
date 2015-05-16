module ConvertHexInt(
	hexChar,
	parseHex,
    parseHexList,
    parseHexMatriz,
    parseIntList,
    parseIntMatriz4
)where

import Matrizes
import Numeric

hexChar :: Char -> Int
hexChar ch
    | ch == '0' = 0
    | ch == '1' = 1
    | ch == '2' = 2
    | ch == '3' = 3
    | ch == '4' = 4
    | ch == '5' = 5
    | ch == '6' = 6
    | ch == '7' = 7
    | ch == '8' = 8
    | ch == '9' = 9
    | ch == 'A' || ch == 'a' = 10
    | ch == 'B' || ch == 'b' = 11
    | ch == 'C' || ch == 'c' = 12
    | ch == 'D' || ch == 'd' = 13
    | ch == 'E' || ch == 'e' = 14
    | ch == 'F' || ch == 'f' = 15
    | otherwise     = 0

parseHex :: String -> Int
parseHex hxStr 
    | length hxStr /= 0 = (hexChar(last(hxStr)))+(16*parseHex(init(hxStr)))
    | otherwise         = 0

parseHexList :: [String] -> [Int]
parseHexList (h:t)
                |t==[] = [parseHex h]
                |otherwise = [(parseHex h)]++(parseHexList t)

--parseHexMatriz :: Matriz a -> Matriz[a]
parseHexMatriz m = do
                let linha1 = parseHexList (getLinha m 0)
                let linha2 = parseHexList (getLinha m 1)
                let linha3 = parseHexList (getLinha m 2)
                let linha4 = parseHexList (getLinha m 3)
                Matriz [linha1,linha2,linha3,linha4]

parseIntList (h:t)
                |t==[] = [showHex h ""]
                |otherwise = [(showHex h "")]++(parseIntList t)

parseIntMatriz4 m = do
                let linha1 = parseIntList (getLinha m 0)
                let linha2 = parseIntList (getLinha m 1)
                let linha3 = parseIntList (getLinha m 2)
                let linha4 = parseIntList (getLinha m 3)
                Matriz [linha1,linha2,linha3,linha4]
