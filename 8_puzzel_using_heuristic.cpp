#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

pair<int, int> mp[9];
map <vector<vector<int>>,  bool> vis;

class node {
public:
    node* parent;
    int f;
    int g;
    vector <vector <int>> v;
    vector <node*> children;
    node(vector <vector <int>> _v, int _f, int _g, node* _parent) {
        v = _v;
        f = _f;
        g = _g;
        parent = _parent;
    }
};

pair <int, int> getIndex(vector <vector <int>> &v) {
    pair <int, int> index;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (v[i][j] == 0) {
                index = {i,j};
                break;
            }
        }
    }
    return index;
}

int calcHeuristic(vector <vector <int>> &v) {

    int val = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            pair<int, int> idx = mp[v[i][j]];
            val += abs(idx.first-i)+abs(idx.second-j);
        }
    }
    return val;
}

node* modify(node* p) {
    vector <vector <int>> v = p->v;
    auto [x,y] = getIndex(v);
    if (y+1 < 3) {
        swap(v[x][y], v[x][y+1]);
        int g = (p->g)+1;
        int f = g + calcHeuristic(v);
        p->children.push_back(new node(v,f,g,p));
        swap(v[x][y], v[x][y+1]);
    }
    if (y-1 >= 0) {
        swap(v[x][y], v[x][y-1]);
        int g = (p->g)+1;
        int f = g + calcHeuristic(v);
        p->children.push_back(new node(v,f,g,p));
        swap(v[x][y], v[x][y-1]);
    }
    if (x+1 < 3) {
        swap(v[x][y], v[x+1][y]);
        int g = (p->g)+1;
        int f = g + calcHeuristic(v);
        p->children.push_back(new node(v,f,g,p));
        swap(v[x][y], v[x+1][y]);
    }
    if (x-1 >= 0) {
        swap(v[x][y], v[x-1][y]);
        int g = (p->g)+1;
        int f = g + calcHeuristic(v);
        p->children.push_back(new node(v,f,g,p));
        swap(v[x][y], v[x-1][y]);
    }
    return p;
}

int main() {

    mp[1] = {0,0};
    mp[2] = {0,1};
    mp[3] = {0,2};
    mp[4] = {1,0};
    mp[5] = {1,1};
    mp[6] = {1,2};
    mp[7] = {2,0};
    mp[8] = {2,1};
    mp[0] = {2,2};

    vector <vector <int>> initial = {{1,2,3},{4,0,5},{7,8,6}};
    vector <vector <int>> goal = {{1,2,3},{4,5,6},{7,8,0}};

    

    node* root = new node(initial, 0, 0, NULL);
    priority_queue <pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> pq;
    node* m = NULL;
    int mx = INT_MAX;

    pq.push({root->f, root});
    while (pq.size()) {
        auto [x,p] = pq.top();
        pq.pop();

        if (p->v == goal) {
            if (p->f < mx) {
                mx = p->f;
                m = p;
            }
        }

        if (vis[p->v])
            continue;
        vis[p->v] = true;

        p = modify(p);
        for (auto i: p->children) {
            pq.push({i->f, i});
        }
    }

    vector<vector<vector<int>>> result; 
    while (m) {
        result.push_back(m->v);
        m = m->parent; 
    }

    reverse(result.begin(), result.end());

    for (auto mat: result) {
        for (auto vec: mat) {
            for (auto i: vec) {
                cout << i << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}