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

    void Add(int pos, int val) {
        while (pos <= n) {
            node[pos].val += val;
            pos += lowbit(pos);
        }
        return;
    }

    lxl Ask(int pos) {
        lxl ret = 0;
        while (pos >= 1) {
            ret += node[pos].val;
            pos -= lowbit(pos);
        }
        return ret;
    }

    void Ask(int l, int r) {
        std::cout << Ask(r) - Ask(l - 1) << '\n';
        return;
    }
} BIT;

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = a[i] - a[i - 1];
    for (int i = 1; i <= n; i++) BIT.Add(i, b[i]);
    for (int i = 1; i <= q; i++) {
        std::cin >> op;
        if (op == 1) std::cin >> l >> r >> x, BIT.Add(l, x), BIT.Add(r + 1, - x);
        if (op == 2) std::cin >> x, BIT.Ask(1, x);
    }
    return 0;
}