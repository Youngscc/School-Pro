# include <stdio.h>
# define s_size 12

void good_echo(){
	char s[s_size];
	while (1) {
		char *p = fgets(s, s_size, stdin);
		if (ferror(stdin) || p == NULL) {
			puts("Something is error");
			break;
		}
		printf("%s",p);
	}
	return;
}

int main(){
	;
}

