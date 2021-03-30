#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

int signed_high_prod(int x, int y){
	return (int) ((1LL*x*y) >> 32);
}

unsigned unsigned_high_prod(unsigned x, unsigned y){
	unsigned x_sgn = x >> 31;
	unsigned y_sgn = y >> 31;
	return signed_high_prod(x,y) + x_sgn*y + y_sgn*x;
}

int main(){
	unsigned x=0xFFFFFFFF;
	unsigned y=0xF1F1F1F1;
	printf("%u\n",unsigned_high_prod(x,y));
	return 0;
}

