#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

// KMP: tabla de fallos y búsqueda de todas las apariciones del patrón en
// el texto. Se usa para localizar de forma eficiente cada aparición de
// cada motivo dentro del ADN.
vi kmpTable(string &p) {
	int m = (int) p.size();
	vi fail(m, 0);
	for (int i = 1; i < m; ++i) {
		int j = fail[i-1];
		while(j > 0 && p[i]!=p[j]) j = fail[j-1];
		if (p[i] == p[j]) j++;
		fail[i]=j;
	}
	return fail;
}

vi kmpSearch(string& text, string& pat) {
	vi fail=kmpTable(pat);
	vi matches;
	int j =0;
	for (int i = 0; i < text.size(); ++i) {
		while( j > 0 && text[i] != pat[j]) j = fail[j-1];
		if (text[i] == pat[j]) j++;
		if (j == pat.size()) {
			matches.push_back(i-j+1);
			j = fail[j-1];
		}
	}
	return matches;
}

// Cada aparición de un motivo en el ADN se representa con dos eventos:
// uno de inicio en la posición del primer carácter y otro de fin en el
// último carácter. La ventana deslizante opera sobre estos eventos en
// lugar de hacerlo sobre los caracteres del ADN.
struct Event {
	int pos;
	int id;
	bool is_start;

	// Empate determinista: ante misma posición y motivo, el inicio va
	// antes que el fin (motivos de longitud 1).
	bool operator<(const Event& o) const {
		if (pos != o.pos) return pos < o.pos;
		if (id != o.id) return id < o.id;
		return is_start && !o.is_start;
	}
};

// Longitud de la subcadena de ADN cubierta por la ventana, medida entre
// el primer y el último evento que aún están dentro.
int window_length(const deque<Event>& window) {
	return window.back().pos - window.front().pos + 1;
}

// Contrae la ventana eliminando el evento más a la izquierda. 
void decrease(deque<Event>& window, int& distinct_in_window, vector<int>& freq) {
	if (window.empty()) return;

	// Si era el inicio de una aparición que estaba completa, esa aparición
	// deja de estar en la ventana, así que hay que actualizar los contadores.
	if (freq[window.front().id] > 0) {
		freq[window.front().id]--;
		if (freq[window.front().id] == 0) distinct_in_window--;
	}

	window.pop_front();

	// La ventana, para ser mínima, debe comenzar en un evento de comienzo de
	// patrón (no tiene sentido empezar antes), así que los eventos de final de
	// patrón que queden al comienzo de la ventana deben eliminarse.
	while (!window.empty() && !window.front().is_start) {
		window.pop_front();
	}
}

// Añade un evento por la derecha.
void increase(
		deque<Event>& window, int& distinct_in_window, vector<int>& freq,
		const Event& e, const vector<string>& patterns)
{
	window.push_back(e);

	// Solo los finales pueden hacer que una aparición pase a estar completa:
	// comprobamos que la ventana sea suficientemente ancha para abarcar todo
	// el motivo, lo que equivale a que el inicio asociado no haya salido por
	// la izquierda.
	if (!e.is_start) {
		if (window_length(window) >= patterns[e.id].size()) {
			freq[e.id]++;
			if (freq[e.id] == 1) {
				distinct_in_window++;
			}
		}
	}
}

int main() {
	string strand;
	getline(cin, strand);

	string tokens;
	getline(cin, tokens);
	istringstream iss(tokens);
	vector<string> patterns;
	string token;
	while (iss >> token) {
		patterns.push_back(token);
	}

	int K;
	cin >> K;

	// Generamos un par de eventos (inicio, fin) por cada aparición de
	// cada motivo en el ADN.
	vector<Event> events;
	for (int i = 0; i < patterns.size(); ++i) {
		auto starts = kmpSearch(strand, patterns[i]);
		for (auto start : starts) {
			events.push_back({start, i, true});
			events.push_back({start + (int)patterns[i].size() - 1, i, false});
		}
	}

	sort(events.begin(), events.end());

	// Pasada de ventana deslizante sobre los eventos.
	// distinct_in_window cuenta cuántos motivos distintos tienen al menos una
	// aparición completamente contenida en la ventana actual.
	int min_length = 1e9;
	deque<Event> window;
	int distinct_in_window = 0;
	vector<int> freq(patterns.size(), 0);
	for (auto& [pos, id, is_start] : events) {
		// Añadimos el evento a la ventana
		increase(window, distinct_in_window, freq, {pos, id, is_start}, patterns);

		// Si la ventana tiene K motivos distintos, anotamos la longitud por si
		// fuese la más corta que hemos visto hasta ahora, y contraemos por la
		// izquierda hasta que ya no contenga K motivos y tenga sentido seguir
		// haciéndola crecer en la siguiente iteración.
		while (distinct_in_window == K) {
			min_length = min(min_length, window_length(window));
			decrease(window, distinct_in_window, freq);
		}
	}

	if (min_length == 1e9) cout << 0 << "\n";
	else cout << min_length << "\n";
}
