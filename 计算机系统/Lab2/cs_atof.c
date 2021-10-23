# include <stdio.h>
# include <string.h>
# include <ctype.h>

float cs_atof(char *s){
	float x=0,f=1,y=0.1;
	while (*s && !isdigit(*s)){if ((*s) == '-') f = -1; s++;}
	while (*s && isdigit(*s)) x = x*10+(*s)-'0', s++;
    if (*s == '.')
    {
        s++;
        while (isdigit(*s)) x += ((*s)-'0')*y, s++, y*=0.1;
    }
	return x*f;
}

int main(){
    char s[128];
    scanf("%s",s);
    float ret = cs_atof(s);
    printf("%f",ret);
    return 0;
}