#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

int cs_ftoa(float x, int pre, char *s) {
    char *t = s;
    if (x < 0) x = -x,*t++ = '-';
    t = t + cs_itoa((int)x , t);
    *t++ = '.';
    x -= (int) x;
    x += 5 * pow(10.0, -pre-1);
    for (int i=0; i<pre; ++i) {
        x = x*10;
        *t++ = ((int)x) + '0';
        x -= (int)x;
    }
    *t = '\0';
    return t - s;
}

int main(){
    char s[128];
    float x;
    scanf("%f",&x);
    int len = cs_ftoa(x,5,s);
    printf("%s\nlen = %d\n",s,len);
    return 0;
}