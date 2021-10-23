# include <bits/stdc++.h>
# define LL long long
# define MAXM 100
# define MAXN 30

using namespace std;

int n,m,v[MAXN];
queue <int> q;
struct edge{int x,y;}ed[MAXM];

struct Matrix{
	
	int matrix[MAXN][MAXN];
	
	Matrix(){
		memset(matrix,0,sizeof(matrix));
	}
	
	void clear(){
		memset(matrix,0,sizeof(matrix));
	}
	
	void Show(){
		printf("  邻接矩阵为：\n    ");
		for (int i=1; i<=n; ++i) printf("%3d",i);
		printf("\n   -----------------------------------\n");
		for (int i=1; i<=n; ++i,printf("\n"))
		{
			printf("%2d |",i);
			for (int j=1; j<=n; ++j) printf("%3d",matrix[i][j]);
		}
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	void Make(){
		for (int i=1; i<=m; ++i) 
			matrix[ed[i].x][ed[i].y] = matrix[ed[i].y][ed[i].x] = 1;
		Show();
	}
	
	void dfs(int x){
		for (int i=1; i<=n; ++i)
		{
			if (!matrix[x][i] || v[i]) continue;
			v[i] = x;
			dfs(i);
		}
	}
	
	void Dfs_rec(){
		memset(v,0,sizeof(v));
		for (int i=1; i<=n; ++i)
		{
			if (!v[i])
			{
				v[i] = -1;
				dfs(i);
				v[i] = 0;
			}
		}
		printf("在基于邻接矩阵的递归深搜树中，各点的父亲节点分别为："); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// 若父节点为0则该点为其所在dfs树中的根节点 
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	void Dfs_Norec(){
		memset(v,0,sizeof(v));
		int mem[MAXN],st[MAXN],top=0;
		for (int i=1; i<=n; ++i) mem[i] = 1; 
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			v[i] = -1;
			st[++top] = i;
			while (top)
			{
				int x = st[top];
				for (int j=mem[x]; j<=n; ++j,mem[x]=j) // 从上一次枚举到的节点开始枚举，优化算法效率
				{
					if (v[j] || !matrix[x][j]) continue;
					st[++top] = j;
					v[j] = x;
					break;
				}
				if (mem[x] == n+1) top--;
			}
			v[i] = 0;
 		} 
 		printf("在基于邻接矩阵的非递归深搜树中，各点的父亲节点分别为："); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// 若父节点为0则该点为其所在dfs树中的根节点 
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	void BFS(int s){
		q.push(s);
		v[s] = 1;
		while (!q.empty())
		{
			int x=q.front();
			printf("%d ",x);
			q.pop();
			for (int i=1; i<=n; ++i)
			{
				if (v[i] || !matrix[x][i]) continue;
				v[i] = 1;
				q.push(i);
			}
		}
	}
	
	void bfs(){
		memset(v,0,sizeof(v));
		printf("基于邻接矩阵的广度优先算法中，生成序列为：");
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			BFS(i);
		}
		printf("\n ------------ 输出结束 ---------------\n\n");
	} 
}mat;

struct List{
	
	vector <int> list[MAXN];
	
	void clear(){
		for (int i=1; i<=n; ++i) list[i].clear();
	}
	
