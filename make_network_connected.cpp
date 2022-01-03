#include<bits/stdc++.h>
using namespace std;

int find(int x,vector<int>&visit)
{
    if(x != visit[x]) {
        visit[x] = find(visit[x], visit);
        return visit[x];
    }

    return x;
}

void Union(int x, int y,vector<int> &visit, vector<int>&sz)
{
    int val1 = find(x,visit);
    int val2 = find(y,visit);

    if(val1 == val2)
        return;

    if(sz[val1]>sz[val2])
        swap(val1,val2);

    visit[val1] = val2;
    sz[val2] += sz[val1];
}

int makeConnected(int n, vector<vector<int>> connections) {
    vector<int>visit(n);
    vector<int>sz(n, 1); // Set all elements in sz to 1
    iota(visit.begin(), visit.end(), 0); // Set the elements in visit from 0 and increment 1 for each
    int cnt = 0;
    int extra = 0;
    for(int i=0;i<connections.size();i++)
    {
        int cmp1 = connections[i][0];
        int cmp2 = connections[i][1];
        if(find(cmp1, visit) == find(cmp2, visit)) // If the superparent of both cmps are the same then we have a redundant connections
        {
            extra++;
            continue;
        }

        Union(cmp1, cmp2, visit, sz); // Else we add the two sets together
    }

    for(int i = 0; i < n; i++) 
        if(find(i, visit) == i) // If node have it self as parent then it is dangling or super parent
            cnt++;

    return cnt - 1 <= extra ? cnt - 1 : -1;
}

int main() {
    int n = 6;
    vector<vector<int>> input {
        { 0, 1 },
        { 0, 2 },
        { 0, 3 },
        { 1, 2 }
    };

    cout << makeConnected(n, input) << endl;
}