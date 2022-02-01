#include<bits/stdc++.h>
#define endl "\n"
using namespace std;

class node {
public:
    int val;
    int level;
    int dist;
    unordered_map <int, bool> mp;

    node (int _val, int _level, int _dist) {
        val = _val;
        level = _level;
        dist = _dist;
    }
};

int main() {

    int nv, ne; cin >> nv >> ne;
    vector <pair <int, int>> graph[nv+1];

    for (int i = 0; i < ne; i++) {
        int u, v, c; cin >> u >> v >> c;
        graph[u].push_back({v,c}); 
        graph[v].push_back({u,c}); 
    }

    int src; cin >> src;
    node* root = new node(src, 1, 0);
    queue <node*> q;
    q.push(root);
    int sDist = INT_MAX;

    while (q.size()) {
        node* p = q.front();
        q.pop();

        for (auto [a,b]: graph[p->val]) {
            if (!(p->mp)[a] || (a == src && (p->level) == nv)) {

                if (a == src) {
                    sDist = min(sDist, (p->dist)+b);
                }
                node* tp = new node(a, (p->level)+1, (p->dist)+b);
                tp->mp = p->mp;
                (tp->mp)[p->val] = true;
                q.push(tp);
            }
        }
    }

    cout << sDist;
}
