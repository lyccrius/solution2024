#include <iostream>

const int maxN = 4e6;
const int maxM = 8e6;
const int mod = 998244353;

int n, m;
int op, u, v;
int ans;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

struct DisjointSetUnion {
    struct Node {
        int fa;
    } node[maxN + 10];

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return node[u].fa = Find(node[u].fa);
    }

    void Union(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        if (fu == fv) return;
        node[fu].fa = fv;
        return;
    }

    void Query(int u, int v) {
        int fu = Find(u);
        int fv = Find(v);
        if (fu == fv) {
            ans = (2 * ans + 1) % mod;
        } else {
            ans = 2 * ans % mod;
        }
        return;
    }
} DSU;

int main() {
    promote();
    std::cin >> n >> m;
    DSU.Init();
    for (int i = 1; i <= m; i++) {
        std::cin >> op >> u >> v;
        if (op == 0) DSU.Union(u, v);
        if (op == 1) DSU.Query(u, v);
    }
    std::cout << ans << '\n';
    return 0;
}