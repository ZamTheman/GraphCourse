#include<bits/stdc++.h>
using namespace std;

int ladderLength(string beginWord, string endWord, vector<string> wordList) {
    map<string, vector<string>> nbrs;
    wordList.push_back(beginWord);
    for (int i = 0; i < wordList.size(); i++)
    {
        auto word = wordList[i];
        for (size_t j = 0; j < wordList.size(); j++)
        {
            if (i == j)
                continue;

            auto nrMatches = 0;
            for (size_t k = 0; k < word.length(); k++)
                if (word[k] == wordList[j][k])
                    nrMatches++;
                    
            if (nrMatches == word.length() - 1)
                nbrs[word].push_back(wordList[j]);
        }
    }

    queue<string> q;
    map<string,int>steps;
    map<string,bool>visited;
    q.push(beginWord);
    steps[beginWord] = 1;
    visited[beginWord] = true;

    while(!q.empty()) {
        auto current = q.front();
        q.pop();

        for (auto nbr : nbrs[current])
        {
            if (!visited[nbr]) {
                q.push(nbr);
                visited[nbr] = true;
                steps[nbr] = steps[current] + 1;
                if (nbr == endWord)
                    return steps[nbr];
            }
        }
        
    }
    
    return 0;
}

int main() {
    auto begin = "hit";
    auto end = "cog";
    vector<string> words { "hot", "dot", "dog", "lot", "log", "cog" };
    auto steps = ladderLength(begin, end, words);
    cout << steps << endl;
    return 0;
}