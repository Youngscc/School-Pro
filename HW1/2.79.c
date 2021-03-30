#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

int divide_power2(int x,int k){
	int sgn = x >> 31;
	x += sgn & ((1 << k) - 1);
	return x >> k;
}

int mul3div4(int x){
	return divide_power2( (x << 1) + x , 2);
}

int main(){
	int x = -2147483647;
	printf("%d\n",mul3div4(x));
	return 0;
}
