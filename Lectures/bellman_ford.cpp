#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

vector<int> bellman_ford(int n, int src, vector<vector<int>> &edges) {
    vector<int> dist(n+1, INT_MAX);
    dist[src] = 0;

    for (size_t i = 0; i < n - 1; i++)
    {
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
                dist[v] = dist[u] + wt;
        }
    }

    for (auto edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]){
            cout << "Negative wt cycle found" << endl;
            exit(0);
        }
    }

    return dist;
};

int main() {
    int vertices, src;
    vertices = 3;
    src = 1;

    // Have negative wt cycle
    vector<vector<int>> edges {
        { 1, 2, 3 },
        { 2, 3, 4 },
        { 3, 1, -10 },
    };

    // vector<vector<int>> edges {
    //     { 1, 2, 3 },
    //     { 2, 3, 4 },
    //     { 1, 3, -10 },
    // };

    auto dist = bellman_ford(vertices, src, edges);
    for (size_t i = 1; i < vertices + 1; i++)
        cout << "Node " << i << " is at dist " << dist[i] << endl;      
}