# include <bits/stdc++.h>
# define pr pair<bool,double>
# define mp make_pair

using namespace std;

const double pi = acos(-1);

namespace test1 {

    pr Newton(double x_0, double eps1, double eps2, int N, double (*f)(double x), double (*df)(double x)) {
        for (int n=1; n<=N; ++n) {
            double F = f(x_0), DF = df(x_0);
            if (fabs(F) < eps1) return mp(true, x_0);
            if (fabs(DF) < eps2) return mp(false, 0);
            double x_1 = x_0 - F/DF;
            double TOL = fabs(x_0 - x_1);
            if (TOL < eps1) return mp(true, x_1);
            x_0 = x_1;
        }
        return mp(false, 0);
    }
    
    double f1(double x) {
        return cos(x) - x;
    }

    double df1(double x) {
        return -sin(x) - 1;
    }

    double f2(double x) {
        return exp(-x) - sin(x);
    }

    double df2(double x) {
        return -exp(-x) - cos(x);
    }

    double g1(double x) {
        return x - exp(-x);
    }

    double dg1(double x) {
        return 1 + exp(-x);
    }

    double g2(double x) {
        return g1(x)*g1(x);
    }

    double dg2(double x) {
        return 2*g1(x)*dg1(x);
    }

    void Main(int opt) {
        if (opt == 1) {
            printf(" ------------------------ \n");
            printf("f(x) = cosx-x \n");
            pr ans = Newton(pi/4, 1e-6, 1e-4, 10, f1, df1);
            if (ans.first == false) printf("No result\n");
            else printf("%lf\n", ans.second);

            printf(" ------------------------ \n");
            printf("f(x) = e^(-x)-sinx \n");
            ans = Newton(0.6, 1e-6, 1e-4, 10, f2, df2);
            if (ans.first == false) printf("No result\n");
            else printf("%lf\n", ans.second);
            printf(" ------------------------ \n");
        } 
        else if (opt == 2) {
            printf(" ------------------------ \n");
            printf("f(x) = x-e^(-x) \n");
            pr ans = Newton(0.5, 1e-6, 1e-4, 10, g1, dg1);
            if (ans.first == false) printf("No result\n");
            else printf("%lf\n", ans.second);

            printf(" ------------------------ \n");
            printf("f(x) = x^2-2xe^(-x)+e^(-2x) \n");
            ans = Newton(0.5, 1e-6, 1e-4, 20, g2, dg2);
            if (ans.first == false) printf("No result\n");
            else printf("%lf\n", ans.second);
            printf(" ------------------------ \n");
        }
    }
}

namespace test2 {

    pr Newton(double x_0, double eps1, double eps2, int N, int n, double (*f)(double x, int n), double (*df)(double x, int n)) {
        for (int t=1; t<=N; ++t) {
            double F = f(x_0, n), DF = df(x_0, n);
            if (fabs(F) < eps1) return mp(true, x_0);
            if (fabs(DF) < eps2) return mp(false, 0);
            double x_1 = x_0 - F/DF;
            double TOL = fabs(x_0 - x_1);
            if (TOL < eps1) return mp(true, x_1);
            x_0 = x_1;
        }
        return mp(false, 0);
    }

    double Legendre(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return x;
        return x * Legendre(x, n-1) * (2*n-1) / n - Legendre(x, n-2) * (n-1) / n;
    }

    double DLegendre(double x, int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        return (Legendre(x, n-1) + x*DLegendre(x, n-1)) * (2*n-1) / n - DLegendre(x, n-2) * (n-1) / n;
    }

    double Laguerre(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return 1-x;
        return Laguerre(x, n-1)*(2*n-1-x) - Laguerre(x, n-2)*(n-1)*(n-1);
    }

    double DLaguerre(double x, int n) {
        if (n == 0) return 0;
        if (n == 1) return -1;
        return -Laguerre(x, n-1) + (2*n-1-x)*DLaguerre(x, n-1) - (n-1)*(n-1)*DLaguerre(x, n-2);
    }

    double Hermite(double x, int n) {
        if (n == 0) return 1;
        if (n == 1) return 2*x;
        return 2*x*Hermite(x, n-1)-2*(n-1)*Hermite(x, n-2);
    }

    double DHermite(double x, int n) {
        if (n == 0) return 0;
        if (n == 1) return 2;
        return 2*Hermite(x, n-1) + 2*x*DHermite(x, n-1) - 2*(n-1)*DHermite(x, n-2);
    }

    set <double> solve (double (*f)(double x, int n), double (*Df)(double x, int n), double l, double r, int n) {
        set <double> ret;
        ret.clear();
        int N = 50;
        while (N--) {
            double x_0 = l + (rand()%1000)*(r - l)/1000;
            pr now = Newton(x_0, 1e-6, 1e-6, 10, n, f, Df);
            if (now.first == false) continue;
            bool flag = 0;
            for (auto x:ret) 
                if (fabs(x - now.second) < 1e-4) flag = 1;
            if (!flag) ret.insert(now.second);
        }
        return ret;
    }

    void Main(){
        srand(time(0));

        set <double> ans1 = solve (Legendre, DLegendre, -1, 1, 6);
        printf("The zero point of the function Legendre is:\n");
        for (auto x:ans1) printf("%lf ",x);
        printf("\n");

        set <double> ans2 = solve (Laguerre, DLaguerre, 0, 20, 5);
        printf("The zero point of the function Laguerre is:\n");
        for (auto x:ans2) printf("%lf ",x);
        printf("\n");

        set <double> ans3 = solve (Hermite, DHermite, -3, 3, 6);
        printf("The zero point of the function Hermite is:\n");
        for (auto x:ans3) printf("%lf ",x);
        printf("\n");
    }
}

int main(int argc, char** argv) {
    if (argc != 2) cerr << "Error\n";
    else if (argv[1][0] == '1') test1::Main(1);
    else if (argv[1][0] == '2') test1::Main(2);
    else if (argv[1][0] == '3') test2::Main();
    else cerr << "Error\n";
}