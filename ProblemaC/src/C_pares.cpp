#include <bits/stdc++.h>
using namespace std;

// Codificación de literales: 2*v representa x_v (variable v cierta) y
// 2*v+1 representa ¬x_v. Estas dos pequeñas funciones encapsulan esa
// convención para que el resto del código no tenga que conocerla.
inline int var_lit(int v) { return 2 * v; }
inline int neg_lit(int lit) { return lit ^ 1; }

// 2-SAT mediante SCC iterativa (Kosaraju). Mantenemos a la vez el
// grafo directo y el inverso para no reconstruirlo en la segunda
// pasada. La recursión se evita con stacks explícitos porque con M
// hasta 10^4 (más auxiliares) la profundidad puede pasar fácilmente
// del stack por defecto.
struct TwoSAT {
	int num_vars, n;
	vector<vector<int>> adj, radj;
	vector<int> comp, order;
	vector<bool> visited;

	// Inicializa la estructura para `nv` variables booleanas (2*nv
	// literales) sin cláusulas.
	TwoSAT(int nv) : num_vars(nv), n(2*nv), adj(2*nv), radj(2*nv),
	                 comp(2*nv, -1), visited(2*nv, false) {
		order.reserve(2*nv);
	}

	// Añade la cláusula (a v b) al sistema, traducida a las dos
	// implicaciones equivalentes (¬a ⇒ b) ∧ (¬b ⇒ a) en el grafo.
	void add_clause(int a, int b) {
		adj[neg_lit(a)].push_back(b);
		adj[neg_lit(b)].push_back(a);
		radj[b].push_back(neg_lit(a));
		radj[a].push_back(neg_lit(b));
	}

	// Calcula las SCC del grafo de implicaciones y devuelve si la
	// fórmula es satisfacible (ningún literal comparte SCC con su
	// negado).
	bool solve() {
		for (int s = 0; s < n; ++s) {
			if (visited[s]) continue;
			visited[s] = true;
			vector<pair<int,int>> stk;
			stk.push_back({s, 0});
			while (!stk.empty()) {
				int u = stk.back().first;
				int i = stk.back().second;
				if (i < (int)adj[u].size()) {
					stk.back().second = i + 1;
					int v = adj[u][i];
					if (!visited[v]) {
						visited[v] = true;
						stk.push_back({v, 0});
					}
				} else {
					order.push_back(u);
					stk.pop_back();
				}
			}
		}

		int comp_id = 0;
		for (int idx = (int)order.size() - 1; idx >= 0; --idx) {
			int s = order[idx];
			if (comp[s] != -1) continue;
			comp[s] = comp_id;
			vector<int> stk = {s};
			while (!stk.empty()) {
				int u = stk.back();
				stk.pop_back();
				for (int v : radj[u]) {
					if (comp[v] == -1) {
						comp[v] = comp_id;
						stk.push_back(v);
					}
				}
			}
			++comp_id;
		}

		for (int v = 0; v < num_vars; ++v) {
			if (comp[var_lit(v)] == comp[neg_lit(var_lit(v))]) return false;
		}
		return true;
	}
};

// Tamaños de la temporada actual.
int M, P, I_count, N_count;

// Marcado por id de polvo: si está en la lista de inestables o de
// neutralizantes respectivamente.
vector<bool> unstable, neutralizing;

// Recetas de cada espectáculo: shows_A[i] (resp. shows_B[i]) es la
// lista de polvos del espectáculo A (resp. B) del fin de semana i.
vector<vector<int>> shows_A, shows_B;

// Conteos precomputados por espectáculo: u_ es cuántos polvos
// inestables usa, n_ es cuántos neutralizantes.
vector<int> uA, uB, nA, nB;

// Para cada polvo, la lista de espectáculos que lo usan, codificados
// como (fin de semana, 0 = A o 1 = B).
vector<vector<pair<int,int>>> dust_uses;

