#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Attaque 5   ///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

unsigned char Sbox[256] = 
 {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
 };
 
unsigned char invSBOX[256] =
{
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
	0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
	0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
	0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
	0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
	0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
	0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
	0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
	0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
	0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
	0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};


unsigned char m9[256] ={0x00,0x09,0x12,0x1b,0x24,0x2d,0x36,0x3f,0x48,0x41,0x5a,0x53,0x6c,0x65,0x7e,0x77,
						0x90,0x99,0x82,0x8b,0xb4,0xbd,0xa6,0xaf,0xd8,0xd1,0xca,0xc3,0xfc,0xf5,0xee,0xe7,
						0x3b,0x32,0x29,0x20,0x1f,0x16,0x0d,0x04,0x73,0x7a,0x61,0x68,0x57,0x5e,0x45,0x4c,
						0xab,0xa2,0xb9,0xb0,0x8f,0x86,0x9d,0x94,0xe3,0xea,0xf1,0xf8,0xc7,0xce,0xd5,0xdc,
						0x76,0x7f,0x64,0x6d,0x52,0x5b,0x40,0x49,0x3e,0x37,0x2c,0x25,0x1a,0x13,0x08,0x01,
						0xe6,0xef,0xf4,0xfd,0xc2,0xcb,0xd0,0xd9,0xae,0xa7,0xbc,0xb5,0x8a,0x83,0x98,0x91,
						0x4d,0x44,0x5f,0x56,0x69,0x60,0x7b,0x72,0x05,0x0c,0x17,0x1e,0x21,0x28,0x33,0x3a,
						0xdd,0xd4,0xcf,0xc6,0xf9,0xf0,0xeb,0xe2,0x95,0x9c,0x87,0x8e,0xb1,0xb8,0xa3,0xaa,	
						0xec,0xe5,0xfe,0xf7,0xc8,0xc1,0xda,0xd3,0xa4,0xad,0xb6,0xbf,0x80,0x89,0x92,0x9b,	
						0x7c,0x75,0x6e,0x67,0x58,0x51,0x4a,0x43,0x34,0x3d,0x26,0x2f,0x10,0x19,0x02,0x0b,
						0xd7,0xde,0xc5,0xcc,0xf3,0xfa,0xe1,0xe8,0x9f,0x96,0x8d,0x84,0xbb,0xb2,0xa9,0xa0,
						0x47,0x4e,0x55,0x5c,0x63,0x6a,0x71,0x78,0x0f,0x06,0x1d,0x14,0x2b,0x22,0x39,0x30,
						0x9a,0x93,0x88,0x81,0xbe,0xb7,0xac,0xa5,0xd2,0xdb,0xc0,0xc9,0xf6,0xff,0xe4,0xed,
						0x0a,0x03,0x18,0x11,0x2e,0x27,0x3c,0x35,0x42,0x4b,0x50,0x59,0x66,0x6f,0x74,0x7d,	
						0xa1,0xa8,0xb3,0xba,0x85,0x8c,0x97,0x9e,0xe9,0xe0,0xfb,0xf2,0xcd,0xc4,0xdf,0xd6,
						0x31,0x38,0x23,0x2a,0x15,0x1c,0x07,0x0e,0x79,0x70,0x6b,0x62,0x5d,0x54,0x4f,0x46};


