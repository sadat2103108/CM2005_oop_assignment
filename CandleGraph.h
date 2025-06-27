#pragma once

#include <bits/stdc++.h>

#include "Candlestick.h"
#include "utils.h"


using namespace std;

class CandleGraph
{
private:

    float MAXTEMP;
    float MINTEMP;
    float UNIT;
    int ROW;


    const vector<string> candlePixel = {
        "          ",
        "     |    ",
        "  |GGGGG| ",  // for green candle
        "  |RRRRR| "   // for red candle
    }; 

    const string space = "      ";

    string formatYscale(float val)
    {
        ostringstream out;
        out << ((val < 0) ? "-" : " ");
        out << setw(5) << setfill(' ') << fixed << setprecision(2) << abs(val) << "F    ";
        return out.str();
    }
    float convertToRow(float t)
    {
        // discritize data
        return (ceil((MAXTEMP - t) / (float)UNIT));
    }

public:
    CandleGraph(float mx, float mn, float unit){
        MAXTEMP = mx;
        MINTEMP = mn;
        UNIT = unit;
        ROW = (MAXTEMP - MINTEMP) / UNIT;
    }

    void display(vector<Candlestick> &candleData, int nextIdx, vector<string>&TIMESTAMPS, int xScaleIdx){

        vector<Candlestick> rowData(candleData.size());
        for (int i = 0; i < candleData.size(); i++)
        {
            rowData[i] = candleData[i];

            rowData[i].open = convertToRow(rowData[i].open);
            rowData[i].high = convertToRow(rowData[i].high);
            rowData[i].low = convertToRow(rowData[i].low);
            rowData[i].close = convertToRow(rowData[i].close);
        }

        ofstream fout("graph.txt");

        const int COL = rowData.size();

        for (int i = 0; i < ROW; i++)
        {

            float p = MAXTEMP - UNIT * i;
            fout << formatYscale(p);
            for (int j = 0; j < COL; j++)
            {
                Candlestick candle = rowData[j];

                int topBody = min(candle.open, candle.close);
                int bottomBody = max(candle.open, candle.close);

                if ((i >= candle.high and i < topBody) or (i > bottomBody and i <= candle.low))
                    fout << candlePixel[1] << space;
                else if (i >= topBody and i <= bottomBody)
                {
                    if (candle.close < candle.open)
                        fout << candlePixel[2] << space;
                    else
                        fout << candlePixel[3] << space;
                }
                else
                    fout << candlePixel[0] << space;
            }
            fout << endl;
        }

        // BOTTOM LINE (X AXIS)
        fout << formatYscale(MINTEMP);

        for(int i=0; i<candleData.size(); i++){
            fout<< TIMESTAMPS[nextIdx].substr(0,10)<<space;

            nextIdx = getNextDateIdx(TIMESTAMPS[nextIdx], xScaleIdx);

        }
        fout << endl;



        system("start notepad graph.txt");



    }
};
