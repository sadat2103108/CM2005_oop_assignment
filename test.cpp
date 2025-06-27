#include <chrono>
#include <iostream>

int main() {
    std::chrono::year_month_day ymd{std::chrono::year{2025}, std::chrono::month{6}, std::chrono::day{27}};
    std::cout << static_cast<int>(ymd.year()) << "-" 
              << static_cast<unsigned>(ymd.month()) << "-"
              << static_cast<unsigned>(ymd.day()) << "\n";
    return 0;
}
