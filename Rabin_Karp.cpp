


// Let’s say you want to find if the word "code" appears inside a big article.
// The simplest way? Start from the first letter and check every group of 4 letters one by one. This is known as the naive approach, and it works fine—but it checks every character every time, which can be very slow if the text is long.

// The naive method has a time complexity of O(n × m), where:

// n = length of the text
// m = length of the pattern
// Now imagine trying to find multiple patterns (like checking 100 different words in a document). Doing this the naive way becomes painfully slow.

// Rabin-Karp improves this by using rolling hash.

// Instead of comparing actual characters every time, it converts both the pattern and parts of the text into numbers (hashes) and compares those numbers. This way, most of the time it can detect mismatches without looking at every character, making it much faster and scalable.

//<=====NEGETIVE OR WORST CASE OF RABIN KARP=====>


// What are Spurious Hits?

// A spurious hit occurs when the hash values match, but the actual substrings do not match.

// This happens because different strings can have the same hash → known as a collision.

// In such cases, Rabin–Karp still has to do a character-by-character verification to confirm.

// 🔹 Example of Spurious Hit

// Let’s say our hash function is very simple:

// hash(s) = sum of ASCII values of characters


// Text = "abcdxyz"
// Pattern = "bcdy"

// Hash("bcdy") = ASCII(b)+ASCII(c)+ASCII(d)+ASCII(y)

// Hash("abcd") = same total sum (if numbers align accidentally)

// 👉 Even though "abcd" != "bcdy", their hash may match → this is a spurious hit.

#include <bits/stdc++.h>
using namespace std;



typedef long long ll;
const ll MOD = 1e9 + 7;
const ll P = 31; 

vector<int> rabinKarp(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;

    if (m > n) return result;

    ll patternHash = 0, currentHash = 0;
    ll power = 1;

   
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * P + (pattern[i] - 'a' + 1)) % MOD;
        currentHash = (currentHash * P + (text[i] - 'a' + 1)) % MOD;
        if (i != m - 1) power = (power * P) % MOD; // P^(m-1)
    }

    for (int i = 0; i <= n - m; i++) {
        if (currentHash == patternHash) {
           
            if (text.substr(i, m) == pattern) result.push_back(i);
        }
        if (i < n - m) {
          
            currentHash = (currentHash - (text[i] - 'a' + 1) * power % MOD + MOD) % MOD;
            currentHash = (currentHash * P + (text[i + m] - 'a' + 1)) % MOD;
        }
    }

    return result;
}

int main() {
    string text = "AABAACAADAABAABA";
    string pattern = "AABA";
    vector<int> res = rabinKarp(text, pattern);

    cout << "Pattern found at indices: ";
    for (int idx : res) cout << idx << " ";
    cout << endl;
}
