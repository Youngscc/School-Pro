# include <bits/stdc++.h>
# define R register
# define DataType int

using namespace std;

struct node{
	DataType val;
	int Height;
	node *Left,*Right;
	node(){val=0,Left = Right = NULL,Height=1;}
	node(DataType _val){val=_val,Left = Right = NULL,Height=1;}
};

struct AVL{
	node *root;
	AVL(){root = NULL;}
	
    void print(node* now){
    	if (now == NULL) return;
    	print(now->Left);
    	printf("%d ",now->val);
    	print(now->Right);
	}
	
	int GetHeight(node* x){
		if (x == NULL) return 0;
		else return x->Height;
	}
		
	void Update(node* t)
    {
        if(t == NULL) return;
        t->Height = max(GetHeight(t->Left), GetHeight(t->Right)) + 1;
    }
	
	node* LeftRotate(node* t){
		node* A = t->Left;
		node* B = A->Right;
		A->Right = t;
		t->Left = B;
		Update(t->Left);
		Update(t);
		return A;
	}
	
	node* RightRotate(node* t){
		node* A = t->Right;
		node* B = A->Left;
		A->Left = t;
		t->Right = B;
		Update(t->Right);
		Update(t);
		return A;
	}
	
	node* LR(node* t){
		t->Left = RightRotate(t->Left);
		return LeftRotate(t);
	}
	
	node* RL(node* t){
		t->Right = LeftRotate(t->Right);
		return RightRotate(t);
	}
	
	void Maintain(node* &t)
    {
    	if (t == NULL) return;
        if(GetHeight(t->Left) == GetHeight(t->Right) + 2)
        {
            if(GetHeight(t->Left->Left) > GetHeight(t->Left->Right)) printf("-->结点%d进行LL旋转\n",t->val),t = LeftRotate(t);
            else printf("-->结点%d进行LR旋转\n",t->val),t = LR(t);
        }
        else if(GetHeight(t->Right) == GetHeight(t->Left) + 2)
        {
            if(GetHeight(t->Right->Right) > GetHeight(t->Right->Left)) printf("-->结点%d进行RR旋转\n",t->val),t = RightRotate(t);
            else printf("-->结点%d进行RL旋转\n",t->val),t = RL(t);
        }
        Update(t);
    }
	
	void InsertIt(node* &t,DataType x)
    {
        if(t == NULL)
        {
            t = new node(x);
            t->Height = 1;
            printf("该元素被成功添加\n");
            return;
        }
        if(t->val > x) InsertIt(t->Left,x);
        else if(t->val < x) InsertIt(t->Right,x);
        else
        {
        	printf("该元素已被添加\n");
        	return;
		}
        Maintain(t);
    }
    
    DataType AskBefore(DataType x){
    	node* now = root;
    	DataType ret;
    	while (now != NULL)
		{
			if (now->val >= x) now = now->Left;
			else ret = now->val,now = now->Right;
		 } 
    	return ret;
	}
    
    void DeleteIt(node* &t,DataType x){
    	if (t == NULL)
    	{
    		printf("未找到该元素\n");
    		return;
		}
    	if(t->val > x) DeleteIt(t->Left,x);
        else if(t->val < x) DeleteIt(t->Right,x);
        else
        {
        	if (t->Left == NULL && t->Right == NULL) t = NULL;
			else if (t->Left == NULL) t = t->Right;
			else if (t->Right == NULL) t = t->Left;
			else
			{
				DataType sum = AskBefore(t->val);
				DeleteIt(t->Left,sum);
				t->val = sum;
			}
			printf("该元素已成功删除！\n"); 
		}
        Maintain(t);
	}

	node* SearchIt(node* t,DataType x){
		if (t == NULL) return NULL;
		if (t->val < x) return SearchIt(t->Right,x);
		else if (t->val > x) return SearchIt(t->Left,x);
		else return t;
	} 

	void Insert(DataType x){InsertIt(root,x);}
	void Delete(DataType x){DeleteIt(root,x);}
	node* Search(DataType x){return SearchIt(root,x);}
	void Print(){print(root); printf("\n");}
};


int main(){
	AVL Tree;
	int opt;
	DataType x;
	while(1)
	{
		printf("------------------菜单------------------\n");
		printf("1、插入元素\n");
		printf("2、删除元素\n");
		printf("3、查找元素\n");
		printf("4、输出排序\n"); 
		printf("------------------End------------------\n");
		printf("请输入操作序号：\n");
		scanf("%d",&opt);
		if (opt == 1)
		{
			printf("请输入要插入的元素:\n");
			scanf("%d",&x);
			Tree.Insert(x);
		}
		else if (opt == 2)
		{
			printf("请输入要删除的元素:\n");
			scanf("%d",&x);
			Tree.Delete(x);
		}
		else if (opt == 3)
		{
			printf("请输入要查询的元素:\n");
			scanf("%d",&x);
			if (Tree.Search(x) != NULL) printf("查找成功，该元素存在\n");
			else printf("查找失败，该元素不存在\n");
		}
		else if (opt == 4)
		{
			printf("排序后的序列为：\n");
			Tree.Print();
		}
		else printf("输入序号有误，请重新输入：\n"); 
	} 
	return 0;
}
