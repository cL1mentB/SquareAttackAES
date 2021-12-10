#include <string.h>
#include <stdio.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// outils  ///////////////////////////////////////////////
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

 //matrice MixColonne
unsigned char tab_mixCol[4][4] = {{0x02,0x03,0x01,0x01},{0x01,0x02,0x03,0x01},{0x01,0x01,0x02,0x03},{0x03,0x01,0x01,0x02}};

unsigned char Rcon[11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Fonctions /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

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




//Fonction qui prend en entrée une matrice et renvoie la matrice multipliée par une matrice définie 
void MixColumns(unsigned char state[4][4])
{
	//Declaration de matrice intermediaire 
	unsigned char tmp[4][4] = {{0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

	//multiplication des matrices dans une matrice temporaire
	for (int i = 0; i<4; i++)
    {
    	for(int j = 0; j<4; j++ )
    	{
     		for (int s = 0; s<4 ; s++)
     		{
     			tmp[i][j] = tmp [i][j] + state[i][s]*tab_mixCol[s][j];
     		}
     	}
    }

    //recopiage de tmp sur state
    for (int i = 0; i<4; i++)
    {
    	for(int j = 0; j<4; j++ )
    	{
     		state[i][j] = tmp[i][j]; 
     	}
    }
}

//Fonction qui prend en entrée une matrice et renvoie la matrice passée dans une Sbox
void SubBytes(unsigned char state[4][4])
{
    for (int i = 0; i<4; i++)
    {
    	for(int j = 0; j<4; j++ )
    	{
     		state[i][j] = Sbox[state[i][j]]; 
     	}
    }
    
}

//Fonction qui prend en entrée une matrice et renvoie la matrice shiftée vers la gauche sur les lignes
void ShiftRows(unsigned char state[4][4])
{
	//Déclaration d'une matrice temporaire 
	unsigned char tmp[4][4] = {{0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

	//Shift de la matrice 
	for (int s = 0; s<4 ; s++)
	{
		for(int j=0; j< 4; j++)
		{
			tmp[s][j] = state[s][(j+s)%4];
		}
	}
   
    //recopiage de tmp sur state
    for (int i = 0; i<4; i++)
    {
    	for(int j = 0; j<4; j++ )
    	{
     		state[i][j] = tmp[i][j]; 
     	}
    }
}


//Fonction qui prend en entrée une matrice et une sous-clef K_i de 128 bits et renvoie le XOR des deux
void AddRoundKey(unsigned char state[4][4], unsigned char * expandedKey,int tour)
{
	for (int i = 0; i < 4; i++)
    {
    	for(int j = 0; j< 4; j++ )
    	{
     		state[i][j] = state[i][j] ^ expandedKey[4*i+j+tour*16];
     	}
    }
}


//Fonction de KeyExpansion qui prend en entrée la clé de base et le nombre de tour
//retourne un tableau de 176 cases contenant les nbtours+1 clés. 
unsigned char * KeyExpansion(unsigned char key[16],int nbtours){ 
    
    unsigned char * expandedKey = malloc( (nbtours+1)*16);

    for(int i =0; i<16;i++){
        expandedKey[i] = key[i];
    }
    int byteCount = 16;
    for(int i=0; i<nbtours; i++){
        unsigned char word[4] = {expandedKey[byteCount-4],expandedKey[byteCount-3],expandedKey[byteCount-2],expandedKey[byteCount-1]};
        unsigned char tmp[4] = {Sbox[word[1]]^Rcon[i+1],Sbox[word[2]],Sbox[word[3]],Sbox[word[0]]};

        for(int j=0; j<4; j++){
            if(j==0){
                for(int k=0; k<4;k++){
                    expandedKey[byteCount+k] = expandedKey[byteCount+k-16]^tmp[k];
                    
                }
                byteCount = byteCount+4;
            }
            else{
                for(int k=0; k<4; k++){
                    expandedKey[byteCount+k] = expandedKey[byteCount+k-16]^expandedKey[byteCount+k-4];
                    
                }
                byteCount = byteCount+4;
            }
        }
    }

    return expandedKey;
} // pour utiliser le tableau expandedKey :
  // au tour t, il faut prendre les valeurs de t*16 à (t+1)*16



//Fonction de chiffrement de l'AES qui prend en entrée un message, un nombre de tours et une clef et qui renvoie le chiffré
void encryption_AES(int nbtours, unsigned char state[4][4], unsigned char key[16]){
	//Key schedule
	unsigned char * expandedKey = KeyExpansion(key,nbtours);

	//Tour 0
	AddRoundKey(state, expandedKey,0); //Normalement, on met key_0

	//Tours 1 à n-1
	for(int i=1; i<nbtours; i++){
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, expandedKey,i); //Normalement, on met key_i
	}
	
	//Tour final
	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, expandedKey, nbtours); //Normalement, on met key_n
}


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	//initialisation du message 
	char * message = "6bc1bee22E409F96e93d7e117393172a";

	//initialisation de la clef : 8d010204081020408d01020408102040
	unsigned char key[16] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40};
	
	//initialisation de la matrice message
	unsigned char state[4][4]; 
	initialisation(state, (unsigned char*)message);
	
	//chiffrement
	encryption_AES(4, state, key);
	affichage(state);

	return 0;
}