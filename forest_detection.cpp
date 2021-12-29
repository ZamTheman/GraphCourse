#include<bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    list<pair<int,int>> l;
public:
    Graph(int V) {
        this->V = V;
    }
    
    int addEdge(int u, int v) {
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

    bool contains_cycle() {
        unique_ptr<int[]> parent(new int[V + 1]);
        for (size_t i = 0; i < V; i++)
            parent[i] = -1;

        for (auto edge : l) {
            auto i = edge.first;
            auto j = edge.second;
            auto s1 = findSet(i, parent);
            auto s2 = findSet(j, parent);

            if (s1 != s2)
                unionSet(s1, s2, parent);
            else {
                cout << "Same parents: " << s1 << " and " << s2 << endl;
                return true;
            }
        }

        return false;
    }
};


bool solve(vector<vector<int>> edges) {
    int maxVal;
    for (auto edge : edges)
        if (max(edge[0], edge[1]) > maxVal)
            maxVal = max(edge[0], edge[1]);

    Graph g(maxVal);
    for (auto edge : edges)
        g.addEdge(edge[0], edge[1]);

    return !g.contains_cycle();
};

int main() {
    vector<vector<int>> edges {
        { 0, 1 },
        { 0, 2 },
        { 3, 4 },
        { 4, 5 }
    };

    cout << solve(edges) << endl;
}