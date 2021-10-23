# include <stdio.h>
# include <string.h>
# include <ctype.h>

int cs_atoi(char *s){
	int x=0,f=1;
	while (*s && !isdigit(*s)){if ((*s) == '-') f = -1; s++;}
	while (isdigit(*s)) x = (x<<1)+(x<<3)+(*s)-'0', s++;
	return x*f;
}

int main(){
    char s[128];
    scanf("%s",s);
    int ret = cs_atoi(s);
    printf("%d",ret);
}