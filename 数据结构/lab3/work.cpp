# include <bits/stdc++.h>
# define MAXN 30
# define inf 1000000000
using namespace std; 
 
struct edge{
 	int to,val;
 	edge(){to = val = 0;}
 	edge(int _to,int _val){to = _to,val = _val;}
};

struct Graph{
	vector <edge> List[MAXN];
	int n,m;
	bool isRec;
	Graph(){n=m=isRec=0;}
}gra,rgra;

struct Heap{
	int size;
	pair <int,int> queue[MAXN];
	Heap()         //初始化 
	{
		size=0;
	}
	void shift_up(int i)
	{
		while(i>1)
		{
			if(queue[i]<queue[i>>1]) swap(queue[i],queue[i>>1]);
	        i>>=1;
	    }
	}
	
	void shift_down(int i)   //下沉 
	{
		while ((i<<1)<=size)
		{
			int next=i<<1;
			if (next<size && queue[next+1]<queue[next]) next++;
			if (queue[i]>queue[next])
			{
				swap(queue[i],queue[next]);
				i=next;
			}
			else return;
		}
	}
    void push(pair <int,int> x)   //加入元素 
    {
        queue[++size]=x;
        shift_up(size);
    }
    
	void pop()         //弹出操作 
    {
        swap(queue[1],queue[size]);
        size--;
        shift_down(1);
    }
    
	pair <int,int> top(){return queue[1];}
    bool empty(){return !size;} 
     
}q;
 
void Input(){
	freopen("dir.txt","r",stdin);
	scanf("%d%d",&gra.n,&gra.m);
	rgra.n = gra.n;
	rgra.m = gra.m;
	rgra.isRec = 1;
 	int x,y,z;
 	for (int i=1; i<=gra.m; ++i)
 	{
 		scanf("%d%d%d",&x,&y,&z);
 		gra.List[x].push_back(edge(y,z));
 		rgra.List[y].push_back(edge(x,z));
	}
	printf("数据读取完毕！\n");
	freopen("CON","r",stdin);
}

namespace DIJ{
	int dis[MAXN],pre[MAXN],s;
	
	void print(int x){
		if (x == -1) return;
		print(pre[x]);
		printf("%d-->",x);
	}
	
	void Dijkstra(int s,Graph &G){
		for (int i=1; i<=G.n; ++i) dis[i] = inf,pre[i] = 0;
		pre[s] = -1;
		dis[s] = 0;
		q.push(make_pair(dis[s],s));
		while (!q.empty())
		{
			int now=q.top().second,nowdis=q.top().first;
			q.pop();
			if (dis[now] != nowdis) continue;
			for (auto x:G.List[now])
			{
				if (dis[x.to] <= dis[now]+x.val) continue;
				dis[x.to] = dis[now]+x.val;
				pre[x.to] = now;
				q.push(make_pair(dis[x.to],x.to));
			}
		}
	}
	
	void doit(int x,Graph &G){
		if (dis[x] == inf)
		{
			if (!G.isRec) printf("源点%d到点%d不可达\n",s,x);
			else printf("点%d到终点%d不可达\n",x,s);
			return;
		}
		if (!G.isRec) printf("源点%d到点%d的最短距离为：",s,x);
		else printf("点%d到终点%d的最短距离为：",x,s);
		printf("%d\n",dis[x]);
		if (!G.isRec)
		{
			printf("源点%d到点%d的最短路径为：",s,x);
			print(pre[x]);
			printf("%d\n",x);
		}
		else
		{
			printf("点%d到终点%d的最短路径为：",x,s);
			int now = x;
			while (now != s)
			{
				printf("%d->",now);
				now = pre[now];
			}
			printf("%d\n",s);
		}
		
		printf("---------------输出完毕----------------\n\n");
	} 
	
	bool qury(Graph &G){
		int x;
		printf("请输入要查询的点的编号，返回请输入-1,全部输出请输入0\n");
		scanf("%d",&x);
		if (x == -1) return 0;
		if (x == 0)
		{
			for (int i=1; i<=G.n; ++i) doit(i,G);
			return 1;
		}
		if (x > G.n||x < 1)
		{
			printf("输入数据超出范围，请重新输入：\n\n");
			return 1;
		}
		doit(x,G);
		return 1;
	}
	
	Main(Graph &G){
		if (!G.isRec) printf("请输入源点：\n");
		else printf("请输入终点：\n");
		scanf("%d",&s);
		while (s<1||s>G.n)
		{
			if (!G.isRec) printf("输入源点超出范围，请重新输入：\n");
			else printf("输入终点超出范围，请重新输入：\n");
			scanf("%d",&s);
		}
		Dijkstra(s,G);
		while (qury(G));
	}
}

