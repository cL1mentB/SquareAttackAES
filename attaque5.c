#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// outils  ///////////////////////////////////////////////
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

void InvMixcol(unsigned char y[256][4])
{
	
}

//recupération des lamdba set 
void Recup_set(unsigned char set[256][16], char* titre)
{
	int val;
	int compteur_ligne = 0;
	char tab[3]= "00";

	//ecriture du lambda set chiffré dans un tableau 
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

}

//Fonction qui prend en entrée une liste de 256 messages et renvoie true s'ils sont équilibrés ou non
int TestCell(unsigned char set[256])
{
	int b = 1;
	unsigned char somme = 0;
	for(int j = 0; j<256; j++)
	{
		//Fais un XOR avec tous les éléments du tableau  pour voir si la case est équilibrée
 		somme = somme ^ set[j]; 
 	}

	if(somme!=0)
	{
		b = 0;
	}
 	
 	return b;
}

//Fonction qui récupère les diagonales 
void Recup_Diag(unsigned char set[256][16], unsigned char Diagonal_Chiffre[256][4])
{
	for( int i = 0; i<256; i++)
	{
		for(int j = 0; j<16 ; j=j+5)
		{
			Diagonal_Chiffre[i][j] = set[i][j];
		}
	}
}

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
		//InvMixcol(y);
		x[n] = invSBOX[b ^y[n][3]];
	}
	if (TestCell(x) == 1)
	{
		return 1;
	}
	return 0;
}



///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Main //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	//recherche des 4 octets de cle de la diagonale centrale 

	//on recupere la diagonale C des octets necessaires dans un tableau de taille 4

	// 4 boucle for pour 4 hypothèses de 4 octets de clés de K5

		//y = invSbox(C[] ^ K5[])
		// for pourhypothese de cle d'un octet b 
			//x = b ^ 4ième octet de(inMixColonne(y))
			// test = teste(invSbox(x))
			//si test = 0 alors on garde les 4 octets en supposition de clé possible (pour les tester sur autre lamdba set)  et ajout au tableau de clé 
			//sinon hypothèse suivante 

	//Récupération des lamdba set dans des tableaux 
	char* titre1 = "set1.txt";
	char* titre2 = "set2.txt";
	char* titre3 = "set3.txt";
	char* titre4 = "set4.txt";
	char* titre5 = "set5.txt";
	char* titre6 = "set6.txt";

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

	//attaque sur les diagonales


	//Initialisations
	unsigned char K5[4]; 
	unsigned char Diagonal_Chiffre1[256][4];
	unsigned char Diagonal_Chiffre2[256][4];
	unsigned char Diagonal_Chiffre3[256][4];
	unsigned char Diagonal_Chiffre4[256][4];
	unsigned char Diagonal_Chiffre5[256][4];
	unsigned char Diagonal_Chiffre6[256][4];



	Recup_Diag(set1, Diagonal_Chiffre1);
	Recup_Diag(set2, Diagonal_Chiffre2);
	Recup_Diag(set3, Diagonal_Chiffre3);
	Recup_Diag(set4, Diagonal_Chiffre4);
	Recup_Diag(set5, Diagonal_Chiffre5);
	Recup_Diag(set6, Diagonal_Chiffre6);


	//Hypothèses de 4 octets de clés de K5
    for(int i =0; i<256;i++)
    {
    	for(int j =0; j<256;j++)
    	{
    		for(int k =0; k<256;k++)
    		{
   				 for(int l =0; l<256;l++)
   				{
   					//hypothèses de beta(1 octet) 
   					for(int b= 0; b<256; b++)
   					{
						K5[0] = i ; 
						K5[1] = j ;
						K5[2] = k ;
						K5[3] = l ;

						//Teste equilibre de la cellule sur les lambdas set 
						if (TestLamdbaSet(Diagonal_Chiffre1, K5, b )== 1)
						{
							if (TestLamdbaSet(Diagonal_Chiffre2, K5, b )== 1)
							{
								if (TestLamdbaSet(Diagonal_Chiffre3, K5, b )== 1)
								{
									if (TestLamdbaSet(Diagonal_Chiffre4, K5, b )== 1)
									{
										if (TestLamdbaSet(Diagonal_Chiffre5, K5, b )== 1)
										{
											if (TestLamdbaSet(Diagonal_Chiffre6, K5, b )== 1)
											{
												//on garde K5 
											}

										}

									}

								}

							}

						}
					}
   				}
    		}
    	}
    }
}