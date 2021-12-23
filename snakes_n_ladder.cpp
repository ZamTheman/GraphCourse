#include<bits/stdc++.h>
using namespace std;

int min_dice_throws(int n,vector<pair<int,int>>snakes, vector<pair<int,int>>ladders){
    map<int, int> shortCuts;
    for (auto pair : snakes)
        shortCuts[pair.first] = pair.second;

    for (auto pair : ladders)
        shortCuts[pair.first] = pair.second;
    
    map<int, vector<int>> graph;
    for (size_t i = 1; i < n + 1; i++)
    {
        graph[i] = vector<int>{};
        for (size_t j = 1; j < 7; j++)
        {
            auto val = -1;
            if (shortCuts.count(i + j))
                val = shortCuts[i + j];
            else
                val = i + j;

            graph[i].push_back(val);
        }
    }

    bool visited[n + 1]{false};
    int steps[n + 1]{-1};
    steps[1] = 0;
    visited[1] = true;
    queue<int> q;
    q.push(1);

    while(!q.empty()) {
        auto current = q.front();
        q.pop();

        for (auto nbr : graph[current]){
            if (visited[nbr])
                continue;

            visited[nbr] = true;
            steps[nbr] = steps[current] + 1;
            q.push(nbr);
        }
    }
    
    return steps[n];
}


int main(){
    vector<pair<int,int>> ladders {{2,15},{5,7},{9,27},{18,29},{25,35}};
    vector<pair<int,int>> snakes = {{17,4},{20,6},{34,12},{24,16},{32,30}};
    auto throwes = min_dice_throws(36, snakes, ladders);

    cout << throwes << endl;

    return 0;
}