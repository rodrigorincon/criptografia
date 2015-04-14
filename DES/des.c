#include <stdio.h>
#include <stdlib.h>

#define SIZE_TEXTO 8 //tamanho do texto a ser encriptado, em bytes
#define SIZE_CHAVE_INICIAL 8 //tamanho da chave inicial, em bytes
#define SIZE_CHAVE_REAL 7 //tamanho da chave realmente utilizada, em bytes
#define NUM_ROUNDS 16


void permutacaoInicial(unsigned char *texto_inicial){
	unsigned char mask[] = {0x40, 0x10, 0x04, 0x01, 0x80, 0x20, 0x08, 0x02};
	unsigned char texto_permutado[SIZE_TEXTO];
	//implementa a tabela de permutação inicial (IP table)
	int i;
	for (i = 0; i < 8; ++i){
		unsigned char bit1 = texto_inicial[7]&mask[i];
		unsigned char bit2 = texto_inicial[6]&mask[i];
		unsigned char bit3 = texto_inicial[5]&mask[i];
		unsigned char bit4 = texto_inicial[4]&mask[i];
		unsigned char bit5 = texto_inicial[3]&mask[i];
		unsigned char bit6 = texto_inicial[2]&mask[i];
		unsigned char bit7 = texto_inicial[1]&mask[i];
		unsigned char bit8 = texto_inicial[0]&mask[i];
		switch(i){
			case 0:
				texto_permutado[i] = bit1<<1 | bit2 | bit3>>1 | bit4>>2 | bit5>>3 | bit6>>4 | bit7>>5 | bit8>>6;
				break;
			case 1:
				texto_permutado[i] = bit1<<3 | bit2<<2 | bit3<<1 | bit4 | bit5>>1 | bit6>>2 | bit7>>3 | bit8>>4;
				break;
			case 2:
				texto_permutado[i] = bit1<<5 | bit2<<4 | bit3<<3 | bit4<<2 | bit5<<1 | bit6 | bit7>>1 | bit8>>2;
				break;
			case 3:
				texto_permutado[i] = bit1<<7 | bit2<<6 | bit3<<5 | bit4<<4 | bit5<<3 | bit6<<2 | bit7<<1 | bit8;
				break;
			case 4:
				texto_permutado[i] = bit1 | bit2>>1 | bit3>>2 | bit4>>3 | bit5>>4 | bit6>>5 | bit7>>6 | bit8>>7;
				break;
			case 5:
				texto_permutado[i] = bit1<<2 | bit2<<1 | bit3 | bit4>>1 | bit5>>2 | bit6>>3 | bit7>>4 | bit8>>5;
				break;
			case 6:
				texto_permutado[i] = bit1<<4 | bit2<<3 | bit3<<2 | bit4<<1 | bit5 | bit6>>1 | bit7>>2 | bit8>>3;
				break;
			case 7:
				texto_permutado[i] = bit1<<6 | bit2<<5 | bit3<<4 | bit4<<3 | bit5<<2 | bit6<<1 | bit7 | bit8>>1;
				break;
		} 
	}

	for (i = 0; i < SIZE_TEXTO; ++i)
		texto_inicial[i] = texto_permutado[i];
}

