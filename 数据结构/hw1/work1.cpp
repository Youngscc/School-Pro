# include <algorithm>
# include <iostream>
# include <cstdio>
# define tmp int
# define MAXN 100000

using namespace std;

namespace Seqlist{
	struct List{
		tmp l[MAXN]; int len;
		List(){ len = 0;}
		void ins(int x,tmp num)
		{
			if (x > len+1 || x <= 0)
			{
				printf("There is no such one\n");
				return;
			}
			len++;
			for (int i=len; i>x; --i) l[i] = l[i-1];
			l[x] = num;
		}
		
		void del(int x)
		{
			if (x > len || x <= 0)
			{
				printf("There is no such one\n");
				return;
			}
			for (int i=x; i<len; ++i) l[i] = l[i+1];
			len--;
		}
		
		void print(){
			for (int i=1; i<=len; ++i) printf("%d ",l[i]);
			printf("\n");
		}
		
		int isSorted(){
			bool flag1=1,flag2=1;
			for (int i=1; i<len; ++i) 
				flag1 &= (l[i+1]>=l[i]),
				flag2 &= (l[i+1]<=l[i]);
			if (flag1) return 1;
			if (flag2) return -1;
			return 0;
		}
		
		void uniq(){
			if (!isSorted())
			{
				printf("The sequence isn't sorted\n");
				return; 
			} 
			int t = 1;
			for (int i=2; i<=len; ++i)
			{
				if (l[i] == l[t]) continue;
				l[++t] = l[i];
			}
			len = t;
		}
		
		void rev(){
			for (int i=1; len+1-i>i; ++i) swap(l[i],l[len+1-i]);
		}
		
		void TurnLeft(int k){
			k %= len;
			for (int i=1; i<=k; ++i) l[len+i] = l[i];
			for (int i=k+1; i<=k+len; ++i) l[i-k] = l[i];
		}
		
		void TurnRight(int k){
			k %= len;
			for (int i=len; i; --i) l[i+k] = l[i];
			for (int i=1; i<=k; ++i) l[i] = l[i+len];
		}
		
		void mergeWith(List b){
			if (!isSorted()) printf("List a isn't sorted\n");
			if (!b.isSorted()) printf("List b isn't sorted\n");
			if (!isSorted() || !b.isSorted()) return;
			if (isSorted() != 1) rev();
			if (b.isSorted() != 1) b.rev();
			for (int i=len; i; --i) l[i+b.len] = l[i];
			int ta = b.len+1,tb = 1,t = 0;
			while (ta <= len+b.len && tb <= b.len)
			{
				if (l[ta] <= b.l[tb]) l[++t] = l[ta++];
				else l[++t] = b.l[tb++];
			}
			while (tb <= b.len) l[++t] = b.l[b.len++];
			len += b.len;
		}
	};
	
	void test1(){
		List a,b;
		int x,y,z;
		while (scanf("%d",&x) != EOF)
		{
			printf("\n顺序表操作  "); 
			if (x == 1) scanf("%d%d",&y,&z),a.ins(y,z),printf("在第%d位插入%d\n",y,z); // 在第y个位置输入z这个元素 
			else if (x == 2) scanf("%d",&y),a.del(y),printf("删去第%d个元素\n",y); // 删除第y个元素
			else if (x == 3) a.uniq(),printf("去重\n"); // 去重 
			else if (x == 4) a.rev(),printf("翻转\n"); // 翻转 
			else if (x == 5) scanf("%d",&y),a.TurnLeft(y),printf("左移%d位\n",y);
			else if (x == 6) scanf("%d",&y),a.TurnRight(y),printf("右移%d位\n",y);
			else if (x == 7)
			{
				b.ins(1,1);
				b.ins(2,3);
				b.ins(3,5);
				b.ins(4,8);
				b.ins(5,8); // 构造另一个排好序的线性表 
				printf("另一个线性表为：");
				b.print(); 
				a.mergeWith(b); // 两个表合并 
				printf("合并后为："); 
			}
			printf("当前数列：");
			a.print(); // 输出结果 
		}
	} 
};

using namespace Seqlist;

namespace Linklist{
	struct List{
		tmp data;
		List *next;
		List(){next = NULL;}
	} head;
	
	void ins (List &head,int pos,tmp x){
		List *now = &head;
		if (pos < 0)
		{
			printf("There is no such one\n");
			return;
		}
		while (pos > 1)
		{
			if (now -> next == NULL)
			{
				printf("There is no such one\n");
				return;
			}
			pos--;
			now = now -> next;
		}
		List *op = new List;
		op -> data = x;
		op -> next = now -> next;
		now -> next = op;
	}
	
