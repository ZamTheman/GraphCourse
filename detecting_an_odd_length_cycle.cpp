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

    bool dfs(int source, vector<int> &visited, int color) {
        auto node = m[source];
        visited[source] = color;
        for (auto nbr : m[source]) {
            if (visited[nbr] == 0) {
                auto newColor = color == 1 ? 2 : 1;
                auto sub = dfs(nbr, visited, newColor);
                if (sub)
                    return true;
            }
            else
                if (visited[nbr] == color)
                    return true;
        }

        return false;
    }
};

bool solve(vector<vector<int>> graph)
{
    int n = graph.size();
    int m = graph[0].size();
    vector<int>col(n+1,-1); // Why n + 1? -1 indicating that they are not visited? col = color?
    for(int i=0;i<n;i++) // Is running bfs for each node, why?
    {
        if(col[i] == -1) // Checking if not visited
        {
            queue<int>q;
            q.push(i);
            col[i] = 0; // 0 is a color
            while(q.size())
            {
                int x=q.front();
                q.pop();
                for(auto nbr : graph[x])
                {
                    if(col[nbr] == -1)
                    {
                        col[nbr] = col[x] ^ 1; // XOR 
                        q.push(nbr);
                    }
                    else
                        if(col[nbr] == col[x])
                            return true;
                }
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> input2 {
        { 1, 2, 3 },
        { 0, 2 },
        { 0, 1, 3 },
        { 0, 2 }
    };

    vector<vector<int>> input {
        { 1 },
        { 0 }
    };

//    cout << solve(input) << endl;
    cout << solve(input2) << endl;
    return 0;
}
