#include <bits/stdc++.h>
using namespace std;

// Variante de I_mastermind.cpp que NO precomputa el histograma de cada
// candidato. Los candidatos se almacenan como enteros (como en I.cpp) y
// el cálculo de (verdes, amarillas) vuelve a recorrer los dígitos con
// %10 y /10 en cada comparación, reconstruyendo los histogramas locales.
// El resto de la estrategia (minimax de Knuth restringido a candidatos y
// muestreo con paso uniforme) es idéntico.

struct Result {
	int v{0}, a{0};
};

Result compare(int n, int m, int L) {
	array<int, 7> hn = {0,0,0,0,0,0,0}, hm = {0,0,0,0,0,0,0};

	Result r;
	for (int k = 0; k < L; ++k) {
		int dn = n % 10;
		int dm = m % 10;
		if (dn == dm) r.v++;
		else {
			hn[dn]++;
			hm[dm]++;
		}
		n /= 10;
		m /= 10;
	}

	for (int i = 1; i <= 6; ++i) {
		r.a += min(hm[i], hn[i]);
	}

	return r;
}

void generate_recursive(int acc, int remaining, int N, vector<int>& out) {
	if (remaining == 0) { out.push_back(acc); return; }
	for (int i = 1; i <= N; ++i) {
		generate_recursive(acc*10 + i, remaining - 1, N, out);
	}
}

vector<int> generate_all(int L, int N) {
	vector<int> out;
	generate_recursive(0, L, N, out);
	return out;
}

int first_guess(int L, int N) {
	int g = 0;
	for (int i = 0; i < L; ++i) g = g*10 + (1 + (i % N));
	return g;
}

int pick_best(const vector<int>& candidates, int L) {
	constexpr int MAX_TRIES = 200;

	int best = candidates[0];
	int best_max = INT_MAX;
	array<int, 64> hist;
	const int C = (int)candidates.size();
	const int step = (C + MAX_TRIES - 1) / MAX_TRIES;

	for (int gi = 0; gi < C; gi += step) {
		int g = candidates[gi];
		hist.fill(0);
		int local_max = 0;
		for (int ci = 0; ci < C; ++ci) {
			Result r = compare(g, candidates[ci], L);
			int e = r.v * 8 + r.a;
			if (++hist[e] > local_max) local_max = hist[e];
			if (local_max >= best_max) break;
		}
		if (local_max < best_max) {
			best_max = local_max;
			best = g;
		}
	}
	return best;
}

int main() {
	int L, N, Q;

	while (cin >> L) {
		if (L == 0) break;
		cin >> N >> Q;

		vector<int> candidates = generate_all(L, N);
		bool first = true;

		while (true) {
			int g;
			if (first) {
				g = first_guess(L, N);
				first = false;
			} else if (candidates.size() == 1) {
				g = candidates[0];
			} else {
				g = pick_best(candidates, L);
			}

			cout << "? " << g << endl;
			int v, a;
			cin >> v >> a;

			if (v == L) {
				cout << "! " << g << endl;
				break;
			}

			vector<int> next;
			next.reserve(candidates.size());
			for (int c : candidates) {
				Result r = compare(g, c, L);
				if (r.v == v && r.a == a) next.push_back(c);
			}
			candidates = std::move(next);
		}
	}
}
