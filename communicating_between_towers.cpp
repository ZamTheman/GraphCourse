#include<bits/stdc++.h>
using namespace std;

void findFullGroup (
    vector<vector<int>> &matrix,
    vector<vector<int>> &visited,
    int x,
    int y,
    int currentGroup) {
    queue<pair<int,int>> q;
    q.push(make_pair(x, y));

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        visited[current.second][current.first] = currentGroup;

        for (size_t i = 0; i < matrix[0].size(); i++) {
            if (visited[current.second][i] < 0 && matrix[current.second][i] == 1) 
                q.push(make_pair(i, current.second));

        }

        for (size_t i = 0; i < matrix.size(); i++)
            if (visited[i][current.first] < 0 && matrix[i][current.first] == 1)
                q.push(make_pair(current.first, i));
    }
}

int solve(vector<vector<int>> matrix) {
    for (auto m : matrix) {
        for (auto r : m) {
            cout << r << " ";
        }
        cout << endl;
    }

    queue<int> q;
    vector<vector<int>> visited(matrix.size(), vector<int>(matrix[0].size(), -2));
    int currentGroup = 0;

    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] > 0 && visited[i][j] < 0) {
                findFullGroup(matrix, visited, j, i, currentGroup);
                currentGroup++;
            }
        }
    }

    return currentGroup;
}

int main() {
    // vector<vector<int>> matrix {
    //     { 1, 1, 0},
    //     { 0, 0, 1},
    //     { 0, 0, 1}
    // };

    vector<vector<int>> matrix {
        { 0, 0, 1, 1, 1 },
        { 1, 1, 1, 1, 0 },
        { 1, 1, 1, 0, 0 },
        { 0, 0, 1, 1, 0 },
        { 0, 0, 0, 1, 0 },
    };

    // vector<vector<int>> matrix {
    //     { 1, 0, 0},
    //     { 0, 0, 1},
    //     { 0, 1, 0}
    // };

    auto groups = solve(matrix);

    cout << "Nr groups: " << groups << endl;

    return 0;
}