namespace Floyed{
	int dis[MAXN][MAXN];
	Make_Matrix(Graph &G){
		for (int i=1; i<=G.n; ++i)
			for (int j=1; j<=G.n; ++j)
			{
				if (i == j) dis[i][j] = 0;
				else dis[i][j] = inf;
			}
			
		for (int i=1; i<=G.n; ++i)
			for (auto x:G.List[i])
				dis[i][x.to] = min(x.val,dis[i][x.to]);
		
		for (int k=1; k<=G.n; ++k)
			for (int i=1; i<=G.n; ++i)
				for (int j=1; j<=G.n; ++j)
					dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
	}
	
	void qury(int s,int t,Graph &G){
		if (dis[s][t] == inf)
		{
			printf("点%d到点%d无法到达\n",s,t); 
			return;
		}
		printf("点%d到点%d的最短距离是：%d\n",s,t,dis[s][t]);
		printf("点%d到点%d的最短路径是：\n",s,t);
		int now = s;
		while (now != t){
			printf("%d->",now);
			for (int i=1; i<=G.n; ++i)
			{
				if (i == now) continue;
				if (dis[now][i]+dis[i][t] == dis[now][t])
				{
					now = i;
					break;
				}
			}
		}
		printf("%d\n",now);
	}
	
	void Main(Graph &G){
		Make_Matrix(G);
		int s,t;
		while (1)
		{
			printf("请输入要查询路径的起点，输入-1退出：\n");
			scanf("%d",&s);
			if (s == -1) break;
			while (s<1 || s>G.n)
			{
				printf("输入数据超出范围，请重新输入：");
				scanf("%d",&s);
			}
			printf("请输入要查询路径的终点：\n");
			scanf("%d",&t);
			while (t<1 || t>G.n)
			{
				printf("输入数据超出范围，请重新输入：");
				scanf("%d",&t);
			}
			qury(s,t,G);
		}
	}
	
	void Main2(Graph &G){
		Make_Matrix(G);
		int s,t;
		while (1)
		{
			printf("请输入点对中的第一个点，输入-1退出：\n");
			scanf("%d",&s);
			if (s == -1) break;
			while (s<1 || s>G.n)
			{
				printf("输入数据超出范围，请重新输入：");
				scanf("%d",&s);
			}
			printf("请输入点对中的另一点：\n");
			scanf("%d",&t);
			while (t<1 || t>G.n)
			{
				printf("输入数据超出范围，请重新输入：");
				scanf("%d",&t);
			}
			qury(s,t,G);
			qury(t,s,G);
			printf("---------------输出完毕----------------\n\n");
		}
	}
	
	void Main3(Graph &G){
		memset(dis,0,sizeof(dis));
		for (int i=1; i<=G.n; ++i)
			for (auto x:G.List[i])
				dis[i][x.to] = 1;
		
		for (int i=1; i<=G.n; ++i) dis[i][i] = 1;
		
		for (int k=1; k<=G.n; ++k)
			for (int i=1; i<=G.n; ++i)
				for (int j=1; j<=G.n; ++j)
					dis[i][j] |= (dis[i][k]&dis[k][j]);
		
		printf("  可达矩阵为：\n    ");
		for (int i=1; i<=G.n; ++i) printf("%3d",i);
		printf("\n   -----------------------------------\n");
		for (int i=1; i<=G.n; ++i,printf("\n"))
		{
			printf("%2d |",i);
			for (int j=1; j<=G.n; ++j) printf("%3d",dis[i][j]);
		}
		printf("\n ------------ 输出结束 ---------------\n\n");
	}
}

int main()
{
 	Input();
 	while (1)
 	{
 		int opt;
 		printf(" ------------------- 功能选择 --------------------\n");
 		printf("            1、求给定起点的最短路径\n");
 		printf("            2、求任意两点间的最短路径\n");
 		printf("            3、求给定终点的最短路径\n");
 		printf("            4、求给定点对的最短路径\n");
 		printf("            5、求可达矩阵\n");
 		scanf("%d",&opt);
		if (opt == 1) DIJ::Main(gra);
		else if (opt == 2) Floyed::Main(gra);
		else if (opt == 3) DIJ::Main(rgra);
		else if (opt == 4) Floyed::Main2(gra);
		else if (opt == 5) Floyed::Main3(gra); 
		else printf("输入序号错误，请重新输入：");
	}	
    return 0;
}