unsigned char m11[256]={0x00,0x0b,0x16,0x1d,0x2c,0x27,0x3a,0x31,0x58,0x53,0x4e,0x45,0x74,0x7f,0x62,0x69,
						0xb0,0xbb,0xa6,0xad,0x9c,0x97,0x8a,0x81,0xe8,0xe3,0xfe,0xf5,0xc4,0xcf,0xd2,0xd9,
						0x7b,0x70,0x6d,0x66,0x57,0x5c,0x41,0x4a,0x23,0x28,0x35,0x3e,0x0f,0x04,0x19,0x12,
						0xcb,0xc0,0xdd,0xd6,0xe7,0xec,0xf1,0xfa,0x93,0x98,0x85,0x8e,0xbf,0xb4,0xa9,0xa2,
						0xf6,0xfd,0xe0,0xeb,0xda,0xd1,0xcc,0xc7,0xae,0xa5,0xb8,0xb3,0x82,0x89,0x94,0x9f,
						0x46,0x4d,0x50,0x5b,0x6a,0x61,0x7c,0x77,0x1e,0x15,0x08,0x03,0x32,0x39,0x24,0x2f,
						0x8d,0x86,0x9b,0x90,0xa1,0xaa,0xb7,0xbc,0xd5,0xde,0xc3,0xc8,0xf9,0xf2,0xef,0xe4,
						0x3d,0x36,0x2b,0x20,0x11,0x1a,0x07,0x0c,0x65,0x6e,0x73,0x78,0x49,0x42,0x5f,0x54,
						0xf7,0xfc,0xe1,0xea,0xdb,0xd0,0xcd,0xc6,0xaf,0xa4,0xb9,0xb2,0x83,0x88,0x95,0x9e,
						0x47,0x4c,0x51,0x5a,0x6b,0x60,0x7d,0x76,0x1f,0x14,0x09,0x02,0x33,0x38,0x25,0x2e,
						0x8c,0x87,0x9a,0x91,0xa0,0xab,0xb6,0xbd,0xd4,0xdf,0xc2,0xc9,0xf8,0xf3,0xee,0xe5,
						0x3c,0x37,0x2a,0x21,0x10,0x1b,0x06,0x0d,0x64,0x6f,0x72,0x79,0x48,0x43,0x5e,0x55,
						0x01,0x0a,0x17,0x1c,0x2d,0x26,0x3b,0x30,0x59,0x52,0x4f,0x44,0x75,0x7e,0x63,0x68,
						0xb1,0xba,0xa7,0xac,0x9d,0x96,0x8b,0x80,0xe9,0xe2,0xff,0xf4,0xc5,0xce,0xd3,0xd8,
						0x7a,0x71,0x6c,0x67,0x56,0x5d,0x40,0x4b,0x22,0x29,0x34,0x3f,0x0e,0x05,0x18,0x13,
						0xca,0xc1,0xdc,0xd7,0xe6,0xed,0xf0,0xfb,0x92,0x99,0x84,0x8f,0xbe,0xb5,0xa8,0xa3};


unsigned char m13[256]={0x00,0x0d,0x1a,0x17,0x34,0x39,0x2e,0x23,0x68,0x65,0x72,0x7f,0x5c,0x51,0x46,0x4b,
						0xd0,0xdd,0xca,0xc7,0xe4,0xe9,0xfe,0xf3,0xb8,0xb5,0xa2,0xaf,0x8c,0x81,0x96,0x9b,
						0xbb,0xb6,0xa1,0xac,0x8f,0x82,0x95,0x98,0xd3,0xde,0xc9,0xc4,0xe7,0xea,0xfd,0xf0,
						0x6b,0x66,0x71,0x7c,0x5f,0x52,0x45,0x48,0x03,0x0e,0x19,0x14,0x37,0x3a,0x2d,0x20,
						0x6d,0x60,0x77,0x7a,0x59,0x54,0x43,0x4e,0x05,0x08,0x1f,0x12,0x31,0x3c,0x2b,0x26,
						0xbd,0xb0,0xa7,0xaa,0x89,0x84,0x93,0x9e,0xd5,0xd8,0xcf,0xc2,0xe1,0xec,0xfb,0xf6,
						0xd6,0xdb,0xcc,0xc1,0xe2,0xef,0xf8,0xf5,0xbe,0xb3,0xa4,0xa9,0x8a,0x87,0x90,0x9d,
						0x06,0x0b,0x1c,0x11,0x32,0x3f,0x28,0x25,0x6e,0x63,0x74,0x79,0x5a,0x57,0x40,0x4d,
						0xda,0xd7,0xc0,0xcd,0xee,0xe3,0xf4,0xf9,0xb2,0xbf,0xa8,0xa5,0x86,0x8b,0x9c,0x91,
						0x0a,0x07,0x10,0x1d,0x3e,0x33,0x24,0x29,0x62,0x6f,0x78,0x75,0x56,0x5b,0x4c,0x41,
						0x61,0x6c,0x7b,0x76,0x55,0x58,0x4f,0x42,0x09,0x04,0x13,0x1e,0x3d,0x30,0x27,0x2a,
						0xb1,0xbc,0xab,0xa6,0x85,0x88,0x9f,0x92,0xd9,0xd4,0xc3,0xce,0xed,0xe0,0xf7,0xfa,
						0xb7,0xba,0xad,0xa0,0x83,0x8e,0x99,0x94,0xdf,0xd2,0xc5,0xc8,0xeb,0xe6,0xf1,0xfc,
						0x67,0x6a,0x7d,0x70,0x53,0x5e,0x49,0x44,0x0f,0x02,0x15,0x18,0x3b,0x36,0x21,0x2c,
						0x0c,0x01,0x16,0x1b,0x38,0x35,0x22,0x2f,0x64,0x69,0x7e,0x73,0x50,0x5d,0x4a,0x47,
						0xdc,0xd1,0xc6,0xcb,0xe8,0xe5,0xf2,0xff,0xb4,0xb9,0xae,0xa3,0x80,0x8d,0x9a,0x97};

