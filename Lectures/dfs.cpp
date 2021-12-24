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
    g.dfs(1);

    return 0;
}