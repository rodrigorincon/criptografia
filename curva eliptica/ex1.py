'''
Escreva um programa que calcule e liste todos os pontos de uma curva elíptica do tipo Zp, y2 = x3 + ax + b (mod p), com sua respectiva ordem. 
O programa terá como entradas os valores de a, b e p. 
Além de listar os pontos da curva e sua ordem, o programa também terá como saída o número total de pontos da curva elíptica e o ponto de maior ordem.
'''
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

points = getPoints(a,b,p)
print "muero de pontos: "+str(len(points))
print points

ponto_maior_ordem = None
maior_ordem_valor = 0
for ponto in points:
	ordem = getOrderPoint(a,b,p,ponto[0],ponto[1])
	if(ordem > maior_ordem_valor):
		maior_ordem_valor = ordem
		ponto_maior_ordem = ponto

print "ponto de maior valor: "+str(ponto_maior_ordem)
