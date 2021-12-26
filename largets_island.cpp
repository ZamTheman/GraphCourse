#include<bits/stdc++.h>
using namespace std;

int dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int posX, int posY) {
    visited[posY][posX] = true;
    auto size = 1;
    int dx[] = { 1, -1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };

    for (int i = 0; i < 4; i++) {
        int newX = dx[i] + posX;
        int newY = dy[i] + posY;

        if (newX >= 0
        && newX < grid[0].size()
        && newY >= 0
        && newY < grid.size()
        && !visited[newY][newX]
        && grid[newY][newX] == 1)

        size += dfs(grid, visited, newX, newY);
    }

    return size;
}

int maxAreaOfIsland(vector<vector<int>> grid)
{
    auto largestIsland = 0;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[0].size(); j++)
        {
            if (visited[i][j] || grid[i][j] == 0)
                continue;

            auto islandSize = dfs(grid, visited, j, i);
            if (islandSize > largestIsland)
                largestIsland = islandSize;
        }
    }

    return largestIsland;    
}

int main() {
    vector<vector<int>> island {
        { 1,0,0,1,0 },
        { 1,0,1,0,0 },
        { 0,0,1,0,1 },
        { 1,0,1,1,1 },
        { 1,0,1,1,0 }
    };

    cout << maxAreaOfIsland(island) << endl;

    return 0;
}