#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
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

int main(){
//unsigned char STATE[4][4] = {{0xbd,0xf2,0x0b,0x8b},{0x6e,0xb5,0x61,0x10},{0x7c,0x77,0x21,0xb6},{0x3d,0x9e,0x6e,0x89}};

unsigned char tab_mixCol[4][4] = {{0x02,0x03,0x01,0x01},{0x01,0x02,0x03,0x01},{0x01,0x01,0x02,0x03},{0x03,0x01,0x01,0x02}};
unsigned char Inv_tab_mixCol[4][4] = {{0x0e,0x0b,0x0d,0x09},{0x09,0x0e,0x0b,0x0d},{0x0d,0x09,0x0e,0x0b},{0x0b,0x0d,0x09,0x0e}};

unsigned char tmp[4][4] = {{0,0,0,0},{0,0,0,0}, {0,0,0,0}, {0,0,0,0}};


	//multiplication des matrices dans une matrice temporaire
	for (int i = 0; i<4; i++)
    {
    	for(int j = 0; j<4; j++ )
    	{
     		for (int s = 0; s<4 ; s++)
     		{	
     			if()
     			tmp[i][j] = tmp [i][j] ^ tab_mixCol[i][s] ^ Inv_tab_mixCol[s][j]^0x1b;
     		}
     	}
    }

   	affichage(tmp);


}