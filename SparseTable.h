#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

class SparseTable {
    vector<vector<float>> st;
    vector<int> logTable;
    bool isMinQuery; // true = min, false = max

public:
    // Constructor: pass "min" or "max"
    SparseTable(const vector<float>& a, const string& type) {
        isMinQuery = (type == "min");
        int n = a.size();
        int maxLog = log2(n) + 1;

        logTable.resize(n + 1);
        logTable[1] = 0;
        for (int i = 2; i <= n; ++i)
            logTable[i] = logTable[i / 2] + 1;

        st.assign(n, vector<float>(maxLog));
        for (int i = 0; i < n; ++i)
            st[i][0] = a[i];

        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                if (isMinQuery)
                    st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                else
                    st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Query range [L, R], inclusive
    float query(int L, int R) const {
        int len = R - L + 1;
        int j = logTable[len];
        if (isMinQuery)
            return min(st[L][j], st[R - (1 << j) + 1][j]);
        else
            return max(st[L][j], st[R - (1 << j) + 1][j]);
    }
};
