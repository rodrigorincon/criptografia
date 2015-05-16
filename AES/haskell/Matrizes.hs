module Matrizes(
	Matriz(..),
	matriz,
	getLinhas,
	parseList,
	addToMatriz,
	size,
	insereLinha,
	insereLinhaFinal,
	getLinha
)where

data Matriz a = Null | Matriz [[a]]
	deriving(Eq,Show)

matriz :: Matriz a -> Int -> Int -> a
matriz Null linha coluna = error "matriz vazia"
matriz (Matriz []) linha coluna = error "matriz vazia"
matriz (Matriz(h:t)) linha coluna
									|linha == 0 = h!!coluna
									|otherwise = (t!!(linha-1))!!coluna

getLinhas m linha
			|linha == 0 = [getLinha m linha]
			|otherwise = (getLinhas m (linha-1) )++[getLinha m linha]

parseList (Matriz m) = m

addToMatriz :: Matriz a -> a -> Int -> Int -> Matriz a
addToMatriz (Matriz []) valor linha coluna = Matriz [[valor]]
addToMatriz Null valor linha coluna = Matriz [[valor]]
addToMatriz m valor linha coluna 
								|linha == 0 = Matriz( [(take coluna (getLinha m linha))++[valor]++(drop (coluna+1) (getLinha m linha) )]++(drop (linha+1) (parseList m) ) )
								|otherwise = Matriz( (getLinhas m (linha-1) )++[(take coluna (getLinha m linha))++[valor]++(drop (coluna+1) (getLinha m linha) )]++(drop (linha+1) (parseList m) ) )

size :: Matriz a -> Int
size Null = 0
size (Matriz []) = 0
size (Matriz(h:t)) = length t+1

insereLinha :: Matriz a -> [a] -> Matriz a
insereLinha Null linha = Matriz [linha]
insereLinha (Matriz []) linha = Matriz [linha]
insereLinha (Matriz m) linha = Matriz(linha:m)

insereLinhaFinal Null linha = Matriz [linha]
insereLinhaFinal (Matriz []) linha = Matriz [linha]
insereLinhaFinal (Matriz m) linha = Matriz(m++[linha])

getLinha :: Matriz a -> Int -> [a]
getLinha Null linha = error "matriz vazia"
getLinha (Matriz []) linha = error "matriz vazia"
getLinha (Matriz(h:t)) linha
							|linha == 0 = h
							|otherwise = t!!(linha-1)