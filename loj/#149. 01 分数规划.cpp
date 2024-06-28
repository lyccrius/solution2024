#include <iostream>
#include <algorithm>

typedef double dbl;

const int maxN = 1e5;
const dbl inf = 1e11 + 10;
const dbl eps = 5e-5;

int n, k;
int a[maxN + 10];
int b[maxN + 10];
dbl c[maxN + 10];

bool check(dbl x) {
    dbl res = 0;
    for (int i = 1; i <= n; i++) c[i] = a[i] - x * b[i];
    std::sort(c + 1, c + n + 1);
    std::reverse(c + 1, c + n + 1);
    for (int i = 1; i <= k; i++) res += c[i];
    return (res >= 0);
}

int main() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    dbl l = 0;
    dbl r = inf;
    while (r - l >= eps) {
        dbl mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    std::cout << l << '\n';
    return 0;
}