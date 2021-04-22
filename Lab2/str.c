#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char cstr[100]="1111111111-Youngsc";
char *pstr="1111111111-Youngsc";

int main(int argc, char *argv[]) {
    printf("cstr:%s\n",cstr);
    printf("pstr:%s\n",pstr);
    // strcpy(cstr,"1111111111111111111");
    strcpy(pstr,"111111111111111111"); 
    // printf("cstr:%s\n",cstr);
    printf("pstr:%s\n",pstr);
    return 0;
}