#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	cin >> N;

	int count = 0;
	while (N != 6174) {
		vector<int> digits(4);
		digits[0] = (N / 1000) % 10;
		digits[1] = (N / 100)  % 10;
		digits[2] = (N / 10)   % 10;
		digits[3] = N          % 10;

		sort(digits.begin(), digits.end());
		int min = digits[0]*1000 + digits[1]*100 + digits[2]*10 + digits[3];

		int max = digits[0] + digits[1]*10 + digits[2]*100 + digits[3]*1000;

		N = max - min;
		count++;
	}
	cout << count << "\n";
}
