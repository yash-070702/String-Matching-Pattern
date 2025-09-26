#include <bits/stdc++.h>
using namespace std;



vector<int> computeLPS(string pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int length = 0; 
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; 
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> KMPSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> lps = computeLPS(pattern);
    vector<int> result;

    int i = 0, j = 0; 
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++; j++;
        }

        if (j == m) {
            result.push_back(i - j); 
            j = lps[j - 1];          
        }
         else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
            j = lps[j - 1];
            }
            else {
            i++;
            }
        }
    }
    return result;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    vector<int> res = KMPSearch(text, pattern);

    cout << "Pattern found at indices: ";
    for (int idx : res) cout << idx << " ";
    cout << endl;
}


// Why KMP is Used?

// Solves inefficiency of Naïve search: Instead of re-checking characters after mismatch, KMP uses preprocessed information to skip unnecessary comparisons.

// No spurious hits: Unlike Rabin–Karp, KMP doesn’t depend on hashing, so it’s deterministic.

// Guarantees O(n + m) worst-case time: Super useful when working with large strings.

// Used in string search, DNA sequencing, plagiarism detection, and text editors (like “find” function).

// 🔹 Idea

// Precompute a Longest Prefix Suffix (LPS) array for the pattern.

// LPS[i] = length of longest proper prefix of pattern[0..i] which is also a suffix.

// Helps decide how many characters can be skipped after a mismatch.

// While searching in the text:

// If characters match → move forward.

// If mismatch occurs → use LPS array to jump to the next best position, instead of starting from scratch.

// Complexity

// Preprocessing (LPS array): O(m)

// Search: O(n)

// Total: O(n + m) (worst-case guaranteed)

// Space: O(m) for LPS array

