#include <bits/stdc++.h>
using namespace std;

int optimizedEditDistance(const string &s1, const string &s2) {
    int m = s1.size(), n = s2.size();
    if(m < n) return optimizedEditDistance(s2, s1);
    vector<int> prev(n+1, 0), curr(n+1, 0);
    for(int j=0; j<=n; j++) prev[j] = j;
    for(int i=1; i<=m; i++) {
        curr[0] = i;
        for(int j=1; j<=n; j++) {
            if(s1[i-1] == s2[j-1]) curr[j] = prev[j-1];
            else curr[j] = 1 + min({prev[j], curr[j-1], prev[j-1]});
        }
        prev = curr;
    }
    return prev[n];
}

int main() {
    cout << "Optimized Edit Distance Tests:\n";
    cout << "kitten -> sitting: " << optimizedEditDistance("kitten", "sitting") << endl;
    cout << "flaw -> lawn: " << optimizedEditDistance("flaw", "lawn") << endl;
    cout << "algorithm -> logarithm: " << optimizedEditDistance("algorithm", "logarithm") << "\n\n";
    cout << "--- Space Optimization ---\n";
    cout << "1. Uses only two 1D arrays (prev and current row)\n";
    cout << "2. Reduces space from O(n*m) to O(n)\n";
    cout << "3. Maintains same time complexity O(n*m)\n";
    
    return 0;
}