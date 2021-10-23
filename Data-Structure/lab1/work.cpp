# include <bits/stdc++.h>

using namespace std;

int gcd(int x,int y){return y? gcd(y,x%y):x;} // 通过辗转相除法求分子和分母的最大公约数从而实现约分通分

struct fraction{ // 分数的结构体 
	int numerator,denominator,flag; // 分别为分子、分母、正负号。
	fraction(){numerator = 0, denominator = 1; flag=0;} // 构造函数初始化
	fraction(int _nume,int _deno){numerator = abs(_nume),denominator = _deno,flag = numerator ? _nume/numerator : 0;}
	
	fraction simplify() // 约分函数
	{
		if (!numerator) denominator = 1;
		else
		{
			int p = gcd(numerator,denominator); // 求得分子分母的最大公约数 
			numerator /= p;
			denominator /= p;
		}
		return *this;
	}
	
	fraction operator + (const fraction& a) const{ // 重载两个分数的加法 
		int p = gcd(denominator,a.denominator); // 求出两个分数的分母的最大公约数用来实现通分 
		fraction ret = fraction(numerator*(a.denominator/p)*flag+a.numerator*(denominator/p)*a.flag,denominator*a.denominator/p);
		return ret.simplify();
	}
	
	fraction operator - (const fraction& a) const{// 重载两个分数的减法 
		int p = gcd(denominator,a.denominator);
		fraction ret = fraction(numerator*(a.denominator/p)*flag-a.numerator*(denominator/p)*a.flag,denominator*a.denominator/p);
		return ret.simplify();
	}
	
	fraction operator * (const fraction& a) const{//重载两个分数的乘法 
		fraction ret = fraction(numerator*a.numerator*flag*a.flag,denominator*a.denominator);
		return ret.simplify();
	}
	
	fraction operator / (const fraction& a) const{//重载两个分数的除法 
		fraction ret = fraction(numerator*a.denominator*flag*a.flag,denominator*a.numerator);
		return ret.simplify();
	}
	
	double operator * (const double& a) const { // 重载一个分数和一个双精度浮点数的乘法 
		return 1.0*numerator*a/denominator*flag;
	}
};

struct ele{ // 定义多项式中每一项的结构体 
	fraction coefficient; // 分数形式的系数 
	int power; // 次幂 
	ele *nxt; // 该项所在多项式中的下一项 
	ele(){};
	ele(int _numer,int _denom,int _power){coefficient = fraction(_numer,_denom),power = _power; nxt = NULL;}
	ele(fraction _ceof,int _power){coefficient = _ceof,power = _power; nxt = NULL;}
	// 两种不同参数的构造函数 
};   

struct polynomial{ // 定义多项式的结构体 
	ele *base;// 该多项式的最高次项 
	polynomial(){base = new ele(0,1,0);} // 构造函数初始化 
	
	void change(ele to) // 向当前多项式加上to这一项 
	{
		if (!to.coefficient.numerator) return; // 加的项为0则返回 
		ele *now = this -> base,*pre = NULL;
		while (now != NULL && now->power > to.power) pre = now,now = now->nxt;
		if (now == NULL || now -> power < to.power) // 若原本不存在与to同次幂的项 
		{
			ele *it = new ele; // 新建项 
			*it = to;
			if (pre != NULL) pre -> nxt = it;
			else base = it;
			it -> nxt = now;
			it -> coefficient.simplify();
		}
		
		else // 若原本就存在该次幂的项 
		{
			now -> coefficient = now -> coefficient + to.coefficient;
			if (!now -> coefficient.numerator && now -> power) 
			{
				if (pre == NULL) this -> base  = now -> nxt;
				else pre -> nxt = now -> nxt;
				delete(now);
			}
		}
	}
	
	polynomial operator + (const polynomial& a) const // 重载多项式加法 
	{
		polynomial ret;
		ele *nowa = base,*nowb = a.base,*now = new ele;
		while (nowa != NULL && nowb != NULL) // 按照将次分别加入 
		{
			if (nowa->power > nowb->power) *now = *nowa,nowa = nowa->nxt;
			else if (nowa->power < nowb->power) *now = *nowb,nowb = nowb->nxt;
			else *now = ele(nowa->coefficient+nowb->coefficient,nowa->power),nowa = nowa->nxt,nowb = nowb->nxt;
			ret.change(*now);
		}
		delete(now);
		while (nowa != NULL) ret.change(*nowa),nowa = nowa->nxt;
		while (nowb != NULL) ret.change(*nowb),nowb = nowb->nxt;
		return ret;
	}
	
	polynomial operator - (const polynomial& a) const //重载多项式的减法 
	{
		polynomial ret;
		ele *nowa = base,*nowb = a.base,*now = new ele;
		while (nowa != NULL && nowb != NULL)
		{
			if (nowa->power > nowb->power) ret.change(*nowa),nowa = nowa->nxt;
			else if (nowa->power < nowb->power)
			{
				*now = *nowb;
				now -> coefficient.flag *= -1;
				ret.change(*now);
				nowb = nowb->nxt;
			}
			else
			{
				*now = ele(nowa->coefficient-nowb->coefficient,nowa->power),nowa = nowa->nxt,nowb = nowb->nxt;
				ret.change(*now);
			}
		}
		
		while (nowa != NULL) ret.change(*nowa),nowa = nowa->nxt;
		while (nowb != NULL) 
		{
			*now = *nowb;
			now->coefficient.flag *= -1;
			ret.change(*now);
			nowb = nowb->nxt;
		}
		delete now;
		return ret;
	}
	
