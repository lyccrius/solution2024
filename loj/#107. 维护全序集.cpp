#include <iostream>

const int maxN = 3e5;

int n;
int opt, x;

struct FHQTreap {
    struct Node {
        int val;
        int rand;
        int size;
        int lson;
        int rson;
    } node[maxN + 10];

    int ncnt;
    int root;

    void PushUp(int u) {
        node[u].size = node[node[u].lson].size + node[node[u].rson].size + 1;
        return;
    }

    int Merge(int u, int v) {
        if (!u || !v) return u + v;
        if (node[u].rand < node[v].rand) {
            node[u].rson = Merge(node[u].rson, v);
            PushUp(u);
            return u;
        } else {
            node[v].lson = Merge(u, node[v].lson);
            PushUp(v);
            return v;
        }
    }

    void Spilt(int u, int val, int &x, int &y) {
        if (!u) {
            x = 0;
            y = 0;
            return;
        }
        if (node[u].val <= val) {
            x = u;
            Spilt(node[u].rson, val, node[u].rson, y);
        } else {
            y = u;
            Spilt(node[u].lson, val, x, node[u].lson);
        }
        PushUp(u);
        return;
    }

    void Insert(int val) {
        ncnt++;
        node[ncnt].val = val;
        node[ncnt].rand = rand();
        node[ncnt].size = 1;
        int x, y;
        Spilt(root, val, x, y);
        root = Merge(Merge(x, ncnt), y);
        return;
    }

    void Delete(int val) {
        int x, y, z;
        Spilt(root, val, x, z);
        Spilt(x, val - 1, x, y);
        y = Merge(node[y].lson, node[y].rson);
        root = Merge(Merge(x, y), z);
        return;
    }

    void QueryRnk(int val) {
        int x, y;
        Spilt(root, val - 1, x, y);
        std::cout << node[x].size << '\n';
        root = Merge(x, y);
        return;
    }

    void QueryKth(int val) {
        int u = root;
        if (!u) {
            std::cout << -1 << '\n';
            return;
        }
        while (true) {
            if (node[node[u].lson].size >= val) {
                u = node[u].lson;
            } else if (node[node[u].lson].size + 1 < val) {
                val -= node[node[u].lson].size + 1;
                u = node[u].rson;
            } else {
                std::cout << node[u].val << '\n';
                return;
            }
        }
        return;
    }

    void QueryPre(int val) {
        int x, y;
        Spilt(root, val - 1, x, y);
        root = x;
        QueryKth(node[x].size);
        root = Merge(x, y);
        return;
    }

    void QuerySuf(int val) {
        int x, y;
        Spilt(root, val, x, y);
        root = y;
        QueryKth(1);
        root = Merge(x, y);
        return;
    }
} FT;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> opt >> x;
        if (opt == 0) FT.Insert(x);
        if (opt == 1) FT.Delete(x);
        if (opt == 2) FT.QueryKth(x);
        if (opt == 3) FT.QueryRnk(x);
        if (opt == 4) FT.QueryPre(x);
        if (opt == 5) FT.QuerySuf(x);
    }
    return 0;
}