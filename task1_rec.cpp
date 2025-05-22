#include <bits/stdc++.h>
using namespace std;

int solve(int i, int j, string &str1, string &str2)
{

    if (i == 0)
        return j;
    if (j == 0)
        return i;
    if (str1[i - 1] == str2[j - 1])
        return solve(i - 1, j - 1, str1, str2);
    else
    {
        return 1 + min({solve(i - 1, j, str1, str2),
                        solve(i, j - 1, str1, str2),
                        solve(i - 1, j - 1, str1, str2)});
    }
}

int editDistance(string str1, string str2)
{
    int n = str1.length();
    int m = str2.length();
    return solve(n , m , str1, str2);
}

int main()
{
    cout << "kitten -> sitting: " << editDistance("kitten", "sitting") << endl;
    cout << "flaw -> lawn: " << editDistance("flaw", "lawn") << endl;
    cout << "algorithm -> logarithm: " << editDistance("algorithm", "logarithm") << endl;
    
    string str1, str2;
    cout << "\nEnter first string: ";
    cin >> str1;
    cout << "Enter second string: ";
    cin >> str2;

    cout << "Edit Distance: " << editDistance(str1, str2) << endl;
    return 0;
}