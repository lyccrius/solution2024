#include <iostream>

typedef long long lxl;

const int maxN = 1e5;
const int maxM = 1e5;
const int maxP = 50;

int n, m;
lxl k;
lxl s[maxN + 10];

struct LinearBase {
    lxl b[maxP + 10];
    int cnt;

    void Insert(lxl x) {
        for (int p = maxP; p >= 0; p--) {
            if ((x & (1ll << p)) == 0) continue;
            if (!b[p]) {
                b[p] = x;
                cnt++;
                return;
            }
            x ^= b[p];
        }
        return;
    }

    lxl Query(lxl k) {
        if (k > (1ll << cnt)) return -1;
        if (cnt != n) k--;
        lxl ret = 0;
        for (int p = maxP, i = cnt - 1; p >= 0; p--) {
            if (!b[p]) continue;
            if (k & (1ll << i)) {
                ret = std::max(ret, ret ^ b[p]);
            } else {
                ret = std::min(ret, ret ^ b[p]);
            }
            i--;
        }
        return ret;
    }
} LB;

signed main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> s[i], LB.Insert(s[i]);
    std::cin >> m;
    for (int i = 1; i <= m; i++) std::cin >> k, std::cout << LB.Query(k) << '\n';
    return 0;
}