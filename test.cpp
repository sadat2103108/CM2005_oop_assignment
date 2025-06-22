#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

int main() {
    std::ifstream file("weather_data.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    std::string line;
    std::getline(file, line); // read header line

    std::vector<int> temp_columns;
    std::stringstream ss(line);
    std::string col;
    int index = 0;

    // Identify temperature column indexes
    while (std::getline(ss, col, ',')) {
        if (col.find("temperature") != std::string::npos) {
            temp_columns.push_back(index);
        }
        index++;
    }

    double min_temp = std::numeric_limits<double>::max();
    double max_temp = std::numeric_limits<double>::lowest();

    // Read data rows
    while (std::getline(file, line)) {
        std::stringstream row_stream(line);
        std::string cell;
        std::vector<std::string> cells;

        while (std::getline(row_stream, cell, ',')) {
            cells.push_back(cell);
        }

        for (int col_idx : temp_columns) {
            if (col_idx < cells.size()) {
                try {
                    double value = std::stod(cells[col_idx]);
                    if (value < min_temp) min_temp = value;
                    if (value > max_temp) max_temp = value;
                } catch (...) {
                    // skip if not a valid double
                }
            }
        }
    }

    file.close();

    std::cout << "Minimum temperature in dataset: " << min_temp << " °C\n";
    std::cout << "Maximum temperature in dataset: " << max_temp << " °C\n";

    // Optional: Convert to Fahrenheit
    auto c_to_f = [](double c) { return c * 9.0 / 5.0 + 32.0; };
    std::cout << "In Fahrenheit:\n";
    std::cout << "Min: " << c_to_f(min_temp) << " °F\n";
    std::cout << "Max: " << c_to_f(max_temp) << " °F\n";

    return 0;
}