void permutacaoInversa(unsigned char *texto){
	unsigned char mask[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	unsigned char texto_permutado[SIZE_TEXTO];
	//implementa a tabela inversa de permutação inicial (IP^-1 table)
	int i;
	for (i = 0; i < 8; ++i){
		unsigned char bit1 = texto[4]&mask[i];
		unsigned char bit2 = texto[0]&mask[i];
		unsigned char bit3 = texto[5]&mask[i];
		unsigned char bit4 = texto[1]&mask[i];
		unsigned char bit5 = texto[6]&mask[i];
		unsigned char bit6 = texto[2]&mask[i];
		unsigned char bit7 = texto[7]&mask[i];
		unsigned char bit8 = texto[3]&mask[i];
		switch(i){
			case 0:
				texto_permutado[i] = bit1<<7 | bit2<<6 | bit3<<5 | bit4<<4 | bit5<<3 | bit6<<2 | bit7<<1 | bit8;
				break;
			case 1:
				texto_permutado[i] = bit1<<6 | bit2<<5 | bit3<<4 | bit4<<3 | bit5<<2 | bit6<<1 | bit7 | bit8>>1;
				break;
			case 2:
				texto_permutado[i] = bit1<<5 | bit2<<4 | bit3<<3 | bit4<<2 | bit5<<1 | bit6 | bit7>>1 | bit8>>2;
				break;
			case 3:
				texto_permutado[i] = bit1<<4 | bit2<<3 | bit3<<2 | bit4<<1 | bit5 | bit6>>1 | bit7>>2 | bit8>>3;
				break;
			case 4:
				texto_permutado[i] = bit1<<3 | bit2<<2 | bit3<<1 | bit4 | bit5>>1 | bit6>>2 | bit7>>3 | bit8>>4;
				break;
			case 5:
				texto_permutado[i] = bit1<<2 | bit2<<1 | bit3 | bit4>>1 | bit5>>2 | bit6>>3 | bit7>>4 | bit8>>5;
				break;
			case 6:
				texto_permutado[i] = bit1<<1 | bit2 | bit3>>1 | bit4>>2 | bit5>>3 | bit6>>4 | bit7>>5 | bit8>>6;
				break;
			case 7:
				texto_permutado[i] = bit1 | bit2>>1 | bit3>>2 | bit4>>3 | bit5>>4 | bit6>>5 | bit7>>6 | bit8>>7;
				break;
		} 
	}

	for (i = 0; i < SIZE_TEXTO; ++i)
		texto[i] = texto_permutado[i];	
}

unsigned char* permutacaoChave1(unsigned char *chave_inicial){
	unsigned char *chave_56bits = malloc(SIZE_CHAVE_REAL*sizeof(unsigned char));
	unsigned char mask[] = {0x80, 0x40, 0x20, 0x10, 0x02, 0x04, 0x08, 0x10};
	//preenche os 3 primeiros bytes
	int i;
	for (i = 0; i < SIZE_CHAVE_REAL/2; ++i)	{
		unsigned char bit1 = chave_inicial[7]&mask[i];
		unsigned char bit2 = chave_inicial[6]&mask[i];
		unsigned char bit3 = chave_inicial[5]&mask[i];
		unsigned char bit4 = chave_inicial[4]&mask[i];
		unsigned char bit5 = chave_inicial[3]&mask[i];
		unsigned char bit6 = chave_inicial[2]&mask[i];
		unsigned char bit7 = chave_inicial[1]&mask[i];
		unsigned char bit8 = chave_inicial[0]&mask[i];
		switch(i){
			case 0:
				chave_56bits[i] = bit1 | bit2>>1 | bit3>>2 | bit4>>3 | bit5>>4 | bit6>>5 | bit7>>6 | bit8>>7;
				break;
			case 1:
				chave_56bits[i] = bit1<<1 | bit2 | bit3>>1 | bit4>>2 | bit5>>3 | bit6>>4 | bit7>>5 | bit8>>6;
				break;
			case 2:
				chave_56bits[i] = bit1<<2 | bit2<<1 | bit3 | bit4>>1 | bit5>>2 | bit6>>3 | bit7>>4 | bit8>>5;
				break;
		}
	}
	//preenche o 4º byte
	unsigned char bit1 = (chave_inicial[7]&mask[3])<<3;
	unsigned char bit2 = (chave_inicial[6]&mask[3])<<2;
	unsigned char bit3 = (chave_inicial[5]&mask[3])<<1;
	unsigned char bit4 = (chave_inicial[4]&mask[3]);
	unsigned char bit5 = (chave_inicial[7]&mask[4])<<2;
	unsigned char bit6 = (chave_inicial[6]&mask[4])<<1;
	unsigned char bit7 = (chave_inicial[5]&mask[4]);
	unsigned char bit8 = (chave_inicial[4]&mask[4])>>1;
	chave_56bits[3] = bit1 | bit2 | bit3 | bit4 | bit5 | bit6 | bit7 | bit8;
	//preenche do 5º e 6º byte
	for (i = 4; i < SIZE_CHAVE_REAL-1; ++i)	{
		unsigned char bit1 = chave_inicial[3]&mask[i];
		unsigned char bit2 = chave_inicial[2]&mask[i];
		unsigned char bit3 = chave_inicial[1]&mask[i];
		unsigned char bit4 = chave_inicial[0]&mask[i];
		unsigned char bit5 = chave_inicial[7]&mask[i+1];
		unsigned char bit6 = chave_inicial[6]&mask[i+1];
		unsigned char bit7 = chave_inicial[5]&mask[i+1];
		unsigned char bit8 = chave_inicial[4]&mask[i+1];
		switch(i){
			case 4:
				chave_56bits[i] = bit1<<6 | bit2<<5 | bit3<<4 | bit4<<3 | bit5<<1 | bit6 | bit7>>1 | bit8>>2;
				break;
			case 5:
				chave_56bits[i] = bit1<<5 | bit2<<4 | bit3<<3 | bit4<<2 | bit5 | bit6>>1 | bit7>>2 | bit8>>3;
				break;
		}
	}
	//preenche o 7º byte
	bit1 = (chave_inicial[3]&mask[6])<<4;
	bit2 = (chave_inicial[2]&mask[6])<<3;
	bit3 = (chave_inicial[1]&mask[6])<<2;
	bit4 = (chave_inicial[0]&mask[6])<<1;
	bit5 = (chave_inicial[3]&mask[7])>>1;
	bit6 = (chave_inicial[2]&mask[7])>>2;
	bit7 = (chave_inicial[1]&mask[7])>>3;
	bit8 = (chave_inicial[0]&mask[7])>>4;
	chave_56bits[6] = bit1 | bit2 | bit3 | bit4 | bit5 | bit6 | bit7 | bit8;
	return chave_56bits;
}

unsigned char* permutacaoChave2(unsigned char *chave){
	unsigned char *chave_48bits = malloc( (SIZE_CHAVE_REAL-1)*sizeof(unsigned char));

	unsigned char bit1 = chave[1]&0x04;
	unsigned char bit2 = chave[2]&0x80;
	unsigned char bit3 = chave[1]&0x20;
	unsigned char bit4 = chave[2]&0x01;
	unsigned char bit5 = chave[0]&0x80;
	unsigned char bit6 = chave[0]&0x08;
	unsigned char bit7 = chave[0]&0x20;
	unsigned char bit8 = chave[3]&0x10;
	chave_48bits[0] = bit1<<5 | bit2>>1 | bit3 | bit4<<4 | bit5>>4 | bit6>>1 | bit7>>4 | bit8>>4;

	bit1 = chave[1]&0x02;
	bit2 = chave[0]&0x04;
	bit3 = chave[2]&0x08;
	bit4 = chave[1]&0x40;
	bit5 = chave[2]&0x02;
	bit6 = chave[2]&0x20;
	bit7 = chave[1]&0x10;
	bit8 = chave[0]&0x10;
	chave_48bits[1] = bit1<<6 | bit2<<4 | bit3<<2 | bit4>>2 | bit5<<2 | bit6>>3 | bit7>>3 | bit8>>4;

	bit1 = chave[3]&0x40;
	bit2 = chave[0]&0x01;
	bit3 = chave[1]&0x01;
	bit4 = chave[0]&0x02;
	bit5 = chave[3]&0x20;
	bit6 = chave[2]&0x10;
	bit7 = chave[1]&0x08;
	bit8 = chave[0]&0x40;
	chave_48bits[2] = bit1<<1 | bit2<<6 | bit3<<5 | bit4<<3 | bit5>>2 | bit6>>2 | bit7>>2 | bit8>>6;

	bit1 = chave[5]&0x80;
	bit2 = chave[6]&0x10;
	bit3 = chave[3]&0x02;
	bit4 = chave[4]&0x08;
	bit5 = chave[5]&0x02;
	bit6 = chave[6]&0x02;
	bit7 = chave[3]&0x04;
	bit8 = chave[4]&0x01;
	chave_48bits[3] = bit1 | bit2<<2 | bit3<<4 | bit4<<1 | bit5<<2 | bit6<<1 | bit7>>1 | bit8;

	bit1 = chave[6]&0x20;
	bit2 = chave[5]&0x08;
	bit3 = chave[4]&0x80;
	bit4 = chave[5]&0x01;
	bit5 = chave[5]&0x10;
	bit6 = chave[6]&0x80;
	bit7 = chave[4]&0x02;
	bit8 = chave[6]&0x01;
	chave_48bits[4] = bit1<<2 | bit2<<3 | bit3>>2 | bit4<<4 | bit5>>1 | bit6>>5 | bit7 | bit8;

	bit1 = chave[4]&0x40;
	bit2 = chave[6]&0x08;
	bit3 = chave[5]&0x04;
	bit4 = chave[5]&0x40;
	bit5 = chave[6]&0x40;
	bit6 = chave[4]&0x10;
	bit7 = chave[3]&0x08;
	bit8 = chave[3]&0x01;
	chave_48bits[5] = bit1<<1 | bit2<<3 | bit3<<3 | bit4>>2 | bit5>>3 | bit6>>2 | bit7>>2 | bit8;
	return chave_48bits;
}

void circularShift(unsigned char *chave, int numero_round){
	int num_byte;
	unsigned char maior_bit_left, maior_bit_right;
	switch(numero_round){
	case 0:
	case 1:
	case 8:
	case 15:
		maior_bit_left = (chave[0]&0x80)>>3;
		maior_bit_right = (chave[3]&0x08)>>3;
		for (num_byte = 0; num_byte < SIZE_CHAVE_REAL; ++num_byte){
			if(num_byte == SIZE_CHAVE_REAL/2) //4º byte (fim da primeira metade e inicio da segunda), move apenas a primeira metade do byte, coloca o 1º bit do 1º byte no meio, da shift nos 3 ultimos  bits descartando o 5º e completa com o 1º bit do proximo
				chave[num_byte] = (chave[num_byte]&0xF0)<<1 | maior_bit_left | (chave[num_byte]&0x07)<<1 | (chave[num_byte+1]&0x80)>>7;
			else if(num_byte == SIZE_CHAVE_REAL-1) //ultimo byte, completa com o primeiro bit da segunda metade (5º bit do 4º byte)
				chave[num_byte] = chave[num_byte]<<1 | maior_bit_right;
			else//os 3 primeiros bytes, o 5º e 6º	
				chave[num_byte] = chave[num_byte]<<1 | ( (chave[num_byte+1]&0x80)>>7 );
		}
		break;
	default:
		maior_bit_left = (chave[0]&0xC0)>>2;
		maior_bit_right = (chave[3]&0x0C)>>2;
		for (num_byte = 0; num_byte < SIZE_CHAVE_REAL; ++num_byte){
			if(num_byte == SIZE_CHAVE_REAL/2) //4º byte (fim da primeira metade e inicio da segunda), move apenas a primeira metade do byte, coloca os 1ºs bit do 1º byte no meio, da shift nos 2 ultimos bits descartando o 5º e 6º e completa com o 1º e 2º bit do proximo
				chave[num_byte] = (chave[num_byte]&0xF0)<<2 | maior_bit_left | (chave[num_byte]&0x03)<<2 | (chave[num_byte+1]&0xC0)>>6;
			else if(num_byte == SIZE_CHAVE_REAL-1) //ultimo byte, completa com o 1º e 2º bits da segunda metade (5º e 6º bits do 4º byte)
				chave[num_byte] = chave[num_byte]<<2 | maior_bit_right;
			else//os 3 primeiros bytes, o 5º e 6º
				chave[num_byte] = chave[num_byte]<<2 | ( (chave[num_byte+1]&0xC0)>>6 );
		}
	}
}

void swap32its(unsigned char *texto){
	unsigned char temp;
	int byte;
	for (byte=0; byte < SIZE_TEXTO/2; ++byte){
	 	temp = texto[byte];
	 	texto[byte] = texto[byte+SIZE_TEXTO/2];
	 	texto[byte+SIZE_TEXTO/2] = temp;
	}
}

unsigned char* expansionPermutation(unsigned char *texto){
	return NULL;
}

unsigned char* sbox(unsigned char *texto){
	return NULL;
}

void tableP(unsigned char *texto){
}

unsigned char* funcao_f(unsigned char *texto, unsigned char *chave){
	//unsigned char *texto_expandido = malloc( (SIZE_CHAVE_REAL-1)*sizeof(unsigned char) );
	unsigned char *texto_expandido = expansionPermutation(texto);
	texto_expandido = xor(texto_expandido, chave, 6);
	//unsigned char *encript = malloc( SIZE_TEXTO/2*sizeof(unsigned char) );
	unsigned char *encript = sbox(texto_expandido);
	tableP(encript);

	free(texto_expandido);
	return encript;
}

unsigned char* xor(unsigned char *dados1, unsigned char *dados2, int size_array){
	int i;
	for(i=0; i<size_array; i++)
		dados1[i] = dados1[i] ^ dados2[i];
	return dados1;
}


int main(){
	
	unsigned char texto[SIZE_TEXTO] = { 0x02, 0x46, 0x8a, 0xce, 0xec, 0xa8, 0x64, 0x20};
	unsigned char chave[SIZE_TEXTO] = { 0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59};
	
	permutacaoInicial(texto);	
	unsigned char *chave_real = permutacaoChave1(chave);//transforma a chave de 64 para 56 bits

	int numero_round;
	for (numero_round = 0; numero_round < NUM_ROUNDS; ++numero_round){
		unsigned char *left_texto = NULL, *right_texto = NULL;
		
		left_texto = &texto[0];
		right_texto = &texto[SIZE_TEXTO/2];
		
		circularShift(chave_real, numero_round);
		unsigned char *chave_round = permutacaoChave2(chave_real);		

		unsigned char *encript = funcao_f(right_texto,chave_round);
		unsigned char *novo_right_texto = xor(encript, left_texto, SIZE_TEXTO/2);
		unsigned char *novo_left_texto = right_texto;

		int byte;
		for (byte = 0; byte < SIZE_TEXTO; ++byte)
			texto[byte] = byte<SIZE_TEXTO/2 ? novo_left_texto[byte] : novo_right_texto[byte%4];
		free(chave_round);
		free(encript);
	}

	swap32its(texto);
	permutacaoInversa(texto);	

	return 0;
}