// Literal asociado a "se elige el espectáculo `show` del fin de
// semana `week`". x_i = elegir A; ¬x_i = elegir B.
inline int lit_choice(int week, int show) {
	return show == 0 ? var_lit(week) : neg_lit(var_lit(week));
}

// Decide si los `k` primeros fines de semana pueden programarse
// respetando todas las restricciones, construyendo y resolviendo el
// 2-SAT correspondiente.
bool feasible(int k) {
	if (k <= 0) return true;

	TwoSAT sat(k);

	// Restricciones de neutralizantes entre cada par consecutivo:
	// para cada combinación (s_i, s_{i+1}) cuyo recuento de
	// neutralizantes es insuficiente, prohibimos elegir esos dos a la vez
	// (al menos uno ha de ser falso).
	for (int i = 0; i < k - 1; ++i) {
		int ua = uA[i], ub = uB[i];
		int na = nA[i+1], nb = nB[i+1];
		int A_i = lit_choice(i, 0),     B_i = lit_choice(i, 1);
		int A_j = lit_choice(i + 1, 0), B_j = lit_choice(i + 1, 1);
		if (na < ua) sat.add_clause(neg_lit(A_i), neg_lit(A_j));
		if (na < ub) sat.add_clause(neg_lit(B_i), neg_lit(A_j));
		if (nb < ua) sat.add_clause(neg_lit(A_i), neg_lit(B_j));
		if (nb < ub) sat.add_clause(neg_lit(B_i), neg_lit(B_j));
	}

	// Polvos: para cada par de espectáculos que comparten algún polvo
	// y caen dentro de los k primeros fines de semana, una cláusula
	// "no se pueden elegir ambos" (al menos uno ha de ser falso).
	for (int d = 1; d <= P; ++d) {
		vector<int> lits;
		for (auto& p : dust_uses[d]) {
			if (p.first >= k) continue;
			lits.push_back(lit_choice(p.first, p.second));
		}
		int r = lits.size();
		for (int i = 0; i < r; ++i) {
			for (int j = i + 1; j < r; ++j) {
				sat.add_clause(neg_lit(lits[i]), neg_lit(lits[j]));
			}
		}
	}

	return sat.solve();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;
	while (T--) {
		cin >> M;
		cin >> P >> I_count >> N_count;

		unstable.assign(P + 1, false);
		neutralizing.assign(P + 1, false);
		for (int i = 0; i < I_count; ++i) {
			int x; cin >> x;
			unstable[x] = true;
		}
		for (int i = 0; i < N_count; ++i) {
			int x; cin >> x;
			neutralizing[x] = true;
		}

		shows_A.assign(M, {});
		shows_B.assign(M, {});
		for (int i = 0; i < M; ++i) {
			int sz;
			cin >> sz;
			shows_A[i].resize(sz);
			for (int j = 0; j < sz; ++j) cin >> shows_A[i][j];
			cin >> sz;
			shows_B[i].resize(sz);
			for (int j = 0; j < sz; ++j) cin >> shows_B[i][j];
		}

		uA.assign(M, 0); uB.assign(M, 0);
		nA.assign(M, 0); nB.assign(M, 0);
		dust_uses.assign(P + 1, {});
		for (int i = 0; i < M; ++i) {
			for (int d : shows_A[i]) {
				if (unstable[d]) ++uA[i];
				if (neutralizing[d]) ++nA[i];
				dust_uses[d].push_back({i, 0});
			}
			for (int d : shows_B[i]) {
				if (unstable[d]) ++uB[i];
				if (neutralizing[d]) ++nB[i];
				dust_uses[d].push_back({i, 1});
			}
		}

		// Búsqueda binaria del máximo k. Monótona: si los k+1 primeros
		// fines de semana son factibles, los k primeros también.
		int lo = 0, hi = M;
		while (lo < hi) {
			int mid = (lo + hi + 1) / 2;
			if (feasible(mid)) lo = mid;
			else hi = mid - 1;
		}
		cout << lo << "\n";
	}
	return 0;
}
