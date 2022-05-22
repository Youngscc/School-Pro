# include <bits/stdc++.h>
# define db double
# define NUM 5
using namespace std;

void RungeKutta(db a, db b, db alpha, int N, db(*f)(db x, db y), vector <pair<db, db> >& ans) {
    db x0 = a, y0 = alpha;
    db h = (b-a)/N;
    for (int i=1; i<=N; ++i) {
        db k1 = f(x0, y0);
        db k2 = f(x0+h/2, y0+h*k1/2);
        db k3 = f(x0+h/2, y0+h*k2/2);
        db k4 = f(x0+h, y0+h*k3);
        db x1 = x0+h, y1 = y0+h*(k1+2*k2+2*k3+k4)/6;
        ans.push_back(make_pair(x1, y1));
        x0 = x1, y0 = y1;
    }
    return;
}

namespace solve1{

vector <pair <db, db> > ans;

db f1(db x, db y) {return x+y;}

db f2(db x, db y) {return -y*y;}

db g1(db x) {return -x-1;}

db g2(db x) {return 1.0/(x+1);}

void Main() {
    cout << "f(x,y)=x+y" << endl;
    RungeKutta(0, 1, -1, NUM, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g1(x.first));
    ans.clear();
    cout << "f(x,y)=-y*y" << endl;
    RungeKutta(0, 1, 1, NUM, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g2(x.first));
}

}


namespace solve2{

vector <pair <db, db> > ans;

db f1(db x, db y) {return 2*y/x+x*x*exp(x);}

db f2(db x, db y) {return (y*y+y)/x;}

db g1(db x) {return x*x*(exp(x)-exp(1));}

db g2(db x) {return 2*x/(1-2*x);}

void Main() {
    cout << "f(x,y)=2*y/x+x*x*exp(x)" << endl;
    cout << "N is " << 5 << endl;
    RungeKutta(1, 3, 0, 5, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g1(x.first),x.second-g1(x.first));
    ans.clear();
    cout << "N is " << 10 << endl;
    RungeKutta(1, 3, 0, 10, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g1(x.first),x.second-g1(x.first));
    ans.clear();
    cout << "N is " << 20 << endl;
    RungeKutta(1, 3, 0, 20, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g1(x.first),x.second-g1(x.first));
    ans.clear();
    cout << "f(x,y)=(y*y+y)/x" << endl;
    cout << "N is " << 5 << endl;
    RungeKutta(1, 3, -2, 5, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g2(x.first),x.second-g2(x.first));
    ans.clear();
    cout << "N is " << 10 << endl;
    RungeKutta(1, 3, -2, 10, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g2(x.first),x.second-g2(x.first));
    ans.clear();
    cout << "N is " << 20 << endl;
    RungeKutta(1, 3, -2, 20, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g2(x.first),x.second-g2(x.first));
    ans.clear();
}

}


namespace solve3{

vector <pair <db, db> > ans;

db f1(db x, db y) {return -20*(y-x*x)+2*x;}

db f2(db x, db y) {return -20*y+20*sin(x)+cos(x);}

db f3(db x, db y) {return -20*(y-exp(x)*sin(x))+exp(x)*(sin(x)+cos(x));}

db g1(db x) {return x*x+exp(-20*x)/3;}

db g2(db x) {return exp(-20*x)+sin(x);}

db g3(db x) {return exp(x)*sin(x);}

void Main() {
    cout << "f(x,y)=-20(y-x^2)+2x" << endl;
    cout << "N is " << 5 << endl;
    RungeKutta(0, 1, 1.0/3, 5, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf err = %lf\n",x.first,x.second,g1(x.first),x.second-g1(x.first));
    ans.clear();
    cout << "N is " << 10 << endl;
    RungeKutta(0, 1, 1.0/3, 10, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g1(x.first),x.second-g1(x.first));
    ans.clear();
    cout << "N is " << 20 << endl;
    RungeKutta(0, 1, 1.0/3, 20, f1, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g1(x.first),x.second-g1(x.first));
    ans.clear();
    cout << "f(x,y)=-20y+20sin(x)+cos(x)" << endl;
    cout << "N is " << 5 << endl;
    RungeKutta(0, 1, 1, 5, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g2(x.first));
    ans.clear();
    cout << "N is " << 10 << endl;
    RungeKutta(0, 1, 1, 10, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g2(x.first));
    ans.clear();
    cout << "N is " << 20 << endl;
    RungeKutta(0, 1, 1, 20, f2, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g2(x.first));
    ans.clear();
    cout << "f(x,y)=-20(y-e^xsin(x))+e^x(sin(x)+cos(x))" << endl;
    cout << "N is " << 5 << endl;
    RungeKutta(0, 1, 0, 5, f3, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g3(x.first));
    ans.clear();
    cout << "N is " << 10 << endl;
    RungeKutta(0, 1, 0, 10, f3, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g3(x.first));
    ans.clear();
    cout << "N is " << 20 << endl;
    RungeKutta(0, 1, 0, 20, f3, ans);
    for (auto x: ans) printf("X = %lf Y = %.10lf g(x) = %.10lf\n",x.first,x.second,g3(x.first));
    ans.clear();
}

}


int main() {
    // solve1::Main();
    // solve2::Main();
    solve3::Main();
}