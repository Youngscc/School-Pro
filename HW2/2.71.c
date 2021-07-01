#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

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

int main(){
	printf("%d\n", xbyte(0xffffffff, 2));
	return 0;
}

