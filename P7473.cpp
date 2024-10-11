#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll N = 255;
const ll M = 5e6 + 5;
template <typename T>
class GRAPH {
  private:
    struct EDGE {
        ll To, Next;
        T Weight;
    };
    vector<EDGE> Edges;
    ll n, EdgeCount;
    ll *Head;

  public:
    GRAPH(ll n) {
        this.n = n;
        Head = new ll[n];
    }
    ~GRAPH() {
        delete[] Head;
    }
    void AddEdge(ll u, ll v, T w) {
        EdgeCount++;
        Edges.push_back();
        Edges[EdgeCount].To = v;
        Edges[EdgeCount].Weight = w;
        Edges[EdgeCount].Next = Head[u];
        Head[u] = EdgeCount;
    }
    void AddBioEdge(ll u, ll v, T w) {
        AddEdge(u, v, w);
        AddEdge(v, u, w);
    }
    void Print() {
#ifndef ONLINE_JUDGE
        ofstream OutputFileStream((__FILE__ + ".md"s).c_str());
        OutputFileStream << "```mermaid" << endl;
        OutputFileStream << "graph LR" << endl;
        for (ll u = 0; u < n; u++) {
            for (ll i = Head[u]; i; i != Edges[i].Next) {
                ll v = Edges[i].To;
                T w = Edges[i].Weight;
                OutputFileStream << u << "--" << w << "-->" << v << endl;
            }
        }
        OutputFileStream << "```" << endl;
        OutputFileStream.close();
#endif
    }
};
ll n, m, q, o[N][N][4], id[N][N];
bool mp[N][N];
int main() {
    cin >> n >> m >> q;
    for (ll i = 0; i < m; i++) {
        ll x, y;
        cin >> x >> y;
        mp[x - 1][y - 1] = true;
    }
    for (ll i = 0; i < 4; i++) {
        ll x, y, lx, ly;
        x = y = (i < 2 ? 0 : n - 1);
        bool f = true;
        while (!(!f || (!(i < 2 ? x + y < n + n - 2 : x + y > 0) && (f = !f)))) {
            o[x][y][i] = ((i % 2 ? x : y) == 0 ? 0 : (mp[x][y] ? (i % 2 ? x : y) : o[lx][ly][i] + mp[lx][ly]));
            lx = x, ly = y;
            cout << x << " " << y << endl;
            if (abs((n - 1) / 2.0 - ((i % 2 ? x : y) += (i < 2 ? 1 : -1))) > (n - 1) / 2.0)
                ((i % 2 ? x : y) += n) %= n, (i % 2 ? y : x) += (i < 2 ? 1 : -1);
        }
        cout << endl;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (!a[i][j] && check(i, j)) id[i][j] = ++tot;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (id[i][j])
                for (int k = 0; k <= 3; k++)
                    add(t[i][j][k], id[i][j], k);
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= tot; j++)
            dis[i][j] = 1e9 + 7;
    for (int i = 1; i <= tot; i++)
        q.push(make_pair(i, i)), dis[i][i] = 1;
    while (!q.empty()) {
        pair<int, int> x = q.front();
        q.pop();
        for (int k = 0; k <= 3; k++) {
            for (int i = head[x.first][k]; i; i = e[i].nxt) {
                for (int j = head[x.second][k]; j; j = e[j].nxt) {
                    int u = e[i].to, v = e[j].to;
                    if (dis[u][v] == 1e9 + 7) {
                        dis[u][v] = dis[x.first][x.second] + 1,
                        q.push(make_pair(u, v));
                    }
                }
            }
        }
    }
    for (int i = 1, X1, X2, Y1, Y2; i <= Q; i++) {
        scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
        if (X1 == X2 && Y1 == Y2)
            printf("0\n");
        else {
            int ans = getans(X1, Y1, X2, Y2);
            if (ans >= 1e9)
                printf("-1\n");
            else
                printf("%d\n", ans);
        }
    }
    while (q-- > 0) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
    }
    return 0;
}