unsigned char m14[256]={0x00,0x0e,0x1c,0x12,0x38,0x36,0x24,0x2a,0x70,0x7e,0x6c,0x62,0x48,0x46,0x54,0x5a,
						0xe0,0xee,0xfc,0xf2,0xd8,0xd6,0xc4,0xca,0x90,0x9e,0x8c,0x82,0xa8,0xa6,0xb4,0xba,
						0xdb,0xd5,0xc7,0xc9,0xe3,0xed,0xff,0xf1,0xab,0xa5,0xb7,0xb9,0x93,0x9d,0x8f,0x81,
						0x3b,0x35,0x27,0x29,0x03,0x0d,0x1f,0x11,0x4b,0x45,0x57,0x59,0x73,0x7d,0x6f,0x61,
						0xad,0xa3,0xb1,0xbf,0x95,0x9b,0x89,0x87,0xdd,0xd3,0xc1,0xcf,0xe5,0xeb,0xf9,0xf7,
						0x4d,0x43,0x51,0x5f,0x75,0x7b,0x69,0x67,0x3d,0x33,0x21,0x2f,0x05,0x0b,0x19,0x17,
						0x76,0x78,0x6a,0x64,0x4e,0x40,0x52,0x5c,0x06,0x08,0x1a,0x14,0x3e,0x30,0x22,0x2c,
						0x96,0x98,0x8a,0x84,0xae,0xa0,0xb2,0xbc,0xe6,0xe8,0xfa,0xf4,0xde,0xd0,0xc2,0xcc,
						0x41,0x4f,0x5d,0x53,0x79,0x77,0x65,0x6b,0x31,0x3f,0x2d,0x23,0x09,0x07,0x15,0x1b,
						0xa1,0xaf,0xbd,0xb3,0x99,0x97,0x85,0x8b,0xd1,0xdf,0xcd,0xc3,0xe9,0xe7,0xf5,0xfb,
						0x9a,0x94,0x86,0x88,0xa2,0xac,0xbe,0xb0,0xea,0xe4,0xf6,0xf8,0xd2,0xdc,0xce,0xc0,
						0x7a,0x74,0x66,0x68,0x42,0x4c,0x5e,0x50,0x0a,0x04,0x16,0x18,0x32,0x3c,0x2e,0x20,
						0xec,0xe2,0xf0,0xfe,0xd4,0xda,0xc8,0xc6,0x9c,0x92,0x80,0x8e,0xa4,0xaa,0xb8,0xb6,
						0x0c,0x02,0x10,0x1e,0x34,0x3a,0x28,0x26,0x7c,0x72,0x60,0x6e,0x44,0x4a,0x58,0x56,
						0x37,0x39,0x2b,0x25,0x0f,0x01,0x13,0x1d,0x47,0x49,0x5b,0x55,0x7f,0x71,0x63,0x6d,
						0xd7,0xd9,0xcb,0xc5,0xef,0xe1,0xf3,0xfd,0xa7,0xa9,0xbb,0xb5,0x9f,0x91,0x83,0x8d};
