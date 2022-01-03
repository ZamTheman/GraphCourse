#include<bits/stdc++.h>
using namespace std;

class Graph {
    vector<pair<int, int>> *l;
    int V;

public:
    Graph(int n) {
        V = n;
        l = new vector<pair<int, int>>[n];
    }

    void addEdge(int x, int y, int w) {
        l[x].push_back({y, w});
        l[y].push_back({x, w});
    }

    int prim_mst() {
        // Init a min heap
        // Priority queye <Type, Container, Comparer>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> Q;
        vector<bool> visited(V, 0);
        int ans = 0;
        Q.push({0,0});
        while (!Q.empty()) {
            auto best = Q.top();
            Q.pop();

            int to = best.second;
            int weight = best.first;

            // If node visited, ignore
            if (visited[to])
                continue;

            ans += weight;
            visited[to] = 1;

            for (auto node : l[to])
                if (visited[node.first] == 0)
                    Q.push({node.second, node.first});
        }

        return ans;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0,1,1);
    g.addEdge(0,2,2);
    g.addEdge(0,3,2);
    g.addEdge(1,2,2);
    g.addEdge(1,3,2);
    g.addEdge(2,3,3);

    cout << g.prim_mst() << endl;
    return 0;
}