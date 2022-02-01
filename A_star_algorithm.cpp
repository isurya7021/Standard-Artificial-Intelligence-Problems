#include<bits/stdc++.h>
#define fio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define int long long
#define endl "\n"
using namespace std;

map <pair<int,int>, bool> vis;
int n,m;
vector <vector <int>> grid;
pair <int,int> goal;
const int dx[] = {0,1,0,-1,1,-1,-1,1};
const int dy[] = {1,0,-1,0,1,-1,1,-1};

class node {
public:
    node* parent;
    pair <int,int> index;
    int d;
    int f;
    int g;
    vector <node*> children;
    node(pair <int,int> _index, int _f, int _g, int _d, node* _parent) {
        index = _index;
        f = _f;
        g = _g;
        d = _d;
        parent = _parent;
    }
};

int calcHeuristic(pair<int,int> index) {
    
    int dx = (goal.first-index.first);
    int dy = (goal.second-index.second);
    return sqrt(dx*dx + dy*dy);
}

bool isValid(int x, int y) {
    if ((0 <= x) && (x < n) && (0 <= y) && (y < m) && grid[x][y] != 1)
        return true;
    return false;
}

node* modify(node* p) {
    auto [x,y] = p->index;
    for (int i = 0; i < 8; i++) {
        if (isValid(x+dx[i], y+dy[i])) {
            pair <int,int> nidx;
            nidx = {x+dx[i], y+dy[i]};
            int g = (p->g)+1;
            int f = g+calcHeuristic(nidx);
            int d = p->d+1;
            p->children.push_back(new node(nidx,f,g,d,p));
        }
    }
    return p;
}

signed main() {

    fio
    cin >> n >> m;
    grid.resize(n, vector <int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    pair <int,int> src;
    cin >> src.first >> src.second;
    cin >> goal.first >> goal.second;

    node* root = new node(src, 0, 0, 0, NULL);
    priority_queue <pair<int,node*>, vector <pair<int,node*>>, greater<pair<int,node*>>> pq; 
    pq.push({0, root});
    node* m = NULL;
    int mx = INT_MAX;

    while (pq.size()) {
        auto [x,p] = pq.top();
        pq.pop();

        if (vis[p->index])
            continue;

        if (p->index == goal) {
            if (p->d < mx) {
                mx = p->d;
                m = p;
            }
        }

        vis[p->index] = true; 

        p = modify(p);
        for (auto i: p->children) {
            pq.push({i->f, i});
        }
    }

    while (m) {
        auto [x,y] = m->index;
        cout << x << " " << y << endl;
        m = m->parent;
    }
}