#include <bits/stdc++.h>
using namespace std;

// Hopcroft-Karp: emparejamiento máximo en grafo bipartito en O(E * sqrt(V)).
// Lado izquierdo con nL vértices (0..nL-1), lado derecho con nR (0..nR-1).
struct HopcroftKarp {
    int nL, nR;
    vector<vector<int>> adj;
    vector<int> pairL, pairR, dist;
    static constexpr int INF = INT_MAX;

    HopcroftKarp(int nL_, int nR_)
        : nL(nL_), nR(nR_), adj(nL_),
          pairL(nL_, -1), pairR(nR_, -1), dist(nL_) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < nL; ++u) {
            if (pairL[u] == -1) { dist[u] = 0; q.push(u); }
            else                 dist[u] = INF;
        }
        bool alcanza_libre = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int w = pairR[v];
                if (w == -1) {
                    alcanza_libre = true;
                } else if (dist[w] == INF) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return alcanza_libre;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            int w = pairR[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                pairL[u] = v;
                pairR[v] = u;
                return true;
            }
        }
        dist[u] = INF;
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs()) {
            for (int u = 0; u < nL; ++u) {
                if (pairL[u] == -1 && dfs(u)) ++res;
            }
        }
        return res;
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

        int L = N / K;  // cupo por rol

        map<string, int> idRol;
        for (int i = 0; i < K; ++i) {
            string r; cin >> r;
            idRol[r] = i;
        }

        // Lado izquierdo: M jugadores.
        // Lado derecho: N = K*L "asientos", el rol r ocupa los índices [r*L, r*L+L).
        HopcroftKarp hk(M, K * L);

        for (int j = 0; j < M; ++j) {
            string a, b;
            cin >> a >> b;
            int ra = idRol[a], rb = idRol[b];
            for (int s = 0; s < L; ++s) {
                hk.add_edge(j, ra * L + s);
                hk.add_edge(j, rb * L + s);
            }
        }

        int matching = hk.max_matching();
        cout << (matching == M ? "YES" : "NO") << "\n";
    }
    return 0;
}
