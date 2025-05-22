#include <bits/stdc++.h>
using namespace std;

int weightedEditDistance(const string &s1, const string &s2, int ci, int cd, int cs) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i=0; i<=m; i++) dp[i][0] = i*cd;
    for(int j=0; j<=n; j++) dp[0][j] = j*ci;
    
    for(int i=1; i<=m; i++) {
        for(int j=1; j<=n; j++) {
            if(s1[i-1] == s2[j-1]) 
                dp[i][j] = dp[i-1][j-1];
            else 
                dp[i][j] = min({dp[i-1][j]+cd, dp[i][j-1]+ci, dp[i-1][j-1]+cs});
        }
    }
    return dp[m][n];
}

vector<string> spellCheck(const string &word, const vector<string> &dict, int ci, int cd, int cs, int maxDist) {
    vector<pair<int, string>> candidates;
    for(const auto &d : dict) {
        if(abs((int)d.size() - (int)word.size()) > maxDist) continue;
        int cost = weightedEditDistance(word, d, ci, cd, cs);
        if(cost <= maxDist) candidates.push_back({cost, d});
    }
    sort(candidates.begin(), candidates.end());
    vector<string> res;
    for(const auto &p : candidates) res.push_back(p.second);
    return res;
}

int main() {
    // Test Case from PDF
    vector<string> dict = {"cred", "bet", "shat", "that", "brad", "cart", "brat", "card"};
    string word = "dat";
    int ci=1, cd=1, cs=1, maxDist=2;
    
    cout << "Test Case: Input='dat', Dictionary=[cred,bet,shat,that,brad,cart,brat,card]\n";
    vector<string> suggestions = spellCheck(word, dict, ci, cd, cs, maxDist);
    cout << "Suggested words: ";
    for(const auto &w : suggestions) cout << w << " ";
    cout << "\n\n";
    
    // Interactive Mode
    string userWord;
    int uCi, uCd, uCs, uMax = 2;
    cout << "Enter word to check: ";
    cin >> userWord;
    cout << "Enter costs (Ci Cd Cs): ";
    cin >> uCi >> uCd >> uCs;
    
    vector<string> res = spellCheck(userWord, dict, uCi, uCd, uCs, uMax);
    cout << "Suggestions: ";
    for(const auto &w : res) cout << w << " ";
    cout << endl;
    return 0;
}