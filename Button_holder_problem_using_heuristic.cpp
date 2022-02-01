#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

unordered_map <int, int> position;
map <vector <deque<int>>, bool> vis;

class node {
public:
	node* parent;
	int f;
	int g;
	int s;
	vector <deque<int>> v;
	vector <node*> children;
	node(int _s, int _f, int _g, vector <deque<int>> _v, node* _parent) {
		s = _s;
		f = _f;
		g = _g;
		v = _v;
		parent = _parent;
	}
};

int heuristic(vector <deque<int>> v) {
	int hVal = 0;
	for (int i = 0; i < v.size(); i++) {
		while (v[i].size()) {
			int x = v[i].front();
			v[i].pop_front();
			if (position[x] != i)
				hVal += 2;
		}
	}
	return hVal;
}

void addChildren(node *p) {
	vector <deque<int>> v = p->v;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size()) {
			int x = v[i].front();
			v[i].pop_front();
			for (int j = 0; j < v.size(); j++) {
				v[j].push_back(x);
				int g = (p->g)+1;
				int f = g+heuristic(v);
				int s = (p->s)+2;
				p->children.push_back(new node(s,f,g,v,p));
				v[j].pop_back();
			}
			v[i].push_front(x);
		}
	}
}

int main() {

	int t; cin >> t;
	while (t--) {
		int nbh; cin >> nbh;
		vector <deque<int>> initial(nbh);
		vector <deque<int>> goal(nbh);

		for (int i = 0; i < nbh; i++) {
			int eibh; cin >> eibh;
			for (int j = 0; j < eibh; j++) {
				int btn; cin >> btn;
				initial[i].push_back(btn);
			}
		} 

		for (int i = 0; i < nbh; i++) {
			int eibh; cin >> eibh;
			for (int j = 0; j < eibh; j++) {
				int btn; cin >> btn;
				goal[i].push_back(btn);
				position[btn] = i;
			}
		} 

		node* root = new node(0, 0, 0, initial, NULL);
		priority_queue <pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> pq;
		pq.push({0, root});
		node* m = NULL;
		bool found = false;

		while (pq.size()) {
			auto [x, p] = pq.top();
			pq.pop();

			if (p->v == goal) {
				cout << p->s << endl;
				found = true;
				m = p;
				break;
			}

			if (vis[p->v])
				continue;
			vis[p->v] = true;

			addChildren(p);
			for (auto i: p->children) {
				pq.push({i->f, i});
			}
		}

		if (!found)
			cout << -1 << endl;
		else {
			vector <vector <deque<int>>> ans; 
			while (m) {
				ans.push_back(m->v);
				m = m->parent;
			}

			reverse(ans.begin(), ans.end());

			for (auto i: ans) {
				for (auto j: i) {
					cout << j.size() << " ";
					while (j.size()) {
						cout << j.front() << " ";
						j.pop_front();
					}
					cout << endl;
				}
				cout << endl;
			}
		}
	}
}