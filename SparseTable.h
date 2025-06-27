#pragma once

#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

class SparseTable {
    vector<vector<pair<float, float>>> st; // pair<min, max>
    vector<int> logTable;

public:
    SparseTable(const vector<float>& a) {
        int n = a.size();
        int maxLog = log2(n) + 1;

        logTable.resize(n + 1);
        logTable[1] = 0;
        for (int i = 2; i <= n; ++i)
            logTable[i] = logTable[i / 2] + 1;

        st.assign(n, vector<pair<float, float>>(maxLog));
        for (int i = 0; i < n; ++i)
            st[i][0] = {a[i], a[i]}; // {min, max}

        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                float leftMin = st[i][j - 1].first;
                float rightMin = st[i + (1 << (j - 1))][j - 1].first;
                float leftMax = st[i][j - 1].second;
                float rightMax = st[i + (1 << (j - 1))][j - 1].second;

                st[i][j].first = min(leftMin, rightMin);
                st[i][j].second = max(leftMax, rightMax);
            }
        }
    }

    float findMin(int L, int R) const {
        int len = R - L + 1;
        int j = logTable[len];
        return min(st[L][j].first, st[R - (1 << j) + 1][j].first);
    }

    float findMax(int L, int R) const {
        int len = R - L + 1;
        int j = logTable[len];
        return max(st[L][j].second, st[R - (1 << j) + 1][j].second);
    }
};
