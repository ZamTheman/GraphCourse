#include<bits/stdc++.h>
using namespace std;

int messageRoute(int n, vector<vector<int>>edges)
{
    vector<vector<int>>cities(n + 1);
    for (auto edge : edges)
    {
        cities[edge[0]].push_back(edge[1]);
        cities[edge[1]].push_back(edge[0]);
    }

    bool visited[n + 1]{false};
    int steps[n + 1]{-1};
    queue<int>q;
    q.push(1);
    visited[1] = true;
    steps[1] = 0;

    while(!q.empty()){
        auto current = q.front();
        q.pop();

        for (auto nbr : edges[current])
        {
            if (!visited[nbr]){
                visited[nbr] = true;
                q.push(nbr);
            }

            if (steps[nbr] > steps[current] + 1)
                steps[nbr] = steps[current] + 1;
        }
    }

    return steps[n];
}

int main(){
    return 0;
}