#include <bits/stdc++.h>
#include "Graphics.h"
#include "processCSV.h"
#include "utils.h"
#include "generateData.h"

using namespace std;

map<string, int> COUNTRIES;
vector<string> TIMESTAMPS;
vector<vector<float>> TEMPERATURES;

int countryIdx;
string countryCode;

const vector<string> xScales = {"Year", "Month", "Day"};
int xScaleIdx;

int startDateIdx, endDateIdx;
int predictY, predictM, predictD;

void init()
{

	clearScreen();

	cout << "LOADING CSV..." << endl;
	loadFromCSV(COUNTRIES, TIMESTAMPS, TEMPERATURES);
	clearScreen();

	// setUpCountryData();
	countryCode = (*COUNTRIES.begin()).first;
	countryIdx = COUNTRIES[countryCode];
	startDateIdx = 0;
	endDateIdx = TIMESTAMPS.size() - 1;
}

void selectCountry()
{
	clearScreen();
	for (auto it : COUNTRIES)
	{
		cout << it.first << " : "<<countryNames[it.first]<<endl;
	}
	
	cout << "Enter a country code: ";
	string x;
	cin >> x;
	x = toUpperCase(x);

	while (COUNTRIES.find(x) == COUNTRIES.end())
	{
		cout << "Invalid country code. try again: ";
		cin >> x;
		x = toUpperCase(x);
	}

	countryCode = x;
	countryIdx = COUNTRIES[x];
	// setUpCountryData();
}

void selectTimeFrame()
{
	clearScreen();
	cout << "1. Year" << endl;
	cout << "2. Month" << endl;
	cout << "3. Day" << endl;
	cout << "Choose Timescale (1/2/3): ";
	int op;
	cin >> op;

	while (op < 1 or op > 3)
	{
		cout << "Invalid input, try again:";
		cin >> op;
	}

	xScaleIdx = op - 1;
}



void selectDateRange() {

    clearScreen();
    cout << "Enter 0 to exit anytime\n";

    tuple<int, int, int> start, end;
    int idx1, idx2;

    while (true) {
        start = getDateInput("Starting", xScaleIdx);
        if (get<0>(start) == 0) return;

        end = getDateInput("Ending", xScaleIdx);
        if (get<0>(end) == 0) return;

        idx1 = dateToIdx(get<0>(start), get<1>(start), get<2>(start), xScaleIdx);
        idx2 = dateToIdx(get<0>(end), get<1>(end), get<2>(end), xScaleIdx);

        if (idx1 <= idx2 && idx1 >= 0 && idx2 >= 0 &&
            idx1 < (int)TIMESTAMPS.size() && idx2 < (int)TIMESTAMPS.size()) {
            break;
        }

        clearScreen();
        cout << "Invalid date or invalid range. Try again !!!!!\n";
        cout << "Enter 0 to exit anytime\n";
    }

    startDateIdx = idx1;
    endDateIdx = idx2;
}

void plotCandleStickData()
{
	startDateIdx = getNextDateIdx(TIMESTAMPS[startDateIdx], xScaleIdx, false);
	endDateIdx = getNextDateIdx(TIMESTAMPS[endDateIdx], xScaleIdx, false);

	vector<Candlestick> data = generateCandlestickData(TEMPERATURES[countryIdx], xScaleIdx, startDateIdx, endDateIdx, TIMESTAMPS);

	float mx = data[0].open, mn = data[0].open;
	for (const auto &c : data)
	{
		mx = max({mx, c.open, c.high, c.low, c.close});
		mn = min({mn, c.open, c.high, c.low, c.close});
	}
	float unit = (mx - mn + 1) / 50;
	mx += (5 * unit);
	mn -= (5 * unit);

	Graphics g(mx, mn, unit);
	g.displayCandleSticks(data, startDateIdx, TIMESTAMPS, xScaleIdx);
}


void selectPredictionDate(){
	clearScreen();
	
    while(true){
		int y,m,d;
		cout<<"Set prediction date :======" ;
		cout<<"Enter year: "; cin>>y;
		cout<<"Enter month: "; cin>>m;
		cout<<"Enter day: "; cin>>d;
		
		chrono::year_month_day ymd = chrono::year{y} / chrono::month{(unsigned int) m} / chrono::day{(unsigned int) d};
		
		if(ymd.ok()){
			predictY=y;
			predictM=m;
			predictD=d;
			break;
		}
		clearScreen();
	} 

}

void plotPredictedData(){

	vector<float> prediction = predictTemperature(TEMPERATURES[countryIdx],predictY, predictM, predictD);
	float mx = prediction[0], mn = prediction[0];

	for(float temp: prediction){
		mx = max(mx,temp);
		mn = min(mn,temp);
	}
	float unit = (mx - mn + 1) / 20;
	mx += (3 * unit);
	mn -= (3 * unit);

	Graphics g(mx,mn,unit);
	g.displayPredictions(prediction);

}

int main()
{

	init();

	while (true)
	{
		clearScreen();

		cout << "MAIN MENU: ========================"<<endl;
		cout << "1. Make Candle Stick Graph." << endl;
		cout << "2. Make predictions." << endl;
		cout << "0. Exit" << endl;
		cout << "Enter option (0,1,2): "; 
		int op; cin >> op;

		while (op < 0 or op > 5)
		{
			cout << "Invalid option, choose again: ";
			cin >> op;
		}

		if (op == 0)
		{
			cout << "Program Ending... " << endl;
			return 0;
		}
		if (op == 1)
		{
			selectCountry();
			selectTimeFrame();
			selectDateRange();

			plotCandleStickData();
		}

		if (op == 2)
		{
			selectCountry();
			selectPredictionDate();

			plotPredictedData();
		}
	}

	return 0;
}
