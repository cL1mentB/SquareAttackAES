#include <string.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Fonctions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//Fonction qui recupère un message de 16 octets et le transforme en matrice 4X4
int initialisation(unsigned char state[4][4], unsigned char* message)
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
	return 1; 
}

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