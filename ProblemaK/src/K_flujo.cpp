#include <bits/stdc++.h>
using namespace std;

// Dinic para flujo máximo en grafo dirigido con capacidades enteras.
struct Dinic {
    struct Edge { int to, rev, cap; };
    vector<vector<Edge>> g;
    vector<int> level, iter;
    int n;

    Dinic(int n_) : g(n_), level(n_), iter(n_), n(n_) {}

    void add_edge(int u, int v, int c) {
        g[u].push_back({v, (int)g[v].size(), c});
        g[v].push_back({u, (int)g[u].size() - 1, 0});
    }

    bool bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[n - 1] >= 0; // se usa sólo cuando el sumidero es n-1
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < (int)g[u].size(); ++i) {
            auto &e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s, int t) {
        int flow = 0;
        while (true) {
            // BFS con sumidero t (no necesariamente n-1).
            fill(level.begin(), level.end(), -1);
            queue<int> q;
            level[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (auto &e : g[u]) {
                    if (e.cap > 0 && level[e.to] < 0) {
                        level[e.to] = level[u] + 1;
                        q.push(e.to);
                    }
                }
            }
            if (level[t] < 0) break;
            fill(iter.begin(), iter.end(), 0);
            while (int f = dfs(s, t, INT_MAX)) flow += f;
        }
        return flow;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;

        int limite = N / K;

        map<string, int> idRol;
        for (int i = 0; i < K; ++i) {
            string r; cin >> r;
            idRol[r] = i;
        }

        // Nodos:  0 = fuente,  1..M = jugadores,  M+1..M+K = roles,  M+K+1 = sumidero
        int S = 0;
        int Sink = M + K + 1;
        Dinic dinic(M + K + 2);

        for (int j = 1; j <= M; ++j) {
            string a, b;
            cin >> a >> b;
            dinic.add_edge(S, j, 1);
            dinic.add_edge(j, M + 1 + idRol[a], 1);
            dinic.add_edge(j, M + 1 + idRol[b], 1);
        }

        for (int r = 0; r < K; ++r) {
            dinic.add_edge(M + 1 + r, Sink, limite);
        }

        int flujo = dinic.max_flow(S, Sink);
        cout << (flujo == M ? "YES" : "NO") << "\n";
    }
    return 0;
}
