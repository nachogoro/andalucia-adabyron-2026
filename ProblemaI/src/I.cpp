#include <bits/stdc++.h>
using namespace std;

// Respuesta del juez a una consulta: número de verdes y de amarillas.
struct Result {
	int v{0}, a{0};

	bool operator==(const Result& o) const {
		return v == o.v && a == o.a;
	}

	bool operator!=(const Result& o) const {
		return !(*this == o);
	}
};

// Par (consulta, respuesta) de una interacción pasada.
struct Answer {
	int number;
	Result r;
};

// Calcula (verdes, amarillas) al comparar dos secuencias representadas como
// enteros cuyos dígitos decimales son los valores en 1..6.
Result compare(int n, int m) {
	array<int, 6> hist_n = {0,0,0,0,0,0}, hist_m = {0,0,0,0,0,0};

	Result r;
	while (n != 0) {
		int dn = n % 10;
		int dm = m % 10;
		if (dn == dm) r.v++;
		else {
			hist_n[dn-1]++;
			hist_m[dm-1]++;
		}
		n /= 10;
		m /= 10;
	}

	for (int i = 0; i < 6; ++i) {
		r.a += min(hist_m[i], hist_n[i]);
	}

	return r;
}

// Enumera todas las secuencias de longitud L con valores en 1..N,
// representadas como enteros decimales.
void generate_recursive(int acc, int remaining, int N, set<int>& s) {
	if (remaining == 0) { s.insert(acc); return; }
	for (int i = 1; i <= N; ++i) {
		generate_recursive(acc*10 + i, remaining - 1, N, s);
	}
}

set<int> generate_all(int L, int N) {
	set<int> s;
	generate_recursive(0, L, N, s);
	return s;
}

// Comprueba que el candidato sea compatible con todas las respuestas
// recibidas.
bool fits_all(int candidate, const vector<Answer>& answers) {
	bool ok = true;

	for (auto& [n, r] : answers) {
		if (compare(candidate, n) != r) {
			ok = false;
			break;
		}
	}

	return ok;
}

// Estrategia: recorremos los candidatos en orden y consultamos el primero
// que sigue siendo compatible con todas las respuestas anteriores. Si
// acertamos (v == L), hemos terminado; si no, guardamos la pareja
// (consulta, respuesta) para seguir filtrando candidatos.
int main() {
	int L, N, Q;

	while(cin >> L >> N >> Q) {
		if (L == 0) break;

		set<int> candidates = generate_all(L, N);
		vector<Answer> answers;
		for (auto c : candidates) {
			if (fits_all(c, answers)) {
				cout << "? " << c << endl;
				int v, a;
				cin >> v >> a;

				if (v == L) {
					cout << "! " << c << endl;
					break;
				} else {
					answers.push_back({c, {v, a}});
				}
			}
		}
	}
}
