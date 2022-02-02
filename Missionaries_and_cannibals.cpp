#include<bits/stdc++.h>
using namespace std;

class node {
public:
	node* parent;
	int f;
	int g;
	vector <int> v;
	vector <node*> children;
	node(int _f, int _g, vector <int> _v, node* _parent) {
		f = _f;
		g = _g;
		v = _v;
		parent = _parent;
	} 
};

int heuristic(vector <int> v) {
	
	return (v[0]+v[1])-1;
}

void addChildren(node* p) {
	vector <int> v = p->v;
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			if (i+j == 0)
				continue;
			if (i+j > 2)
				break;

			if (v[4] == 0) {

				if (((v[0]-i == 0) || (v[0]-i >= v[1]-j)) && ((v[2]+i >= v[3]+j) || (v[2]+i == 0))) {
					v[0] -= i;
					v[1] -= j;
					v[2] += i;
					v[3] += j;
					v[4] = 1;
					int g = (p->g)+1;
					int f = g + heuristic(v);
					p->children.push_back(new node(f,g,v,p));
					v[0] += i;
					v[1] += j;
					v[2] -= i;
					v[3] -= j;
					v[4] = 0;
				}

			}
			else {

				if (((v[0]+i == 0) || (v[0]+i >= v[1]+j)) && ((v[2]-i >= v[3]-j) || (v[2]-i == 0))) {
					v[0] += i;
					v[1] += j;
					v[2] -= i;
					v[3] -= j;
					v[4] = 0;
					int g = (p->g)+1;
					int f = g + heuristic(v);
					p->children.push_back(new node(f,g,v,p));
					v[0] -= i;
					v[1] -= j;
					v[2] += i;
					v[3] += j;
					v[4] = 1;
				}

			}
		}
	}
}

int main() {


	vector <int> initial(5);
	vector <int> goal(5);

	for (int i = 0; i < 5; i++) 
		cin >> initial[i];

	for (int i = 0; i < 5; i++) 
		cin >> goal[i];

	int f = heuristic(initial);

	node* root = new node(f, 0, initial, NULL);
	priority_queue <pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> pq;
	pq.push({root->f, root});
	node* m = NULL;

	while (pq.size()) {
		auto [x, p] = pq.top();
		pq.pop();

		if (p->v == goal) {
			m = p;
			break;
		}

		addChildren(p);
		for (auto i: p->children)
			pq.push({i->f, i});
	}

	vector <vector <int>> ans;
	while (m) {
		ans.push_back(m->v);
		m = m->parent;
	}

	reverse(ans.begin(), ans.end());

	cout << "m1 c1  m2  c2  boat" << endl; 
	for (auto vector: ans) {
		for (auto ele: vector) {
			cout << ele << "   ";
		}
		cout << endl;
	}
}