#include <iostream>

int n, p;

int pow(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % p;
        a = 1ll * a * a % p;
        b = b / 2;
    }
    return ret;
}

int inv(int a, int p) {
    return pow(a, p - 2, p);
}

int main() {
    std::cin >> n >> p;
    for (int i = 1; i <= n; i++) std::cout << inv(i, p) << '\n';
    return 0;
}