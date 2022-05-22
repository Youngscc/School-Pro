# include <bits/stdc++.h>
# define mp pair<double**,int>
# define mk make_pair
using namespace std;

double Romberg(double a, double b, int N, double eps, double (*f)(double x)) {
    double h = (b-a)/2, T1, T2, R1, R2, S1, S2, C1, C2, ret[50][50];
    T1 = h*(f(a)+f(b));
    ret[0][0] = T1;
    for (int i=1,ii=1; i<=N; ++i,ii<<=1) {
        double now = 0;
        for (int j=1; j<=ii; ++j) now += f(a+(j*2-1)*h);
        T2 = T1/2 + h*now;
        ret[0][i] = T2;
        S2 = (4*T2-T1)/3;
        ret[1][i] = S2;
        if (i > 1) C2 = (16*S2-S1)/15, ret[2][i] = C2;
        if (i > 2) R2 = (64*C2-C1)/63, ret[3][i] = R2;
        if (i > 3) {
            if (fabs(R2 - R1) < eps) return R2;
        }
        R1 = R2, C1 = C2, S1 = S2, T1 = T2, h /= 2;
    }
    return R2;
}


namespace test1 {

    double f1(double x) {
        return x*x*exp(x);
    }

    double f2(double x) {
        return exp(x)*sin(x);
    }

    double f3(double x) {
        return 4.0/(1+x*x);
    }

    double f4(double x) {
        return 1.0/(1+x);
    }

    void Main(){
        cerr << "When N is 3" << endl;
        printf("(1) the ans is %.10lf\n", Romberg(0, 1, 3, 1e-6, f1));
        printf("(2) the ans is %.10lf\n", Romberg(1, 3, 3, 1e-6, f2));
        printf("(3) the ans is %.10lf\n", Romberg(0, 1, 3, 1e-6, f3));
        printf("(4) the ans is %.10lf\n", Romberg(0, 1, 3, 1e-6, f4));
        cerr << "When N is 10" << endl;

        printf("(1) the ans is %.10lf\n", Romberg(0, 1, 10, 1e-6, f1));
        printf("(2) the ans is %.10lf\n", Romberg(1, 3, 10, 1e-6, f2));
        printf("(3) the ans is %.10lf\n", Romberg(0, 1, 10, 1e-6, f3));
        printf("(4) the ans is %.10lf\n", Romberg(0, 1, 10, 1e-6, f4));
        cerr << "When N is 20" << endl;

        printf("(1) the ans is %.10lf\n", Romberg(0, 1, 20, 1e-6, f1));
        printf("(2) the ans is %.10lf\n", Romberg(1, 3, 20, 1e-6, f2));
        printf("(3) the ans is %.10lf\n", Romberg(0, 1, 20, 1e-6, f3));
        printf("(4) the ans is %.10lf\n", Romberg(0, 1, 20, 1e-6, f4));
    }
}


int main(int argc, char** argv) {
    test1::Main();

}