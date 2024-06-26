#include <iostream>
#include <cstring>

typedef char chr;
typedef unsigned long long ull;

const int maxN = 1e6;
const int base = 131;

struct Hash {
    int n;
    chr s[maxN + 10];
    ull h[maxN + 10];
    ull p[maxN + 10];

    void init() {
        n = strlen(s + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++) h[i] = h[i - 1] * base + s[i] - 'A';
        for (int i = 1; i <= n; i++) p[i] = p[i - 1] * base;
        return;
    }

    ull hash(int l, int r) {
        return h[r] - h[l - 1] * p[r - l + 1];
    }
} A, B;

int ans = 0;

int main() {
    std::cin >> A.s + 1;
    std::cin >> B.s + 1;
    A.init();
    B.init();
    for (int i = 1; i <= A.n - B.n + 1; i++) {
        if (A.hash(i, i + B.n - 1) == B.hash(1, B.n)) {
            ans++;
        }
    }
    std::cout << ans << '\n';
    return 0;
}