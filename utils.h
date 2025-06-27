#pragma once

#include <bits/stdc++.h>

#include "Candlestick.h"

using namespace std;




map<string, string> countryNames = {
    {"AT", "Austria"},
    {"BE", "Belgium"},
    {"BG", "Bulgaria"},
    {"CH", "Switzerland"},
    {"CZ", "Czech Republic"},
    {"DE", "Germany"},
    {"DK", "Denmark"},
    {"EE", "Estonia"},
    {"ES", "Spain"},
    {"FI", "Finland"},
    {"FR", "France"},
    {"GB", "United Kingdom"},
    {"GR", "Greece"},
    {"HR", "Croatia"},
    {"HU", "Hungary"},
    {"IE", "Ireland"},
    {"IT", "Italy"},
    {"LT", "Lithuania"},
    {"LU", "Luxembourg"},
    {"LV", "Latvia"},
    {"NL", "Netherlands"},
    {"NO", "Norway"},
    {"PL", "Poland"},
    {"PT", "Portugal"},
    {"RO", "Romania"},
    {"SE", "Sweden"},
    {"SI", "Slovenia"},
    {"SK", "Slovakia"}
};






void clearScreen(){
    system("cls");
}




string toUpperCase(const string& input) {
    string result = input;
    for (char& c : result) {
        c = toupper(c); 
    }
    return result;
}



tuple<int, int, int> getDateInput(const string& label, int xScaleIdx) {
    int y = 1980, m = 1, d = 1;

    cout << "Enter " << label << " Year: ";
    cin >> y;
    if (y == 0) return make_tuple(0, 0, 0);

    if (xScaleIdx > 0) {
        cout << "Enter " << label << " Month: ";
        cin >> m;
        if (m == 0) return make_tuple(0, 0, 0);

        if (xScaleIdx > 1) {
            cout << "Enter " << label << " Day: ";
            cin >> d;
            if (d == 0) return make_tuple(0, 0, 0);
        }
    }

    return make_tuple(y, m, d);
}



chrono::year_month_day timestampToDate(const string& timestamp){
    
    int y = stoi(timestamp.substr(0, 4));
    int m = stoi(timestamp.substr(5, 2));
    int d = stoi(timestamp.substr(8, 2));

    chrono::year_month_day ymd = chrono::year{y} / chrono::month{(unsigned int) m} / chrono::day{(unsigned int) d};

    return ymd;

}    

int dateToIdx(int y, int m, int d, int xScaleIdx) {
    using namespace chrono;

    if( xScaleIdx < 2 ) d=1;
    if( xScaleIdx < 1 ) m = 1;

    // Validate date range
    if (y < 1980 || y > 2020) return -1;
    if (m < 1 || m > 12) return -1;
    if (d < 1 || d > 31) return -1;

    // Create date object
    chrono::year_month_day ymd = chrono::year{y} / chrono::month{(unsigned int) m} / chrono::day{(unsigned int) d};
    
    if (!ymd.ok()) return -1;  // Checks if the date is valid (e.g. not Feb 30)

    // Define base date: 1980-01-01
    chrono::year_month_day base_date = chrono::year{1980} / chrono::month{1} / chrono::day{1};

    // Convert to sys_days to get difference
    chrono::sys_days input = chrono::sys_days{ymd};
    chrono::sys_days base = chrono::sys_days{base_date};

    // Calculate day difference
    int days = (input - base).count();

    // Convert to hourly index
    return days * 24;
}    




int getNextDateIdx(const string& timestamp, int xScaleIdx, bool update=true) {

    chrono::year_month_day ymd = timestampToDate(timestamp);

    if(update){
        if (xScaleIdx == 0) ymd += chrono::years{1};
        else if (xScaleIdx == 1) ymd += chrono::months{1};
        else if (xScaleIdx == 2) {
            chrono::sys_days sd = chrono::sys_days{ymd};
            sd += chrono::days{1};
            ymd = chrono::year_month_day{sd};
        }
        
    }

    int y = static_cast<int>(ymd.year());
    int m = static_cast<unsigned>(ymd.month()) ;
    int d = static_cast<unsigned>(ymd.day()) ;
 
    return dateToIdx(y,m,d, xScaleIdx);
}

