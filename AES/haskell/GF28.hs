module GF28(
	mult,
	soma,
	calcElement,
	multMatriz,
	invMultMatriz,
	invCalcElement,
	multInv,
	mult8,
	mult4,
	mult2	
)where

import Matrizes
import Data.Bits

soma a b c d = a `xor` b `xor` c `xor` d

xorCondicional valor
				|valor > 255 = valor `xor` 283
				|otherwise = valor

mult coef valor
			|coef == 1 = valor
			|coef == 2 = xorCondicional (valor `shiftL` 1)
			|otherwise = (xorCondicional (valor `shiftL` 1) ) `xor` valor


--calcElement coef matrix linha coluna = soma (mult ((coef!!linha)!!0) (matriz matrix 0 coluna) ) (mult ((coef!!linha)!!1) (matriz matrix 1 coluna) ) (mult ((coef!!linha)!!2) (matriz matrix 2 coluna) ) (mult ((coef!!linha)!!3) (matriz matrix 3 coluna) )
calcElement coef matrix linha coluna = soma (mult ((coef!!linha)!!0) (matriz matrix coluna 0) ) (mult ((coef!!linha)!!1) (matriz matrix coluna 1) ) (mult ((coef!!linha)!!2) (matriz matrix coluna 2) ) (mult ((coef!!linha)!!3) (matriz matrix coluna 3) )

multMatriz matrix = do
	let coef = [ [2,3,1,1],[1,2,3,1],[1,1,2,3],[3,1,1,2] ]
	let linha1 = [calcElement coef matrix 0 0, calcElement coef matrix 1 0, calcElement coef matrix 2 0, calcElement coef matrix 3 0]
	let linha2 = [calcElement coef matrix 0 1, calcElement coef matrix 1 1, calcElement coef matrix 2 1, calcElement coef matrix 3 1]
	let linha3 = [calcElement coef matrix 0 2, calcElement coef matrix 1 2, calcElement coef matrix 2 2, calcElement coef matrix 3 2]
	let linha4 = [calcElement coef matrix 0 3, calcElement coef matrix 1 3, calcElement coef matrix 2 3, calcElement coef matrix 3 3]
--	let linha1 = [calcElement coef matrix 0 0, calcElement coef matrix 0 1, calcElement coef matrix 0 2, calcElement coef matrix 0 3]
--	let linha2 = [calcElement coef matrix 1 0, calcElement coef matrix 1 1, calcElement coef matrix 1 2, calcElement coef matrix 1 3]
--	let linha3 = [calcElement coef matrix 2 0, calcElement coef matrix 2 1, calcElement coef matrix 2 2, calcElement coef matrix 2 3]
--	let linha4 = [calcElement coef matrix 3 0, calcElement coef matrix 3 1, calcElement coef matrix 3 2, calcElement coef matrix 3 3]
	Matriz [linha1, linha2, linha3, linha4]


mult2 valor = xorCondicional (valor `shiftL` 1)
mult4 valor = mult2 (mult2 valor)
mult8 valor = mult2 (mult2 (mult2 valor) ) 

multInv coef valor
			|coef == 9 = (mult8 valor) `xor` valor
			|coef == 11 = (mult8 valor) `xor` (mult2 valor) `xor` valor
			|coef == 13 = (mult8 valor) `xor` (mult4 valor) `xor` valor
			|otherwise = (mult8 valor) `xor` (mult4 valor) `xor` (mult2 valor)

invCalcElement coef matrix linha coluna = soma (multInv ((coef!!linha)!!0) (matriz matrix coluna 0) ) (multInv ((coef!!linha)!!1) (matriz matrix coluna 1) ) (multInv ((coef!!linha)!!2) (matriz matrix coluna 2) ) (multInv ((coef!!linha)!!3) (matriz matrix coluna 3) )

invMultMatriz matrix = do
	let coef = [ [14,11,13,9],[9,14,11,13],[13,9,14,11],[11,13,9,14] ]
	let linha1 = [invCalcElement coef matrix 0 0, invCalcElement coef matrix 1 0, invCalcElement coef matrix 2 0, invCalcElement coef matrix 3 0]
	let linha2 = [invCalcElement coef matrix 0 1, invCalcElement coef matrix 1 1, invCalcElement coef matrix 2 1, invCalcElement coef matrix 3 1]
	let linha3 = [invCalcElement coef matrix 0 2, invCalcElement coef matrix 1 2, invCalcElement coef matrix 2 2, invCalcElement coef matrix 3 2]
	let linha4 = [invCalcElement coef matrix 0 3, invCalcElement coef matrix 1 3, invCalcElement coef matrix 2 3, invCalcElement coef matrix 3 3]
	Matriz [linha1, linha2, linha3, linha4]