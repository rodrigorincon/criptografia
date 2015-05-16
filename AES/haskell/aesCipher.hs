import Matrizes
import XorData
import ConvertHexInt
import Data.Bits
import GF28

sbox = do
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

getWord :: Matriz a -> Int -> Matriz a
getWord key num_round = Matriz [(getLinha key (4*num_round) ), (getLinha key (4*num_round+1) ), (getLinha key (4*num_round+2) ), (getLinha key (4*num_round+3) )]

rotWord linha = [linha!!1,linha!!2,linha!!3,linha!!0]

subWord linha = do
				let matriz_substituicao = sbox
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
				let linha1 = [matriz text 0 0,matriz text 1 1,matriz text 2 2,matriz text 3 3]
				let linha2 = [matriz text 1 0,matriz text 2 1,matriz text 3 2,matriz text 0 3]
				let linha3 = [matriz text 2 0,matriz text 3 1,matriz text 0 2,matriz text 1 3]
				let linha4 = [matriz text 3 0,matriz text 0 1,matriz text 1 2,matriz text 2 3]
				Matriz [linha1,linha2,linha3,linha4]
--				let linha1 = getLinha text 0
--				let linha2 = getLinha text 1
--				let linha3 = getLinha text 2
--				let linha4 = getLinha text 3
--				Matriz [ linha1,[linha2!!1,linha2!!2,linha2!!3,linha2!!0],[linha3!!2,linha3!!3,linha3!!0,linha3!!1],[linha4!!3,linha4!!0,linha4!!1,linha4!!2] ]

mixColumns text = multMatriz text

addRoundKey :: Bits a => Matriz a -> Matriz a -> Int -> Matriz a
addRoundKey text key num_round = xorMatriz text (getWord key num_round)

initialTransformation :: Bits a => Matriz a -> Matriz a -> Matriz a
initialTransformation text key = addRoundKey text key 0

--lastRound :: Bits a => Matriz a -> Matriz a -> Int -> Matriz a
lastRound text key num_round = do
								let subst_text = subBytes text 3 3
								let shift_text = shiftRow subst_text
								addRoundKey shift_text key num_round

--aesRound :: Bits a => Matriz a -> Matriz a -> Int -> Int -> Matriz a
aesRound text key actual_round total_rounds = do
								let subst_text = subBytes text 3 3
								let shift_text = shiftRow subst_text
								let mix_text = mixColumns shift_text
								let round_output = addRoundKey mix_text key actual_round
								if actual_round < total_rounds
									then aesRound round_output key (actual_round+1) total_rounds
								else round_output

--aesCipher :: Bits a => Matriz a -> Matriz a -> Matriz a
aesCipher text key = do
						let key_expanded = keyExpansion key
						let text_initial_transformed = initialTransformation text key_expanded
						let semi_cipher_text = aesRound text_initial_transformed key_expanded 1 9
						lastRound semi_cipher_text key_expanded 10

main = do
	let texto = Matriz [[1,35,69,103],[137,171,205,239],[254,220,186,152],[118,84,50,16]]
	print "mensagem: "
	print (parseIntMatriz4 texto)
	let key = Matriz [[15,21,113,201],[71,217,232,89],[12,183,173,214],[175,127,103,152]]
	print "chave: "
	print (parseIntMatriz4 key)
	let cripto = parseIntMatriz4 (aesCipher texto key)
	print "mensagem criptografada"
	print cripto