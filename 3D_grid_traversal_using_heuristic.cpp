#include<bits/stdc++.h>
#define fio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define int long long
#define endl "\n"
#define triple pair<int, pair<int, int>>
using namespace std;

triple goal;
vector <vector <vector <int>>> grid; 
int row, clm, hgt;
map <triple, bool> vis;

const int dx[] = {0, 0, 1, -1, 0, 0};
const int dy[] = {1, -1, 0, 0, 0, 0,};
const int dh[] = {0, 0, 0, 0, 1, -1};

class node {
public:
	int f;
	int g;
	int tm;
	triple state;
	vector <node*> children; 
	node(int _tm, int _f, int _g, triple _state) {
		tm = _tm;
		f = _f;
		g = _g;
		state = _state;
	}
};

bool isValid(int h, int r, int c) {
	if (0<=r && r<row && 0<=c && c<clm && 0<=h && h<hgt && grid[h][r][c] != 0)
		return true;
	return false;
}

int heuristic(int h, int r, int c) {
	int dh = abs(goal.first-h);
	int dx = abs(goal.second.first - r);
	int dy = abs(goal.second.second - c);
	return (dh+dx+dy);
}

void addChildren(node* p) {
	auto [h,pp] = p->state;
	auto [x,y] = pp;
	int mx = 6; 

	if (grid[h][x][y] != 2)
		mx = 4;

	for (int i = 0; i < mx; i++) {

		if (isValid(h+dh[i], x+dx[i], y+dy[i])) {
			triple state;
			state = {h+dh[i], {x+dx[i], y+dy[i]}};
			int g = (p->g)+1;
			int f = g + heuristic(h+dh[i], x+dx[i], y+dy[i]);
			int tm = (p->tm)+1;
			if (dh[i] == 1)
				tm += 1;
			p->children.push_back(new node(tm, f, g, state));
		}
	}
}

signed main() {

	fio
	int t; cin >> t;
	while (t--) {
		cin >> row >> clm >> hgt;
		grid.resize(hgt, vector <vector <int>> (row, vector <int> (clm)));

		for (int i = 0; i < hgt; i++) {
			for (int j = 0; j < row; j++) {
				for (int k = 0; k < clm; k++) {
					cin >> grid[i][j][k];
				}
			}
		} 

		int q; cin >> q;
		while (q--) {
			triple initial;
			cin >> initial.first >> initial.second.first >> initial.second.second;
			cin >> goal.first >> goal.second.first >> goal.second.second;


			node* root = new node(0, 0, 0, initial);
			priority_queue <pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> pq;
			pq.push({root->f, root});

			while (pq.size()) {
				auto [x, p] = pq.top();
				pq.pop();

				if (p->state == goal) {
					cout << p->tm << endl;
					break;
				}

				if (vis[p->state])
					continue;
				vis[p->state] = true;

				addChildren(p);
				for (auto i: p->children) 
					pq.push({i->f, i});
			} 
		} 
		grid.clear();
	}
}