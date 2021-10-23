# include <bits/stdc++.h>

int d[22][22];

int main(){
	freopen("undir.txt","w",stdout);
	srand(time(0));
	int n = rand()%10+10,m = rand()%20+15;
	printf("%d %d\n",n,m);
	while (m)
	{
		int x = rand()%n+1,y = rand()%n+1;
		if (d[x][y]||d[y][x]) continue;
		d[x][y] = 1;
		m--;
		printf("%d %d\n",x,y);
	}
}
