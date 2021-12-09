#include <string.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Fonctions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

//Fonction qui recupère un message de 16 octets et le transforme en matrice 4X4
void initialisation(unsigned char state[4][4], unsigned char* message)
{
	int val;
	char init[3] = "00";
	for(int i=0; i<32; i+=2)
    {
        strncpy(init, (char *)message+i, 2);
        sscanf(init, "%x", &val);
        state[(i/2)%4][(i/2)/4] = val;
    }
	/*int a=0; 
	for(int i=0 ; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			state[i][j] = message[a];
			a = a + 1 ;
		}
	}*/
}


//Fonction AddRoundKey prend en entrée une matrice
// et un sous-clef K_i de 128 bits et renvoie le XOR des deux


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{

	//déclaration du message 
	char * message = "6bc1bee22E409F96e93d7e117393172a";
	//unsigned char message1[16] = {0x6b , 0xc1, 0xbe, 0xe2, 0x2E, 0x40 , 0x9F, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a}; 
 
	//declaration de la matrice AES
	unsigned char state[4][4];
	//remplissage de la matrice 
	initialisation(state, (unsigned char*)message);
	//verif
	printf("%x\n",state[0][1]);


}