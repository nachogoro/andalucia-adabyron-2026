#include <bits/stdc++.h>
using namespace std;

// Cada candidato guarda:
//   d[0..L-1]  dígitos en orden
//   cnt[1..N]  cuántas veces aparece cada dígito
//   num        representación decimal, para imprimirlo como consulta
//
// Con esta precomputación, compare_cand no tiene que hacer %10 ni /10 en
// bucle, y se apoya en la identidad
//
//     amarillas = sum_i min(cnt_a[i], cnt_b[i]) - verdes
//
// porque la cardinalidad del multiset común no depende de la posición y
// las verdes son las coincidencias con posición.
struct Cand {
	array<uint8_t, 6> d;
	array<uint8_t, 8> cnt;
	int num;
};

inline pair<int,int> compare_cand(const Cand& A, const Cand& B, int L, int N) {
	int v = 0;
	for (int i = 0; i < L; ++i) v += (A.d[i] == B.d[i]);
	int comun = 0;
	for (int i = 1; i <= N; ++i) comun += min(A.cnt[i], B.cnt[i]);
	return {v, comun - v};
}

Cand make_cand_from_digits(const array<uint8_t, 6>& digits, int L) {
	Cand c;
	c.d = digits;
	c.cnt.fill(0);
	c.num = 0;
	for (int i = 0; i < L; ++i) {
		c.cnt[digits[i]]++;
		c.num = c.num * 10 + digits[i];
	}
	return c;
}

void generate_recursive(array<uint8_t, 6>& cur, int pos, int L, int N, vector<Cand>& out) {
	if (pos == L) {
		out.push_back(make_cand_from_digits(cur, L));
		return;
	}
	for (uint8_t i = 1; i <= (uint8_t)N; ++i) {
		cur[pos] = i;
		generate_recursive(cur, pos + 1, L, N, out);
	}
}

vector<Cand> generate_all(int L, int N) {
	vector<Cand> out;
	out.reserve((size_t)pow(N, L));
	array<uint8_t, 6> cur{};
	generate_recursive(cur, 0, L, N, out);
	return out;
}

// Reconstruye un Cand a partir de su entero decimal. Se usa para el
// primer intento, que viene de una heurística y no del conjunto de
// candidatos.
Cand cand_from_int(int num, int L) {
	array<uint8_t, 6> digits{};
	int n = num;
	for (int i = L - 1; i >= 0; --i) {
		digits[i] = (uint8_t)(n % 10);
		n /= 10;
	}
	return make_cand_from_digits(digits, L);
}

// Primer intento heurístico: los dígitos 1..N en ciclo hasta cubrir L
// posiciones. Evita el coste cuadrático del minimax sobre el conjunto
// inicial de candidatos cuando N^L es grande.
int first_guess(int L, int N) {
	int g = 0;
	for (int i = 0; i < L; ++i) g = g*10 + (1 + (i % N));
	return g;
}

// Minimax de Knuth restringido al conjunto de candidatos. Para cada
// posible intento g tomado del conjunto de candidatos se cuenta cuántos
// candidatos quedarían en el peor caso tras conocer (v, a), y se elige
// el g que minimiza ese peor caso. La poda abandona un g tan pronto
// como su local_max alcanza al mejor conocido.
//
// Cuando el conjunto es grande (por ejemplo, tras el primer intento en
// L = N = 6 pueden quedar varios miles de candidatos), el coste O(C^2)
// se dispara. Para acotarlo, se limita el número de candidatos que se
// evalúan como intento, pero no los que se evalúan para el histograma
// de particiones: se recorren los candidatos como intento con un paso
// uniforme step = ceil(C / MAX_TRIES), lo que mantiene la cobertura del
// espacio de guesses y acota el trabajo a O(MAX_TRIES * C) por llamada.
// La pérdida de calidad respecto al minimax completo es muy pequeña.
int pick_best_idx(const vector<Cand>& candidates, int L, int N) {
	constexpr int MAX_TRIES = 200;

	int best_idx = 0;
	int best_max = INT_MAX;
	array<int, 64> hist;
	const int C = (int)candidates.size();
	const int step = (C + MAX_TRIES - 1) / MAX_TRIES;

	for (int gi = 0; gi < C; gi += step) {
		const Cand& G = candidates[gi];
		hist.fill(0);
		int local_max = 0;
		for (int ci = 0; ci < C; ++ci) {
			auto [v, a] = compare_cand(G, candidates[ci], L, N);
			int e = v * 8 + a;
			if (++hist[e] > local_max) local_max = hist[e];
			if (local_max >= best_max) break;
		}
		if (local_max < best_max) {
			best_max = local_max;
			best_idx = gi;
		}
	}
	return best_idx;
}

int main() {
	int L, N, Q;

	while (cin >> L) {
		if (L == 0) break;
		cin >> N >> Q;

		vector<Cand> candidates = generate_all(L, N);
		Cand G;
		bool first = true;

		while (true) {
			if (first) {
				G = cand_from_int(first_guess(L, N), L);
				first = false;
			} else if (candidates.size() == 1) {
				G = candidates[0];
			} else {
				G = candidates[pick_best_idx(candidates, L, N)];
			}

			cout << "? " << G.num << endl;
			int v, a;
			cin >> v >> a;

			if (v == L) {
				cout << "! " << G.num << endl;
				break;
			}

			vector<Cand> next;
			next.reserve(candidates.size());
			for (const auto& c : candidates) {
				auto [cv, ca] = compare_cand(G, c, L, N);
				if (cv == v && ca == a) next.push_back(c);
			}
			candidates = std::move(next);
		}
	}
}
