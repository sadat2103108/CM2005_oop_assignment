#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "Candlestick.h"
#include <cmath>
using namespace std;

class Graphics
{
private:
    /*
        the given dataset has a max temperature of 105.537F
        and min temperature of -35.5234F
        so the scale is made in range [-40,120]
        in Y axis , 1 Unit = 5F
    */
    const float MAXTEMP = 45;
    const float MINTEMP = -40;
    // const int MAXTEMP = 100;
    // const int MINTEMP = 40;
    const float UNIT = 1;
    const int ROW = (MAXTEMP - MINTEMP) / UNIT;
    vector<Candlestick> &candleData;

    const vector<string> candlePixel = {
        "     ",
        "  |  ",
        "|GGG|",  // for green candle
        "|RRR|"}; // for red candle

    const string space = "    ";

    string formatYscale(int val)
    {
        ostringstream out;
        out << ((val < 0) ? "-" : " ");
        out << setw(6) << setfill(' ') << abs(val) << "F    ";
        return out.str();
    }
    float convertToRow(float t)
    {
        // discritize data
        return (ceil((MAXTEMP - t) / (float)UNIT));
    }

public:
    Graphics(vector<Candlestick> &candleData) : candleData(candleData) {}

    void display()
    {

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

            int p = MAXTEMP - UNIT * i;
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
        for (int i = 0; i < COL; i++)
        {
            fout << "MAR" << setfill('0') << setw(2) << i << space;
        }
        fout << endl;
        ///////////////////////////////
    }
};
