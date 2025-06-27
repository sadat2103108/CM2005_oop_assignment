# European Weather Candlestick Visualizer

This C++ program processes hourly temperature data from multiple European countries and generates a candlestick chart representation for a user-specified date range.


## 🚀 Requirements

- **C++ Compiler**: `g++` with C++20 or later.
- **Operating System**: Windows (tested); should work on Linux/macOS with minor adjustments.

You can check your compiler version using:
```
g++ --version
```

## 📥 Dataset Setup

1. Download the weather data CSV from:

   https://data.open-power-system-data.org/weather_data/2020-09-16/weather_data.csv

2. Place the downloaded file as `weather_data.csv` in the **root directory** of this project (same folder as `main.cpp`).

3. ⚠️ **Do not rename the file.** The program expects the filename to be exactly:
weather_data.csv



## 🛠️ Compilation & Running

### On Linux/macOS:
```
g++ -std=c++20 main.cpp -o weather_app
./weather_app
```

### On Windows (Command Prompt or VS Code terminal):
```
g++ -std=c++20 main.cpp -o weather_app && weather_app
```
