#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int x;
int main(int argc, char *argv[]){
    float y;
    static char z[256]={0};
    assert(argc == 4);
    x = atoi(argv[1]);
    y = atof(argv[2]);
    memcpy(z, argv[3], 256);
    printf("%d\n%f\n%s\n",x,y,z);
}
