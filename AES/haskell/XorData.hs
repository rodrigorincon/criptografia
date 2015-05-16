module XorData(
	xorLista,
	xorMatriz
)where

import Matrizes
import Data.Bits

xorLista ::Bits t => [t] -> [t] -> [t]
xorLista (h1:t1) (h2:t2)
						|null t1 || null t2 = [h1 `xor` h2]
						|otherwise = (h1 `xor` h2):(xorLista t1 t2)

xorMatriz ::Bits a => Matriz a -> Matriz a -> Matriz a
xorMatriz a b = do
				let linha1 = xorLista (getLinha a 0 ) (getLinha b 0 )
				let linha2 = xorLista (getLinha a 1 ) (getLinha b 1 )
				let linha3 = xorLista (getLinha a 2 ) (getLinha b 2 )
				let linha4 = xorLista (getLinha a 3 ) (getLinha b 3 )
				Matriz [linha1,linha2,linha3,linha4]
