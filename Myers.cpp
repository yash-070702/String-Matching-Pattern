#include <bits/stdc++.h>
using namespace std;

// Myers' bit-parallel algorithm for approximate string matching
int myersEditDistance(const string &pattern, const string &text)
{
    int m = pattern.size();
    int n = text.size();
    if (m == 0)
        return n;
    if (n == 0)
        return m;

    // Bitmasks for each character
    unordered_map<char, long long> peq;
    for (char c : pattern)
        peq[c] = 0;
    for (int i = 0; i < m; i++)
    {
        peq[pattern[i]] |= (1LL << i);
    }

    long long VP = ~0LL; 
    long long VN = 0;  
    int score = m;

    for (int j = 0; j < n; j++)
    {
        long long PM = peq.count(text[j]) ? peq[text[j]] : 0;
        long long X = PM | VN;
        long long D0 = (((X & VP) + VP) ^ VP) | X;

        long long HP = VN | ~(D0 | VP);
        long long HN = D0 & VP;

        if (HP & (1LL << (m - 1)))
            score++;
        if (HN & (1LL << (m - 1)))
            score--;

        HP = (HP << 1) | 1;
        HN = (HN << 1);

        VP = HN | ~(D0 | HP);
        VN = HP & D0;
    }
    return score;
}

int main()
{
    string pattern = "abccde";
    string text = "xabcxabcde";
    cout << "Edit distance = " << myersEditDistance(pattern, text) << endl;
    return 0;
}


// 1. Why Myers’ Algorithm?

// Most pattern matching algorithms (Naive, KMP, Z, Rabin-Karp) deal with exact matching.

// But in real life (DNA search, spell check, fuzzy search), we need to find substrings that match approximately (with insertions, deletions, substitutions allowed).

// This is where Myers’ algorithm comes in.

// ✅ Myers’ algorithm computes approximate matches with edit distance ≤ k in bit-parallel fashion, making it super fast in practice.

// 🔹 2. Core Idea (Bit-parallelism)

// Instead of doing DP with a full m × n table (O(mn)), it:

// Represents rows of the DP table with bit-vectors.

// Uses bitwise operations (AND, OR, XOR, shifts) to simulate multiple DP transitions in parallel.

// This speeds things up dramatically because 1 CPU instruction can handle 32/64 DP states at once.

// 🔹 3. Complexity

// Time: O(n * ⌈m / w⌉)

// n = text length

// m = pattern length

// w = word size (e.g., 64 bits in most machines)

// For small patterns (≤ word size), it’s basically linear in n.

// Much faster than traditional DP (O(mn)) for small k.