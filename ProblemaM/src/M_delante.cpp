#include <bits/stdc++.h>
using namespace std;

// Simulación hacia delante: procesamos los niveles en orden creciente y,
// para cada copa, repartimos su excedente entre sus cuatro hijos. Cuando
// llegamos a una copa todas las aportaciones de los padres ya están
// acumuladas en su flujo, así que basta una pasada por la pirámide.
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	double L;
	int H;
	cin >> L >> H;

	vector<vector<vector<double>>> cap(H), flujo(H);
	for (int n = 0; n < H; ++n) {
		int lado = n + 1;
		cap[n].assign(lado, vector<double>(lado));
		flujo[n].assign(lado, vector<double>(lado, 0.0));
		for (int f = 0; f < lado; ++f)
			for (int c = 0; c < lado; ++c)
				cin >> cap[n][f][c];
	}

	flujo[0][0][0] = L;
	for (int n = 0; n + 1 < H; ++n) {
		int lado = n + 1;
		for (int f = 0; f < lado; ++f) {
			for (int c = 0; c < lado; ++c) {
				double sobra = flujo[n][f][c] - cap[n][f][c];
				if (sobra <= 0) continue;
				double parte = sobra / 4.0;
				flujo[n+1][f  ][c  ] += parte;
				flujo[n+1][f+1][c  ] += parte;
				flujo[n+1][f  ][c+1] += parte;
				flujo[n+1][f+1][c+1] += parte;
			}
		}
	}

	int Q;
	cin >> Q;
	cout << fixed << setprecision(6);
	while (Q--) {
		int n, f, c;
		cin >> n >> f >> c;
		cout << min(cap[n][f][c], flujo[n][f][c]) << "\n";
	}
	return 0;
}
