#include<bits/stdc++.h>
using namespace std;

int count_pairs(int N, vector<pair<int,int> > astronauts){
    int countries = 0;
    map<int, int> astroAndCountry;
    vector<int> asPerCountry;
    for (auto pair : astronauts) {
        if (astroAndCountry.count(pair.first)) {
            astroAndCountry[pair.second] = astroAndCountry[pair.first];
            asPerCountry[astroAndCountry[pair.first]]++;
            continue;
        }
        else if (astroAndCountry.count(pair.second)) {
            astroAndCountry[pair.first] = astroAndCountry[pair.second];
            asPerCountry[astroAndCountry[pair.second]]++;
            continue;
        }
        else {
            astroAndCountry[pair.first] = countries;
            astroAndCountry[pair.second] = countries;
            countries++;
            asPerCountry.push_back(2);
        }
    }

    auto totalSum = 0;
    for (size_t i = 0; i < asPerCountry.size() - 1; i++)
    {
        auto current = asPerCountry[i];
        auto rest = 0;
        for (size_t j = i + 1; j < asPerCountry.size(); j++)
            rest += asPerCountry[j];

        totalSum += current * rest;
    }

    return totalSum;
}

int main() {
    int n = 5;
    vector<pair<int,int>> astronauts {
        { 0, 1 }, { 2, 3 }, { 0, 4 }
    };

    cout << count_pairs(n, astronauts) << endl;

    n = 7;
    vector<pair<int,int>> astronaut2 {
        { 0, 1 }, { 2, 3 }, { 3, 4 }, { 5, 6 }
    };

    cout << count_pairs(n, astronaut2) << endl;
}