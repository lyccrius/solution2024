#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 2e5;
const int maxM = 5e5;

int n, m;
int u, v, w;

namespace graph {
    struct Vertex {

    } vertex[maxN + 10];

    struct Edge {
        int tail;
        int head;
        int weight;

        bool operator<(const Edge &other) const {
            return weight < other.weight;
        }
    } edge[maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int weight) {
        ecnt++;
        edge[ecnt].tail = tail;
        edge[ecnt].head = head;
        edge[ecnt].weight = weight;
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
    } DSU;

    lxl Kruscal() {
        DSU.Init();
        lxl ret = 0;
        std::sort(edge + 1, edge + ecnt + 1);
        for (int e = 1; e <= ecnt; e++) {
            int u = edge[e].tail;
            int v = edge[e].head;
            int w = edge[e].weight;
            if (DSU.Find(u) == DSU.Find(v)) continue;
            DSU.Union(u, v);
            ret += w;
        }
        return ret;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
    }
    std::cout << graph::Kruscal() << '\n';
    return 0;
}