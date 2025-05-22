#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "word_dic.h"

using namespace std;

// Basic edit distance calculation (unweighted)
int edit_distance(const string &s1, const string &s2)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({dp[i - 1][j],      
                                    dp[i][j - 1],      
                                    dp[i - 1][j - 1]}); 
            }
        }
    }

    return dp[m][n];
}
int weighted_edit_distance(const string &s1, const string &s2, int ci, int cd, int cs, int threshold = -1)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i * cd;
    }

    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j * ci;
    }

    for (int i = 1; i <= m; i++)
    {
        int min_row = numeric_limits<int>::max();
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({dp[i - 1][j] + cd,       // deletion
                                dp[i][j - 1] + ci,       // insertion
                                dp[i - 1][j - 1] + cs}); // substitution
            }
            min_row = min(min_row, dp[i][j]);
        }

        if (threshold != -1 && min_row > threshold)
        {
            return numeric_limits<int>::max();
        }
    }

    return dp[m][n];
}

// Create weighted edit distance matrix for visualization
vector<vector<int>> create_weighted_edit_distance_matrix(const string &s1, const string &s2, int ci, int cd, int cs)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
        dp[i][0] = i * cd;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j * ci;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = min({dp[i - 1][j] + cd,       // deletion
                                dp[i][j - 1] + ci,       // insertion
                                dp[i - 1][j - 1] + cs}); // substitution
            }
        }
    }

    return dp;
}

// Generate explanation of operations
vector<string> explain_edit_distance(const string &s1, const string &s2, int ci, int cd, int cs)
{
    int m = s1.length();
    int n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    vector<vector<vector<string>>> operations(m + 1, vector<vector<string>>(n + 1));

    // Initialize first row and column
    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i * cd;
        operations[i][0].clear();
        for (int j = 0; j < i; j++)
        {
            operations[i][0].push_back("Delete '" + string(1, s1[j]) + "'");
        }
    }

    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j * ci;
        operations[0][j].clear();
        for (int i = 0; i < j; i++)
        {
            operations[0][j].push_back("Insert '" + string(1, s2[i]) + "'");
        }
    }

    // Fill the DP table and track operations
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
                operations[i][j] = operations[i - 1][j - 1];
                operations[i][j].push_back("Keep '" + string(1, s1[i - 1]) + "'");
            }
            else
            {
                int delete_cost = dp[i - 1][j] + cd;
                int insert_cost = dp[i][j - 1] + ci;
                int sub_cost = dp[i - 1][j - 1] + cs;
                if (insert_cost <= delete_cost && insert_cost <= sub_cost)
                {
                    dp[i][j] = insert_cost;
                    operations[i][j] = operations[i][j - 1];
                    operations[i][j].push_back("Insert '" + string(1, s2[j - 1]) + "'");
                }
                else if (delete_cost <= insert_cost && delete_cost <= sub_cost)
                {
                    dp[i][j] = delete_cost;
                    operations[i][j] = operations[i - 1][j];
                    operations[i][j].push_back("Delete '" + string(1, s1[i - 1]) + "'");
                }
                else
                {
                    dp[i][j] = sub_cost;
                    operations[i][j] = operations[i - 1][j - 1];
                    operations[i][j].push_back("Substitute '" + string(1, s1[i - 1]) + "' with '" + string(1, s2[j - 1]) + "'");
                }
            }
        }
    }

    return operations[m][n];
}

// Spell checker function
vector<string> spell_checker(const string &word, const vector<string> &dictionary, int ci, int cd, int cs, int max_distance = 2)
{
    if (word.empty() || dictionary.empty())
    {
        return {};
    }

    // --- NEW: Deduplicate dictionary ---
    vector<string> unique_dict = dictionary;
    sort(unique_dict.begin(), unique_dict.end());
    auto last = unique(unique_dict.begin(), unique_dict.end());
    unique_dict.erase(last, unique_dict.end());

    // --- NEW: Remove input word if present ---
    auto it = lower_bound(unique_dict.begin(), unique_dict.end(), word);
    if (it != unique_dict.end() && *it == word)
    {
        unique_dict.erase(it);
    }

    vector<pair<string, int>> distances;

    // Iterate over deduplicated dictionary
    for (const auto &dict_word : unique_dict)
    { // Changed from 'dictionary' to 'unique_dict'
        if (abs((int)dict_word.length() - (int)word.length()) > max_distance)
        {
            continue;
        }

        int dist = weighted_edit_distance(word, dict_word, ci, cd, cs, max_distance);
        if (dist <= max_distance)
        {
            distances.push_back({dict_word, dist});
        }
    }

    if (distances.empty())
    {
        return {};
    }

    sort(distances.begin(), distances.end(),
         [](const pair<string, int> &a, const pair<string, int> &b)
         {
             if (a.second != b.second)
                 return a.second < b.second;
             return a.first < b.first;
         });

    vector<string> result;
    for (const auto &pair : distances)
    {
        result.push_back(pair.first);
    }

    return result;
}

