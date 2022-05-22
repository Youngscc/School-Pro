# include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
int sgn(double x) {
    if (x < -eps) return -1;
    else if (x > eps) return 1;
    return 0;
}

void print(double** a, double * b, int n) {
    for (int i=1; i<=n; ++i,printf("\n")) {
        for (int j=1; j<=n; ++j)
            cerr << a[i][j] << " ";
        cerr << b[i];
        }
    printf("\n");
}

namespace solve1{

double* Gauss(int n, double ** a, double * b, bool& flag) {
    double *x = (double *) malloc((n + 1) * sizeof(double));
    for (int k=1; k<n; ++k) {
        int p = 0;
        for (int j=k; j<=n; ++j) 
            if (!p || sgn(fabs(a[j][k]) - fabs(a[p][k])) > 0) p = j;
        if (sgn(a[p][k]) == 0) {
            flag = false;
            return NULL;
        }
        if (p != k) {
            for (int j=1; j<=n; ++j) swap(a[p][j], a[k][j]);
            swap(b[p], b[k]);
        }
        for (int i=k+1; i<=n; ++i) {
            double m = a[i][k]/a[k][k];
            a[i][k] = 0;
            for (int j=k+1; j<=n; ++j) a[i][j] -= a[k][j]*m;
            b[i] = b[i]-b[k]*m;
        }
    }
    if (sgn(a[n][n]) == 0) {
        flag = false;
        return NULL;
    }
    x[n] = b[n] / a[n][n];
    for (int k=n-1; k; --k) {
        double now = 0;
        for (int j=k+1; j<=n; ++j) {
            now += a[k][j]*x[j];
        }
        x[k] = (b[k] - now) / a[k][k];
    }
    flag = true;
    return x;
}

}

namespace solve2{

double* Gauss(int n, double ** a, double * b, bool& flag) {
    double *x = (double *) malloc((n + 1) * sizeof(double));
    // print(a ,b ,4);
    for (int k=1; k<n; ++k) {
        for (int i=k; i<=n; ++i) {
            double mx = 0;
            for (int j=k; j<=n; ++j)
                mx = max(mx, fabs(a[i][j]));
            if (sgn(mx) == 0) {
                flag = false;
                return NULL;
            }
            for (int j=k; j<=n; ++j)
                a[i][j] = a[i][j]/mx;
            b[i] /= mx;
        }
        // print(a, b, 4);
        int p = 0;
        for (int j=k; j<=n; ++j) 
            if (p == 0 || sgn(fabs(a[j][k]) - fabs(a[p][k])) > 0) p = j;
        if (sgn(a[p][k]) == 0) {
            flag = 0;
            return NULL;
        }
        if (p != k) {
            for (int j=1; j<=n; ++j) swap(a[p][j], a[k][j]);
            swap(b[p], b[k]);
        }
        for (int i=k+1; i<=n; ++i) {
            double m = a[i][k]/a[k][k];
            a[i][k] = 0;
            for (int j=k+1; j<=n; ++j) a[i][j] -= a[k][j]*m;
            b[i] = b[i]-b[k]*m;
        }
        // print(a, b, n);
    }
    if (sgn(a[n][n]) == 0) {
        flag = false;
        return NULL;
    }
    x[n] = b[n] / a[n][n];
    for (int k=n-1; k; --k) {
        double now = 0;
        for (int j=k+1; j<=n; ++j) {
            now += a[k][j]*x[j];
        }
        x[k] = (b[k] - now) / a[k][k];
    }
    flag = true;
    return x;
}

}

namespace solve3{

double* Gauss(int n, double ** a, double * b, bool& flag) {
    double *x = (double *) malloc((n + 1) * sizeof(double));
    // print(a ,b ,4);
    double s[n+1] = {0};
    for (int k=1; k<n; ++k) {
        for (int i=k; i<=n; ++i) {
            for (int j=k; j<=n; ++j)
                s[i] = max(s[i], fabs(a[i][j]));
            if (sgn(s[i]) == 0) {
                flag = false;
                return NULL;
            }
        }
        // print(a, b, 4);
        int p = 0;
        for (int j=k; j<=n; ++j) 
            if (p == 0 || sgn(fabs(a[j][k]/s[j]) - fabs(a[p][k]/s[p])) > 0) p = j;
        if (sgn(a[p][k]) == 0) {
            flag = 0;
            return NULL;
        }
        if (p != k) {
            for (int j=1; j<=n; ++j) swap(a[p][j], a[k][j]);
            swap(b[p], b[k]);
        }
        for (int i=k+1; i<=n; ++i) {
            double m = a[i][k]/a[k][k];
            a[i][k] = 0;
            for (int j=k+1; j<=n; ++j) a[i][j] -= a[k][j]*m;
            b[i] = b[i]-b[k]*m;
        }
        // print(a, b, n);
    }
    if (sgn(a[n][n]) == 0) {
        flag = false;
        return NULL;
    }
    x[n] = b[n] / a[n][n];
    for (int k=n-1; k; --k) {
        double now = 0;
        for (int j=k+1; j<=n; ++j) {
            now += a[k][j]*x[j];
        }
        x[k] = (b[k] - now) / a[k][k];
    }
    flag = true;
    return x;
}

}

