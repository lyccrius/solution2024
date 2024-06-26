#include <iostream>
#include <queue>

typedef bool bol;
typedef std::deque<int> diq;

const int maxN = 400;
const int maxM = 15000;
const int inf = (1ll << 31) - 1;

int n, m;
int s, t, c, w;

namespace graph {
    struct Vertex {
        int head;
        int cur;
        int dis;
        bol inq;
        bol ins;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
        int flow;
        int capacity;
        int weight;
    } edge[2 * maxM + 10];

    int ecnt;

    void addEdge(int tail, int head, int capacity, int weight) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        edge[ecnt].capacity = capacity;
        edge[ecnt].weight = weight;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }

    int flow;
    int cost;

    bool SPFA(int s, int t) {
        for (int i = 1; i <= n; i++) vertex[i].dis = inf;
        for (int i = 1; i <= n; i++) vertex[i].inq = false;
        diq q;
        q.push_back(s);
        vertex[s].inq = false;
        vertex[s].dis = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            vertex[u].inq = false;
            for (int e = vertex[u].head; ~e; e = edge[e].next) {
                int v = edge[e].head;
                int w = edge[e].weight;
                if (vertex[v].dis > vertex[u].dis + w && edge[e].capacity > edge[e].flow) {
                    vertex[v].dis = vertex[u].dis + w;
                    if (!vertex[v].inq) {
                        vertex[v].inq = true;
                        q.push_back(v);
                    }
                }
            }
        }
        return vertex[t].dis < inf;
    }

    int DFS(int u, int t, int tot) {
        if (u == t) return tot;
        if (!tot) return tot;
        int ret = 0;
        vertex[u].ins = true;
        for (int &e = vertex[u].cur; ~e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;
            if (vertex[v].dis != vertex[u].dis + w) continue;
            if (vertex[v].ins) continue;
            int res = DFS(v, t, std::min(tot - ret, edge[e].capacity - edge[e].flow));
            if (!res) continue;
            ret += res;
            cost += res * w;
            edge[e].flow += res;
            edge[e ^ 1].flow -= res;
            if (ret == tot) break;
        }
        vertex[u].ins = false;
        return ret;
    }

    void Dinic(int s, int t) {
        while (SPFA(s, t)) {
            for (int i = 1; i <= n; i++) vertex[i].cur = vertex[i].head;
            flow += DFS(s, t, inf);
        }
        return;
    }
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> s >> t >> c >> w;
        graph::addEdge(s, t, c, w);
        graph::addEdge(t, s, 0, - w);
    }
    graph::Dinic(1, n);
    std::cout << graph::flow << ' ' << graph::cost << '\n';
    return 0;
}