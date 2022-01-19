#include<bits/stdc++.h>
using namespace std;

class Graph {
    int V;
    list<pair<int, int>> * l;

public:
    Graph(int v) {
        V = v;
        l = new list<pair<int,int>>[V];
    }

    void addEdge(int u, int v, int wt, bool undir = true) {
        l[u].push_back({ wt, v });
        if (undir)
            l[v].push_back({ wt, u });
    }

    int dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        set<pair<int, int>> s;

        dist[src] = 0;
        s.insert({ 0, src });

        while(!s.empty()) {
            auto it = s.begin();
            int node = it -> second;
            int nodeDist = it -> first;
            s.erase(it);

            for (auto nbrPair : l[node]) {
                int nbr = nbrPair.second;
                int currentEdge = nbrPair.first;
                if (nodeDist + currentEdge < dist[nbr]) {
                    auto f = s.find({ dist[nbr],nbr });
                    if (f != s.end())
                        s.erase(f);

                    dist[nbr] = nodeDist + currentEdge;
                    s.insert({ dist[nbr], nbr });
                }
            }
        }

        auto sum = 0;
        for (size_t i = 1; i < V + 1; i++)
            sum += dist[i];
        
        return sum;
    }
};

int networkDelayTime(vector<vector<int>> times, int n, int k) {
    Graph g(n);
    for (auto time : times)
        g.addEdge(time[0], time[1], time[2], false);

    return g.dijkstra(k);
}

int main () {
    int n = 4;
    int k = 2;
    vector<vector<int>> times {
        { 2, 1, 1 },
        { 2, 3, 1 },
        { 3, 4, 1 }
    };

    cout << networkDelayTime(times, n, k) << endl;
    return 0;
}