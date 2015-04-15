#include <stdio.h>
#include <stdlib.h>

#define SIZE_TEXTO 8 //tamanho do texto a ser encriptado, em bytes
#define SIZE_CHAVE_INICIAL 8 //tamanho da chave inicial, em bytes
#define SIZE_CHAVE_REAL 7 //tamanho da chave realmente utilizada, em bytes
#define NUM_ROUNDS 16

//realiza a permutação inicial no texto, embaralhando os bits (IP table)
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

//realiza a permutação final no texto, voltando os bits para a posição inicial (IP^-1 table)
void permutacaoInversa(unsigned char *texto){
	unsigned char mask[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	unsigned char texto_permutado[SIZE_TEXTO];

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

//realiza a permutação inicial  na chave e o descarte do ultimo bit de cada byte (PC-1 table)
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

//realiza a permutação na chave feita em todo loop e o descarte de mais 8 bits (PC-2 table)
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

//realiza o shift circular na chave, considerando que cada metade da chave é independente
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

//faz a troca final das duas metades do texto (esquerda e direita)
void swap32its(unsigned char *texto){
	unsigned char temp;
	int byte;
	for (byte=0; byte < SIZE_TEXTO/2; ++byte){
	 	temp = texto[byte];
	 	texto[byte] = texto[byte+SIZE_TEXTO/2];
	 	texto[byte+SIZE_TEXTO/2] = temp;
	}
}

//realiza a permutação do texto em claro dentro da função F (E table)
unsigned char* expansionPermutation(unsigned char *texto){
	unsigned char *texto_expandido = calloc( SIZE_CHAVE_REAL-1,sizeof(unsigned char) );
	
	unsigned char bit1 = texto[3]&0x01;
	unsigned char bit2 = texto[0]&0x80;
	unsigned char bit3 = texto[0]&0x40;
	unsigned char bit4 = texto[0]&0x20;
	unsigned char bit5 = texto[0]&0x10;
	unsigned char bit6 = texto[0]&0x08;
	unsigned char bit7 = texto[0]&0x10;
	unsigned char bit8 = texto[0]&0x08;
	texto_expandido[0] = bit1<<7 | bit2>>1 | bit3>>1 | bit4>>1 | bit5>>1 | bit6>>1 | bit7>>3 | bit8>>3;

	bit1 = texto[0]&0x04;
	bit2 = texto[0]&0x02;
	bit3 = texto[0]&0x01;
	bit4 = texto[1]&0x80;
	bit5 = texto[0]&0x01;
	bit6 = texto[1]&0x80;
	bit7 = texto[1]&0x40;
	bit8 = texto[1]&0x20;
	texto_expandido[1] = bit1<<5 | bit2<<5 | bit3<<5 | bit4>>3 | bit5<<3 | bit6>>5 | bit7>>5 | bit8>>5;

	bit1 = texto[1]&0x10;
	bit2 = texto[1]&0x08;
	bit3 = texto[1]&0x10;
	bit4 = texto[1]&0x08;
	bit5 = texto[1]&0x04;
	bit6 = texto[1]&0x02;
	bit7 = texto[1]&0x01;
	bit8 = texto[2]&0x80;
	texto_expandido[2] = bit1<<3 | bit2<<3 | bit3<<1 | bit4<<1 | bit5<<1 | bit6<<1 | bit7<<1 | bit8>>7;

	bit1 = texto[1]&0x01;
	bit2 = texto[2]&0x80;
	bit3 = texto[2]&0x40;
	bit4 = texto[2]&0x20;
	bit5 = texto[2]&0x10;
	bit6 = texto[2]&0x08;
	bit7 = texto[2]&0x10;
	bit8 = texto[2]&0x08;
	texto_expandido[3] = bit1<<7 | bit2>>1 | bit3>>1 | bit4>>1 | bit5>>1 | bit6>>1 | bit7>>3 | bit8>>3;

	bit1 = texto[2]&0x04;
	bit2 = texto[2]&0x02;
	bit3 = texto[2]&0x01;
	bit4 = texto[3]&0x80;
	bit5 = texto[2]&0x01;
	bit6 = texto[3]&0x80;
	bit7 = texto[3]&0x40;
	bit8 = texto[3]&0x20;
	texto_expandido[4] = bit1<<5 | bit2<<5 | bit3<<5 | bit4>>3 | bit5<<3 | bit6>>5 | bit7>>5 | bit8>>5;

	bit1 = texto[3]&0x10;
	bit2 = texto[3]&0x08;
	bit3 = texto[3]&0x10;
	bit4 = texto[3]&0x08;
	bit5 = texto[3]&0x04;
	bit6 = texto[3]&0x02;
	bit7 = texto[3]&0x01;
	bit8 = texto[0]&0x80;
	texto_expandido[5] = bit1<<3 | bit2<<3 | bit3<<1 | bit4<<1 | bit5<<1 | bit6<<1 | bit7<<1 | bit8>>7;	

	return texto_expandido;
}

//conhece as 8 tabelas do sbox e, de acordo com o parametro box recebido, executa a tabela correta com a entrada
unsigned char sboxPermut(unsigned char input, int box){
	unsigned char box1[4][16] = { {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13} };
	unsigned char box2[4][16] = { {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9} };
	unsigned char box3[4][16] = { {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12} };
	unsigned char box4[4][16] = { {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} };
	unsigned char box5[4][16] = { {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3} };
	unsigned char box6[4][16] = { {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13} };
	unsigned char box7[4][16] = { {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} };
	unsigned char box8[4][16] = { {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11} };

	int linha = (input&0x80)>>6 | (input&0x04)>>2;
	int coluna = (input&0x78)>>3;
	unsigned char nibble;
	switch(box){
	case 0:
		nibble = box1[linha][coluna];
		break;
	case 1:
		nibble = box2[linha][coluna];
		break;
	case 2:
		nibble = box3[linha][coluna];
		break;
	case 3:
		nibble = box4[linha][coluna];
		break;
	case 4:
		nibble = box5[linha][coluna];
		break;
	case 5:
		nibble = box6[linha][coluna];
		break;
	case 6:
		nibble = box7[linha][coluna];
		break;
	case 7:
		nibble = box8[linha][coluna];
		break;
	}
	return nibble;
}

//divide os 48 bits recebidos em 8 grupos de 6 bits (preenche os 2 finais com 0) e os envia para a função que executará a tabela correta do sbox para cada grupo, recebendo os 4 bits de resposta e concatenando-os
unsigned char* sbox(unsigned char *texto){
	unsigned char *novo_texto = calloc( SIZE_TEXTO/2,sizeof(unsigned char) );
	
	unsigned char sbox_input[8];
	sbox_input[0] = texto[0]&0xFC;
	sbox_input[1] = (texto[0]&0x03)<<6 | (texto[1]&0xF0)>>2;
	sbox_input[2] = (texto[1]&0x0F)<<4 | (texto[2]&0xc0)>>4;
	sbox_input[3] = (texto[2]&0x3F)<<2;
	sbox_input[4] = texto[3]&0xFC;
	sbox_input[5] = (texto[3]&0x03)<<6 | (texto[4]&0xF0)>>2;
	sbox_input[6] = (texto[4]&0x0F)<<4 | (texto[5]&0xc0)>>4;
	sbox_input[7] = (texto[5]&0x3F)<<2;

	int nibble;
	for (nibble = 0; nibble < 8; ++nibble)
		novo_texto[nibble/2] |= nibble%2 ? sboxPermut(sbox_input[nibble],nibble) : sboxPermut(sbox_input[nibble],nibble)<<4;	
	
	return novo_texto;
}

//realiza a última permutação do texto cifrado dentro da função F (P table)
void tableP(unsigned char *texto){
	unsigned char temp[4];
	int i;
	for(i=0; i<4; i++)
		temp[i] = texto[i];

	unsigned char bit1 = temp[1]&0x01;
	unsigned char bit2 = temp[0]&0x02;
	unsigned char bit3 = temp[2]&0x10;
	unsigned char bit4 = temp[2]&0x08;
	unsigned char bit5 = temp[3]&0x08;
	unsigned char bit6 = temp[1]&0x10;
	unsigned char bit7 = temp[3]&0x10;
	unsigned char bit8 = temp[2]&0x80;
	texto[0] = bit1<<7 | bit2<<5 | bit3<<1 | bit4<<1 | bit5 | bit6>>2 | bit7>>3 | bit8>>7;

	bit1 = temp[0]&0x80;
	bit2 = temp[1]&0x02;
	bit3 = temp[2]&0x02;
	bit4 = temp[3]&0x40;
	bit5 = temp[0]&0x08;
	bit6 = temp[2]&0x40;
	bit7 = temp[3]&0x02;
	bit8 = temp[1]&0x40;
	texto[1] = bit1 | bit2<<5 | bit3<<4 | bit4>>2 | bit5 | bit6>>4 | bit7 | bit8>>6;

	bit1 = temp[0]&0x40;
	bit2 = temp[0]&0x01;
	bit3 = temp[2]&0x01;
	bit4 = temp[1]&0x04;
	bit5 = temp[3]&0x01;
	bit6 = temp[3]&0x20;
	bit7 = temp[0]&0x20;
	bit8 = temp[1]&0x80;
	texto[2] = bit1<<1 | bit2<<6 | bit3<<5 | bit4<<2 | bit5<<3 | bit6>>3 | bit7>>4 | bit8>>7;

	bit1 = temp[2]&0x20;
	bit2 = temp[1]&0x08;
	bit3 = temp[3]&0x04;
	bit4 = temp[0]&0x04;
	bit5 = temp[2]&0x04;
	bit6 = temp[1]&0x20;
	bit7 = temp[0]&0x10;
	bit8 = temp[3]&0x80;
	texto[3] = bit1<<2 | bit2<<3 | bit3<<3 | bit4<<2 | bit5<<1 | bit6>>3 | bit7>>3 | bit8>>7;
}

unsigned char* xor(unsigned char *dados1, unsigned char *dados2, int size_array){
	int i;
	for(i=0; i<size_array; i++)
		dados1[i] = dados1[i] ^ dados2[i];
	return dados1;
}

unsigned char* funcao_f(unsigned char *texto, unsigned char *chave){
	unsigned char *texto_expandido = expansionPermutation(texto);
	texto_expandido = xor(texto_expandido, chave, 6);
	unsigned char *encript = sbox(texto_expandido);
	tableP(encript);
	free(texto_expandido);
	return encript;
}

int main(){
	
	unsigned char texto[SIZE_TEXTO] = { 0x02, 0x46, 0x8a, 0xce, 0xec, 0xa8, 0x64, 0x20};
	unsigned char chave[SIZE_TEXTO] = { 0x0f, 0x15, 0x71, 0xc9, 0x47, 0xd9, 0xe8, 0x59};
	
	permutacaoInicial(texto);	
	unsigned char *chave_real = permutacaoChave1(chave);//transforma a chave de 64 para 56 bits
	
	int numero_round;
	int i;
	for (numero_round = 0; numero_round < NUM_ROUNDS; ++numero_round){
		unsigned char *left_texto = NULL, *right_texto = NULL;
		
		left_texto = &texto[0];
		right_texto = &texto[SIZE_TEXTO/2];
		
		circularShift(chave_real, numero_round);
		unsigned char *chave_round = permutacaoChave2(chave_real);		

		unsigned char *encript = funcao_f(right_texto,chave_round);
		unsigned char *novo_right_texto = xor(encript, left_texto, SIZE_TEXTO/2);
		unsigned char *novo_left_texto = right_texto;

		//insere as duas metades do texto cifrado (left e right) de volta na variavel texto
		int byte;
		for (byte = 0; byte < SIZE_TEXTO; ++byte)
			texto[byte] = byte<SIZE_TEXTO/2 ? novo_left_texto[byte] : novo_right_texto[byte%4];
		free(chave_round);
		free(encript);
	}

	swap32its(texto);
	permutacaoInversa(texto);	

	for (i = 0; i < SIZE_TEXTO; ++i)
		printf("%x ",texto[i] );
	printf("\n");

	return 0;
}