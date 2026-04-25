#include <bits/stdc++.h>
using namespace std;

using vvvd = vector<vector<vector<double>>>;

double L;

bool exists(const vvvd& cap, int n, int f, int c) {
	return !(n < 0 || f < 0 || c < 0
			|| n >= cap.size()
			|| f >= cap[n].size()
			|| c >= cap[n][f].size());
}

double capacity(const vvvd& cap, int n, int f, int c) {
	if (!exists(cap, n, f, c)) {
		// Non existent
		return 0.0;
	}

	return cap[n][f][c];
}

int valid_children(const vvvd& cap, int n, int f, int c) {
	// Does not exist, return 1.0 to avoid division by zero
	if (!exists(cap, n, f, c)) return 1.0;

	int children = 0;
	if (exists(cap, n+1, f, c)) children++;
	if (exists(cap, n+1, f+1, c)) children++;
	if (exists(cap, n+1, f, c+1)) children++;
	if (exists(cap, n+1, f+1, c+1)) children++;
	return children;
}

double query(const vvvd& cap, vvvd& flow, int n, int f, int c) {
	if (!exists(cap, n, f, c)) {
		// Out of range, assume empty
		return 0;
	}

	if (flow[n][f][c] > -0.5) return flow[n][f][c];

	// Uncached, need to compute it
	if(n == 0 && f == 0 && c == 0) {
		flow[n][f][c] = L;
		return L;
	}

	auto parent_contribution = [&cap, &flow](int n, int f, int c) {
		auto flow_to = query(cap, flow, n, f, c);
		auto capacity_of = capacity(cap, n, f, c);
		auto children_of = valid_children(cap, n, f, c);
		auto result = max(0.0, flow_to - capacity_of) / children_of;

		return result;
	};

	// Lo que se bosa de cada padre a este hijo
	double f1 = parent_contribution(n-1, f, c);
	double f2 = parent_contribution(n-1, f, c-1);
	double f3 = parent_contribution(n-1, f-1, c);
	double f4 = parent_contribution(n-1, f-1, c-1);

	flow[n][f][c] = f1 + f2 + f3 + f4;
	return f1 + f2 + f3 + f4;
}

int main() {
	int H;
	cin >> L >> H;

	vvvd cap(H);
	vvvd flow(H);
	for (int i = 0; i < H; ++i) {
		cap[i] = vector<vector<double>>(i+1);
		flow[i] = vector<vector<double>>(i+1);
		for (int j = 0; j < (i+1); ++j) {
			for (int k = 0; k < (i+1); ++k) {
				double v;
				cin >> v;
				cap[i][j].push_back(v);
				flow[i][j].push_back(-1.0);
			}
		}
	}

	int Q;
	cin >> Q;
	while (Q--) {
		int n, f, c;
		cin >> n >> f >> c;
		cout << setprecision(6) << fixed << min(cap[n][f][c], query(cap, flow, n, f, c)) << "\n";
	}
}
