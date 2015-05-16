# -*- coding: UTF-8 -*-

from aesCipher import aesCipher, aesDecipher

def main():
	repete_entrada = True
	while(repete_entrada):
		texto = raw_input("entre com seu texto de 16 caracteres (128 bits)")
		chave = raw_input("entre com sua chave de 16 caracteres bits (128 bits)")
		
		if( len(texto) ==16 and len(chave) ==16):
			repete_entrada = False
		else:
			print "escreva as mensagens com 16 bytes, por favor"

	mensagem_cifrada = aesCipher(texto,chave)
	print "mensagem cifrada:"
	print mensagem_cifrada
	mensagem_decifrada = aesDecipher(mensagem_cifrada,chave)
	print "mensagem decifrada:"
	print mensagem_decifrada
	

if __name__ == "__main__":
	main()