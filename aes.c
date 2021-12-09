#include <string.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Fonctions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//Fonction qui recupère un message de 16 octets et le transforme en matrice 4X4
void initialisation(unsigned char state[4][4], unsigned char* message)
{

	int a=0; 
	for(int i=0 ; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			state[i][j] = message[a];
			a = a + 1 ;
		}
	}
}


//Fonction AddRoundKey prend en entrée une matrice et un sous-clef K_i de 128 bits et renvoie le XOR des deux
void AddRoundKey( unsigned char state[4][4], unsigned char key[16])
{

}

//Fonction MixColumns prend une matrice et renvoie la matrice multipliée par une matrice définie 
void mixColumns(unsigned char state[4][4])
{

}

//Fonction SubBytes prend en entrée une matrice et renvoie la matrice passée dans une Sbox
void byteSubShiftRow(unsigned char state[4][4])
{
}

//Fonction ShiftRows prend une matrice et renvoie la matrice shiftée vers la gauche sur les lignes


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

	//déclaration du message 
	unsigned char message1[16] = {0x6b , 0xc1, 0xbe, 0xe2, 0x2E, 0x40 , 0x9F, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a}; 
 
	//declaration de la matrice AES
	unsigned char state[4][4];
	//remplissage de la matrice 
	initialisation(state, message1);
	//verif
	printf("%x\n",state[1][1]);
}