	polynomial operator * (const polynomial& a) const // 重载多项式的乘法 
	{
		polynomial ret;
		ele *nowa = base,*nowb,*now = new ele;
		while (nowa != NULL)
		{
			nowb = a.base;
			while (nowb != NULL) ret.change(ele(nowa->coefficient*nowb->coefficient,nowa->power+nowb->power)),nowb = nowb->nxt;
			// 使得两多项式中的任意两项均相乘后加入结果 
			nowa = nowa->nxt;
		}
		return ret;
	}
	
	pair <polynomial,polynomial> operator / (const polynomial& a) const // 使用二元组的形式重载多项式除法，从而可以同时返回商多项式和余数多项式 
	{
		polynomial ret,res=*this,*b = new polynomial;
		while (res.base -> power >= a.base -> power)
		{
			ele *now;
			*b = a;
			polynomial ex;
			ex.change(ele(res.base->coefficient/b->base->coefficient,res.base->power-b->base->power));
			*b = *b*ex;
			res = res-(*b);
			ret.change(*(ex.base));
		}
		// 按照多项式除法的法则计算结果 
		return make_pair(ret,res);
	}
	
	polynomial derivative(int k){ //求k次导函数 
		polynomial ret;
		ele *now = this -> base;
		while (now != NULL && now->power >= k)
		{
			fraction x=now->coefficient;
			for (int i=now->power; i>=now->power-k+1; -  -i) x = x*fraction(i,1);
			ret.change(ele(x,now->power-k));
			now = now->nxt;
		}// 按照多项式求导法则求导 
		return ret;
	}
	
	void print(){ // 打印多项式 
		ele *now = base;
		if (now -> power == 0) //  
		{
			if (now->coefficient.denominator != 1) printf("%d/%d",now->coefficient.numerator*now->coefficient.flag,now->coefficient.denominator);
			else printf("%d",now->coefficient.numerator*now->coefficient.flag); // 识别整数或分数 
			printf("\n");
			return;
		}
		bool flag = 0;
		while (now != NULL)
		{              
			if (now->coefficient.numerator == 0 && flag) break;
			if (!flag) // 判断是不是要输出的第一项 
			{
				flag = 1;
				if (now -> coefficient.flag < 0) printf("-"); // 第一项为正不管，为负输出符号 
			}
			else
			{
				if (now -> coefficient.flag > 0) printf("+ "); // 除第一项外，根据正负确定输出的符号为加号减号。 
				else printf("- ");
			}

			if (now->coefficient.denominator != 1) printf("%d/%d",abs(now->coefficient.numerator),now->coefficient.denominator); // 系数是分数的输出形式 
			else if (!now->power) printf("%d",abs(now->coefficient.numerator)); // 
			else if (now->coefficient.numerator != 1) printf("%d",abs(now->coefficient.numerator));	 // 系数为整数的输出形式。 
			
			if (now->power > 1) printf("x^%d ",now->power); // 当前项次数高于1的输出形式 
			else if (now->power == 1) printf("x ",now->power); // 当前项次数等于1时只输出x 
			else printf(" "); //常数项输出形式 
			now = now -> nxt;
		}
		printf("\n");
	}
	
	void scan(){ // 输入多项式 
		int n,x,y,z;
		scanf("%d",&n);
		for (int i=1; i<=n; ++i) scanf("%d%d%d",&x,&y,&z),change(ele(x,y,z)); 
	}
	
	double calc(double x){ // 计算x不同取值下的函数值 
		double ret = 0;
		ele *now = this->base;
		while (now != NULL)
		{
			double sum = 1;
			for (int i=1; i<=now->power; ++i) sum *= x;
			ret += now->coefficient*sum;
			now = now->nxt;
		}
		return ret;
	}
};

int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	polynomial x,y;
	printf("不等式A为："); 
	x.scan(); x.print();
	printf("不等式B为：");
	y.scan(); y.print();
	printf("\nA+B为：");
	(x+y).print();
	printf("\nA-B为：");
	(x-y).print();
	printf("\nA*B为：");
	(x*y).print();
	pair <polynomial,polynomial> now = x/y;
	printf("\nA/B的商多项式为：");
	now.first.print();
	printf("A/B的余数多项式为：");
	now.second.print();
	printf("验证结果：");
	(now.first*y+now.second).print();
	
	printf("\n");
	for (int i=0; i<=5; ++i)
	{
		printf("A多项式的%d阶导数为：",i);
		x.derivative(i).print();
	}
	printf("\n");
	
	printf("当原函数中自变量取值为1时，多项式A取值为%.3lf\n",x.calc(1));
	printf("当原函数中自变量取值为2时，多项式A取值为%.3lf\n",x.calc(2));
	printf("当原函数中自变量取值为3时，多项式A取值为%.3lf\n",x.calc(3));
}

