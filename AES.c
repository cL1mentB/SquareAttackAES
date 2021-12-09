#include <stdio.h>
#include <string.h>

int main(){

	unsigned char * a = "0x6bc1bee22E409F96e93d7e117393172a";
    for(int i=0; i<16; i++){
    	printf("%02.2x\n", a[i]);
    }
}