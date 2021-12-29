#include<bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    list<pair<int,int>> l;
public:
    Graph(int V) {
        this->V = V;
    }
    
    void addEdge(int u, int v) {
        l.push_back(make_pair(u,v));
    }

    int findSet(int i, unique_ptr<int[]> &parent) {
        if (parent[i] == -1)
            return i;

        return findSet(parent[i], parent);
    }

    void unionSet(int x, int y, unique_ptr<int[]> &parent) {
        auto s1 = findSet(x, parent);
        auto s2 = findSet(y, parent);

        if (s1 != s2)
            parent[s1] = s2;
    }
};

vector<bool> DSU(vector<vector<int>>query)
{
    vector<bool> response;
    int maxNode = -1;
    for (auto q : query)
        if (q[1] > maxNode || q[2] > maxNode)
            maxNode = max(q[1], q[2]);

    unique_ptr<int[]> parent(new int[maxNode + 1]);
    for (size_t i = 0; i < maxNode + 1; i++)
        parent[i] = -1;

    Graph g {maxNode + 1};
    for (auto q : query) {
        if (q[0] == 1) {
            g.unionSet(q[1], q[2], parent);
        }
        else {
            auto s1 = g.findSet(q[1], parent);
            auto s2 = g.findSet(q[2], parent);
            response.push_back(s1 == s2);
        }
    }

    return response;
}

int main() {
    vector<vector<int>> query {
        { 1, 1, 2 },
        { 1, 1, 3 },
        { 2, 1, 4 },
        { 2, 2, 3 }
    };

    auto resp = DSU(query);
    for (auto r : resp)
        cout << r << endl;
}