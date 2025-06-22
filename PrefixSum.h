#pragma once

#include <vector>
using namespace std;

class PrefixSum {
    vector<double> prefix;  // use double for better precision on floats

public:
    PrefixSum(const vector<float>& arr) {
        int n = arr.size();
        prefix.resize(n + 1);
        prefix[0] = 0.0;
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
    }

    // Query sum in range [L, R], 0-based indexing
    double query(int L, int R) const {
        return prefix[R + 1] - prefix[L];
    }
};
