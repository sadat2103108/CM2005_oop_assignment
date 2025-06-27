#pragma once
#include <bits/stdc++.h>

using namespace std;

// Transpose a 2D matrix
vector<vector<float>> transpose(const vector<vector<float>>& matrix) {
    if (matrix.empty()) return {};

    int rows = matrix.size();
    int maxCols = 0;
    for (const auto& row : matrix)
        maxCols = max(maxCols, (int)row.size());

    vector<vector<float>> result(maxCols, vector<float>(rows, 0.0f));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < (int)matrix[i].size(); ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

// Load temperature data from CSV and populate country map, timestamps, and temperatures
void loadFromCSV(
    map<string, int>& countryIndexMap, 
    vector<string>& timestamps, 
    vector<vector<float>>& temperatureData
) {
    ifstream file("weather_data.csv");
    if (!file.is_open()) {
        cerr << "Error: Could not open file weather_data.csv\n";
        return;
    }

    string line;
    getline(file, line); // Read header line
    stringstream headerStream(line);
    string headerToken;
    int colIndex = 0;

    // Parse header to build country index map
    while (getline(headerStream, headerToken, ',')) {
        if ((colIndex - 1) % 3 == 0 && colIndex >= 1) {
            string countryCode = headerToken.substr(0, 2);
            if (!countryCode.empty() && countryIndexMap.find(countryCode) == countryIndexMap.end()) {
                countryIndexMap[countryCode] = countryIndexMap.size();
            }
        }
        ++colIndex;
    }

    // Parse each row of data
    while (getline(file, line)) {
        stringstream lineStream(line);
        string token;
        int tokenIndex = 0;
        vector<float> rowTemperatures;
        string timestamp;

        while (getline(lineStream, token, ',')) {
            if (tokenIndex == 0) {
                timestamp = token;
            } else if ((tokenIndex - 1) % 3 == 0) {
                try {
                    rowTemperatures.push_back(stof(token));
                } catch (const exception& e) {
                    rowTemperatures.push_back(NAN); // Handle invalid float
                }
            }
            ++tokenIndex;
        }

        timestamps.push_back(timestamp);
        temperatureData.push_back(rowTemperatures);
    }

    file.close();

    // Transpose so each row corresponds to a country
    temperatureData = transpose(temperatureData);
}
