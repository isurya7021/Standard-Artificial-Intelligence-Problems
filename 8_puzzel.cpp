#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

map <vector<vector<int>>, bool> mp;

class node {
public:
    node* parent;
    vector <vector <int>> mat;
    vector <node*> children;

    node (vector <vector <int>> _mat, node* _parent) {
        mat = _mat;
        parent = _parent;
    }
    node (vector <vector <int>> _mat, vector <node*> _children) {
        mat = _mat;
        children = _children;
    }
};

pair <int,int> getIndex(vector <vector <int>> _tp, int cr) {
    pair <int, int> index;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (_tp[i][j] == cr) {
                index = {i,j};
                break;
            }
        }
    }
    return index;
}

node* modify(node* t) {

    vector <vector <int>> tp = t->mat;

    auto [x,y] = getIndex(tp, -1);
    node *f, *s, *th, *fr;
    f = s = th = fr = NULL;

    if (y+1 < 3) {
        swap(tp[x][y], tp[x][y+1]);
        if (!mp[tp])
            f = new node(tp, t);
        swap(tp[x][y], tp[x][y+1]);
    }
    if (y-1 >= 0) {
        swap(tp[x][y], tp[x][y-1]);
        if (!mp[tp])
            s = new node(tp, t);
        swap(tp[x][y], tp[x][y-1]);
    }
    if (x+1 < 3) {
        swap(tp[x][y], tp[x+1][y]);
        if (!mp[tp])
            th = new node(tp, t);
        swap(tp[x][y], tp[x+1][y]);
    }
    if (x-1 >= 0) {
        swap(tp[x][y], tp[x-1][y]);
        if (!mp[tp])
            fr = new node(tp, t);
        swap(tp[x][y], tp[x-1][y]);
    }

    if (f)
        t->children.push_back(f);
    if (s)
        t->children.push_back(s);
    if (th)
        t->children.push_back(th);
    if (fr)
        t->children.push_back(fr);

    return t;
}

int main() {

    vector <vector <int>> initial = {{1,2,3},{4,-1,5},{7,8,6}};
    vector <vector <int>> goal = {{1,2,3},{4,5,6},{7,8,-1}};

    queue <node*> q;
    node* p = new node(initial, NULL);
    q.push(p);
    node* m;

    while (q.size()) {
        node* t = q.front();
        q.pop();

        if (t->mat == goal) {
            m = t;
            break;
        }

        if (mp[t->mat])
            continue;

        mp[t->mat] = true;

        t = modify(t);
        for (auto i: t->children) {
            q.push(i);
        }
    }

    vector<vector<vector<int>>> result; 
    while (m) {
        result.push_back(m->mat);
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