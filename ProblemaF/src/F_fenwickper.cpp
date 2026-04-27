#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Versión persistente del Fenwick tree: en cada posición no guardamos un
// único valor, sino una lista de pares (version, valor) que registra
// cómo evoluciona ese nodo a lo largo del tiempo. Las inserciones se
// hacen en orden de versión creciente, así que la lista queda ordenada
// por su primer componente.
//
// Para consultar el estado en una versión v se hace una búsqueda binaria
// en cada posición tocada para localizar el último par con `version ≤ v`.
// Cada `update` toca O(log N) posiciones; cada `prefix` también, y en
// cada una hace una búsqueda binaria de coste O(log Q).
struct PersistentFenwick {
	int N;
	vector<vector<pair<int, ll>>> entries;

	PersistentFenwick(int n_, const vector<ll>& a0) : N(n_), entries(n_ + 1) {
		// Construcción del Fenwick base en O(N): cada posición transmite
		// su contenido a su "padre" j = i + lowbit(i), igual que en la
		// versión no persistente.
		vector<ll> aux(n_ + 1, 0);
		for (int i = 1; i <= N; ++i) aux[i] = a0[i];
		for (int i = 1; i <= N; ++i) {
			int j = i + (i & -i);
			if (j <= N) aux[j] += aux[i];
		}
		for (int i = 1; i <= N; ++i) entries[i].push_back({0, aux[i]});
	}

	// Suma `delta` a la posición `i` y registra el nuevo valor de cada
	// nodo afectado bajo la `version` indicada.
	void update(int i, ll delta, int version) {
		for (; i <= N; i += i & (-i)) {
			ll prev = entries[i].back().second;
			entries[i].push_back({version, prev + delta});
		}
	}

	// Suma del prefijo [1..i] en la versión `version`. En cada posición
	// tocada se busca el último par cuyo `.first` sea ≤ version.
	ll prefix(int i, int version) {
		ll s = 0;
		for (; i > 0; i -= i & (-i)) {
			const auto& list = entries[i];
			int lo = 0, hi = (int) list.size();
			while (lo < hi) {
				int m = (lo + hi) / 2;
				if (list[m].first <= version) lo = m + 1;
				else hi = m;
			}
			if (lo > 0) s += list[lo - 1].second;
		}
		return s;
	}

	ll query(int l, int r, int version) {
		return prefix(r, version) - prefix(l - 1, version);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N, Q;
	cin >> N >> Q;

	vector<ll> a(N + 1, 0);
	for (int i = 1; i <= N; ++i) cin >> a[i];

	PersistentFenwick fen(N, a);

	int version = 0;

	while (Q--) {
		char op;
		cin >> op;
		if (op == 'U') {
			int i;
			ll x;
			cin >> i >> x;
			++version;
			ll delta = x - a[i];
			a[i] = x;
			fen.update(i, delta, version);
		} else {
			int v, l, r;
			cin >> v >> l >> r;
			cout << fen.query(l, r, v) << "\n";
		}
	}
	return 0;
}
