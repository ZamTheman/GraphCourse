#include<iostream>
#include<vector>
using namespace std;

bool dfs_helper(vector<int> graph[], int node, int *visited, int parent, int color) {
    visited[node] = color;

    for (auto nbr : graph[node]) {
        if (visited[nbr] == 0) {
            auto newColor = color == 1 ? 2 : 1;
            int subprob = dfs_helper(graph, nbr, visited, node, newColor);
            if (subprob == false)
                return false;
        }
        else if (nbr != parent && color == visited[nbr])
            return false;
    }

    return true;
}

bool dfs(vector<int> graph[], int N) {
    int visited[N] = { 0 }; // 0 - Not visited, 1 - Visited and Color is 1, 2 Visited and Color is 2 
    int color = 1;
    return dfs_helper(graph, 0, visited, -1, color);
}

int main() {
    int N,M;
    cin >> N >> M;
    vector<int> graph[N];
    while (M--) {
        int x,y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    cout << (dfs(graph, N) ? "It's bipartite" : "It's not") <<  endl;

    return 0;
};