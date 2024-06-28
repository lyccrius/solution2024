#include <iostream>

typedef long long lxl;

const int maxN = 1e6;
const int maxQ = 1e6;

int n, q;
int a[maxN + 10];
int b[maxN + 10];
int op, l, r, x;

struct BinaryIndexedTree {
    struct Node {
        lxl val;
    } node[maxN + 10];

    int lowbit(int x) {
        return x & (- x);
    }

    void Add(int pos, lxl val) {
        while (pos <= n) {
            node[pos].val += val;
            pos += lowbit(pos);
        }
        return;
    }

    lxl Ask1(int pos) {
        lxl ret = 0;
        lxl tmp = (pos + 1);
        while (pos >= 1) {
            ret += node[pos].val;
            pos -= lowbit(pos);
        }
        return ret * tmp;
    }

    lxl Ask1(int l, int r) {
        return Ask1(r) - Ask1(l - 1);
    }

    lxl Ask2(int pos) {
        lxl ret = 0;
        while (pos >= 1) {
            ret += node[pos].val;
            pos -= lowbit(pos);
        }
        return ret;
    }

    lxl Ask2(int l, int r) {
        return Ask2(r) - Ask2(l - 1);
    }
} BIT1, BIT2;

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];
    for (int i = 1; i <= n; i++) BIT1.Add(i, b[i]);
    for (int i = 1; i <= n; i++) BIT2.Add(i, 1ll * i * b[i]);
    for (int i = 1; i <= q; i++) {
        std::cin >> op >> l >> r;
        if (op == 1) std::cin >> x, BIT1.Add(l, x), BIT1.Add(r + 1, - x), BIT2.Add(l, 1ll * l * x), BIT2.Add(r + 1, - 1ll * (r + 1) * x);
        if (op == 2) std::cout << BIT1.Ask1(l, r) - BIT2.Ask2(l, r) << '\n';
    }
    return 0;
}