#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 5005;
const int INF = 0x3FFF'FFFF;
struct GRAPH {
    struct EDGE {
        int v, Next, cap, flow;
    } Edge[N];

    int fir[N], EdgeCount = 0;

    int n, Start, End;
    ll MaxFlow = 0;
    int Depth[N], CurrentHead[N];

    void init() {
        memset(fir, -1, sizeof fir);
        EdgeCount = 0;
    }

    void addedge(int u, int v, int w) {
        Edge[EdgeCount] = {v, fir[u], w, 0};
        fir[u] = EdgeCount++;
        Edge[EdgeCount] = {u, fir[v], 0, 0};
        fir[v] = EdgeCount++;
    }

    bool BFS() {
        queue<int> Queue;
        memset(Depth, 0, sizeof(int) * (n + 1));

        Depth[Start] = 1;
        Queue.push(Start);
        while (Queue.size()) {
            int u = Queue.front();
            Queue.pop();
            for (int i = fir[u]; ~i; i = Edge[i].Next) {
                int v = Edge[i].v;
                if (!Depth[v] && Edge[i].cap > Edge[i].flow) {
                    Depth[v] = Depth[u] + 1;
                    Queue.push(v);
                }
            }
        }
        return Depth[End];
    }

    int DFS(int u, int flow) {
        if (u == End || !flow) return flow;

        int Return = 0;
        for (int &i = CurrentHead[u]; ~i; i = Edge[i].Next) {
            int v = Edge[i].v, d;
            if ((Depth[v] == Depth[u] + 1) &&
                (d = DFS(v, min(flow - Return, Edge[i].cap - Edge[i].flow)))) {
                Return += d;
                Edge[i].flow += d;
                Edge[i ^ 1].flow -= d;
                if (Return == flow) return Return;
            }
        }
        return Return;
    }

    void dinic() {
        while (BFS()) {
            memcpy(CurrentHead, fir, sizeof(int) * (n + 1));
            MaxFlow += DFS(Start, INF);
        }
    }
} mf;

int main() {
    int m;
    cin >> mf.n >> m >> mf.Start >> mf.End;
    mf.init();
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mf.addedge(u, v, w);
    }
    mf.dinic();
    cout << mf.MaxFlow << endl;
    return 0;
}