#include <bits/stdc++.h>
using namespace std;

// Union-Find con compresión de caminos y unión por rango.
struct UnionFind {
	vector<int> padre, rango;
	UnionFind(int n) : padre(n), rango(n, 0) {
		iota(padre.begin(), padre.end(), 0);
	}
	int buscar(int x) {
		return padre[x] == x ? x : padre[x] = buscar(padre[x]);
	}
	bool unir(int a, int b) {
		a = buscar(a); b = buscar(b);
		if (a == b) return false;
		if (rango[a] < rango[b]) swap(a, b);
		padre[b] = a;
		if (rango[a] == rango[b]) rango[a]++;
		return true;
	}
};

struct Arista {
	long long peso;
	int u, v;
	bool operator<(const Arista& o) const { return peso < o.peso; }
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int N;
	cin >> N;

	vector<vector<int>> dist(N, vector<int>(N));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> dist[i][j];

	vector<vector<char>> material(N, vector<char>(N));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> material[i][j];

	// Trabajamos en "días por km" para mantenernos en enteros: los cuatro
	// materiales dan valores exactos (1000, 250, 100, 50) al invertir m/día
	// y multiplicar por los 1000 metros de un km.
	auto diasPorKm = [](char m) {
		switch (m) {
			case 'G': return 1000;
			case 'A': return 250;
			case 'P': return 100;
			case 'L': return 50;
		}
		return 0;
	};

	vector<Arista> aristas;
	aristas.reserve((long long)N * (N - 1) / 2);
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			long long peso = (long long)dist[i][j] * diasPorKm(material[i][j]);
			aristas.push_back({peso, i, j});
		}
	}

	sort(aristas.begin(), aristas.end());

	// Kruskal: recorremos las aristas en orden creciente y aceptamos la que
	// conecte dos componentes distintas, hasta haber cosido N-1 aristas.
	UnionFind uf(N);
	long long coste = 0;
	int usadas = 0;
	for (const auto& a : aristas) {
		if (uf.unir(a.u, a.v)) {
			coste += a.peso;
			if (++usadas == N - 1) break;
		}
	}

	cout << coste << "\n";
	return 0;
}
