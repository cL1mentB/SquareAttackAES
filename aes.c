#include <string.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Fonctions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//Fonction qui affiche une matrice 4*4
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
}

//Fonction qui recupère un message de 16 octets et le transforme en matrice 4X4
void initialisation(unsigned char state[4][4], unsigned char* message)
{
	int val;
	char init[3]="00";
	for(int i=0; i<32; i+=2)
    {
        strncpy(init, (char *)message+i, 2);
        sscanf(init, "%x", &val);
        state[(i/2)/4][(i/2)%4] = val;
    }
}


//Fonction AddRoundKey prend en entrée une matrice et un sous-clef K_i de 128 bits et renvoie le XOR des deux
void AddRoundKey(unsigned char state[4][4], unsigned char key[16])
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
	char * message = "6bc1bee22E409F96e93d7e117393172a";
	//declaration de la matrice AES
	unsigned char state[4][4];

	//remplissage de la matrice 
	initialisation(state, (unsigned char*)message);
	//affichage matrice
	affichage(state);
}