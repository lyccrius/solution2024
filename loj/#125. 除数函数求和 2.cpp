#include <iostream>

const int mod = 998244353;
const int inv2 = 499122177;
const int inv6 = 166374059;

int n;
int ans;

int s2(int n) {
    return (2ll * n % mod + 1) % mod * (n + 1) % mod * n % mod * inv6 % mod;
}

int s1(int n) {
    return 1ll * (n + 1) % mod * n % mod * inv2 % mod;
}

int main() {
    std::cin >> n;
    for (int i = 1, j, t; i <= n; i = j + 1) {
        t = n / i;
        j = n / t;
        ans = (ans + 2ll * t % mod * (s2(j) - s2(i - 1) + mod) % mod) % mod;
        ans = (ans + 3ll * t % mod * (s1(j) - s1(i - 1) + mod) % mod) % mod;
        ans = (ans + 5ll * t % mod * (j - (i - 1)) % mod) % mod;
    }
    std::cout << ans << '\n';
    return 0;
}