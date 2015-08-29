'''
Escreva um programa que implemente o algoritmo RSA e que seja capaz de cifrar e decifrar um texto de mensagem que aceite todos os caracteres da tabela ASCII estendida (de 0 a 255). 
O programa terá como entradas os valores dos primos p e q, e o valor da chave pública e.
O programa deverá calcular o valor de n = p x q, e o valor de phi(n). Em seguida o programa deverá checar a validade da chave pública provida e (ela deve ser prima relativamente ao valor de phi(n), isto é mdc(e, phi(n)) = 1). 
Caso a chave pública e não seja válida, o programa deve imprimir uma mensagem de erro e solicitar outra chave pública, e continuar fazendo assim até que uma chave pública válida seja fornecida. 
Quando a chave pública e provida for válida, o programa deve calcular a chave privada d. Em seguida o programa deverá solicitar ao usuário se a ação desejada é cifração ou decifração. 
Finalmente o programa irá solicitar ao usuário o path do arquivo onde se encontra o texto a ser cifrado ou decifrado e prosseguir com a cifração (usando o valor de e) ou a decifração (usando o valor de d) do texto. 
O texto resultante da cifração ou decifração deverá ser armazenado em um outro arquivo.
'''
import sys

INVALIDO = '-1'
CIFRACAO = '0'
DECIFRACAO = '1'

def phi(primo1,primo2):
	return (primo1-1)*(primo2-1)

def mdc(val1, val2):
	dividendo = val1
	divisor = val2
	while(divisor != 0):
		resto = dividendo % divisor;
		dividendo = divisor;
		divisor = resto;
	return dividendo;

def euclidesExtendido(divisor, dividendo, sinal):
    r = dividendo % divisor
    if (r == 1):
		if(sinal<0):
			return (sinal+dividendo)/ divisor
		else:
			return (sinal / divisor) % (dividendo / divisor)
    return ((euclidesExtendido(r, divisor, -sinal) * dividendo + sinal) / (divisor%dividendo))


p = int(raw_input("digite p: "))
q = int(raw_input("digite q: "))
chave_publica = int(raw_input("digite a chave publica: "))

n = p*q
phi_n = phi(p,q)

while( mdc(chave_publica, phi_n) != 1):
	chave_publica = int(raw_input("chave publica invalida! digite outra: "))

chave_privada = euclidesExtendido(chave_publica,phi_n,1)

tipo_operacao = INVALIDO
while( tipo_operacao != CIFRACAO and tipo_operacao != DECIFRACAO):
	tipo_operacao = raw_input("digite "+CIFRACAO+" para cifrar ou "+DECIFRACAO+" para decifrar: ")

caminho_arq_original = raw_input("digite o caminho do arquivo a ser lido: ")
arquivo = open(caminho_arq_original, 'r')
texto_original = arquivo.read()

texto_alterado = ""
if(tipo_operacao == CIFRACAO):
	for letra in texto_original:
		texto_alterado +=  str((ord(letra)**chave_publica) % n)+" "
else:
	for letra in texto_original.split():
		texto_alterado +=  chr((int(letra)**chave_privada) % n)
arquivo.close()

caminho_arq_final = raw_input("digite o caminho do arquivo a ser escrito: ")
arquivo = open(caminho_arq_final, 'w')
arquivo.write(texto_alterado)
arquivo.close()
