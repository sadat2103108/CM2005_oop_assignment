#pragma once
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>


using namespace std;

vector<vector<float>> transpose(const vector<vector<float>>& mat) {
    if (mat.empty()) return {};

    int rows = mat.size();
    // Find max number of columns in any row
    int cols = 0;
    for (const auto& row : mat)
        if ((int)row.size() > cols) cols = row.size();

    vector<vector<float>> transposed(cols, vector<float>(rows, 0.0f));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < (int)mat[i].size(); ++j) {
            transposed[j][i] = mat[i][j];
        }
    }

    return transposed;
}

// tm parseTimestamp(const string& timestamp) {
//     tm t = {};
//     istringstream ss(timestamp.substr(0, 19));
//     ss >> get_time(&t, "%Y-%m-%dT%H:%M:%S");

//     return t;
// }

void loadFromCSV(
    map<string, int> &countries, 
    // vector<tm> &timestamps, 
    vector<string> &timestamps, 
    vector<vector<float>> &temperatures
){

    ifstream fin("weather_data.csv");
    string line;
    fin >> line;
    stringstream ss(line);
    string token;
    int j = 0;

    while (getline(ss, token, ','))
    {
        if ((j - 1) % 3 == 0)
        {
            countries[token.substr(0, 2)]= countries.size();
        }
        j++;
    }

    while (fin >> line)
    {
        vector<float> temperature;
        stringstream s1(line);
        string token1;
        j = 0;
        while (getline(s1, token1, ','))
        {
            if (j == 0)
                // timestamps.push_back(parseTimestamp(token1));
                timestamps.push_back(token1);
            if ((j - 1) % 3 == 0)
            {
                temperature.push_back(stof(token1));
            }
            j++;
        }
        temperatures.push_back(temperature);
    }

    temperatures = transpose(temperatures);
}

