#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long


typedef unsigned float_bits;

float_bits float_half(float_bits f) {
	
	unsigned sgn = f >> 31;
	unsigned num = f & 0x7FFFFFFF;
	unsigned exp = f >> 23 & 0xFF;
	unsigned frac = f & 0x7FFFFF;
	
	if (exp == 0xFF) return f;
	int tag = (frac & 0x3) == 0x3;
	
	if (exp == 0) {
		frac >>= 1;
		frac += tag;
	} 
	
	else if (exp == 1) {
		num >>= 1;
		num += tag;
		exp = num >> 23 & 0xFF;
		frac = num & 0x7FFFFF;
	} 
	
	else exp--;
	
	return sgn << 31 | exp << 23 | frac;
}

int main(){
	float f;
	unsigned x,i;
	for (i=0; i<0xFFFFFFFF; ++i)
	{
		memcpy(&f, &i, sizeof(float));
		if (isnan(f)) continue;
		f *= 0.5;
		memcpy(&x, &f, sizeof(unsigned));
		if (float_half(i) != x) printf("%u\n",i);
	}
	
	memcpy(&f, &i, sizeof(float));
	if (isnan(f)) {
		printf("over!\n");
		return;
	}
	f *= 0.5;
	memcpy(&x, &f, sizeof(unsigned));
	if (float_half(i) != x) printf("%u\n",i);
	printf("over!\n");
}
