# include <stdio.h>

int f[1000],n;

int main(){
    f[0] = 0;
    f[1] = 1;
    scanf("%d",&n);
    for (int i=2; i<=n; ++i) f[i] = f[i-1]+f[i-2];
    printf("%d",f[n]);
}