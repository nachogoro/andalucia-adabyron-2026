#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // --- Fase 1: registro y cancelaciones ---
    vector<long long> S;
    long long p;
    while (cin >> p) {
        if (p >= 0) {
            S.push_back(p);
        } else {
            long long cnt = -p;
            if ((long long)S.size() <= cnt) S.clear();
            else S.resize(S.size() - (size_t)cnt);
        }
    }

    // --- Fase 2: reordenación por bloques de 4 ---
    vector<long long> E;
    E.reserve(S.size());
    for (size_t i = 0; i < S.size(); i += 4) {
        size_t fin = min(i + 4, S.size());
        for (size_t j = i; j < fin; ++j)
            if (S[j] % 2 == 0) E.push_back(S[j]);
        for (size_t j = i; j < fin; ++j)
            if (S[j] % 2 != 0) E.push_back(S[j]);
    }

    // --- Salida ---
    // Nota: a pesar de lo que decía el enunciado original, durante el
    // concurso se corrigió que la salida SÍ lleva salto de línea al final.
    if (E.empty()) {
        cout << "NOPROCESO\n";
    } else {
        for (size_t i = 0; i < E.size(); ++i) {
            if (i) cout << ' ';
            cout << E[i];
        }
        cout << '\n';
    }
    return 0;
}
