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

    void unionSet(int x, int y, unique_ptr<int[]> &parent, unique_ptr<int[]> &rank) {
        auto s1 = findSet(x, parent);
        auto rankOfS1 = rank[s1];
        auto s2 = findSet(y, parent);
        auto rankOfS2 = rank[s2];

        if (s1 == s2)
            return;

        // Union by rank
        if (rank[s1] >= rank[s2]) {
            parent[s2] = s1;
            rank[s1] += rank[s2];
        }
        else {
            parent[s1] = s2;    
            rank[s2] += rank[s1];
        }
    }

    bool contains_cycle() {
        unique_ptr<int[]> parent(new int[V + 1]);
        unique_ptr<int[]> rank(new int[V + 1]);
        for (size_t i = 0; i < V; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }

        for (auto edge : l) {
            auto i = edge.first;
            auto j = edge.second;
            auto s1 = findSet(i, parent);
            auto s2 = findSet(j, parent);

            if (s1 != s2)
                unionSet(s1, s2, parent, rank);
            else {
                cout << "Same parents: " << s1 << " and " << s2 << endl;
                return true;
            }
        }

        return false;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    //g.addEdge(3,0); // Removing this should make it return 0

    cout << g.contains_cycle() << endl;
}