void didit(double ** a, double * b, int n) {
    bool flag;
    double aa[n+1][n+1], bb[n+1];

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j)
            aa[i][j] = a[i][j];
        bb[i] = b[i];
    }
    cerr << "Gauss列主元消去法" << "\n";
    double *ans = solve1::Gauss(n, a, b, flag);
    if (flag == false) cerr << "ERROR\n";
    else {
        for (int i=1; i<=n; ++i) printf("%.20lf ",ans[i]);
        printf("\n");
    }

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j)
            a[i][j] = aa[i][j];
        b[i] = bb[i];
    }
    // for (int i=1; i<=n; ++i,printf("\n")) for (int j=1; j<=n; ++j) cerr << a[i][j] << " ";
    
    cerr << "显式相对Gauss列主元消去法" << "\n";
    ans = solve2::Gauss(n, a, b, flag);
    if (flag == false) cerr << "ERROR\n";
    else {
        for (int i=1; i<=n; ++i) printf("%.20lf ",ans[i]);
        printf("\n");
    }

    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j)
            a[i][j] = aa[i][j];
        b[i] = bb[i];
    }
    // for (int i=1; i<=n; ++i,printf("\n")) for (int j=1; j<=n; ++j) cerr << a[i][j] << " ";
    
    cerr << "隐式相对Gauss列主元消去法" << "\n";
    ans = solve3::Gauss(n, a, b, flag);
    if (flag == false) cerr << "ERROR\n";
    else {
        for (int i=1; i<=n; ++i) printf("%.20lf ",ans[i]);
        printf("\n");
    }

    cerr << endl;
}

double *a1[]={  new double[5] {0, 0, 0, 0, 0},
                new double[5] {0, 0.4096, 0.1234, 0.3678, 0.2943},
                new double[5] {0, 0.2246, 0.3872, 0.4015, 0.1129},
                new double[5] {0, 0.3645, 0.1920, 0.3781, 0.0643},
                new double[5] {0, 0.1784, 0.4002, 0.2786, 0.3927} },
        b1[]={0, 1.1951, 1.1262, 0.9989, 1.2499};

double *a2[]={
                new double[5] {0, 0, 0, 0, 0},
                new double[5] {0, 136.01, 90.860, 0, 0},
                new double[5] {0, 90.860, 98.810, -67.590, 0},
                new double[5] {0, 0, -67.590, 132.01, 46.260},
                new double[5] {0, 0, 0, 46.260, 177.17} },
        b2[]={0, 226.87, 122.08, 110.68, 223.43};

double *a3[]={
                new double[5] {0, 0, 0, 0, 0},
                new double[5] {0, 1, 1.0/2, 1.0/3, 1.0/4},
                new double[5] {0, 1.0/2, 1.0/3, 1.0/4, 1.0/5},
                new double[5] {0, 1.0/3, 1.0/4, 1.0/5, 1.0/6},
                new double[5] {0, 1.0/4, 1.0/5, 1.0/6, 1.0/7} },
        b3[]={0, 25.0/12, 77.0/60, 57.0/60, 319.0/420};

double *a4[]={
                new double[5] {0, 0, 0, 0, 0},
                new double[5] {0, 10, 7, 8, 7},
                new double[5] {0, 7, 5, 6, 5},
                new double[5] {0, 8, 6, 10, 9},
                new double[5] {0, 7, 5, 9, 10} },
        b4[]={0, 32, 23, 33, 31};

double *a5[]={
                new double[5] {0, 0, 0, 0, 0},
                new double[5] {0, 197, 305, -206, -804},
                new double[5] {0, 46.8, 71.3, -47.4, 52.0},
                new double[5] {0, 88.6, 76.4, -10.8, 802},
                new double[5] {0, 1.45, 5.90, 6.13, 36.5} },
        b5[]={0, 136, 11.7, 25.1, 6.60};

double *a6[]={
                new double[5] {0, 0, 0, 0, 0},
                new double[5] {0, 0.5398, 0.7161, -0.5554, -0.2982},
                new double[5] {0, 0.5257, 0.6924, 0.3565,  -0.6255},
                new double[5] {0, 0.6465, -0.8187,-0.1872, 0.1291},
                new double[5] {0, 0.5814, 0.9400, -0.7779, -0.4042} },
        b6[]={0, 0.2058, -0.0503, 0.1070, 0.1859};

double *a7[]={
                new double[4] {0, 0, 0, 0},
                new double[4] {0, 10, 1, 2},
                new double[4] {0, 1, 10, 2},
                new double[4] {0, 1, 1, 5} },
        b7[]={0, 13, 13, 7};

double *a8[]={
                new double[4] {0, 0, 0, 0},
                new double[4] {0, 4, -2, -4},
                new double[4] {0, -2, 17, 10},
                new double[4] {0, -4, 10, 9} },
        b8[]={0, -2, 25, 15};


int main() {

    didit(a1, b1, 4);
    didit(a2, b2, 4);
    didit(a3, b3, 4);
    didit(a4, b4, 4);
    didit(a5, b5, 4);
    didit(a6, b6, 4);
    didit(a7, b7, 3);
    didit(a8, b8, 3);
}