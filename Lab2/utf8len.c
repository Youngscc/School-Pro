#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int utf8len(char *s) {
    int ret = 0;
    for (; *s; ++s)
        if (((*s) & 0xC0) == 0x80);
        else ret++;
    return ret;
}

int main(){
    char s[100];
    scanf("%s",s);
    printf("%d",utf8len(s));
    return 0;
}