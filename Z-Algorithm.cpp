#include <bits/stdc++.h>
using namespace std;

vector<int> computeZ(string s) {
    int n = s.size();
    vector<int> Z(n, 0);
    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
        if (i > R) {
            L = R = i;
            while (R < n && s[R - L] == s[R]) R++;
            Z[i] = R - L;
            R--;
        } else {
            int k = i - L;
            if (Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } else {
                L = i;
                while (R < n && s[R - L] == s[R]) R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
    return Z;
}

vector<int> searchPattern(string text, string pattern) {
    string concat = pattern + "$" + text;
    vector<int> Z = computeZ(concat);
    vector<int> result;
    int m = pattern.size();

    for (int i = m + 1; i < Z.size(); i++) {
        if (Z[i] == m) result.push_back(i - m - 1);
    }
    return result;
}

int main() {
    string text = "AABAACAADAABAABA";
    string pattern = "AABA";

    vector<int> res = searchPattern(text, pattern);
    cout << "Pattern found at indices: ";
    for (int idx : res) cout << idx << " ";
    cout << endl;
}


// Efficient for pattern matching, substring search, and string analysis.

// Computes length of the longest substring starting at position i which is also a prefix of the string.

// Can be used instead of KMP in some problems, and simpler to implement for certain pattern search scenarios.

// Works well for finding all occurrences of a pattern in a text by concatenating pattern + $ + text.

// 🔹 Idea

// Construct a Z-array for a string s of length n.

// Z[i] = length of longest substring starting at i that matches the prefix s[0..n-1].

// Use two pointers L and R to maintain the rightmost segment [L,R] which matches prefix.

// Allows O(n) time computation of Z-array.

// 🔹 Complexity

// Time: O(n + m)

// Space: O(n + m) for concatenated string and Z-array