#include <bits/stdc++.h>
using namespace std;

void test_case() {
	array<array<string, 8>, 8> board;
	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			if ((r + c) % 2 == 0) board[r][c] = "\u25FC";
			else board[r][c] = "\u25FB";
		}
	}

	int P;
	cin >> P;
	while (P--) {
		cin.ignore();
		char C;
		string X;
		cin >> C >> X;

		int r, c;
		c = X[0] - 'a';
		r = X[1] - '1';

		switch(C) {
			case 'R':
				board[r][c] = "\u2654";
				break;
			case 'D':
				board[r][c] = "\u2655";
				break;
			case 'T':
				board[r][c] = "\u2656";
				break;
			case 'A':
				board[r][c] = "\u2657";
				break;
			case 'C':
				board[r][c] = "\u2658";
				break;
			case 'P':
				board[r][c] = "\u2659";
				break;
			case 'r':
				board[r][c] = "\u265A";
				break;
			case 'd':
				board[r][c] = "\u265B";
				break;
			case 't':
				board[r][c] = "\u265C";
				break;
			case 'a':
				board[r][c] = "\u265D";
				break;
			case 'c':
				board[r][c] = "\u265E";
				break;
			case 'p':
				board[r][c] = "\u265F";
				break;
		}
	}

	for (int r = 0; r < 8; ++r) {
		for (int c = 0; c < 8; ++c) {
			cout << board[r][c];

			if (c == 7) cout << "\n";
			else cout << "  ";
		}
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) {
		test_case();
	}
}
