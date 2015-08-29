'''
Escreva um programa que implemente um algoritmo de criptografia de curva elíptica (cifração e decifração) do tipo Zp, y2 = x3 + ax + b (mod p). 
Este programa deverá ter como entradas:
a. Os valores de a, b e p;
b. Um ponto base G (Gx , Gy) para ser utilizado na cifração e decifração; e
c. Um ponto da curva a ser cifrado P (Px, Py).
O programa deverá cifrar o ponto dado P gerando os dois pontos cifrados correspondentes C1 e C2. 
Em seguida, o programa deverá decifrar os pontos C1 e C2, usando o algoritmo de decifração da mesma curva elíptica, obtendo o ponto P', que deverá ser igual a P. 
Os pontos C1 e C2, e depois P', serão mostrados na tela durante o processo de decifração.
'''
from random import randint

INFINITY_POINT_X = -1
INFINITY_POINT_Y = -1

def isInfinityPoint(x,y):
	return x==INFINITY_POINT_X and y==INFINITY_POINT_Y

def getPoints(a,b,p):
	points = []
	for x in range(p):
		for y in range(p):
			if( (y**2)%p == (x**3 + a*x + b)%p ):
				points += [(x,y)]
	return points

def modularDivision(dividendo, divisor, modulo):
	if(dividendo%divisor == 0):
		return (dividendo/divisor)%modulo
	value = 0
	while( (value*divisor)%modulo != dividendo%modulo ):
		value+=1
	return value		

def sumPoints(a,b,p,point_x1,point_y1,point_x2,point_y2):
	x = 0
	y = 0
	if(point_x1==INFINITY_POINT_X and point_y1==INFINITY_POINT_Y):
		x = point_x2
		y = point_y2
	elif(point_x2==INFINITY_POINT_X and point_y2==INFINITY_POINT_Y):
		x = point_x1
		y = point_y1
	elif(point_x1==point_x2 and point_y1!=point_y2): #os pontos sao inversos um do outro e sua soma sera o ponto no infinito
		x = INFINITY_POINT_X
		y = INFINITY_POINT_Y
	else:
		delta = modularDivision(3*point_x1**2 + a,2*point_y1,p) if point_x1==point_x2 and point_y1==point_y2 else modularDivision(point_y2-point_y1,point_x2-point_x1,p)
		x = (delta**2 - point_x1 - point_x2)%p
		y = (delta*(point_x1-x)-point_y1)%p
	return (x,y)

def getOrderPoint(a,b,p,point_x,point_y):
	order = 1
	point = (point_x,point_y)
	while( isInfinityPoint(point[0],point[1])==False ):
		point = sumPoints(a,b,p,point[0],point[1],point_x,point_y)
		order+=1
	return order

def multPoint(a,b,p,point_x,point_y,multiplicator):
	point = (INFINITY_POINT_X,INFINITY_POINT_Y)
	for i in range(multiplicator):
		point = sumPoints(a,b,p,point[0],point[1],point_x,point_y)
	return point

a = int(raw_input('entre com o valor de a: '))
b = int(raw_input('entre com o valor de b: '))
p = int(raw_input('entre com o valor de p (modulo): '))
g_point_x = int(raw_input('entre com a coordenada x do ponto base G: '))
g_point_y = int(raw_input('entre com a coordenada y do ponto base G: '))
p_point_x = int(raw_input('entre com a coordenada x do ponto a ser cifrado: '))
p_point_y = int(raw_input('entre com a coordenada y do ponto a ser cifrado: '))

order_g = getOrderPoint(a,b,p,g_point_x,g_point_y)

private_key_A = randint(1,order_g)
public_key_A = multPoint(a,b,p,g_point_x,g_point_y,private_key_A)

private_key_B = randint(1,order_g)
public_key_B = multPoint(a,b,p,g_point_x,g_point_y,private_key_B)

#k_A = multPoint(a,b,p,public_key_B[0],public_key_B[1],private_key_A) # compartilhamento de chave
#k_B = multPoint(a,b,p,public_key_A[0],public_key_A[1],private_key_B) # compartilhamento de chave
k = randint(1,order_g)

temp = multPoint(a,b,p,public_key_B[0],public_key_B[1],k)
cypher_msg = [multPoint(a,b,p,g_point_x,g_point_y,k), sumPoints(a,b,p,p_point_x,p_point_y,temp[0],temp[1]) ]
print "mensagen cifrada: "
print cypher_msg

inverse_cypher_point = ( cypher_msg[0][0], (-cypher_msg[0][1])%p )
temp = multPoint(a,b,p,inverse_cypher_point[0],inverse_cypher_point[1],private_key_B)
decypher_point = sumPoints(a,b,p,cypher_msg[1][0],cypher_msg[1][1],temp[0],temp[1])
print "mensagem decifrada: "
print decypher_point