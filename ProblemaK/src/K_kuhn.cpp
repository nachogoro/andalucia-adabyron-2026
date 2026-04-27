#include <bits/stdc++.h>
using namespace std;

// Kuhn: emparejamiento máximo en grafo bipartito mediante DFS de
// caminos aumentantes. Lado izquierdo con nL vértices (0..nL-1), lado
// derecho con nR (0..nR-1). Coste O(V * E) en el peor caso.
struct Kuhn {
    int nL, nR;
    vector<vector<int>> adj;
    // pairR[v] guarda el nodo izquierdo emparejado con el derecho v, o
    // -1 si v está libre. No mantenemos pairL porque no hace falta.
    vector<int> pairR;
    // Marca, durante un DFS de aumento, los nodos del lado derecho ya
    // explorados, para evitar bucles en la búsqueda.
    vector<bool> used;

    Kuhn(int nL_, int nR_) : nL(nL_), nR(nR_), adj(nL_), pairR(nR_, -1) {}

    void add_edge(int u, int v) { adj[u].push_back(v); }

    // Intenta encontrar un camino aumentante desde u y, si lo logra,
    // reasigna los emparejamientos a lo largo del camino y devuelve
    // true.
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (used[v]) continue;
            used[v] = true;
            if (pairR[v] == -1 || dfs(pairR[v])) {
                pairR[v] = u;
                return true;
            }
        }
        return false;
    }

    int max_matching() {
        int res = 0;
        for (int u = 0; u < nL; ++u) {
            used.assign(nR, false);
            if (dfs(u)) ++res;
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

        // El truco habitual para reducir un emparejamiento con cupos a
        // uno sin cupos: cada rol r se duplica en L asientos
        // independientes con índices [r*L, r*L+L).
        Kuhn kuhn(M, K * L);

        for (int j = 0; j < M; ++j) {
            string a, b;
            cin >> a >> b;
            int ra = idRol[a], rb = idRol[b];
            for (int s = 0; s < L; ++s) {
                kuhn.add_edge(j, ra * L + s);
                kuhn.add_edge(j, rb * L + s);
            }
        }

        int matching = kuhn.max_matching();
        cout << (matching == M ? "YES" : "NO") << "\n";
    }
    return 0;
}
