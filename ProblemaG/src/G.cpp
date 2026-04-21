#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool factible(ll H, ll K, const vector<ll>& sums) {
	int N = (int)sums.size() - 1;
	int pos = 0;

	for (int b = 0; b < K; ++b) {
		if (pos == N) return true; // ya hemos cubierto toda la muralla

		ll objetivo = sums[pos] + H;

		// upper_bound devuelve el primer valor estrictamente > objetivo;
		// el índice anterior a ese es el mayor j con sums[j] <= sums[pos] + H.
		auto it = upper_bound(sums.begin() + pos, sums.end(),
				objetivo);
		int j = int(it - sums.begin()) - 1;

		if (j == pos) return false;
		pos = j;
	}

	return pos == N;
}

int main() {
	int N, K;
	while (cin >> N >> K) {
		// prefix_sum[i]: sum(h[0]...h[i-1]) (suma de las primeras i alturas)
		vector<ll> prefix_sum(N + 1, 0);
		ll max_v = 0;
		for (int i = 1; i <= N; ++i) {
			ll v;
			cin >> v;
			prefix_sum[i] = prefix_sum[i-1] + v;
			max_v = max(max_v, v);
		}

		ll lo = max_v, hi = prefix_sum[N];
		while (lo < hi) {
			ll mid = lo + (hi - lo) / 2;
			if (factible(mid, K, prefix_sum)) hi = mid;
			else lo = mid + 1;
		}

		cout << lo << "\n";
	}
}
