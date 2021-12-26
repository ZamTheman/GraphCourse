#include<bits/stdc++.h>
using namespace std;

class Graph {
    map<int, vector<int>> m;
    map<int, bool> visited;

public:
    void addEdge(int i, int j, bool undir = true) {
        if(!m.count(i)) {
            m[i] = vector<int> {};
            visited[i] = false;
        }

        if(find(m[i].begin(), m[i].end(), j) == m[i].end())
            m[i].push_back(j);

        if(undir) {
            if(!m.count(j)) {
                m[j] = vector<int> {};
                visited[j] = false;
            }

            if(find(m[j].begin(), m[j].end(), i) == m[j].end())
                m[j].push_back(i);
        }

    }

    void dfs(int source) {
        cout << source << endl;
        auto current = m[source];
        visited[source] = true;

        for (auto nbr : current)
            if (!visited[nbr])
                dfs(nbr);
    }

    bool dfs_cycle_detection(int source, int parent) {
        visited[source] = true;
        for (auto nbr : m[source])
        {
            if (!visited[nbr]) {
                bool nbrFoundCycle = dfs_cycle_detection(nbr, source);
                if (nbrFoundCycle)
                    return true;
            }
            else if (nbr != parent)
                return true;
        }

        return false;
    }
};

bool solve(int n, vector<vector<int>> edges) {
    Graph g;
    for (auto edge : edges)
        g.addEdge(edge[0], edge[1]);
        
    return g.dfs_cycle_detection(edges[0][0], -1);
}

int main(){
    // Graph g;
    // g.addEdge(0,1);
    // g.addEdge(1,2);
    // g.addEdge(2,3);
    // g.addEdge(3,5);
    // g.addEdge(5,6);
    // g.addEdge(4,5);
    // g.addEdge(0,4);
    // g.addEdge(3,4);
    // // g.dfs(1);
    // cout << g.dfs_cycle_detection(1, -1) << endl;

    // Graph g1;
    // g1.addEdge(0,1);
    // g1.addEdge(1,2);
    // g1.addEdge(2,3);
    // cout << g1.dfs_cycle_detection(0, -1) << endl;

    int n = 5;
    vector<vector<int>> edges {
        { 1, 2 },
        { 1, 3 },
        { 2, 3 },
        { 1, 4 },
        { 4, 5 }
    };

    vector<vector<int>> edges2 {
        { 3, 5 },
        { 10, 3 },
        { 4, 10 },
        { 4, 2 },
        { 4, 7 },
        { 10, 5 },
        { 4, 6 }
    };
    
    cout << solve(n,edges2) << endl;

    return 0;
}