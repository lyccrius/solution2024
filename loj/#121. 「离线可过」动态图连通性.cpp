#include <iostream>
#include <vector>

typedef std::pair<int, int> pii;
typedef std::vector<int> vic;
typedef char chr;

const int maxN = 5000;
const int maxM = 500000;

int n, m;
int op[maxM + 10], x[maxM + 10], y[maxM + 10];
int t[maxN + 10][maxN + 10];
chr ans[maxM + 10];

struct DisjointSetUnion {
    struct Node {
        int fa;
        int size;
    } node[maxN + 10];

    std::vector<Node> backup;

    void BackUp(int u) {
        backup.push_back(node[u]);
        return;
    }

    int Version() {
        return backup.size();
    }

    void Restore(int u) {
        node[node[u].fa].size -= node[u].size;
        node[u].fa = u;
        return;
    }

    void RollBack(int ver) {
        while (Version() > ver) {
            Restore(backup.back().fa);
            backup.pop_back();
        }
        return;
    }

    void Init() {
        for (int i = 1; i <= n; i++) node[i].fa = i;
        for (int i = 1; i <= n; i++) node[i].size = 1;
        return;
    }

    int Find(int u) {
        if (node[u].fa == u) return u;
        return Find(node[u].fa);
    }

    void Union(int u, int v) {
        u = Find(u);
        v = Find(v);
        if (u == v) return;
        if (node[u].size > node[v].size) std::swap(u, v);
        BackUp(u);
        node[u].fa = v;
        node[v].size += node[u].size;
        return;
    }
} DSU;

struct SegmentTree {
    struct Node {
        vic e;
    } node[4 * maxM + 10];

    void MakeTag(int u, int x) {
        node[u].e.push_back(x);
        return;
    }

    void PushDown(int u) {
        for (auto i : node[u].e) DSU.Union(x[i], y[i]);
        return;
    }

    void Modify(int u, int l, int r, int s, int t, int x) {
        if (s <= l && r <= t) {
            MakeTag(u, x);
            return;
        }
        int mid = (l + r) / 2;
        if (s <= mid) Modify(2 * u, l, mid, s, t, x);
        if (t >= mid + 1) Modify(2 * u + 1, mid + 1, r, s, t, x);
        return;
    }

    void Solve(int u, int l, int r) {
        int mid = (l + r) / 2;
        int ver = DSU.Version();
        PushDown(u);
        if (l == r) {
            if (op[l] == 2) {
                if (DSU.Find(x[l]) == DSU.Find(y[l])) {
                    ans[l] = 'Y';
                } else {
                    ans[l] = 'N';
                }
            }
        } else {
            Solve(2 * u, l, mid);
            Solve(2 * u + 1, mid + 1, r);
        }
        DSU.RollBack(ver);
        return;
    }
} SGT;

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> op[i] >> x[i] >> y[i];
        if (x[i] > y[i]) std::swap(x[i], y[i]);
        if (op[i] == 0) t[x[i]][y[i]] = i;
        if (op[i] == 1) SGT.Modify(1, 1, m, t[x[i]][y[i]], i, i), t[x[i]][y[i]] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (t[i][j]) SGT.Modify(1, 1, m, t[i][j], m, t[i][j]);
        }
    }
    DSU.Init();
    SGT.Solve(1, 1, m);
    for (int i = 1; i <= m; i++) if (op[i] == 2) std::cout << ans[i] << '\n';
    return 0;
}