	void del(List &head,int pos)
	{
		List *now = &head;
		if (pos < 0)
		{
			printf("There is no such one\n");
			return; 
		}
		while (pos>1)
		{
			if (now -> next == NULL)
			{
				printf("There is no such one\n");
				return;
			}
			pos--;
			now = now -> next;
		}
		List *it = now -> next;
		now -> next = it -> next;
		delete(it);
	}
	
	int isSorted(List head){
		List *now = head.next;
		bool flag1=1,flag2=1;
		while (now -> next != NULL)
		{
			flag1 &= ((*now).data <= (*(now->next)).data);
			flag2 &= ((*now).data >= (*(now->next)).data);
			now = now -> next;
		}
		if (flag1) return 1;
		if (flag2) return -1;
		return 0;
	}
	
	void uniq(List head){
		if (isSorted(head) == 0)
		{
			printf("This sequence isn't sorted\n");
			return;
		}
		List *now = head.next;
		while (now != NULL)
		{
			List *it = now -> next;
			while (it != NULL)
			{
				if (now -> data == it -> data) now -> next = it -> next,delete(it);
				else break;
				it = now -> next;
			}
			now = now -> next;
		}
	}
	
	void rev(List &head){
		List *x = head.next;
		if (x == NULL) return;
		List *y = x->next, *z;
		x -> next = NULL;
		while (y != NULL){
			z = y -> next;
			y -> next = x;
			x = y;
			y = z;
		}
		head.next = x;
	}
	
	int getLength(List head){
		int ret = 0;
		List *now = &head;
		while (now -> next != NULL){
			ret++;
			now = now -> next;
		}
		return ret;
	}
	
	void turnLeft(int k,List &head){
		List *x = head.next;
		if (x == NULL) return;
		int len = getLength(head);
		k %= len;
		if (!k) return;
		while (k > 1)
		{
			k--;
			x = x->next;
		}
		List *last = head.next;
		while (last -> next != NULL) last = last -> next;
		last -> next = head.next,head.next = x -> next;
		x -> next = NULL;
	}
	
	void turnRight(int k,List &head){
		int len = getLength(head);
		k %= len;
		turnLeft(len-k,head);
	}
	
	void print(List head){
		List *now = &head;
		while (now -> next != NULL)
		{
			now = now -> next;
			printf("%d ",(*now).data);
		}
		printf("\n");
	}
	
	void Merge(List &a,List &b){
		if (!isSorted(a)) printf("List a isn't sorted\n");
		if (!isSorted(b)) printf("List b isn't sorted\n");
		if (!isSorted(a) || !isSorted(b)) return;
		if (isSorted(a) != 1) rev(a);
		if (isSorted(b) != 1) rev(b);
		List *head = new List;
		List *x = a.next,*y = b.next,*now = head;
		while (x != NULL && y != NULL)
		{
			if ((*x).data <= (*y).data) now -> next = x,x = x -> next;
			else now -> next = y,y = y -> next;
			now = now -> next;
		}
		
		if (x != NULL) now -> next = x;
		if (y != NULL) now -> next = y;
		
		a = *head;
		return;
	}
	
	void test2(){
		List head,headb;
		int x,y,z;
		while (scanf("%d",&x) != EOF)
		{
			printf("\n链式表操作  "); 
			if (x == 1) scanf("%d%d",&y,&z),ins(head,y,z),printf("在第%d位插入%d\n",y,z); // 在第y个位置输入z这个元素 
			else if (x == 2) scanf("%d",&y),del(head,y),printf("删去第%d个元素\n",y); // 删除第y个元素
			else if (x == 3) uniq(head),printf("去重\n"); // 去重 
			else if (x == 4) rev(head),printf("翻转\n"); // 翻转 
			else if (x == 5) scanf("%d",&y),turnLeft(y,head),printf("左移%d位\n",y);
			else if (x == 6) scanf("%d",&y),turnRight(y,head),printf("右移%d位\n",y);
			else if (x == 7)
			{
				ins(headb,1,1);
				ins(headb,2,3);
				ins(headb,3,5);
				ins(headb,4,8);
				ins(headb,5,8); // 构造另一个排好序的线性表 
				printf("另一个线性表为：");
				print(headb); 
				Merge(head,headb); // 两个表合并 
				printf("合并后为："); 
			}
			printf("当前数列："); 
			print(head); // 输出结果 
		}
	} 
}

using namespace Linklist;

int main(){
	
	int opt;
	
	freopen("test1.in","r",stdin);
//	freopen("test1.out","w",stdout);
	
	
	printf("输入1：顺序储存结构，2：链式储存结构\n");
	scanf("%d",&opt);
	
	if (opt == 1) Seqlist::test1();
	else Linklist::test2();

}
/*
1 
1 1 2
1 2 3
1 3 4
1 4 7
1 5 7
1 6 9
1 3 7
4
2 5
4
3
1 5 7
5 3
6 2
5 5
7
*/ 
