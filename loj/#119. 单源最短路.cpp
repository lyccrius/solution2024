#include <iostream>
#include <vector>
#include <queue>

typedef long long lxl;

const int maxN = 2500;
const int maxM = 6200;
const lxl inf = 1e18 + 10;

int n, m, s, t;
int u, v, w;

namespace graph {
struct Vertex {
    int index;
    int head;
    int vis;
    lxl dis;

    bool operator<(const Vertex &other) const {
        return dis > other.dis;
    }
} vertex[maxN + 10];

struct Edge {
    int head;
    int next;
    int weight;
} edge[2 * maxM + 10];

int ecnt;

void addEdge(int tail, int head, int weight) {
    ecnt++;
    edge[ecnt].head = head;
    edge[ecnt].next = vertex[tail].head;
    edge[ecnt].weight = weight;
    vertex[tail].head = ecnt;
    return;
}

void Dijkstra(int s) {
    std::priority_queue<Vertex> q;

    for (int i = 1; i <= n; i++)
        vertex[i].index = i;

    for (int i = 1; i <= n; i++)
        vertex[i].dis = inf;

    vertex[s].dis = 0;
    q.push(vertex[s]);

    while (!q.empty()) {
        int u = q.top().index;
        q.pop();

        if (vertex[u].vis)
            continue;

        vertex[u].vis = true;

        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            int w = edge[e].weight;

            if (vertex[v].dis > vertex[u].dis + w) {
                vertex[v].dis = vertex[u].dis + w;
                q.push(vertex[v]);
            }
        }
    }

    return;
}
}

int main() {
    std::cin >> n >> m >> s >> t;

    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v >> w;
        graph::addEdge(u, v, w);
        graph::addEdge(v, u, w);
    }

    graph::Dijkstra(s);
    std::cout << graph::vertex[t].dis << '\n';
    return 0;
}