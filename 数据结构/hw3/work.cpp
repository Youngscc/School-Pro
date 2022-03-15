# include <bits/stdc++.h>
# include <windows.h>
# include <mmsystem.h>
# define DataType int
# define MAXN 10010

using namespace std;

struct node{
	DataType data;
	int dep,id;
	node *LeftChild,*RightChild;
	node(){data = dep = id = 0; LeftChild = RightChild = NULL;}
	node(DataType dat){data = dat;  LeftChild = RightChild = NULL;} 
};

stack <node*> st;

int max_id,max_dep,sum;

void gotoxy(int y, int x) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//	HideCursor();
}

void RecPreorder (node *now){
	printf("%d ",now->data);
	if (now->LeftChild != NULL) RecPreorder(now->LeftChild);
	if (now->RightChild != NULL) RecPreorder(now->RightChild);
}

void RecMidorder (node *now){
	if (now->LeftChild != NULL) RecMidorder(now->LeftChild);
	printf("%d ",now->data);
	if (now->RightChild != NULL) RecMidorder(now->RightChild);
}

void RecPostorder (node *now){
	if (now->LeftChild != NULL) RecPostorder(now->LeftChild);
	if (now->RightChild != NULL) RecPostorder(now->RightChild);
	printf("%d ",now->data);
}

void NoRecPreorder (node* now){
	if (now == NULL) return;
	while (now != NULL || !st.empty())
	{
		while (now != NULL)
		{
			printf("%d ",now->data);
			st.push(now);
			now = now->LeftChild;
		}
		
		if (!st.empty())
		{
			now = st.top();
			st.pop();
			now = now->RightChild;
		}
	}
}

void NoRecMidorder (node *now){
	if (now == NULL) return;
	while (now != NULL || !st.empty())
	{
		while (now != NULL)
		{
			st.push(now);
			now = now->LeftChild;
		}
		
		if (!st.empty())
		{
			now = st.top();
			st.pop();
			printf("%d ",now->data);
			now = now->RightChild;
		}
	}
}

void NoRecPostorder (node *now){
	if (now == NULL) return;
	node *last=NULL;
	while (now != NULL || !st.empty())
	{
		while (now != NULL)
		{
			st.push(now);
			now = now->LeftChild;
		}
		
		if (!st.empty())
		{
			now = st.top();
			if (now->RightChild == NULL || now->RightChild == last)
			{
				printf("%d ",now->data);
				last = now;
				now = NULL;
				st.pop();			
			}
			else now = now->RightChild;
		}
	}
}

int t[MAXN];

void dfs(node *now){
	sum++;
	t[now->dep]++;
	max_id = max(max_id,now->id);
	max_dep = max(max_dep,now->dep);
	if (now->LeftChild != NULL)
	{
		now->LeftChild->id = now->id<<1;
		now->LeftChild->dep = now->dep+1;
		dfs(now->LeftChild);
	}
	if (now->RightChild != NULL)
	{
		now->RightChild->id = now->id<<1|1;
		now->RightChild->dep = now->dep+1;
		dfs(now->RightChild);
	}
}

bool IsFull(node* root){
	if (root == NULL) return 0;
	return sum == max_id;
}


int GetWidth(node* root){
	int ret = 0;
	for (int i=0; i<=max_dep; ++i) ret = max(ret,t[i]);
	return ret;
}

void dfsPrint(node* now,int max_dep,bool isLeft){
	int x,y;
	int perLength = (1<<max_dep)*4/(1<<now->dep);
	x = now->dep*2+1;
	if (now->dep == 0) y = perLength/2-1; 
	else y = (now->id-((1<<now->dep)-1)-1)*perLength+perLength/2-1;
	gotoxy(x,y); printf(" %2d ",now->data); 
	if (now->dep)
	{
		 gotoxy(x-1,y);
		 if (isLeft) printf("  /");
		 else printf("\\");
	} 
	if (now->LeftChild != NULL) dfsPrint(now->LeftChild,max_dep,1);
	if (now->RightChild != NULL) dfsPrint(now->RightChild,max_dep,0);
}

void print(node* root){
	root->id = 1;
	dfs(root);
	system("cls");
	printf("The tree is\n");
	dfsPrint(root,max_dep,0); 
	gotoxy(max_dep*2+2,0);
}

int n;
char s[10];

int main(){
	freopen("data2.txt","r",stdin); 
	scanf("%d",&n);
	node* root = new node;
	scanf("%d",&root->data);
	for (int i=2; i<=n; ++i)
	{
		node* now = root,*pre;
		bool isLeft;
		while (scanf("%s",s) != EOF)
		{
			if (!isdigit(s[0]))
			{
				if (now == NULL) printf("Wrong Input!!!"),exit(0);
				pre = now;
				if (s[0] == 'L') now = now->LeftChild,isLeft = 1;
				else now = now->RightChild,isLeft = 0;
			}
			else
			{
				now = new node;
				sscanf(s,"%d",&now->data);
				if (isLeft) pre->LeftChild = now;
				else pre->RightChild = now;
				break;
			}
		}
	}
	print(root);
	printf("先序遍历如下：\n");
	printf("  递归："); 
	RecPreorder(root);
	printf("\n");
	printf("非递归：");
	NoRecPreorder(root);
	printf("\n\n");
	printf("中序遍历如下：\n");
	printf("  递归："); 
	RecMidorder(root);
	printf("\n");
	printf("非递归：");
	NoRecMidorder(root);
	printf("\n\n");
	printf("后序遍历如下：\n");
	printf("  递归："); 
	RecPostorder(root);
	printf("\n");
	printf("非递归：");
	NoRecPostorder(root);
	printf("\n\n");
	if (IsFull(root)) puts("这是一棵完全二叉树");
	else puts("这不是一棵完全二叉树");
	printf("\n树的宽度为%d\n",GetWidth(root));
	return 0; 
}
