#include <iostream>
#include <queue>

typedef long long lxl;
typedef bool bol;
typedef std::deque<int> diq;

const int maxN = 100;
const int maxM = 5000;
const int inf = (1ll << 31) - 1;

int n, m, s, t;
int u, v, c;

namespace graph {
    struct Vertex {
        int head;
        int cur;
        int dep;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        lxl flow;
        lxl capacity;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int capacity) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].capacity = capacity;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    bol BFS(int s, int t) {
        for (int i = 1; i <= n; i++) vertex[i].dep = 0;
        vertex[s].dep = 1;
        diq q;
        q.push_back(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                if (edge[e].flow == edge[e].capacity) continue;
                if (vertex[v].dep) continue;
                vertex[v].dep = vertex[u].dep + 1;
                q.push_back(v);
            }
        }
        return vertex[t].dep;
    }

    lxl DFS(int u, int t, lxl tot) {
        if (u == t) return tot;
        if (!tot) return tot;
        lxl ret = 0;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].dep != vertex[u].dep + 1) continue;
            lxl res = DFS(v, t, std::min(tot - ret, edge[e].capacity - edge[e].flow));
            if (!res) continue;
            ret += res;
            edge[e].flow += res;
            edge[e ^ 1].flow -= res;
            if (ret == tot) break;
        }
        return ret;
    }

    lxl Dinic(int s, int t) {
        lxl ret = 0;
        while (BFS(s, t)) {
            for (int i = 1; i <= n; i++) vertex[i].cur = vertex[i].head;
            ret += DFS(s, t, inf);
        }
        return ret;
    }
}

int main() {
    std::cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> c;
        graph::addEdge(u, v, c);
        graph::addEdge(v, u, 0);
    }
    std::cout << graph::Dinic(s, t) << '\n';
    return 0;
}