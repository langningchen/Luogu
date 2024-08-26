#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 50005;
const ll INF = 0x3FFF'FFFF'FFFF'FFFF;
struct GRAPH {
    struct EDGE {
        ll To, Next, Capability, Value;
    } Edges[N];
    ll Head[N], EdgeCount;
    ll n, Start, End;
    ll Depth[N], CurrentHead[N];
    void AddEdge(ll u, ll v, ll w) {
        EdgeCount++;
        Edges[EdgeCount].To = v;
        Edges[EdgeCount].Next = Head[u];
        Edges[EdgeCount].Capability = w;
        Head[u] = EdgeCount;

        EdgeCount++;
        Edges[EdgeCount].To = u;
        Edges[EdgeCount].Next = Head[v];
        Edges[EdgeCount].Capability = 0;
        Head[v] = EdgeCount;
    }
    bool BFS() {
        queue<ll> Queue;
        memset(Depth, 0, sizeof(Depth));
        Depth[Start] = 1;
        Queue.push(Start);
        while (Queue.size()) {
            ll u = Queue.front();
            Queue.pop();
            for (ll i = Head[u]; i; i = Edges[i].Next) {
                ll v = Edges[i].To;
                if (!Depth[v] && Edges[i].Capability > Edges[i].Value) {
                    Depth[v] = Depth[u] + 1;
                    Queue.push(v);
                }
            }
        }
        return Depth[End];
    }
    ll DFS(ll u, ll Value) {
        if (u == End || !Value) return Value;
        ll Answer = 0;
        for (ll &i = CurrentHead[u]; i; i = Edges[i].Next) {
            ll v = Edges[i].To, d;
            if (Depth[v] != Depth[u] + 1) continue;
            d = DFS(v, min(Value - Answer, Edges[i].Capability - Edges[i].Value));
            if (!d) continue;
            Answer += d;
            Edges[i].Value += d;
            Edges[i % 2 == 0 ? i - 1 : i + 1].Value -= d;
            if (Answer == Value) return Answer;
        }
        return Answer;
    }

    ll Dinic() {
        ll Answer = 0;
        while (BFS()) {
            memcpy(CurrentHead, Head, sizeof(Head));
            Answer += DFS(Start, INF);
        }
        return Answer;
    }
} Graph;
int main() {
    ll m;
    cin >> Graph.n >> m >> Graph.Start >> Graph.End;
    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        Graph.AddEdge(u, v, w);
    }
    cout << Graph.Dinic() << endl;
    return 0;
}