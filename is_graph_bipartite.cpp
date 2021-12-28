#include<bits/stdc++.h>
using namespace std;

bool dfs(map<int, vector<int>> graph, int source, int *visited, int parent, int color) {
    visited[source] = color;
    for (auto nbr : graph[source]) {
        if (visited[nbr] == 0) {
            auto nextColor = color == 1 ? 2 : 1;
            int subProb = dfs(graph, nbr, visited, source, nextColor);
            if (!subProb)
                return false;
        }
        else if (nbr != parent && color == visited[nbr])
            return false;
    }
    
    return true;
}

bool isBipartite(vector<vector<int>> graph){
    map<int, vector<int>> nodeAndNbrs;
    for (auto edge : graph) {
        nodeAndNbrs[edge[0]].push_back(edge[1]);
        nodeAndNbrs[edge[1]].push_back(edge[0]);
    }

    int visited[nodeAndNbrs.size()] = { 0 }; // 0 - Not visited, 1 - Visited and Color is 1, 2 Visited and Color is 2 
    return dfs(nodeAndNbrs, graph[0][0], visited, -1, 1);
}

int main() {
    vector<vector<int>> shouldBeBipartite {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 },
        { 0, 4 },
        { 4, 5 },
        { 5, 6 },
    };

    vector<vector<int>> shouldNotBeBipartite {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 },
        { 0, 4 },
        { 4, 5 },
        { 5, 6 },
        { 1, 4 },
    };

    cout << isBipartite(shouldBeBipartite) << endl;
    cout << isBipartite(shouldNotBeBipartite) << endl;

    return 0;
}

/*
https://en.wikipedia.org/wiki/Bipartite_graph

    Case 1
    - - 0 - -
    |       |
    1       4
    |       |
    2       5
    |       |
    3       6

    Case 2
    - - 0 - -
    |       |
    1 - - - 4
    |       |
    2       5
    |       |
    3       6
*/