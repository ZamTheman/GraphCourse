#include<list>
#include<set>
#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
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

    vector<int> dijkstra(int src, int dest) {
        vector<pair<int,int>> dist(V, { -1, INT_MAX });
        set<pair<int, int>> s;

        dist[src] = { -1, 0 };
        s.insert({ 0, src });

        while(!s.empty()) {
            auto it = s.begin();
            int node = it -> second;
            int nodeDist = it -> first;
            s.erase(it);

            for (auto nbrPair : l[node]) {
                int nbr = nbrPair.second;
                int currentEdge = nbrPair.first;
                if (nodeDist + currentEdge < dist[nbr].second) {
                    auto f = s.find({ dist[nbr].second, nbr });
                    if (f != s.end())
                        s.erase(f);

                    dist[nbr] = { node, nodeDist + currentEdge };
                    s.insert({ dist[nbr].second, nbr });
                }
            }
        }

        vector<int> path { dest };
        auto current = dist[dest];
        while (current.first != -1){
            path.push_back(current.first);
            current = dist[current.first];
        }

        reverse(path.begin(), path.end());
        return path;
    }
};

vector<int> shortestPath(vector<vector<int>> roads,int n)
{
    Graph g(n + 1);
    for (auto edge : roads)
        g.addEdge(edge[0], edge[1], edge[2]);

    return g.dijkstra(1, n);
}

int main() {
    vector<vector<int>> edges {
        { 1, 2, 2 },
        { 2, 5, 5 },
        { 2, 3, 4 },
        { 1, 4, 1 },
        { 4, 3, 3 },
        { 3, 5, 1 }
    };
    int n = 5;
    auto result = shortestPath(edges, n);
    for (auto res : result)
        cout << res << " ";
    
    cout << endl;

    return 0;
}