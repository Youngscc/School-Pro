//《深入理解计算机系统》第二章作业

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

/*
	-------------------   2.59   -------------------
*/

int didit(int x,int y){
	return ( (x & 0xFF) | (y & 0xFFFFFF00) );
}

void solve_2_59(){
	int x=0x89ABCDEF,y=0x76543210;
	printf("0x%X\n",didit(x,y));
}

/*
	-------------------   2.63   -------------------
*/

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

void solve_2_63(){
	int x = -2;
	printf("%u %d\n",srl(x,1),sra(x,1));
}

/*
	-------------------   2.65   -------------------
*/

int odd_ones(unsigned x){
	x ^= (x>>16);
	x ^= (x>>8);
	x ^= (x>>4);
	x ^= (x>>2);
	x ^= (x>>1);
	return x&1;
}

void solve_2_65(){
	puts("Input the number:");
	unsigned x;
	scanf("%u",&x);
	if (odd_ones(x)) puts("x contains an odd number of 1s");
	else puts("x doesn't contain an odd number of 1s");
}

/*
	-------------------   2.67   -------------------
*/

/*
    A、一次左移时左移的位数不能超过当前数据类型的位数 
*/

int int_size_is_32(){
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;
	return set_msb && !beyond_msb;
}

int int_size_is_32_for16bit(){
	int set_msb = 1 << 15;
	set_msb <<= 15;
	set_msb <<= 1;
	int beyond_msb = set_msb << 1;
	return set_msb && !beyond_msb;
}

void solve_2_67(){
	if (int_size_is_32()) printf("It's 32-bit\n");
	else printf("It's not 32-bit\n");
}

/*
	-------------------   2.71   -------------------
*/

/*
	A、因为我们每一个字节是有符号字节，我们从unsigned中提出某一个字节的时候需要注意其符号位的正负值，再决定前边补充位数时补充0或1，而该代码默认补0，就会导致如果当前数字是个负数，补充之后会变成一个正数。 
*/

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum){
	int turnLeft = (3 - bytenum) << 3;
	int turnRight = 24;
	int num = word;
	return num << turnLeft >> turnRight;
}

void solve_2_71(){
	printf("%d\n", xbyte(0xffffffff, 2));
}

/*
	-------------------   2.75   -------------------
*/

int signed_high_prod(int x, int y){
	return (int) ((1LL*x*y) >> 32);
}

unsigned unsigned_high_prod(unsigned x, unsigned y){
	unsigned x_sgn = x >> 31;
	unsigned y_sgn = y >> 31;
	return signed_high_prod(x,y) + x_sgn*y + y_sgn*x;
}

void solve_2_75(){
	unsigned x=0xFFFFFFFF;
	unsigned y=0xF1F1F1F1;
	printf("%u\n",unsigned_high_prod(x,y));
}

/*
	-------------------   2.79   -------------------
*/

int divide_power2(int x,int k){
	int sgn = x >> 31;
	x += sgn & ((1 << k) - 1);
	return x >> k;
}

int mul3div4(int x){
	return divide_power2( (x << 1) + x , 2);
}

void solve_2_79(){
	int x = -2147483647;
	printf("%d\n",mul3div4(x));
}

/*
	-------------------   2.83   -------------------
*/

/*
	A、我们设x = 0.yyyyyyyy……，那么x<<k = y.yyyyyyyy……=x*(2^k)，即x*(2^k)=x+y，即x((2^k)-1)=y，x=y/((2^k)-1);
	x=y/((2^k)-1)
	
	B、
		a.  x = 101 / 111 = 5/7
		b.	x = 0110 / 1111 = 2/5
		c.  x = 010011 / 111111 = 19/63
*/

/*
	-------------------   2.87   -------------------
*/

/*
	-0:
		Hex : 0x8000
		M   : 0
		E   : -14
		V   : -0
		D   : -0.0
	
	最小的大于2的值:
		Hex : 0x4001
		M   : 1025/1024
		E   : 1
		V   : 1025/512
		D   : 2.001953
		
	512:
		Hex : 0x6000
		M   : 1
		E   : 9
		V   : 512
		D   : 512.0
	
	最大的非规格化数: 
		Hex : 0x03FF
		M   : 1023/1024
		E   : -14
		V   : 1023*(2^(-24))
		D   : 0.000061
		
	-oo:
		Hex : 0xFC00
		M   : --
		E   : --
		V   : -oo
		D   : -oo
		
	0x3BB0:
		Hex : 0x3BB0
		M   : 123/64
		E   : -1
		V   : 123/128
		D   : 0.960938
		
/*
	-------------------   2.91   -------------------
*/

/*
	A、 11.0010010000111111011011
	B、 11.001001001001……
	C、第9位
*/

/*
	-------------------   2.95   -------------------
*/

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

void solve_2_95(){
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

int main(){
//	solve_2_59();
//	solve_2_63();
//	solve_2_65();
//	solve_2_67();
//	solve_2_71();
//	solve_2_75();
//	solve_2_79();
//	solve_2_95();
} 
