#include<vector>
#include<list>
#include<queue>
#include<map>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Graph {
    map<int, vector<int>> m;

public:
    void addEdge(int i, int j, bool undir = true) {
        if(!m.count(i))
            m[i] = vector<int> {};

        if(find(m[i].begin(), m[i].end(), j) == m[i].end())
            m[i].push_back(j);

        if(undir) {
            if(!m.count(j))
                m[j] = vector<int> {};

            if(find(m[j].begin(), m[j].end(), i) == m[j].end())
                m[j].push_back(i);
        }

    }

    void bfs(int source, int dest = -1) {
        queue<int> q;
        bool visited[m.size()]{0};
        int dist[m.size()]{0};
        int parent[m.size()]{-1};
        
        q.push(source);
        visited[source] = true;
        parent[source] = source;

        while(!q.empty()) {
            int f = q.front();
            cout << f << endl;
            q.pop();

            for (auto nbr : m[f]) {
                if (!visited[nbr]){
                    q.push(nbr);
                    parent[nbr] = f;
                    dist[nbr] = dist[f] + 1;
                    visited[nbr] = true;
                }
            }
        }

        // Print shortest distance from any node to source
        for (size_t i = 0; i < m.size(); i ++)
            cout << "Shortest dist to " << i << " is " << dist[i] << endl;
        
        // Print path from source to destination
        if (dest == -1)
            return;

        int temp = dest;
        while (temp != source) {
            cout << temp << "--";
            temp = parent[temp];
        }

        cout << source << endl;

    }
};

int main(){
    Graph g;
    g.addEdge(0,1);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,5);
    g.addEdge(5,6);
    g.addEdge(4,5);
    g.addEdge(0,4);
    g.addEdge(3,4);
    g.bfs(1, 6);

    return 0;
}