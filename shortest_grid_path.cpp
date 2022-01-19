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

int shortest_path(vector<vector<int>> grid){
    vector<int> deltaX { -1, 1, 0, 0 };
    vector<int> deltaY { 0, 0, -1, 1 };
    Graph g(grid.size() * grid[0].size());
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            for (int k = 0; k < 4; k++)
            {
                auto x = j + deltaX[k];       
                auto y = i + deltaY[k];
                if (x > -1 && x < grid.size() && y > -1 && y < grid[0].size())
                    g.addEdge(
                        i * grid.size() + j,
                        y * grid.size() + x,
                        grid[y][x],
                        false);
            }
        }
    }
    
    auto smallest = g.dijkstra(0, grid.size() * grid[0].size() - 1);
    return smallest + grid[0][0];   
}

int main() {
    vector<vector<int>> graph {
        { 31, 100, 65, 12, 18 },
        { 10, 13, 47, 157, 6 },
        { 100, 113, 174, 11, 33 },
        { 88, 124, 41, 20, 140 },
        { 99, 32, 111, 41, 20 }
    };

    auto result = shortest_path(graph);
    cout << result << endl;

    return 0;
}