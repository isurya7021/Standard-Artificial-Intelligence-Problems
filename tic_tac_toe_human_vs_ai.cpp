#include<bits/stdc++.h>
using namespace std;
char user = 'x';
char computer = 'o';

int getResult(vector<string> &board) {

	bool incmp = false;
	int x1 = 0, o1 = 0;
	int x2 = 0, o2 = 0;
	int x3 = 0, o3 = 0;
	int x4 = 0, o4 = 0;
	for(int i = 0; i < 3; i++) {
		x1 = 0, o1 = 0;
		x2 = 0, o2 = 0;
		for (int j = 0; j < 3; j++) {

			if (board[i][j] == '.')
				incmp = true;

			if (board[i][j] == 'x')
				x1++;
			if (board[i][j] == 'o')
				o1++;
			if (board[j][i] == 'x')
				x2++;
			if (board[j][i] == 'o')
				o2++;
			if (i == j && board[i][j] == 'x')
				x3++;
			if (i == j && board[i][j] == 'o')
				o3++;
			if (i+j == 2 && board[i][j] == 'x')
				x4++;
			if (i+j == 2 && board[i][j] == 'o')
				o4++;
		}
		if (x1 == 3)
			return -1;
		if (o1 == 3)
			return 1;
		if (x2 == 3)
			return -1;
		if (o2 == 3)
			return 1;
		if (x3 == 3)
			return -1;
		if (o3 == 3)
			return 1;
	}

	if (incmp)
		return 3;
	else
		return 0;
}

int minimax(vector<string> &board, bool isMax) {

	int result = getResult(board);
	if (result < 3) {
		return result;
	}

	if(isMax) {
		int bestscore = INT_MIN;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '.') {
					board[i][j] = computer;
					int score = minimax(board, false);
					bestscore = max(score, bestscore);
					board[i][j] = '.';
				}
			}
		}
		return bestscore; 
	}
	else {
		int bestscore = INT_MAX;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '.') {
					board[i][j] = user;
					int score = minimax(board, true);
					bestscore = min(score, bestscore);
					board[i][j] = '.';
				}
			}
		}
		return bestscore;
	}
}
pair <int, int> getbestmove(vector<string> &board) {
	int bestscore = INT_MIN;
	int x = 0, y = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '.') {
				board[i][j] = computer;
				int score = minimax(board, false);
				if (score > bestscore) {
					bestscore = score;
					x = i;
					y = j;
				}
				board[i][j] = '.';
			}
		}
	}
	return {x,y};
}

void display(vector<string> &board) {
	for (auto i: board) {
		for (auto j: i) {
			cout << j << " ";
		}
		cout << endl;
	}
}

void solve(vector <string> &board, bool isUser, int c) {
	while (c < 9) {
		if (isUser) {
			cout << "User's turn" << endl;
			int x, y;
			cin >> x >> y;
			if (board[x][y] == '.')
				board[x][y] = user;
			isUser = false;
			c++;
		}
		else {
			cout << "computer's turn" << endl;
			pair <int, int> tp = getbestmove(board);
			board[tp.first][tp.second] = computer;
			isUser = true;
			c++;
			
		}
		int result = getResult(board);
		display(board);
		cout << endl;
		if (result == 1) {
			cout << "Computer won" << endl << endl;
			break;
		}
		cout << endl;
	}
}

int main() {
	vector <string> board(3, string(3,'.'));
	solve(board, true, 0);
}