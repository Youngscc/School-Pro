# include <bits/stdc++.h>
# define LL long long
# define N 101

using namespace std;

const double pi = acos(-1);

double Lagrange(double *x, double *y, int n, double X) {
    /* *x *y 为数据点， n为数据点个数-1， x为插值点*/
    double Y = 0;
    for (int k=0; k<=n; ++k) {
        double l = 1;
        for (int j=0; j<=n; ++j) {
            if (k == j) continue;
            l = l*(X-x[j])/(x[k]-x[j]);
        }
        Y += l*y[k];
    }
    return Y;
}

namespace test1 {

    double test_x1[] = {0.75, 1.75, 2.75, 3.75, 4.75};
    double test_x2[] = {-0.95, -0.05, 0.05, 0.95};
    double test_x3[] = {-4.75, -0.25, 0.25, 4.75};

    double g1(double x) {
        return 1.0 / (1.0 + x*x);
    }

    double g2(double x) {
        return exp(x);
    }

    void gen1(double *x,int n) {
        double h = 10.0/n;
        for (int i=0; i<=n; ++i) x[i] = -5+i*h;
    }

    void gen2(double *x,int n) {
        double h = 2.0/n;
        for (int i=0; i<=n; ++i) x[i] = -1+i*h;
    }

    void gen3(double *x,int n) {
        for (int i=0; i<=n; ++i) x[i] = cos((2*i+1)*pi/(2*(n+1)));
    }

    void check (double (*f)(double x), void (*gen)(double *x,int n), int n, double *test, int test_n) {
        double x[n+1],y[n+1];
        gen(x, n);
        for (int i=0; i<=n; ++i) y[i] = f(x[i]);
        printf("When n is equal to %d \n",n);
        for (int i=0; i<test_n; ++i) {
            double ans = Lagrange(x, y, n, test[i]);
            printf("x = %lf  f(x) = %lf err = %lf\n", test[i], ans, ans-f(test[i]));
        }
    }

    void Main(int opt) {
        if (opt == 1) {
            printf(" ------------------------ \n");
            printf("This is f(x) = 1/(x^2+1) \n");
            check(g1, gen1, 5, test_x1, 5);
            check(g1, gen1, 10, test_x1, 5);
            check(g1, gen1, 20, test_x1, 5);
            printf(" ------------------------ \n");
            printf("This is f(x) = e^x \n");
            check(g2, gen2, 5, test_x2, 4);
            check(g2, gen2, 10, test_x2, 4);
            check(g2, gen2, 20, test_x2, 4);
            printf(" ------------------------ \n");
        } else if (opt == 2) {
            printf(" ------------------------ \n");
            printf("This is f(x) = 1/(x^2+1) \n");
            check(g1, gen2, 5, test_x2, 4);
            check(g1, gen2, 10, test_x2, 4);
            check(g1, gen2, 20, test_x2, 4);
            printf(" ------------------------ \n");
            printf("This is f(x) = e^x \n");
            check(g2, gen1, 5, test_x3, 4);
            check(g2, gen1, 10, test_x3, 4);
            check(g2, gen1, 20, test_x3, 4);
            printf(" ------------------------ \n");
        } else if (opt == 3) {
            printf(" ------------------------ \n");
            printf("This is f(x) = 1/(x^2+1) \n");
            check(g1, gen3, 5, test_x2, 4);
            check(g1, gen3, 10, test_x2, 4);
            check(g1, gen3, 20, test_x2, 4);
            printf(" ------------------------ \n");
            printf("This is f(x) = e^x \n");
            check(g2, gen3, 5, test_x2, 4);
            check(g2, gen3, 10, test_x2, 4);
            check(g2, gen3, 20, test_x2, 4);
            printf(" ------------------------ \n");
        }
    }
}

namespace test2 {

    const double test[]={5, 50, 115, 185};
    const double x1[]={1, 4, 9};
    const double x2[]={36, 49, 64};
    const double x3[]={100, 121, 144};
    const double x4[]={169, 196, 225};

    void check(const double* gen_x, int n) {
        double x[3], y[3];
        for (int i=0; i<=2; ++i) x[i] = gen_x[i], y[i] = sqrt(x[i]);
        for (int i=0; i<4; ++i) {
            double ans = Lagrange(x, y, n, test[i]);
            printf("x = %lf  f(x) = %lf  err = %lf\n", test[i], ans, ans-sqrt(test[i]));
        }
    }

    void Main() {
        printf(" ------------------------ \n");
        printf("When use x0=1, x1=4, x2=9\n");
        check(x1, 2);
        printf(" ------------------------ \n");
        printf("When use x0=36, x1=49, x2=64\n");
        check(x2, 2);
        printf(" ------------------------ \n");
        printf("When use x0=100, x1=121, x2=144\n");
        check(x3, 2);
        printf(" ------------------------ \n");
        printf("When use x0=169, x1=196, x2=225\n");
        check(x4, 2);
        printf(" ------------------------ \n");
    }
}

int main(int argc, char** argv) {
    if (argc != 2) cerr << "Error\n";
    else if (argv[1][0] == '1') test1::Main(1);
    else if (argv[1][0] == '2') test1::Main(2);
    else if (argv[1][0] == '3') test1::Main(3);
    else if (argv[1][0] == '4') test2::Main();
    else cerr << "Error\n";
    return 0;
}