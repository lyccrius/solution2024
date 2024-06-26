#include <iostream>

typedef unsigned long long ull;

const int maxN = 50;
const int maxP = 50;

int n;
ull s[maxN + 10];

struct LinearBase {
    ull b[maxP + 10];

    void Insert(ull x) {
        for (int p = maxP; p >= 0; p--) {
            if ((x & (1ll << p)) == 0) continue;
            if (!b[p]) {
                b[p] = x;
                return;
            }
            x ^= b[p];
        }
        return;
    }

    ull Query() {
        ull ret = 0;
        for (int p = maxP; p >= 0; p--) ret = std::max(ret, ret ^ b[p]);
        return ret;
    }
} LB;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> s[i], LB.Insert(s[i]);
    std::cout << LB.Query() << '\n';
    return 0;
}