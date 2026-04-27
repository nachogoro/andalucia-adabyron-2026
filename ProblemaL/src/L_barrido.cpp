#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

// KMP: tabla de fallos y búsqueda de todas las apariciones del patrón en
// el texto. Se usa para localizar las ocurrencias de cada motivo.
vi kmpTable(string& p) {
	int m = (int) p.size();
	vi fail(m, 0);
	for (int i = 1; i < m; ++i) {
		int j = fail[i-1];
		while (j > 0 && p[i] != p[j]) j = fail[j-1];
		if (p[i] == p[j]) j++;
		fail[i] = j;
	}
	return fail;
}

vi kmpSearch(string& text, string& pat) {
	vi fail = kmpTable(pat);
	vi matches;
	int j = 0;
	for (int i = 0; i < (int)text.size(); ++i) {
		while (j > 0 && text[i] != pat[j]) j = fail[j-1];
		if (text[i] == pat[j]) j++;
		if (j == (int)pat.size()) {
			matches.push_back(i - j + 1);
			j = fail[j-1];
		}
	}
	return matches;
}

// Cada aparición se reduce a una tripleta (fin, inicio, id_motivo). El
// barrido principal recorre estas tripletas en orden de fin creciente.
struct Aparicion {
	int fin;
	int inicio;
	int id;
	bool operator<(const Aparicion& o) const {
		if (fin != o.fin) return fin < o.fin;
		return inicio < o.inicio;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string strand;
	getline(cin, strand);

	string tokens;
	getline(cin, tokens);
	istringstream iss(tokens);
	vector<string> patterns;
	string tok;
	while (iss >> tok) patterns.push_back(tok);

	int K;
	cin >> K;

	// Eliminamos motivos repetidos: la pregunta exige K motivos diferentes y
	// dos copias del mismo no cuentan como dos.
	sort(patterns.begin(), patterns.end());
	patterns.erase(unique(patterns.begin(), patterns.end()), patterns.end());
	int M = (int) patterns.size();

	// Localizamos todas las apariciones de cada motivo y las representamos
	// por su (fin, inicio, id).
	vector<Aparicion> ocs;
	for (int i = 0; i < M; ++i) {
		auto starts = kmpSearch(strand, patterns[i]);
		int len = (int) patterns[i].size();
		for (int s : starts) ocs.push_back({s + len - 1, s, i});
	}

	// Ordenamos por la posición de fin.
	sort(ocs.begin(), ocs.end());

	// Para cada motivo guardamos el inicio más a la derecha de sus
	// apariciones vistas hasta ahora. Fijado un fin R, esa es la posición
	// más tardía en la que puede arrancar una aparición completa de ese
	// motivo dentro de [?, R]. La ventana óptima terminada en R toma los K
	// motivos con mayor `latest`; el menor de esos K define el inicio L.
	vector<int> latest(M, -1);
	int activos = 0;
	int min_length = INT_MAX;

	for (const auto& oc : ocs) {
		if (latest[oc.id] == -1) ++activos;
		latest[oc.id] = max(latest[oc.id], oc.inicio);

		if (activos >= K) {
			// Como M <= 25, ordenar la lista entera de latests es trivial
			// y nos evita mantener una estructura más sofisticada.
			vector<int> tmp(latest);
			sort(tmp.begin(), tmp.end(), greater<int>());
			int L_win = tmp[K - 1];
			min_length = min(min_length, oc.fin - L_win + 1);
		}
	}

	cout << (min_length == INT_MAX ? 0 : min_length) << "\n";
}
