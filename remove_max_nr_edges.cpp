#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

struct Edge {
    int w, x, y, t;
    Edge(int x, int y, int w, int t) {
        this -> w = w;
        this -> x = x;
        this -> y = y;
        this -> t = t;
    }
};

class DSU {
    std::vector<int> parent;
    std::vector<int> rank;
    
public:
    DSU(int n) {
        parent = std::vector<int>(n, -1);
        rank = std::vector<int>(n, 1);
    }

    int find(int i) {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    void unite(int x, int y) {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
                rank[s2] += rank[s1];
            }
            else{
                parent[s2] = s1;
                rank[s1] += rank[s2];
            }
        }
    }
};

class Graph {
    std::vector<std::vector<int>> edgelist;

public:
    Graph() {
    }

    std::vector<std::vector<int>> getEdgeList() {
        return edgelist;
    }

    void addEdge(int x, int y, int w, int t) {
        edgelist.push_back({w, x, y, t});
    }

    vector<Edge> kruksal_mst(int v) {
        // First sort edges by weight
        sort(edgelist.begin(), edgelist.end());
        
        // Init a DSU
        DSU dsu(v);

        int ans = 0;
        vector<Edge> usedEdges;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
            int t = edge[3];

            // Take the edge to mst if it does not form a cycle
            if (dsu.find(x) != dsu.find(y)) {
                dsu.unite(x, y);
                std::cout << "Edge used is between: " << x << " and " << y << std::endl;
                usedEdges.push_back({ x, y, w, t });
                ans += w;
            }
        }

        return usedEdges;
    }
};

bool areEqual(Edge e1, Edge e2) {
    return e1.x == e2.x && e1.y == e2.y && e1.t == e2.t;
}

int maxNumEdgesToRemove(int n, vector<vector<int>> edges) {
    for (auto r : edges)
        cout << r[0] << ", " << r[1] << ", " << r[2] << endl;
    
    Graph alice;
    Graph bob;
    vector<Edge> allEdges;
    
    for (size_t i = 0; i < edges.size(); i++)
    {
        auto x = edges[i][1];
        auto y = edges[i][2];
        auto t = edges[i][0];
        cout << x << ", " << y << endl;
        if (t == 1) {
            alice.addEdge(x, y, 10, t);
            allEdges.push_back({ x, y, 10, t });
        }
        else if (t == 2) {
            bob.addEdge(x, y, 10, t);
            allEdges.push_back({ x, y, 10, t });
        }
        else {
            alice.addEdge(x, y, 1, t);
            bob.addEdge(x, y, 1, t);
            allEdges.push_back({ x, y, 1, t });
        }
    }
     
    auto res1 = alice.kruksal_mst(n);
    auto res2 = bob.kruksal_mst(n);

    if (res1.size() != n - 1 || res2.size() != n - 1)
        return -1;

    int unused = 0;
    for (auto edge : allEdges)
    {
        bool needed = false;
        for (auto &res : res1) {
            if (areEqual(edge, res)) {
                needed = true;
                break;
            }
        }

        if (needed)
            continue;

        for (auto &res : res2) {
            if (areEqual(edge, res)) {
                needed = true;
                break;
            }
        }
        
        if (!needed)
            unused++;
    }
    
    return unused;
}

int main() {
    // vector<vector<int>> edges {
    //     { 3, 1, 2 },
    //     { 3, 2, 3 },
    //     { 1, 1, 3 },
    //     { 1, 2, 4 },
    //     { 1, 1, 2 },
    //     { 2, 3, 4 },
    // };

    vector<vector<int>> edges {
        { 3, 1, 2 },
        { 3, 2, 3 },
        { 1, 1, 4 },
        { 2, 1, 4 },
    };

    int n = 4;

    cout << maxNumEdgesToRemove(n, edges) << endl;

    return 0;
}