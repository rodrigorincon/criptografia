#include<stdio.h>
#define SIZE_TEXTO 8
#define NUM_ROUNDS 16


void troca(unsigned char *texto, unsigned char *novo_left, unsigned char *novo_right){

	unsigned char *txt_cifr_left = &texto[0];
	unsigned char *txt_cifr_right = &texto[SIZE_TEXTO/2];
	unsigned char *temp;

	temp = txt_cifr_left;
	txt_cifr_left = txt_cifr_right;
	txt_cifr_right = temp;

	novo_right = txt_cifr_right;
	novo_left = txt_cifr_left;

	int k;
	for (k = 0; k < SIZE_TEXTO/2; ++k)
		printf("%x ", novo_left[k]);
	for (k = 0; k < SIZE_TEXTO/2; ++k)
		printf("%x ", novo_right[k]);
	printf("\n");
}

unsigned char* funcao_f(unsigned char *texto, unsigned char *chave){
	unsigned char *encript = malloc( SIZE_TEXTO/2*sizeof(unsigned char) );

	return encript;
}

unsigned char* xor(unsigned char *dados1, unsigned char *dados2){
	int i;
	for(i=0; i<SIZE_TEXTO/2; i++)
		dados1[i] = dados1[i] ^ dados2[i];
	return dados1;
}


int main(){
	
	unsigned char texto[SIZE_TEXTO] = { 0x5a, 0x00, 0x5a, 0x00, 0x3c, 0xf0, 0x3c, 0x0f};
	unsigned char chave[SIZE_TEXTO] = { 0x1e, 0x03, 0x0f, 0x03, 0x08, 0x0d, 0x29, 0x30};
	
	unsigned char *left = NULL, *right = NULL;

	int i;
	for (i = 0; i < NUM_ROUNDS; ++i){
		
		left = &texto[0];
		right = &texto[SIZE_TEXTO/2];
	
		unsigned char *encript = funcao_f(right,chave);
		unsigned char *novo_right = xor(encript,left);
		unsigned char *novo_left = right;

		int j;
		for (j = 0; j < SIZE_TEXTO; ++j)
			texto[j] = j<SIZE_TEXTO/2 ? novo_left[j] : novo_right;
		free(encript);
	}

	unsigned char temp;
	for (i=0; i < SIZE_TEXTO/2; ++i){
	 	temp = texto[i];
	 	texto[i] = texto[i+SIZE_TEXTO/2];
	 	texto[i+SIZE_TEXTO/2] = temp;
	}
	

	return 0;
}