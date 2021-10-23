#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

int didit(int x,int y){
	return ( (x & 0xFF) | (y & 0xFFFFFF00) );
}

int main(){
	int x=0x89ABCDEF,y=0x76543210;
	printf("0x%X\n",didit(x,y));
	return 0;
}

