#include <iostream>

const int maxN = 500;
const int maxP = 500;
const int maxM = 500;
const int mod = 1e9 + 7;

int n, p, m;

struct Matrix {
    int n, m;
    int a[maxN + 10][maxM + 10];

    void clear() {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) a[i][j] = 0;
        return;
    }

    void scan() {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
        return;
    }

    void print() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) std::cout << (a[i][j] + mod) % mod << ' ';
            std::cout << '\n';
        }
        return;
    }

    Matrix operator*(const Matrix &other) const {
        Matrix ret;
        ret.n = n;
        ret.m = other.m;
        ret.clear();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= other.m; j++) {
                for (int k = 1; k <= m; k++) {
                    ret.a[i][j] = (ret.a[i][j] + 1ll * a[i][k] * other.a[k][j] % mod) % mod;
                }
            }
        }
        return ret;
    }
} A, B, C;

int main() {
    std::cin >> n >> p >> m;
    A.n = n;
    A.m = p;
    B.n = p;
    B.m = m;
    A.scan();
    B.scan();
    C = A * B;
    C.print();
    return 0;
}