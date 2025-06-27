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