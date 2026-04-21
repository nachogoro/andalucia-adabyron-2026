#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct BIT {
	int n; vector<ll> t;
	BIT(int n): n(n), t(n+1, 0) {}

	void update(int i, ll delta) { // 1-indexed
		for(; i<=n; i+=i&(-i)) t[i]+=delta;
	}

	ll query(int i) { // sum [1..i]
		ll s=0;
		for(; i>0; i-=i&(-i)) s+=t[i];
		return s;
	}

	ll query(int l, int r) { return query(r)-query(l-1); }

	ll exact(int i) { return query(i, i); }
};

struct Query {
	int v, l, r, pos;
	bool operator<(const Query& o) const {
		if (v != o.v) return v < o.v;
		if (l != o.l) return l < o.l;
		if (r != o.r) return r < o.r;
		return pos < o.pos;
	}
};

int main() {
	int N, Q;
	cin >> N >> Q;
	BIT fen(N);

	for (int i = 1; i <= N; ++i) {
		ll val;
		cin >> val;
		fen.update(i, val);
	}

	string line;
	getline(cin, line);

	deque<pair<int, int>> updates;
	vector<Query> queries;

	while (Q--) {
		getline(cin, line);
		istringstream iss(line.substr(1));

		if (line[0] == 'S') {
			int v, l, r;
			iss >> v >> l >> r;
			queries.push_back({v, l, r, (int)queries.size()});
		} else {
			int i, x;
			iss >> i >> x;
			updates.push_back({i, x});
		}
	}

	sort(queries.begin(), queries.end());

	vector<ll> answers(queries.size());
	int version = 0;
	for (auto [v, l, r, pos] : queries) {
		while (version < v) {
			auto [i, x] = updates.front();
			updates.pop_front();
			auto cv = fen.exact(i);
			fen.update(i, x - cv);
			version++;
		}

		answers[pos] = fen.query(l, r);
	}

	for (auto ans : answers) {
		cout << ans << "\n";
	}
}
