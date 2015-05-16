import Matrizes
import XorData
import ConvertHexInt
import Data.Bits
import GF28

sboxKey = do
		let matriz_substituicao_hex = ["63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76",
				   					   "CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0",
								   	   "B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15",
									   "04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75",
									   "09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84",
									   "53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF",
									   "D0", "EF", "AA", "FB", "43", "4D", "33", "85", "45", "F9", "02", "7F", "50", "3C", "9F", "A8",
									   "51", "A3", "40", "8F", "92", "9D", "38", "F5", "BC", "B6", "DA", "21", "10", "FF", "F3", "D2",
									   "CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73",
									   "60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB",
									   "E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79",
									   "E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56", "F4", "EA", "65", "7A", "AE", "08",
									   "BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A",
									   "70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E",
									   "E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF",
									   "8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"]
		parseHexList matriz_substituicao_hex

sbox = do
		let matriz_substituicao_hex = ["52", "09", "6A", "D5", "30", "36", "A5", "38", "BF", "40", "A3", "9E", "81", "F3", "D7", "FB",
				   					   "7C", "E3", "39", "82", "9B", "2F", "FF", "87", "34", "8E", "43", "44", "C4", "DE", "E9", "CB",
								   	   "54", "7B", "94", "32", "A6", "C2", "23", "3D", "EE", "4C", "95", "0B", "42", "FA", "C3", "4E",
									   "08", "2E", "A1", "66", "28", "D9", "24", "B2", "76", "5B", "A2", "49", "6D", "8B", "D1", "25",
									   "72", "F8", "F6", "64", "86", "68", "98", "16", "D4", "A4", "5C", "CC", "5D", "65", "B6", "92",
									   "6C", "70", "48", "50", "FD", "ED", "B9", "DA", "5E", "15", "46", "57", "A7", "8D", "9D", "84",
									   "90", "D8", "AB", "00", "8C", "BC", "D3", "0A", "F7", "E4", "58", "05", "B8", "B3", "45", "06",
									   "D0", "2C", "1E", "8F", "CA", "3F", "0F", "02", "C1", "AF", "BD", "03", "01", "13", "8A", "6B",
									   "3A", "91", "11", "41", "4F", "67", "DC", "EA", "97", "F2", "CF", "CE", "F0", "B4", "E6", "73",
									   "96", "AC", "74", "22", "E7", "AD", "35", "85", "E2", "F9", "37", "E8", "1C", "75", "DF", "6E",
									   "47", "F1", "1A", "71", "1D", "29", "C5", "89", "6F", "B7", "62", "0E", "AA", "18", "BE", "1B",
									   "FC", "56", "3E", "4B", "C6", "D2", "79", "20", "9A", "DB", "C0", "FE", "78", "CD", "5A", "F4",
									   "1F", "DD", "A8", "33", "88", "07", "C7", "31", "B1", "12", "10", "59", "27", "80", "EC", "5F",
									   "60", "51", "7F", "A9", "19", "B5", "4A", "0D", "2D", "E5", "7A", "9F", "93", "C9", "9C", "EF",
									   "A0", "E0", "3B", "4D", "AE", "2A", "F5", "B0", "C8", "EB", "BB", "3C", "83", "53", "99", "61",
									   "17", "2B", "04", "7E", "BA", "77", "D6", "26", "E1", "69", "14", "63", "55", "21", "0C", "7D"]
		parseHexList matriz_substituicao_hex

--getWord :: Matriz a -> Int -> Matriz a
getWord key num_round = Matriz [(getLinha key (4*num_round) ), (getLinha key (4*num_round+1) ), (getLinha key (4*num_round+2) ), (getLinha key (4*num_round+3) )]

rotWord linha = [linha!!1,linha!!2,linha!!3,linha!!0]

subWord linha = do
				let matriz_substituicao = sboxKey
				let v0 = matriz_substituicao!!(linha!!0)
				let v1 = matriz_substituicao!!(linha!!1)
				let v2 = matriz_substituicao!!(linha!!2)
				let v3 = matriz_substituicao!!(linha!!3)
				[v0,v1,v2,v3]

rcon num
		|num == 1 = [1,0,0,0]
		|num == 2 = [2,0,0,0]
		|num == 3 = [4,0,0,0]
		|num == 4 = [8,0,0,0]
		|num == 5 = [16,0,0,0]
		|num == 6 = [32,0,0,0]
		|num == 7 = [64,0,0,0]
		|num == 8 = [128,0,0,0]
		|num == 9 = [27,0,0,0]
		|otherwise = [54,0,0,0]

