#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

int odd_ones(unsigned x){
	x ^= (x>>16);
	x ^= (x>>8);
	x ^= (x>>4);
	x ^= (x>>2);
	x ^= (x>>1);
	return x&1;
}

int main(){
	puts("Input the number:");
	unsigned x;
	scanf("%u",&x);
	if (odd_ones(x)) puts("x contains an odd number of 1s");
	else puts("x doesn't contain an odd number of 1s");
	return 0;
}

