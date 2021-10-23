#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cs_itoa(int x,char *s){
    if (x == 0)
    {
        *s = '0';
        return 1;
    }
    char *t = s;
    if (x < 0) *t++ = '-',x = -x;
    char rev[128];
    char *p = rev;
    while (x)
    {
        *p++ = x%10+'0';
        x /= 10;
    }
    while (p != rev) *t++ = *--p;
    *t = '\0';
    return t-s;
}

int main(){
    int x; char s[128];
    scanf("%d",&x);
    int len = cs_itoa(x,s);
    printf("%s\nlen=%d\n",s,len);
}