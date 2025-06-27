#pragma once

#include <cstdlib>
#include<string>
#include<iostream>
#include "Candlestick.h"
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

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


chrono::year_month_day timestampToDate(const string& timestamp){
    
    int y = std::stoi(timestamp.substr(0, 4));
    int m = std::stoi(timestamp.substr(5, 2));
    int d = std::stoi(timestamp.substr(8, 2));

    chrono::year_month_day ymd = chrono::year{y} / chrono::month{(unsigned int) m} / chrono::day{(unsigned int) d};

    return ymd;

}    

int dateToIdx(int y, int m, int d, int xScaleIdx) {
    using namespace std::chrono;

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



vector<Candlestick> generateCandlestickData(vector<float>&TEMPERATURES, int xScaleIdx, int startDateIdx, int endDateIdx, vector<string>& TIMESTAMPS){
    vector<Candlestick> data;
    
    startDateIdx = getNextDateIdx(TIMESTAMPS[startDateIdx], xScaleIdx, false );
    
    float open = 0; 
    int cnt =0;
    for(int i=startDateIdx; i<= getNextDateIdx(TIMESTAMPS[startDateIdx], xScaleIdx); i++){
        cnt++;
        open+= TEMPERATURES[i];
    }
    open/=cnt;
    cnt=0;
    
    float close =0, mn = 200, mx = -200;
    int nextIdx = getNextDateIdx(TIMESTAMPS[startDateIdx], xScaleIdx);

    for(int i =startDateIdx; i<=endDateIdx; i++){
        
        float t = TEMPERATURES[i];
        mn = min(mn,t);
        mx = max(mx,t);
        close += t;
        cnt++;


        if(i == nextIdx ){
            close/=cnt;
            cout<<open<<" "<<mx<<" "<<mn<<" "<<close<<endl;
            
            data.emplace_back(Candlestick{open, mx, mn, close});

            open = close;
            close =0, mn = 200, mx = -200;
            cnt=0;
            nextIdx =  getNextDateIdx(TIMESTAMPS[nextIdx], xScaleIdx);
        }
    }


    return data;




}