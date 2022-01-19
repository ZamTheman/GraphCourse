#include<list>
#include<set>
#include<iostream>
#include<vector>
#include<limits.h>
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

    int dijkstra(int src, int dest) {
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

        return dist[dest];
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 4);
    g.addEdge(0, 3, 7);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(3, 4, 3);

    cout << g.dijkstra(0, 4) << endl;

    return 0;
}

/*
    0   -   w1  -   1
    |               |       
    w7              w1
    |               |
    3   -   w2  -   2
    |
    w3
    |
    4
*/