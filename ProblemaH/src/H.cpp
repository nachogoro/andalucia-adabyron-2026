#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int cap;
		cin >> cap;
		cin.ignore();

		string line;
		getline(cin, line);

		int peopleIn = 0;

		for (auto r : line) {
			if (r == 'E') {
				peopleIn++;
				if (peopleIn > cap) break;
			} else {
				peopleIn--;
				if (peopleIn < 0) break;
			}
		}

		cout << ((peopleIn == 0) ? "VALIDO\n" : "INVALIDO\n");
	}
}
