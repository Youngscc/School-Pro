# include <bits/stdc++.h>
# define MAXN 1000
# define datatype double

using namespace std;

char InfixExpression[MAXN],PostExpression[MAXN];

struct Stk{
	
	char ele[MAXN];
	int top;	
	Stk(){ top = 0; }
	
	void push(char c){ele[++top] = c;}
	
	int Length(){return top;}
	
	char pop(){
		char c = ele[top--];
		return c;
	}
	
	void print(){
		for (int i=1; i<=top; ++i) printf("%c ",ele[i]);
		printf("\n");
	}
};

// int类型栈 

struct Stk2{
	
	datatype ele[MAXN];
	int top;	
	Stk2(){ top = 0; }
	
	void push(datatype c){ele[++top] = c;}
	
	int Length(){return top;}
	
	datatype pop(){
		datatype c = ele[top--];
		return c;
	}
	
	void print(){
		for (int i=1; i<=top; ++i) printf("%.4f ",ele[i]);
		printf("\n");
	}
}sums;

void InfixToPostfix(char *str,char *toStr){
	int i=0,len=0; Stk s;
	char c;
	while (str[i] != '#') i++;
	for (i++; str[i] != '#'; ++i)
	{
		while (isdigit(str[i]) || str[i] == '.' || (str[i] == '-' && (str[i-1] == '(' || str[i-1] == '#' )))
		{
			toStr[len++] = str[i++];
			if (!isdigit(str[i]) && !(str[i] == '-' && str[i-1] == '(') && str[i] != '.')
				toStr[len++] = ' ';
		}
		
		if (str[i] == '+' || str[i] == '-')
		{
			if (!s.Length()) s.push(str[i]),s.print();
			else
			{
				do
				{
					c = s.pop(),s.print();
					if (c == '(') s.push(c),s.print();
					else toStr[len++] = c,toStr[len++] = ' ';
				}while (s.Length() && c != '(');
				s.push(str[i]);
				s.print();
			}
		}
	
		else if (str[i] == '*' || str[i] == '/')
		{
			if (!s.Length()) s.push(str[i]),s.print();
			else
			{
				do
				{
					c = s.pop(),s.print();
					if (c == '(' || c == '+' || c == '-') s.push(c),s.print();
					else toStr[len++] = c,toStr[len++] = ' ';
				}while (s.Length() && c != '(' && c != '+' && c != '-');
				s.push(str[i]);
				s.print();
			}
		}
		
		else if (str[i] == ')')
		{
			c = s.pop();
			s.print();
			while (c != '(')
			{
				toStr[len++] = c,toStr[len++] = ' ';
				c = s.pop();
				s.print();
			}
		}
		
		else if (str[i] == '^' || str[i] == '(') s.push(str[i]),s.print();
		
		else if (str[i] == '\0') break;
		
		else printf("Something wrong with the input!\n");
	}
	
	while (s.Length())
	{
		c = s.pop();
		s.print();
		toStr[len++] = c,toStr[len++] = ' ';
	}
	
	toStr[len++] = '\0';
}

datatype calc(datatype x,datatype y,char c){
	if (c == '+') return x+y;
	else if (c == '-') return x-y;
	else if (c == '*') return x*y;
	else if (c == '/') return x/y;
	else if (c == '^') return pow(x,y);
}

datatype GetValue(char *str){
	for (int i=0; str[i]!='\0'; ++i)
	{
		if (str[i] == ' ') continue;
		else if ((isdigit(str[i]) || str[i] == '.' || (str[i] == '-'&&isdigit(str[i+1]))))
		{
			datatype flag=1,nowsum=0,p=1;
			bool isbehind=0;
			while (isdigit(str[i]) || str[i] == '.' || (str[i] == '-'&&isdigit(str[i+1])))
			{
				if (str[i] == '-') flag = -1;
				else if (str[i] == '.') isbehind = 1;
				else 
				{
					if (isbehind) nowsum += (p*=0.1)*(str[i]-'0'); 
					else nowsum = nowsum*10+str[i]-'0';
				}
				i++;
			}
			sums.push(flag*nowsum);
			sums.print();
		}
		else
		{
			datatype y = sums.pop(),x = sums.pop();
			sums.push(calc(x,y,str[i]));
			sums.print();
		}
	}
	return sums.pop();
}

int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	gets(InfixExpression);
	printf("The Infix Expression is:\n");
	int i=0;
	while (InfixExpression[i] != '#') i++;
	for (i++; InfixExpression[i] != '#'; ++i) printf("%c",InfixExpression[i]);
	printf("\n"); 	
	printf("*********************-------------------------***********************\n");
	InfixToPostfix(InfixExpression,PostExpression); // 转化为后缀表达式以及栈中元素的变化情况 
	printf("*********************-------------------------***********************\n");
	printf("The Post Expression is:\n%s\n",PostExpression);
	printf("*********************-------------------------***********************\n");
	printf("%.4lf\n",GetValue(PostExpression));//根据后缀表达式计算并输出栈中元素的变化情况 
	printf("*********************-------------------------***********************\n");
}
//#-5.6*(-8+5.3^3*(-6))/(-8*2.0)+0.5#
