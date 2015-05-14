#include<stdio.h>

int euclides(int dividendo, int divisor){
	int resto;
	do{
		resto = dividendo % divisor;
		dividendo = divisor;
		divisor = resto;
	}while(resto != 0);
	return dividendo;
}

int main(){
	int a, b;
	printf("digite o maior numero ");
	scanf("%d",&a);
	printf("digite o menor numero ");
	scanf("%d",&b);

	int mdc = euclides(a,b);
	printf("o MDC de %d e %d eh %d \n",a,b,mdc);

	return 0;
}