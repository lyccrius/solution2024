#include <iostream>
#include <algorithm>
#include <cstring>

typedef char chr;
typedef unsigned long long ull;

const int maxN = 1e6;
const int mod = 131;

struct SuffixArray {
    int n;
    chr s[maxN + 10];
    ull p[maxN + 10];
    ull h[maxN + 10];
    int sa[maxN + 10];
    int rk[maxN + 10];

    ull hash(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }

    int LCP(int x, int y) {
        int l = 0;
        int r = std::min(n - x + 1, n - y + 1);
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (hash(x, x + mid - 1) == hash(y, y + mid - 1)) l = mid;
            else r = mid - 1;
        }
        return l;
    }

    void Init() {
        n = strlen(s + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] * mod;
        for (int i = 1; i <= n; i++) h[i] = h[i - 1] * mod + s[i] - '0' + 1;
        for (int i = 1; i <= n; i++) sa[i] = i;
        return;
    }
} SA;

bool cmp(int x, int y) {
    int lcp = SA.LCP(x, y);
    return SA.s[x + lcp] < SA.s[y + lcp];
}

int main() {
    std::cin >> SA.s + 1;
    SA.Init();
    std::stable_sort(SA.sa + 1, SA.sa + SA.n + 1, cmp);
    for (int i = 1; i <= SA.n; i++) SA.rk[SA.sa[i]] = i;
    for (int i = 1; i <= SA.n; i++) std::cout << SA.sa[i] << ' ';
    return 0;
}