expansionCond temp i
					|i `mod` 4 == 0 = xorLista (subWord (rotWord temp)) (rcon (i `div` 4) )--floor i/4
					|otherwise = temp

keyExpansion key = do
					let i = size key
					let temp = expansionCond (getLinha key (i-1) ) i
					let new_key = insereLinhaFinal key (xorLista temp (getLinha key (i - 4) ) )
					if i+1 == 44
						then new_key
					else
						keyExpansion new_key 


subBytesSwap texto linhas colunas = do
									let matriz_substituicao_int = sbox
									let valor = matriz_substituicao_int!!(matriz texto linhas colunas)
									addToMatriz texto valor linhas colunas

subBytesColumn text linhas colunas
								|colunas == 0 = subBytesSwap text linhas colunas
								|otherwise = subBytesSwap(subBytesColumn text linhas (colunas-1) ) linhas colunas

subBytes text linhas colunas = do
							let linha1 = subBytesColumn text 0 colunas
							let linha2 = subBytesColumn text 1 colunas
							let linha3 = subBytesColumn text 2 colunas
							let linha4 = subBytesColumn text 3 colunas
							Matriz [(getLinha linha1 0),(getLinha linha2 1),(getLinha linha3 2),(getLinha linha4 3)]

--							|linhas == 0 = subBytesColumn text linhas colunas
--							|otherwise = insereLinha (subBytes text (linhas-1) colunas) (getLinha (subBytesColumn text linhas colunas) linhas)
				
shiftRow text = do
				let linha1 = [matriz text 0 0,matriz text 3 1,matriz text 2 2,matriz text 1 3]
				let linha2 = [matriz text 1 0,matriz text 0 1,matriz text 3 2,matriz text 2 3]
				let linha3 = [matriz text 2 0,matriz text 1 1,matriz text 0 2,matriz text 3 3]
				let linha4 = [matriz text 3 0,matriz text 2 1,matriz text 1 2,matriz text 0 3]
				Matriz [linha1,linha2,linha3,linha4]
--				let linha1 = getLinha text 0
--				let linha2 = getLinha text 1
--				let linha3 = getLinha text 2
--				let linha4 = getLinha text 3
--				Matriz [ linha1,[linha2!!1,linha2!!2,linha2!!3,linha2!!0],[linha3!!2,linha3!!3,linha3!!0,linha3!!1],[linha4!!3,linha4!!0,linha4!!1,linha4!!2] ]

mixColumns text = invMultMatriz text

--addRoundKey :: Bits a => Matriz a -> Matriz a -> Int -> Matriz a
addRoundKey text key num_round = xorMatriz text (getWord key num_round)

--initialTransformation :: Bits a => Matriz a -> Matriz a -> Matriz a
initialTransformation text key = addRoundKey text key 10

--lastRound :: Bits a => Matriz a -> Matriz a -> Int -> Matriz a
lastRound text key num_round = do
								let shift_text = shiftRow text
								let subst_text = subBytes shift_text 3 3
								addRoundKey subst_text key num_round

--aesRound :: Bits a => Matriz a -> Matriz a -> Int -> Int -> Matriz a
aesRound text key actual_round total_rounds = do
								let shift_text = shiftRow text
								let subst_text = subBytes shift_text 3 3
								let add_key_text = xorMatriz subst_text (getWord key actual_round)
								let output_text = mixColumns add_key_text
								if actual_round > total_rounds
									then aesRound output_text key (actual_round-1) total_rounds
								else output_text

--aesCipher :: Bits a => Matriz a -> Matriz a -> Matriz a
aesDecipher text key = do
						let key_expanded = keyExpansion key
						let text_initial_transformed = initialTransformation text key_expanded
						let semi_cipher_text = aesRound text_initial_transformed key_expanded 9 1
						lastRound semi_cipher_text key_expanded 0

main = do
	let cifrado = Matriz [[255,11,132,74],[8,83,191,124],[105,52,171,67],[100,20,143,185]]
	print "mensagem: "
	print ( cifrado)
	let key = Matriz [[15,21,113,201],[71,217,232,89],[12,183,173,214],[175,127,103,152]]
	print "chave: "
	print ( key)
	let texto = parseIntMatriz4 (aesDecipher cifrado key)
	print "mensagem descriptografada"
	print texto