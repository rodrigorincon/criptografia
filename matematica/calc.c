#include<stdio.h>

int main(){
	int tempA, tempB;
	unsigned char a, b;
	printf("digite o primeiro carai ");
	scanf("%d",&tempA);
	printf("digite o segundo carai ");
	scanf("%d",&tempB);

	a = (unsigned char) tempA;
	b = (unsigned char) tempB;
	
	unsigned char soma = a ^ b;
	printf("%d + %d = %d \n",a,b,soma);

	unsigned  char inverso_b = 256-b;
	unsigned char sub = a ^ inverso_b;
	printf("%d - %d = %d \n",a,b,sub);

	return 0;
}