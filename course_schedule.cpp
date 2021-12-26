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

    bool dfs_directed_graph_cycle_detection(int source, vector<int> stack) {
        visited[source] = true;
        stack.push_back(source);
        for (auto node : m[source]) {
            if (visited[node] && std::find(stack.begin(), stack.end(), node) != stack.end())
                return true;

            if (dfs_directed_graph_cycle_detection(node, stack))
                return true;
        }

        return false;
    }
};

bool canFinish(vector<vector<int>> prerequisites,int numCourses) {
    Graph g;
    for (auto edge : prerequisites)
        g.addEdge(edge[0], edge[1], false);

    return !g.dfs_directed_graph_cycle_detection(0, vector<int> {});
}

int main(){
    vector<vector<int>> edges3 {
        { 1, 0 },
        { 2, 3 },
        { 3, 2 }
    };
    
    cout << canFinish(edges3, 2) << endl;

    return 0;
}