unsigned char Rcon[11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

unsigned char Inv_tab_mixCol[4][4] = {{0x0e,0x0b,0x0d,0x09},{0x09,0x0e,0x0b,0x0d},{0x0d,0x09,0x0e,0x0b},{0x0b,0x0d,0x09,0x0e}};

//Fonction qui affiche une matrice 4*4 en hexadécimal
void affichage(unsigned char state[4][4]){
	for(int i=0 ; i<4; i++)
	{
		printf("|");
		for(int j=0; j<4; j++)
		{
			printf(" %x |",state[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//Fonction qui récupère un message de 16 octets et le transforme en matrice 4*4
void initialisation(unsigned char state[4][4], unsigned char* message)
{
	int val;
	char init[3]="00";
	for(int i=0; i<32; i+=2)
    {
    	//Pour récupérer les caractères deux par deux
        strncpy(init, (char *)message+i, 2);
        //Pour les transformer en hexa
        sscanf(init, "%x", &val);
        //Pour les ajouter dans la matrice dans l'ordre
        state[(i/2)/4][(i/2)%4] = val;
    }
}

//Fonction qui prend en entrée une colonne et retourne la colonne mutlipliée par la matrice inverse du MixColumns
void InvMixCol(unsigned char col[4]){ 
	//Initialisation d'une colonne temporaire
	unsigned char tmp[4];

	tmp[0] = m14[col[0]]^m11[col[1]]^m13[col[2]]^m9[col[3]];
	tmp[1] = m9[col[0]]^m14[col[1]]^m11[col[2]]^m13[col[3]];
	tmp[2] = m13[col[0]]^m9[col[1]]^m14[col[2]]^m11[col[3]];
	tmp[3] = m11[col[0]]^m13[col[1]]^m9[col[2]]^m14[col[3]];

	//Recopiage de la colonne
	for (int i=0;i<4;i++){
		col[i] = tmp[i];
	}
}

//Fonction qui ouvre un fichier lambdaset et l'écrit dans une matrice 256*16
void Recup_set(unsigned char set[256][16], char* titre)
{
	//Initialisations
	int val;
	int compteur_ligne = 0;
	char tab[3]= "00";

	//Ecriture du lambdaset chiffré dans une matrice
	FILE* chiffres; 
	chiffres = fopen(titre, "r"); 

	char * buffer = (char *) malloc(40);
    while ( ! feof( chiffres) ) 
    {
        fgets((char *)buffer, 40 , chiffres);
        if ( ferror(chiffres) ) 
        {
			fprintf(stderr, "Reading error wih code %d\n",errno);
			break;
		}

        //Parcours des lignes chiffres et ajout au tableau 
    	for(int j=0; j<32; j+=2)
    	{
    		//Pour récupérer les caractères deux par deux
	        strncpy(tab, (char *)buffer+j, 2);
	        //Pour les transformer en hexa
	        sscanf(tab, "%x", &val);
	        //Pour les ajouter dans la matrice dans l'ordre
	        set[compteur_ligne][j/2] = val;
    	}
   
        compteur_ligne = compteur_ligne +1;     
    }
    free( buffer ); 
	fclose(chiffres);
}

//Fonction qui prend en entrée une cellule d'un set et renvoie true si la cellule de set est équilibrée
int TestCell(unsigned char set[256])
{
	int b = 1;
	unsigned char somme = 0;
	for(int j = 0; j<256; j++)
	{
		//Fait un XOR avec tous les éléments du tableau pour voir si la cellule du set est équilibrée
 		somme = somme ^ set[j]; 
 	}

	if(somme!=0)
	{
		b = 0;
	}
 	
 	return b;
}

//Fonctions qui récupère les diagonales 
void Recup_Diag1(unsigned char set[256][16], unsigned char Diagonal_Chiffre[256][4])  
{
	for( int i = 0; i<256; i++)
	{
		
		Diagonal_Chiffre[i][0] = set[i][4];
		Diagonal_Chiffre[i][1] = set[i][1];
		Diagonal_Chiffre[i][2] = set[i][14];
		Diagonal_Chiffre[i][3] = set[i][11];

	}
}

void Recup_Diag2(unsigned char set[256][16], unsigned char Diagonal_Chiffre[256][4])  
{
	for( int i = 0; i<256; i++)
	{
		
		Diagonal_Chiffre[i][0] = set[i][0];
		Diagonal_Chiffre[i][1] = set[i][13];
		Diagonal_Chiffre[i][2] = set[i][10];
		Diagonal_Chiffre[i][3] = set[i][7];

	}
}

void Recup_Diag3(unsigned char set[256][16], unsigned char Diagonal_Chiffre[256][4])  
{
	for( int i = 0; i<256; i++)
	{
		
		Diagonal_Chiffre[i][0] = set[i][8];
		Diagonal_Chiffre[i][1] = set[i][5];
		Diagonal_Chiffre[i][2] = set[i][2];
		Diagonal_Chiffre[i][3] = set[i][15];

	}
}

void Recup_Diag4(unsigned char set[256][16], unsigned char Diagonal_Chiffre[256][4])  
{
	for( int i = 0; i<256; i++)
	{
		
		Diagonal_Chiffre[i][0] = set[i][12];
		Diagonal_Chiffre[i][1] = set[i][9];
		Diagonal_Chiffre[i][2] = set[i][6];
		Diagonal_Chiffre[i][3] = set[i][3];

	}
}


//Fonction qui prend en entrée les diagonales d'un set, 4 octets de clé de K5, et 1 octet de K4
//La fonction renvoie 1 si le set est équilibré, et sinon 0
int TestLamdbaSet(unsigned char Diagonal_Chiffre[256][4], unsigned char K5[4],unsigned char b)
{
	unsigned char y[256][4];
	unsigned char x[256]; 

	for(int n = 0 ; n<256; n++)
	{
		for(int m= 0; m<4; m++)
		{
			y[n][m] = invSBOX[Diagonal_Chiffre[n][m]^K5[m]];
		}
		InvMixCol(y[n]);
		x[n] = invSBOX[b ^y[n][3]];
	}
	if (TestCell(x) == 1)
	{
		return 1;
	}
	return 0;
}

//Fonction d'attaque 
unsigned char * Diagonale_Key(unsigned char K5[4],unsigned char D1[256][4],unsigned char D2[256][4],unsigned char D3[256][4],unsigned char D4[256][4],unsigned char D5[256][4],unsigned char D6[256][4]){
	
	//Hypothèses du premier octet de la clé de K5
    for(int i =0 ; i<256;i++){
		printf("%d\n",i);

		//Hypothèses du deuxième  octet de la clé de K5
    	for(int j =0; j<256;j++){
			
			//for( int k=0; k<256; k++)
			//{
				//for( int l=0; l<256; l++)
				//{
    			//Hypothèse d'un octet de clé de K4
					for(int b= 0; b<256; b++)
					{
						K5[0] = i ;
						K5[1] = j ;
						K5[2] =0x96; //k;
						K5[3] =0x71; //l;
					
						//Test si la cellule est équilibré sur tous les lambdasets 
						if (TestLamdbaSet(D1, K5, b ) == 1)
						{
							if (TestLamdbaSet(D2, K5, b ) == 1)
							{
								if (TestLamdbaSet(D3,K5,b)==1)
								{
									if (TestLamdbaSet(D4,K5,b)==1)
									{
										if (TestLamdbaSet(D5,K5,b)==1)
										{
											if (TestLamdbaSet(D6,K5,b)==1)
											{

												for(int z=0;z<4;z++)
												{
													//Affichage de la clé supposée
													printf("%x ",K5[z]);
												}
												printf("\n");
												return K5;
												
											}
										}
									}
								}
							}
						}
					//}
				//}
			}
    	}
    }
	return 0;
}


//Fonction qui retourne la clé initiale à partir d'une sous clé.
unsigned char * invKeyExpansion(unsigned char key[16],int nbtours){
	unsigned char * tmpKey = NULL;
	tmpKey = malloc(sizeof(unsigned char)*16);
	

	for(int i= 0; i<16;i++){
		tmpKey[i] = 0;
	}

	for (int i=0; i<nbtours;i++){
		
		for (int j=15;j>=0;j--){
			if(j>=4){
				tmpKey[j]=key[j]^key[j-4];
			}
			else{
				switch(j){
					case 3 : 
						tmpKey[j] = key[j] ^ Sbox[tmpKey[12]];
						break;
					case 2 : 
						tmpKey[j] = key[j] ^ Sbox[tmpKey[15]];
						break;
					case 1 :
						tmpKey[j] = key[j] ^ Sbox[tmpKey[14]];
						break;
					case 0 :
						tmpKey[j] = key[j] ^ Sbox[tmpKey[13]]^Rcon[nbtours - i];
						break;
				}
			}
		}
		for(int s = 0; s<16; s++){
			key[s]= tmpKey[s];
		}	
	}
	return key;
};


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	


	//Initialisations des sets 
	char* titre1 = "AES5_ciphered_set_1_key_C.txt";
	char* titre2 = "AES5_ciphered_set_2_key_C.txt";
	char* titre3 = "AES5_ciphered_set_3_key_C.txt";
	char* titre4 = "AES5_ciphered_set_4_key_C.txt";
	char* titre5 = "AES5_ciphered_set_5_key_C.txt";
	char* titre6 = "AES5_ciphered_set_6_key_C.txt";

	unsigned char set1[256][16];
	unsigned char set2[256][16];
	unsigned char set3[256][16];
	unsigned char set4[256][16];
	unsigned char set5[256][16];
	unsigned char set6[256][16];

	Recup_set(set1, titre1);
	Recup_set(set2, titre2);
	Recup_set(set3, titre3);
	Recup_set(set4, titre4);
	Recup_set(set5, titre5);
	Recup_set(set6, titre6);

	//Initialisations des diagonales 
	unsigned char K5[4]; 
	unsigned char Diagonal_Chiffre1[256][4];
	unsigned char Diagonal_Chiffre2[256][4];
	unsigned char Diagonal_Chiffre3[256][4];
	unsigned char Diagonal_Chiffre4[256][4];
	unsigned char Diagonal_Chiffre5[256][4];
	unsigned char Diagonal_Chiffre6[256][4];


	Recup_Diag1(set1, Diagonal_Chiffre1);
	Recup_Diag1(set2, Diagonal_Chiffre2);
	Recup_Diag1(set3, Diagonal_Chiffre3);
	Recup_Diag1(set4, Diagonal_Chiffre4);
	Recup_Diag1(set5, Diagonal_Chiffre5);
	Recup_Diag1(set6, Diagonal_Chiffre6);


	//Attaque
	Diagonale_Key(K5, Diagonal_Chiffre1, Diagonal_Chiffre2, Diagonal_Chiffre3, Diagonal_Chiffre4, Diagonal_Chiffre5, Diagonal_Chiffre6);


}


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main de l'attaque complète ////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
// temps d'éxecution trop long 

/*int main(int argc, char* argv[])
{

	//Initalisation de la clé 
	unsigned char cle[16];


	//Initialisations des sets 
	char* titre1 = "AES5_ciphered_set_1_key_C.txt";
	char* titre2 = "AES5_ciphered_set_2_key_C.txt";
	char* titre3 = "AES5_ciphered_set_3_key_C.txt";
	char* titre4 = "AES5_ciphered_set_4_key_C.txt";
	char* titre5 = "AES5_ciphered_set_5_key_C.txt";
	char* titre6 = "AES5_ciphered_set_6_key_C.txt";

	unsigned char set1[256][16];
	unsigned char set2[256][16];
	unsigned char set3[256][16];
	unsigned char set4[256][16];
	unsigned char set5[256][16];
	unsigned char set6[256][16];

	Recup_set(set1, titre1);
	Recup_set(set2, titre2);
	Recup_set(set3, titre3);
	Recup_set(set4, titre4);
	Recup_set(set5, titre5);
	Recup_set(set6, titre6);

	//Initialisations des diagonales 
	unsigned char K5[4]; 
	unsigned char Diagonal_Chiffre1[256][4];
	unsigned char Diagonal_Chiffre2[256][4];
	unsigned char Diagonal_Chiffre3[256][4];
	unsigned char Diagonal_Chiffre4[256][4];
	unsigned char Diagonal_Chiffre5[256][4];
	unsigned char Diagonal_Chiffre6[256][4];


	//Attaque première diagonale
	Recup_Diag1(set1, Diagonal_Chiffre1);
	Recup_Diag1(set2, Diagonal_Chiffre2);
	Recup_Diag1(set3, Diagonal_Chiffre3);
	Recup_Diag1(set4, Diagonal_Chiffre4);
	Recup_Diag1(set5, Diagonal_Chiffre5);
	Recup_Diag1(set6, Diagonal_Chiffre6);

	Diagonale_Key(K5, Diagonal_Chiffre1, Diagonal_Chiffre2, Diagonal_Chiffre3, Diagonal_Chiffre4, Diagonal_Chiffre5, Diagonal_Chiffre6);

	//remplissage de la clé
	cle[4]= K5[0];
	cle[1]= K5[1];
	cle[14]= K5[2];
	cle[11]= K5[3];


	//Attaque deuxième diagonale
	Recup_Diag2(set1, Diagonal_Chiffre1);
	Recup_Diag2(set2, Diagonal_Chiffre2);
	Recup_Diag2(set3, Diagonal_Chiffre3);
	Recup_Diag2(set4, Diagonal_Chiffre4);
	Recup_Diag2(set5, Diagonal_Chiffre5);
	Recup_Diag2(set6, Diagonal_Chiffre6);

	Diagonale_Key(K5, Diagonal_Chiffre1, Diagonal_Chiffre2, Diagonal_Chiffre3, Diagonal_Chiffre4, Diagonal_Chiffre5, Diagonal_Chiffre6);/Attaque première diagonale
	
	//remplissage de la clé
	cle[0]= K5[0];
	cle[13]= K5[1];
	cle[10]= K5[2];
	cle[7]= K5[3];


	//Attaque troisème diagonale 
	Recup_Diag3(set1, Diagonal_Chiffre1);
	Recup_Diag3(set2, Diagonal_Chiffre2);
	Recup_Diag3(set3, Diagonal_Chiffre3);
	Recup_Diag3(set4, Diagonal_Chiffre4);
	Recup_Diag3(set5, Diagonal_Chiffre5);
	Recup_Diag3(set6, Diagonal_Chiffre6);

	Diagonale_Key(K5, Diagonal_Chiffre1, Diagonal_Chiffre2, Diagonal_Chiffre3, Diagonal_Chiffre4, Diagonal_Chiffre5, Diagonal_Chiffre6);/Attaque première diagonale
	
	//remplissage de la clé
	cle[8]= K5[0];
	cle[5]= K5[1];
	cle[2]= K5[2];
	cle[15]= K5[3];


	//Attaque quatrième diagonale 
	Recup_Diag4(set1, Diagonal_Chiffre1);
	Recup_Diag4(set2, Diagonal_Chiffre2);
	Recup_Diag4(set3, Diagonal_Chiffre3);
	Recup_Diag4(set4, Diagonal_Chiffre4);
	Recup_Diag4(set5, Diagonal_Chiffre5);
	Recup_Diag4(set6, Diagonal_Chiffre6);

	Diagonale_Key(K5, Diagonal_Chiffre1, Diagonal_Chiffre2, Diagonal_Chiffre3, Diagonal_Chiffre4, Diagonal_Chiffre5, Diagonal_Chiffre6);

	//remplissage de la clé
	cle[12]= K5[0];
	cle[9]= K5[1];
	cle[6]= K5[2];
	cle[3]= K5[3];



	//Affichage de la clé retrouvée
	printf("voici la clé de tour K5 : ");
	for(int z=0;z<16;z++)
	{
		printf("%x ",cle[z]);
	}
	printf("\n");



	//Récupération de la clé initiale 
	invKeyExpansion(cle, 5); 

	//Affichage de la clé initiale trouvée 
	printf("La clé initiale trouvée : \n");
	for(int i=0; i<16; i++){
		printf("%x  ",cle[i]);
	}


}*/