// Task2 Minimum Weighted Edit Distance Calculation

#include <bits/stdc++.h>
using namespace std;
int EditDistance(const string &s1, const string &s2, int Ci, int Cd, int Cs)
{
    int m = s1.size();
    int n = s2.size();
    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, LLONG_MAX));
    dp[0][0] = 0;
    for (int i = 1; i <= m; ++i)
    {
        dp[i][0] = dp[i - 1][0] + Cd;
    }
    for (int j = 1; j <= n; ++j)
    {
        dp[0][j] = dp[0][j - 1] + Ci;
    }

    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {

            dp[i][j] = min(dp[i][j], dp[i - 1][j] + Cd);

            dp[i][j] = min(dp[i][j], dp[i][j - 1] + Ci);

            int costSub = (s1[i - 1] == s2[j - 1]) ? 0 : Cs;
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + costSub);
        }
    }
    return dp[m][n];
}

int main()
{

    string a1="kitten", b1="sitting";
    string a2="flaw", b2="lawn";
    string a3 = "algorithm", b3 = "logarithm";

    
    cout << "Test Case 1: 'kitten' -> 'sitting', Ci=1, Cd=2, Cs=3" << endl;
    cout << "Expected: 7, Got: " << EditDistance(a1, b1, 1, 2, 3) << endl
         << endl;


    cout << "Test Case 2: 'flaw' -> 'lawn', Ci=2, Cd=2, Cs=1" << endl;
    cout << "Expected: 4, Got: " << EditDistance(a2, b2, 2, 2, 1) << endl
         << endl;


    cout << "Test Case 3: 'algorithm' -> 'logarithm', Ci=1, Cd=3, Cs=2" << endl;
    cout << "Expected: 6, Got: " << EditDistance(a3, b3, 1, 3, 2) << endl
         << endl;

    string s1, s2;
    int Ci, Cd, Cs;
    cout << "\nEnter s1, s2 and costs Ci Cd Cs: ";
    if (cin >> s1 >> s2 >> Ci >> Cd >> Cs)
    {
        cout << "Edit Distance: " << EditDistance(s1, s2, Ci, Cd, Cs) << endl;
    }
    return 0;
}
