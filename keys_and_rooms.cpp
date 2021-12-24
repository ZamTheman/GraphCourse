#include<bits/stdc++.h>
using namespace std;

void dfs(int room, vector<vector<int>> rooms, vector<bool> &visited) {
    auto current = rooms[room];
    visited[room] = true; 
    for (auto nbr : current)
        if (!visited[nbr])
            dfs(nbr, rooms, visited);
}

bool canVisitAllRooms(vector<vector<int>> rooms) {
    vector<bool> visited(rooms.size(), false);
    dfs(0, rooms, visited);
    for (auto visit : visited)
        if (!visit)
            return false;

    return true;
}
