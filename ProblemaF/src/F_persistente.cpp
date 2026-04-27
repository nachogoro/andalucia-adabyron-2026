#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Segment tree persistente sobre [0, N-1] que mantiene sumas. Cada
// actualización crea una nueva raíz duplicando solo los O(log N) nodos
// del camino raíz-hoja afectado; el resto del árbol se comparte con la
// versión anterior. Así cada versión se accede en O(log N) y se
// almacena en O(log N) nodos extra.
//
// Pool de nodos en arrays planos: hijos en `Lc`/`Rc` (índices) y suma
// en `Sm`. Los índices van creciendo monótonamente y nunca se liberan,
// así que basta con reservar el espacio máximo necesario al inicio:
// ~4N por la construcción del árbol base más ~ceil(log N) por cada
// posible actualización.
struct PersistentSegTree {
	vector<int> Lc, Rc;
	vector<ll> Sm;
	int N;

	PersistentSegTree(int n_, int max_updates) : N(n_) {
		int cap = 4 * n_ + 22 * (max_updates + 1);
		Lc.reserve(cap);
		Rc.reserve(cap);
		Sm.reserve(cap);
	}

	int new_node(int l, int r, ll s) {
		Lc.push_back(l);
		Rc.push_back(r);
		Sm.push_back(s);
		return (int) Sm.size() - 1;
	}

	// Construye la versión 0 a partir del array inicial. Devuelve la
	// raíz de esa versión.
	int build(int l, int r, const vector<int>& a) {
		if (l == r) return new_node(0, 0, a[l]);
		int m = (l + r) / 2;
		int li = build(l, m, a);
		int ri = build(m + 1, r, a);
		return new_node(li, ri, Sm[li] + Sm[ri]);
	}

	// A partir de la raíz `prev`, crea una nueva raíz en la que la
	// posición `pos` toma el valor `val`. Solo los nodos del camino
	// raíz-hoja se copian; los demás se reutilizan tal cual.
	int update(int prev, int l, int r, int pos, int val) {
		if (l == r) return new_node(0, 0, val);
		int m = (l + r) / 2;
		int li, ri;
		if (pos <= m) {
			li = update(Lc[prev], l, m, pos, val);
			ri = Rc[prev];
		} else {
			li = Lc[prev];
			ri = update(Rc[prev], m + 1, r, pos, val);
		}
		return new_node(li, ri, Sm[li] + Sm[ri]);
	}

	// Suma de [ql, qr] en la versión cuya raíz es `node`.
	ll query(int node, int l, int r, int ql, int qr) {
		if (qr < l || r < ql) return 0;
		if (ql <= l && r <= qr) return Sm[node];
		int m = (l + r) / 2;
		return query(Lc[node], l, m, ql, qr) +
		       query(Rc[node], m + 1, r, ql, qr);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	vector<int> a(N);
	for (int i = 0; i < N; ++i) cin >> a[i];

	PersistentSegTree st(N, Q);

	// roots[v] = raíz del árbol que representa la versión v.
	vector<int> roots;
	roots.reserve(Q + 1);
	roots.push_back(st.build(0, N - 1, a));

	while (Q--) {
		char op;
		cin >> op;
		if (op == 'U') {
			int i, x;
			cin >> i >> x;
			roots.push_back(st.update(roots.back(), 0, N - 1, i - 1, x));
		} else {
			int v, l, r;
			cin >> v >> l >> r;
			cout << st.query(roots[v], 0, N - 1, l - 1, r - 1) << "\n";
		}
	}
	return 0;
}
