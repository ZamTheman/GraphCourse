#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

struct Edge {
    int w, x, y;
    Edge(int x, int y, int w) {
        this -> w = w;
        this -> x = x;
        this -> y = y;
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
    int V;

public:
    Graph(int v) {
        V = v;
    }

    void addEdge(int x, int y, int w) {
        edgelist.push_back({w, x, y});
    }

    int kruksal_mst() {
        // First sort edges by weight
        sort(edgelist.begin(), edgelist.end());
        
        // Init a DSU
        DSU dsu(V);

        int ans = 0;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            // Take the edge to mst if it does not form a cycle
            if (dsu.find(x) != dsu.find(y)) {
                dsu.unite(x, y);
                std::cout << "Edge used is between: " << x << " and " << y << std::endl;
                ans += w;
            }
        }

        return ans;
    }
};

int minCostConnectPoints(vector<vector<int>> points) {
    Graph g(points.size());
    for (size_t i = 0; i < points.size() - 1; i++)
    {
        for (size_t j = i + 1; j < points.size(); j++)
        {
            auto distance = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]); 
            g.addEdge(i,j,distance); 
        }
    }
    
    return g.kruksal_mst();
}

int main() {
    vector<vector<int>> points {
        { 3, 12 },
        { -2, 5 },
        { -4, 1 }
    };

    cout << minCostConnectPoints(points) << endl;

    return 0;
}