/*
      < 1 <
    0 < 2 < 4
      < 3 < 
*/

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

    void addNodeWithoutNbr(int i){
        m[i] = vector<int> {};
    }

    int getSizeOfMap() {
        return m.size();
    }

    void dfs(int source, int destination, vector<int> stack, vector<vector<int>> &results) {
        auto node = m[source];
        stack.push_back(source);
        if (source == destination) {
            results.push_back(stack);
            return;
        }

        for (auto nbr : m[source])
            dfs(nbr, destination, stack, results);
    }
};

vector<vector<int>> allPathsSourceTarget(vector<vector<int>> graph) {
    Graph g;
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].empty()) {
            g.addNodeWithoutNbr(i);
            continue;
        }

        for (auto nbr : graph[i])
            g.addEdge(i, nbr, false);
    }

    vector<vector<int>> results {};
    g.dfs(0, g.getSizeOfMap() - 1, vector<int> {}, results);
    return results;
}

int main() {
    vector<vector<int>> input {
        { 1, 2, 3 },
        { 4 },
        { 4 },
        { 4 },
        { }
    };

    auto output = allPathsSourceTarget(input);
    for (auto path : output) {
        for (auto nr : path)
            cout << nr << " ";
        
        cout << endl;
    }

    return 0;
}
