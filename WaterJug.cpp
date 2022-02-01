#include<bits/stdc++.h>
#define int long long
#define endl "\n"
#define j1 4
#define j2 9
using namespace std;

class node {
public:
    node* parent;
    pair <int, int> index;
    node(pair <int, int> _index, node* _parent) {
        index = _index;
        parent = _parent;
    }
};

signed main() {

    for (int i = 1; i <= 9; i++) {
        node* root = new node({0,0}, NULL);
        queue <node*> q;
        q.push({root});
        node* m = NULL;

        while (q.size()) {
            node* p = q.front();
            q.pop();
            auto [x,y] = p->index;

            if (x == i || y == i) {
                m = p;
                break;
            }

            if (x < j1) 
                q.push(new node({j1, y}, p));

            if (y < j2) 
                q.push(new node({x,j2}, p));

            if (x > 0)
                q.push(new node({0,y}, p));

            if (y > 0)
                q.push(new node({x,0}, p));

            if (x > 0 && y < j2) {
                if (j2-y >= x) {
                    q.push(new node({0,y+x}, p));
                }
                else {
                    q.push(new node({x-j2+y, j2}, p));
                }
            }

            if (y > 0 && x < j1) {
                if (j1-x >= y) {
                    q.push(new node({x+y, 0}, p));
                }
                else {
                    q.push(new node({j1,y-j1+x},p));
                }
            }
        }

        vector <pair<int,int>> ans;

        while (m) {
            ans.push_back(m->index);
            m = m->parent;
        }

        reverse(ans.begin(), ans.end());

        cout << "For : " << i << endl; 

        for (auto [x,y]: ans)
            cout << x << " " << y << endl;
        cout << endl;
    }

}