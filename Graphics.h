#pragma once

#include <bits/stdc++.h>

#include "Candlestick.h"
#include "utils.h"


using namespace std;

class Graphics
{
private:

    float MAXTEMP;
    float MINTEMP;
    float UNIT;
    int ROW;


    const vector<string> pixels = {
        "          ",
        "     |    ",
        "  |GGGGG| ",  // for green candle
        "  |RRRRR| ",   // for red candle
        "  ##  ",   // for prediction temp
        "      ",   // for prediction temp
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
    Graphics(float mx, float mn, float unit){
        MAXTEMP = mx;
        MINTEMP = mn;
        UNIT = unit;
        ROW = (MAXTEMP - MINTEMP) / UNIT;
    }

    void displayCandleSticks(vector<Candlestick> &candleData, int nextIdx, vector<string>&TIMESTAMPS, int xScaleIdx){

        const string FILEPATH = "graphCandle.txt";

        vector<Candlestick> rowData(candleData.size());
        for (int i = 0; i < candleData.size(); i++)
        {
            rowData[i] = candleData[i];

            rowData[i].open = convertToRow(rowData[i].open);
            rowData[i].high = convertToRow(rowData[i].high);
            rowData[i].low = convertToRow(rowData[i].low);
            rowData[i].close = convertToRow(rowData[i].close);
        }

        ofstream fout(FILEPATH);

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
                    fout << pixels[1] << space;
                else if (i >= topBody and i <= bottomBody)
                {
                    if (candle.close < candle.open)
                        fout << pixels[2] << space;
                    else
                        fout << pixels[3] << space;
                }
                else
                    fout << pixels[0] << space;
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



        const string command =  "start notepad \"" + FILEPATH + "\"";
        system(command.c_str());

    }


    void displayPredictions(vector<float>&predictData){
        const string FILEPATH = "graphPredicton.txt";

        vector<float> rowData(predictData.size());
        for (int i = 0; i < predictData.size(); i++)
        {
            rowData[i] = convertToRow(predictData[i]);
        }

        //////////////////////////

        ofstream fout(FILEPATH);

        const int COL = rowData.size();

        for (int i = 0; i < ROW; i++)
        {

            float p = MAXTEMP - UNIT * i;
            fout << formatYscale(p);
            for (int j = 0; j < COL; j++)
            {
                if(i== rowData[j] ) fout<<pixels[4]<<space ;
                else fout << pixels[5] << space;
            }
            fout << endl;
        }

        // BOTTOM LINE (X AXIS)
        fout << formatYscale(MINTEMP);

        for(int i=0; i<predictData.size(); i++){
            fout<<setw(2) << setfill('0') <<i;
            fout<<":00H" <<space;

        }
        fout << endl;

        //////////////////////////




        

        const string command =  "start notepad \"" + FILEPATH + "\"";
        system(command.c_str());
    }



};
