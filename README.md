# Levenshtein Distance Calculator Project

## My Development Journey

When I first approached the problem of string matching, my instinct was to use recursion. In `task1_rec.cpp`, I implemented a straightforward recursive solution that checked every possible way to convert one string into another However, I quickly realized that this approach was highly inefficient—its time complexity was exponential (O(3^(m+n))), and it became painfully slow for strings longer than 10 characters. The repeated calculations made it impractical for real-world use.

Determined to improve, I explored dynamic programming. In `task1.cpp`, I used memoization (tabulation) to store intermediate results, reducing the time and space complexity to O(n*m). This made the solution much faster and more scalable, allowing it to handle much larger strings efficiently.

Next, I wanted to extend the functionality. In `task2.cpp`, I introduced weighted operations, allowing custom costs for insertion, deletion, and substitution. This made the algorithm more flexible for different use cases.

For `task3.cpp`, I built a spell checker. By leveraging the Levenshtein distance algorithm, the program could suggest the most similar word from a dictionary. This required iterating over a list of common words and finding the one with the minimum edit distance to the input. The time and space complexity remained O(n*m), but the practical utility increased significantly.

I then focused on optimizing space. In `task4.cpp`, I reduced the space complexity from O(n*m) to O(m) by using only two arrays (previous and current) instead of the full DP matrix. This optimization allowed the program to handle even longer strings without running into memory issues.

Finally, after thoroughly understanding the Levenshtein distance algorithm, I created `levenshtein_calculator.cpp`. This comprehensive CLI tool brings everything together: it takes two strings as input, computes both the standard and weighted Levenshtein distances, displays the tabulation matrix, and traces the path of the minimum distance using a bottom-up approach. It also integrates a spell checker and provides step-by-step explanations and visualizations.

## Task Implementations


## Task 1 (DP): Basic Edit Distance with Dynamic Programming

- **File:** `task1.cpp`
- **Time Complexity:** O(m * n)
- **Space Complexity:** O(m * n)

**How to run:**

```bash
g++ -std=c++11 task1.cpp -o task1
./task1
```

---

## Task 2: Weighted Edit Distance

- **File:** `task2.cpp`
- **Time Complexity:** O(m * n)
- **Space Complexity:** O(m * n)

**How to run:**

```bash
g++ -std=c++11 task2.cpp -o task2
./task2
```

---

## Task 3: Spell Checker

- **File:** `task3.cpp`
- **Time Complexity:** O(k * m * n) (k = dictionary size)
- **Space Complexity:** O(m * n)

**How to run:**

```bash
g++ -std=c++11 task3.cpp -o task3
./task3
```

---

## Task 4: Space-Optimized Edit Distance

- **File:** `task4.cpp`
- **Time Complexity:** O(m * n)
- **Space Complexity:** O(min(m, n))

**How to run:**

```bash
g++ -std=c++11 task4.cpp -o task4
./task4
```

---

## Levenshtein Calculator (Comprehensive CLI)

- **Files:**
  - `levenshtein_calculator.cpp`
  - `word_dic.h`
  - `word_dic.cpp`

**How to run:**

```bash
g++ -std=c++11 levenshtein_calculator.cpp word_dic.cpp -o program
./program
```

**Features:**

- Basic and weighted edit distance calculation
- Matrix visualization
- Step-by-step operation explanations
- Spell checking with dictionary integration
- Space optimization explanation

---

## Implementation Details

The Levenshtein distance algorithm measures the minimum number of  
single-character edits (insertions, deletions, or substitutions) required  
to change one string into another. My implementations cover:

- Recursive approach  
- Dynamic programming  
- Weighted operations  
- Space optimization  
- Dictionary-based spell checking

---

## Performance Comparison

| Implementation     | Time Complexity | Space Complexity | Best Use Case                     |
|--------------------|------------------|-------------------|-----------------------------------|
| Recursive           | O(3^(m+n))       | O(m+n)            | Educational, very short strings   |
| DP (Basic)          | O(m * n)         | O(m * n)          | General purpose                   |
| DP (Weighted)       | O(m * n)         | O(m * n)          | Custom operation costs            |
| DP (Optimized)      | O(m * n)         | O(min(m, n))      | Memory-constrained scenarios      |
