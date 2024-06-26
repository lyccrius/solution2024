#include <iostream>

const int mod = 1e9 + 7;

const int maxN = 1e7;
const int maxK = 1e7;

int n, k;
int dk[maxN + 10];
int fac[maxN + 10];
int ans;

int pow(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = 1ll * ret * a % mod;
        a = 1ll * a * a % mod;
        b = b / 2;
    }
    return ret;
}

void init() {
    dk[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!fac[i]) {
            dk[i] = pow(i, k);
            for (int j = i; j <= n; j += i) fac[j] = i;
        } else {
            dk[i] = 1ll * dk[fac[i]] * dk[i / fac[i]] % mod;
        }
    }
    return;
}

int main() {
    std::cin >> n >> k;
    init();
    for (int i = 1; i <= n; i++) ans = (ans + 1ll * (n / i) * dk[i] % mod) % mod;
    std::cout << ans << '\n';
    return 0;
}