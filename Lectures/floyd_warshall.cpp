#include<vector>
#include<limits.h>
#include<iostream>

std::vector<std::vector<int>> floyd_warshall(std::vector<std::vector<int>> graph) {
    std::vector<std::vector<int>> dist(graph);
    auto V = graph.size();

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (size_t j = 0; j < V; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
            
        }
    }

    return dist;
}

int main() {
    int INF = 1e9;
    std::vector<std::vector<int>> graph {
        { 0, INF, -2, INF },
        { 4, 0, 3, INF },
        { INF, INF, 0, 2},
        { INF, -1, INF, 0 }
    };

    auto result = floyd_warshall(graph);

    for (auto row : result)
        std::cout << row[0] << ", " << row[1] << ", " << row[2] << ", " << row[3] << std::endl;
    
    return 0;
}

/*
    0   MAX -2  MAX
    4   0   3   MAX
    MAX MAX 0   2
    MAX -1  MAX 0

    -------wt-1--------
    |                 |
    v                 |
    1 -> wt3 ->  |    3
    |            |    ^
    v            v   wt2
   wt3           |    |
    |            |    |
    0 -> wt-2 -> 2 -> |

    0 -> 2 wt -2
    1 -> 0 wt 4
    1 -> 2 wt 3
    2 -> 3 wt 2
    3 -> 1 wt -1
*/