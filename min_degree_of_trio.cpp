using namespace std;
#include<bits/stdc++.h>

int minTrioDegree(int n, vector<vector<int>> edges) {
    int sum = 1e9;
    int v[n+1][n+1];
    memset(v,0,sizeof(v));
    int deg[n+1];
    memset(deg,0,sizeof(deg));

    for (int i = 0; i < edges.size(); i++) {
        auto cty1 = edges[i][0];
        auto cty2 = edges[i][1];
        v[cty1][cty2]++;
        v[cty2][cty1]++;
        deg[cty1]++;
        deg[cty2]++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                cout << i << ", " << j << ", " << k << endl;
                    if(v[i][j] && v[j][k] && v[i][k])
                    sum = min(sum, deg[i] + deg[j] + deg[k]- 6);
            }
        }
    }
    
    return sum == 1e9 ? -1 : sum;
}

int main() {
    int n = 6;
    vector<vector<int>> vec { { 1,2 },{ 1,3 },{ 3,2 },{ 4,1 },{ 5,2 },{ 3,6 } };
    auto val = minTrioDegree(n, vec);

    cout << val << endl;

    return 0;
}