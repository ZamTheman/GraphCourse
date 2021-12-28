/*
Kahn's algorithm
Used for resolving the order to handle dependency chains.

    0 < 2 < 3 < 5
        |       |
    - < -       |
    |           |
    1 < 4 < - - - 
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

    void topological_sort() {
        vector<int> indegree(m.size(), 0);
        for (auto item : m)
            for (auto nbr : item.second)
                indegree[nbr]++;

        queue<int> q;
        for (int i = 0; i < indegree.size(); i++)
            if (indegree[i] == 0)
                q.push(i);

        while(!q.empty()) {
            int node = q.front();
            cout << node << endl;
            q.pop();

            for (auto nbr : m[node]){
                indegree[nbr] --;
                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }
    }
};

int main() {
    Graph g;
    g.addEdge(0, 2, false);
    g.addEdge(2, 3, false);
    g.addEdge(3, 5, false);
    g.addEdge(4, 5, false);
    g.addEdge(1, 4, false);
    g.addEdge(1, 2, false);

    g.topological_sort();
    return 0;
}