	void Show(){
		printf("  邻接表为：\n");
		for (int i=1; i<=n; ++i,printf("\n"))
		{
			printf("%2d: ",i);
			for (auto x:list[i])
				printf("%4d",x);
		}
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	
	void Make(){
		for (int i=1; i<=n; ++i) list[i].clear();
		for (int i=1; i<=m; ++i)
		{
			list[ed[i].x].push_back(ed[i].y);
			if (ed[i].x != ed[i].y)	list[ed[i].y].push_back(ed[i].x);
		}
		Show();
	}
	
	void dfs(int x){
		for (auto t:list[x])
		{
			if (v[t]) continue;
			v[t] = x;
			dfs(t);
		}
	}
	
	void Dfs_rec(){
		memset(v,0,sizeof(v));
		for (int i=1; i<=n; ++i)
		{
			if (!v[i])
			{
				v[i] = -1;
				dfs(i);
				v[i] = 0;
			}
		}
		printf("在基于邻接表的深搜树中，各点的父亲节点分别为："); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// 若父节点为0则该点为其所在dfs树中的根节点
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	void Dfs_Norec(){
		memset(v,0,sizeof(v));
		int st[MAXN],top=0,mem[MAXN]={0};
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			v[i] = -1;
			st[++top] = i;
			while (top)
			{
				int x = st[top];
				for (int j=mem[x]; j<list[x].size(); ++j,mem[x]=j) // 从上一次枚举到的节点开始枚举，优化算法效率 
				{
					if (v[list[x][j]]) continue;
					st[++top] = list[x][j];
					v[list[x][j]] = x;
					break;
				}
				if (mem[x] == list[x].size()) top--;
			}
			v[i] = 0;
 		} 
 		printf("在基于邻接表的非递归深搜树中，各点的父亲节点分别为："); 
		for (int i=1; i<=n; ++i) printf("%d ",v[i]);
		// 若父节点为0则该点为其所在dfs树中的根节点 
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	void BFS(int s){
		q.push(s);
		v[s] = 1;
		while (!q.empty())
		{
			int x=q.front();
			printf("%d ",x);
			q.pop();
			for (auto i:list[x])
			{
				if (v[i]) continue;
				v[i] = 1;
				q.push(i);
			}
		}
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
	
	void bfs(){
		memset(v,0,sizeof(v));
		printf("基于邻接表的广度优先算法中，生成序列为：");
		for (int i=1; i<=n; ++i)
		{
			if (v[i]) continue;
			BFS(i);
		}
	} 
}lst;


void MatrixToList(Matrix& mat,List& lst){
	for (int i=1; i<=n; ++i) lst.list[i].clear();
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			if (mat.matrix[i][j])
				lst.list[i].push_back(j);
	
	lst.Show();
}

void ListToMatrix(List &lst,Matrix &mat){
	mat.clear();
	for (int i=1; i<=n; ++i)
		for (auto x:lst.list[i])
			mat.matrix[i][x] = 1;
	mat.Show();
}

int main(){
	freopen("undir.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; ++i) scanf("%d%d",&ed[i].x,&ed[i].y);
	printf("文件读取数据完成!\n");
	freopen("CON","r",stdin);
	while (1)
	{
		int opt,op;
		printf("\n\n请选择储存方式： 1、邻接矩阵    2、邻接表\n");
		scanf("%d",&opt);
		if (opt == 1) mat.Make();
		else if (opt == 2) lst.Make();
		else
		{
			printf("输入有误，请检查后重新输入！\n");
			continue;
		}
		while (1)
		{
			printf("\n\n                         请选择操作：  \n            1、递归深搜并输出深搜树的各节点父节点\n            2、非递归深搜并输出深搜树的各节点父节点\n");
			printf("            3、宽搜并输出序列\n            4、输出另一种储存方式\n            5、更改当前储存方式\n\n"); 
			scanf("%d",&op);
			if (opt == 1)
			{
				if (op == 1) mat.Dfs_rec();
				else if (op == 2) mat.Dfs_Norec();
				else if (op == 3) mat.bfs();
				else if (op == 4) MatrixToList(mat,lst);
				else if (op == 5) break;
				else printf("输入有误，请检查后重新输入！\n");
			} 
			
			if (opt == 2)
			{
				if (op == 1) lst.Dfs_rec();
				else if (op == 2) lst.Dfs_Norec();
				else if (op == 3) lst.bfs();
				else if (op == 4) ListToMatrix(lst,mat);
				else if (op == 5) break;
				else printf("输入有误，请检查后重新输入！\n");
			} 
		}
	}
}
