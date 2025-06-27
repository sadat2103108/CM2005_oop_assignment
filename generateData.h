#pragma once

#include <bits/stdc++.h>
#include "utils.h"
#include "Candlestick.h"

using namespace std;



vector<Candlestick> generateCandlestickData(vector<float>&TEMPERATURES, int xScaleIdx, int startDateIdx, int endDateIdx, vector<string>& TIMESTAMPS){
    vector<Candlestick> data;
    
    
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
            // cout<<open<<" "<<mx<<" "<<mn<<" "<<close<<endl;
            
            data.emplace_back(Candlestick{open, mx, mn, close});

            open = close;
            close =0, mn = 200, mx = -200;
            cnt=0;
            nextIdx =  getNextDateIdx(TIMESTAMPS[nextIdx], xScaleIdx);
        }
    }


    return data;

}




////////////////////////////////////////
////////////////////////////////////////


struct LinearModel {
    double slope = 0.0;
    double intercept = 0.0;
};

// Perform simple linear regression for (x, y) points
LinearModel linearRegression(const vector<double>& x, const vector<double>& y) {
    int n = (int)x.size();
    double sumX = accumulate(x.begin(), x.end(), 0.0);
    double sumY = accumulate(y.begin(), y.end(), 0.0);
    double sumXY = 0.0, sumXX = 0.0;
    
    for (int i = 0; i < n; ++i) {
        sumXY += x[i] * y[i];
        sumXX += x[i] * x[i];
    }
    
    double slope = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;
    
    return {slope, intercept};
}

// Predict future temperatures for given year, month, day
vector<float> predictTemperature(
    const vector<float>& temperature,
    int target_year, int target_month, int target_day
) {
    using namespace std;
    using namespace chrono;

    year_month_day baseDate = year{1980} / month{1} / day{1};
    sys_days baseSys = sys_days{baseDate};
    int total_hours = (int)temperature.size();

    // Collect data for target_month and target_day across years
    // Store (year, temperature) pairs for each hour
    vector<vector<double>> temps_by_hour(24);
    vector<int> years_found;

    // To avoid duplicates in years_found
    vector<bool> year_recorded(2100, false);

    for (int hour_index = 0; hour_index + 23 < total_hours; hour_index += 24) {
        sys_days current_day = baseSys + days{hour_index / 24};
        year_month_day ymd{current_day};
        unsigned m = unsigned(ymd.month());
        unsigned d = unsigned(ymd.day());
        int y = int(ymd.year());

        if (m == unsigned(target_month) && d == unsigned(target_day)) {
            if (!year_recorded[y]) {
                years_found.push_back(y);
                year_recorded[y] = true;
            }
            for (int h = 0; h < 24; ++h) {
                temps_by_hour[h].push_back(static_cast<double>(temperature[hour_index + h]));
            }
        }
    }

    // Sanity check: all temps_by_hour vectors must have same size = years_found.size()
    if (years_found.empty()) return {};

    // Fit linear regression for each hour
    vector<float> prediction(24);

    for (int h = 0; h < 24; ++h) {
        LinearModel lm = linearRegression(vector<double>(years_found.begin(), years_found.end()), temps_by_hour[h]);
        prediction[h] = static_cast<float>(lm.slope * target_year + lm.intercept);
    }

    return prediction;
}
