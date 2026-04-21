#include <bits/stdc++.h>
using namespace std;

int main() {
	array<array<int, 3>, 12> A;
	array<array<bool, 12>, 12> MB;

	// Leemos la matriz inicial
	for (int r = 0; r < 12; ++r) {
		for (int c = 0; c < 3; ++c) {
			cin >> A[r][c];
		}
	}

	// Convertimos cada entero en 4 bits de MB
	for (int r = 0; r < 12; ++r) {
		for (int c = 0; c < 3; ++c) {
			int n = A[r][c] & 0xF;
			MB[r][4*c]   = (n >> 3) & 1;
			MB[r][4*c+1] = (n >> 2) & 1;
			MB[r][4*c+2] = (n >> 1) & 1;
			MB[r][4*c+3] =  n       & 1;
		}
	}

	// Rotamos cada submatriz
	for (int r = 1; r < 12; r += 3) {
		for (int c = 1; c < 12; c += 3) {
			deque<bool> s;
			s.push_back(MB[r-1][c-1]);
			s.push_back(MB[r-1][c]);
			s.push_back(MB[r-1][c+1]);
			s.push_back(MB[r][c+1]);
			s.push_back(MB[r+1][c+1]);
			s.push_back(MB[r+1][c]);
			s.push_back(MB[r+1][c-1]);
			s.push_back(MB[r][c-1]);

			int n = 0;
			for (auto b : s) {
				if (b) n++;
			}

			bool clockwise = MB[r][c];

			while (n--) {
				if (clockwise) {
					s.push_front(s.back());
					s.pop_back();
				} else {
					s.push_back(s.front());
					s.pop_front();
				}
			}

			MB[r-1][c-1] = s.front(); s.pop_front();
			MB[r-1][c] = s.front(); s.pop_front();
			MB[r-1][c+1] = s.front(); s.pop_front();
			MB[r][c+1] = s.front(); s.pop_front();
			MB[r+1][c+1] = s.front(); s.pop_front();
			MB[r+1][c] = s.front(); s.pop_front();
			MB[r+1][c-1] = s.front(); s.pop_front();
			MB[r][c-1] = s.front(); s.pop_front();
		}
	}

	for (int c = 0; c < 12; ++c) {
		int n = 0;
		for (int r = 0; r < 12; ++r) {
			n = (n << 1) | MB[r][c];
		}
		cout << n;
		if (c == 11) cout << "\n";
		else cout << " ";
	}
}
