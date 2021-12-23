using namespace std;
#include<bits/stdc++.h>
#include<map>
#include<set>

int maximalNetworkRank(int n, vector<vector<int>> roads) {
    vector<int> cities(n);
    map<int, set<int>> roadsBetweenCities {};
    for (auto r : roads) {
        // x = city1, y = city2
        int x = r[0];
        int y = r[1];
        // Increase nr roads per city
        cities[x]++;
        cities[y]++;
        // Store each road
        roadsBetweenCities[x].insert(y);
        roadsBetweenCities[y].insert(x);
    }

    int ans = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            auto roadSum = cities[i] + cities[j];
            auto test = roadsBetweenCities[i].find(j);
            if (roadsBetweenCities[i].count(j) != 0)
                roadSum --;

            if (roadSum > ans)
                ans = roadSum;
        }
    }
    
    return ans;
}

int main() {
    int n = 4;
    vector<vector<int>> vec { { 0,1 },{ 0,3 },{ 1,2 },{ 1,3 } };
    auto val = maximalNetworkRank(n, vec);

    cout << val << endl;

    return 0;
}

//      0 
//      |
//    -----
//    |   |
//    1---3
//    |
//    2