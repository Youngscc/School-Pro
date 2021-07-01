#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define LL long long

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

int main(){
	if (int_size_is_32()) printf("It's 32-bit\n");
	else printf("It's not 32-bit\n");
	return 0;
}

