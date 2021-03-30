#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

unsigned srl(unsigned x,int k){
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	int w = sizeof(int) << 3;
	unsigned sum = ( 1 << (w-k) ) - 1;
	return xsra & sum;
}

int sra(int x,int k){
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
	int w = sizeof(int) << 3;
	int p = 1 << (w - k - 1);
	p = (p & xsrl);
	p = ~(p - 1);
	return p | xsrl;
}

int main(){
	int x = -2;
	printf("%u %d\n",srl(x,1),sra(x,1));
	return 0;
}
