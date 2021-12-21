#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Attaque 4 tours  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

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

//fonction qui xor tout le tableau avec une clé
void AddRoundKey(unsigned char set[256][16], unsigned char Key[16])
{
    for (int i = 0; i<256; i++)
    {
    	for(int j = 0; j<16; j++)
    	{
     		set[i][j] = set[i][j]^Key[j]; 
     	}
    }
}

//Fonction qui prend en entrée une liste de 256 messages et renvoie true s'ils sont équilibrés ou non
int TestCell(unsigned char set[256][16])
{
	int b = 1;
	unsigned char somme[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i<256; i++)
    {
    	for(int j = 0; j<16; j++)
    	{
    		//Fais un XOR avec tous les éléments d'une colonne pour savoir si elle est équilibrée
     		somme[j] = somme[j] ^ set[i][j]; 
     	}
    }
 

    for(int j = 0; j<16; j++)
	{
		if(somme[j]!=0){
			b = 0;
		}
 	}
 	return b;
}

//Fonction qui prend en entrée le tableau de 256 chiffrés et renvoie les messages passés dans la SboxInv
void SubBytesInv(unsigned char set[256][16])
{
    for (int i = 0; i<256; i++)
    {
    	for(int j = 0; j<16; j++)
    	{
     		set[i][j] = invSBOX[set[i][j]]; 
     	}
    }
}


//----- Fonctions sur 1 octet ----- //

//Fonction qui prend en entrée un octet du set et un octet de la clé et renvoi l'octet passé dans la SboxInv
unsigned char InvSubBytes(unsigned char set){
	set = invSBOX[set];
	return set;
}

int balancedByte(unsigned char set[256]){
	unsigned char somme = 0;
	for(int i=0;i<256;i++){
		somme ^= set[i];
	}
	return somme;
}


//----- Fonctions sur 1 octet ----- //



void invShiftRows(unsigned char state[4][4])
{
	//Déclaration d'une matrice temporaire 
	unsigned char tmp[4][4] = {{0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

	//Shift de la matrice 
	for (int s = 0; s<4 ; s++)
	{
		for(int j=0; j< 4; j++)
		{
			tmp[s][j] = state[s][(j-s)%4];
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

///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////



int main(int argc, char* argv[])
{
	int val;
	int compteur_ligne = 0;
	char tab[3]= "00";
	unsigned char set[256][16];


	//ecriture du lambda set chiffré dans un tableau 
	FILE* chiffres; 
	chiffres = fopen("set.txt", "r"); 

	char * buffer = (char *) malloc(40);
    while ( ! feof( chiffres) ) 
    {
        fgets((char *)buffer, 40 , chiffres);
        if ( ferror(chiffres) ) 
        {
			fprintf(stderr, "Reading error wih code %d\n",errno);
			break;
		}
        //parcour des lignes chiffres et ajout au tableau 
    
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
        //puts( (char *)buffer );  //affichage des lignes recup      
    }
    free( buffer ); 
	fclose(chiffres);


	//affichage du set chiffré à partir du tableau
	/*
	for(int i=0;i<256;i++){
		for (int j=0; j<16;j++){
			if(set[i][j]>=16){
				printf("%x",set[i][j]);
			}
			else{
				printf("0%x",set[i][j]);
			}
		}
		printf("\n");
	}
	
*/


	//guess de cle 
	unsigned char tmpset[256][16]; //Ajout du set dans tmpset
	for(int i=0;i<256;i++){
		for(int j=0;j<16;j++){
			tmpset[i][j] = set[i][j];
		}
	}
/*				                            Sans allocation dynamique
	unsigned char KeySuggested[16][5];
	for(int i=0;i<16;i++){
		for(int j=0;j<10;j++){
			KeySuggested[i][j]=0;
		}
	}
*/
										// avec allocation dynamique
	unsigned char **KeySuggested2;
	KeySuggested2 = malloc(sizeof(unsigned char)*16);
	if(KeySuggested2 == NULL){
		exit(0);
	}

	for(int a=0; a<16; a++){ // a = 4*i + j sur la matrice State
		
		int compteurDeCle = 1;
		printf("%d ---> ",a);

		for(int k=0; k<256; k++){ // les clés possibles sur la position i,j

			unsigned char tmpSet[256]; 
			for(int i=0; i<256; i++){	// les 256 octets de chaque lambdaSet pour la position i,j
				
				unsigned char tmp = tmpset[i][a] ^ k; 
				tmp = InvSubBytes(tmp);  // InvSubBytes(d ^ k) 
				tmpSet[i] = tmp;
			}
	
			if (balancedByte(tmpSet)==0){
				
				// KeySuggested[a][compteurDeCle-1] = k 
				if(compteurDeCle == 1){
					KeySuggested2[a] = malloc(sizeof(unsigned char));
					if(KeySuggested2[a] == NULL){
						exit(0);
					}
				} 
				else{
					KeySuggested2[a] = realloc(KeySuggested2[a], sizeof(unsigned char)*(compteurDeCle));
					if(KeySuggested2[a] == NULL){
						exit(0);
					}
				}
				KeySuggested2[a][compteurDeCle] = k;
				printf("%x ",KeySuggested2[a][compteurDeCle]);
				
				compteurDeCle++;
			}
		
		}
		printf("\n");
	
	}

	

free(KeySuggested2);


/*
	for(int i=0;i<16;i++){
		for(int j=0;j<5;j++){
			printf("%x ",KeySuggested[i][j]);
		}
		printf("\n");
	}
*/
	

	// trouver toutes les combinaisons de clé à partir de KeySuggested.
	// faire la fonction inverse d'expandKey pour retrouver la clé initiale.

	
}