// Print matrix with proper formatting
void print_matrix(const vector<vector<int>> &matrix, const string &s1, const string &s2)
{
    cout << "\nEdit Distance Matrix:" << endl;

    // Print header row with epsilon and s2 characters
    cout << setw(4) << "#";
    for (char c : s2)
    {
        cout << setw(3) << c;
    }
    cout << endl;

    // Print matrix rows with row labels
    for (size_t i = 0; i <= s1.length(); i++)
    {
        if (i == 0)
        {
            cout << setw(3) << "#";
        }
        else
        {
            cout << setw(3) << s1[i - 1];
        }

        for (size_t j = 0; j <= s2.length(); j++)
        {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
}

// Main CLI function
void run_cli()
{
    vector<string> dictionary = getDictionary();

    cout << "\n--- Levenshtein Distance Calculator (CLI) ---" << endl;

    while (true)
    {
        string s1, s2;
        int ci = 1, cd = 1, cs = 1;

        cout << "\nEnter the first string (or 'quit' to exit): ";
        getline(cin, s1);

        if (s1 == "quit")
            break;

        cout << "Enter the second string: ";
        getline(cin, s2);

        // Get insertion cost with default value
        cout << "Enter insertion cost (default 1): ";
        string input;
        getline(cin, input);
        if (!input.empty())
        {
            ci = stoi(input);
        }

        // Get deletion cost with default value
        cout << "Enter deletion cost (default 1): ";
        getline(cin, input);
        if (!input.empty())
        {
            cd = stoi(input);
        }

        // Get substitution cost with default value
        cout << "Enter substitution cost (default 1): ";
        getline(cin, input);
        if (!input.empty())
        {
            cs = stoi(input);
        }

        // Validate costs
        if (ci <= 0 || cd <= 0 || cs <= 0)
        {
            cout << "Costs must be positive integers." << endl;
            continue;
        }

        // Task 1: Basic Edit Distance
        cout << "\nBasic Edit Distance ('" << s1 << "', '" << s2 << "'): "
             << edit_distance(s1, s2) << endl;

        // Task 2: Weighted Edit Distance
        int weighted_dist = weighted_edit_distance(s1, s2, ci, cd, cs);
        cout << "\nWeighted Edit Distance ('" << s1 << "', '" << s2 << "') with costs ("
             << ci << "," << cd << "," << cs << "): " << weighted_dist << endl;

        // Weighted Edit Distance Matrix Visualization
        auto weighted_matrix = create_weighted_edit_distance_matrix(s1, s2, ci, cd, cs);
        print_matrix(weighted_matrix, s1, s2);

        // Explanation of steps (using weighted costs)
        cout << "\nCalculation Steps:" << endl;
        auto steps = explain_edit_distance(s1, s2, ci, cd, cs);
        if (!steps.empty())
        {
            for (size_t i = 0; i < steps.size(); i++)
            {
                cout << "Step " << i + 1 << ": " << steps[i] << endl;
            }
        }
        else
        {
            cout << "No operations needed (strings are identical)." << endl;
        }
        // int max_distance = 2; // Default value
        // cout << "Enter max edit distance (default 2): ";
        // getline(cin, input);
        // if (!input.empty())
        // {
        //     max_distance = stoi(input);
        // }

        // Task 3: Spell Checker (if first string is a single word)
        if (s1.find(' ') == string::npos && !s1.empty())
        {
            cout << "\nSpell checking for '" << s1 << "' against dictionary..." << endl;
            auto similar_words = spell_checker(s1, dictionary, ci, cd, cs );
            if (!similar_words.empty())
            {
                cout << "Similar words:" << endl;
                for (const auto &word : similar_words)
                {
                    int dist = weighted_edit_distance(s1, word, ci, cd, cs);
                    cout << "- " << word << " (distance: " << dist << ")" << endl;
                }
            }
            else
            {
                cout << "No similar words found within max distance." << endl;
            }
        }

        // Task 4: Optimization Explanation
        cout << "\n--- Optimization (Task 4) ---" << endl;
        cout << "The standard dynamic programming approach uses O(m*n) space." << endl;
        cout << "Space can be optimized to O(min(m, n)) by only keeping the previous and current rows of the DP table in memory." << endl;
        cout << "Further optimizations like early termination (for distance thresholding) and caching can improve performance, especially for spell checking." << endl;
    }

    cout << "\nExiting calculator." << endl;
}

int main()
{
    run_cli();
    return 0;
}