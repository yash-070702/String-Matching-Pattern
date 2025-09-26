#include <bits/stdc++.h>
using namespace std;

vector<int> naiveSearch(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;

   
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        // Check match for current shift
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }
        if (j == m) {
            result.push_back(i); 
        }
    }
    return result;
}

int main() {
    string text = "AABAACAADAABAABA";
    string pattern = "AABA";
    vector<int> res = naiveSearch(text, pattern);

    cout << "Pattern found at indices: ";
    for (int idx : res) cout << idx << " ";
    cout << endl;
}

//<============EXPLAINATION===========>

//it is to find out that whether the string is available in the given text or not. If it is available then return the starting index of the string in the text.
// The naive approach is to check for the pattern at every possible position in the text.
// We slide the pattern over the text one by one and check for a match at each position.

//  Complexity

// Time:

// Worst Case: O((n - m + 1) * m) → e.g., text = "AAAAAAAA", pattern = "AAA".

// Best Case (when mismatches occur quickly): O(n).

// Space: O(1) (no extra space apart from output).