#include <bits/stdc++.h>
#include "Graphics.h"
#include "processCSV.h"
#include "SparseTable.h"
#include "PrefixSum.h"
#include "utils.h"
#include <string>
#include <vector>

using namespace std;

const int BASE_YEAR = 1980;


map<string, int> COUNTRIES; //country initials and their index number
vector<string> TIMESTAMPS; // all 
vector<vector<float>> TEMPERATURES;

map<int, SparseTable> stMinMax;	  // for efficiently finding min value of a range
map<int, PrefixSum> prefixSums; // for efficiently finding sum of a range



int countryIdx;
string countryCode;

const vector<string> xScales = {"Year", "Month", "Day"};
int xScaleIdx;

int startDateIdx, endDateIdx;


void setUpCountryData(){
	if(stMinMax.find(countryIdx) != stMinMax.end()) return;

	cout<<"......."<<endl;
	stMinMax.emplace(countryIdx, SparseTable(TEMPERATURES[countryIdx]));
	prefixSums.emplace(countryIdx, PrefixSum(TEMPERATURES[countryIdx]));
	
	clearScreen();

}

void init()
{
	clearScreen();

	cout<<"LOADING CSV..."<<endl;
	loadFromCSV(COUNTRIES, TIMESTAMPS, TEMPERATURES);
	clearScreen();
	

	int i = 0;
	int n = COUNTRIES.size();

	setUpCountryData();
	countryCode = (* COUNTRIES.begin()).first;
	countryIdx = COUNTRIES[countryCode];
	startDateIdx = 0;
	endDateIdx = TIMESTAMPS.size()-1;

}

void changeCountry(){
	clearScreen();
	for(auto it: COUNTRIES){
		cout<<it.first<<" ";
	}
	cout<<endl;
	cout<<"Choose a country: "; 
	string x; cin>>x;
	x = toUpperCase(x);

	while(COUNTRIES.find(x) == COUNTRIES.end()){
		cout<<"Invalid country code. try again: "; 
		cin>>x;
		x = toUpperCase(x);
		
	}

	countryCode = x;
	countryIdx = COUNTRIES[x];
	setUpCountryData();

}


void changeDate(){
	
	clearScreen();
	int y1, y2, m1,m2, d1,d2;
	cout<<"Enter starting Year (0 to exit): "; cin>>y1;
	cout<<"Enter starting month: "; cin>>m1;
	cout<<"Enter starting day: "; cin>>d1;
	if(y1==0 or m1==0 or d1==0) return ;
	cout<<"Enter ending Year (0 to exit): "; cin>>y2;
	cout<<"Enter ending month: "; cin>>m2;
	cout<<"Enter ending day: "; cin>>d2;
	if(y2==0 or m2==0 or d2==0) return ;

	int idx1 = dateToIdx(y1,m1,d1, xScaleIdx);
	int idx2 = dateToIdx(y2,m2,d2, xScaleIdx);

	while(idx1>idx2 or idx1<0 or idx1>= (TIMESTAMPS.size()) or idx2<0 or idx2>= (TIMESTAMPS.size()) ){

		clearScreen();
		cout<<"Invalid date or invalid range. Try again !!!!!"<<endl;
		cout<<"Enter starting Year: "; cin>>y1;
		cout<<"Enter starting month: "; cin>>m1;
		cout<<"Enter starting day: "; cin>>d1;

		cout<<"Enter ending Year: "; cin>>y2;
		cout<<"Enter ending month: "; cin>>m2;
		cout<<"Enter ending day: "; cin>>d2;

		idx1 = dateToIdx(y1,m1,d1, xScaleIdx );
		idx2 = dateToIdx(y2,m2,d2, xScaleIdx );

	}


	startDateIdx = idx1;
	endDateIdx = idx2;
}


void changeTimeScale(){
	clearScreen();
	cout<<"1. Year"<<endl;
	cout<<"2. Month"<<endl;
	cout<<"3. Day"<<endl;
	cout<<"Choose Timescale (1/2/3): ";
	int op; cin>>op;
	
	while(op<1 or op>3){
		cout<<"Invalid input, try again:";
		cin>>op;
	} 

	xScaleIdx = op-1;

}


void displayCandleSticks(){

	vector<Candlestick> data = generateCandlestickData( TEMPERATURES[countryIdx], xScaleIdx, startDateIdx, endDateIdx, TIMESTAMPS);
	Graphics g(data);
	g.display();

	
}




int main(){



// vector<Candlestick> data = {
// 	{-3.2, 2.0, -5.1, 1.9},         // green, around 0
//     {1.9, 5.0, -1.0, 0.5},          // red, large lower wick
//     {0.5, 6.0, -0.3, 5.7},          // green
//     {12.0, 18.0, 10.2, 17.5},       // green
//     {17.5, 19.0, 14.0, 15.8},       // red
//     {15.8, 22.0, 13.0, 21.7},       // green
//     {-20.8, -19.0, -27.2, -26.9},   // red
//     {-26.9, -22.0, -30.0, -22.1},   // green
//     {-22.1, -15.0, -23.5, -16.2},   // green
//     {21.7, 23.5, 20.0, 22.4},       // green
//     {22.4, 25.0, 21.0, 21.2},       // red
//     {21.2, 30.0, 18.0, 29.7},       // green
//     {5.7, 5.8, 5.5, 5.6},           // doji
//     {5.6, 10.0, 3.0, 4.4},          // red
//     {4.4, 11.0, 4.0, 10.2},         // green
//     {10.2, 12.5, 8.7, 9.3},         // red
//     {9.3, 13.0, 8.9, 12.1},         // green
//     {12.1, 13.0, 11.9, 12.0},       // doji
//     {-24.3, -19.5, -28.1, -20.8},   // green
//     {-16.2, -12.2, -18.9, -17.8},   // red
//     {-17.8, -10.0, -19.0, -11.4},   // green
//     {29.7, 35.0, 27.0, 33.9},       // green, near max range
//     {33.9, 34.0, 32.5, 33.5},       // red
//     {33.5, 35.0, 33.0, 34.7},       // green
//     {-30.0, -25.0, -34.5, -28.7},   // green, near min range
//     {-28.7, -20.1, -29.9, -22.2},   // green
//     {-22.2, -18.0, -26.0, -24.3},   // red
//     {-11.4, -6.5, -13.8, -7.9},     // green
//     {-7.9, -4.0, -10.1, -9.5},      // red
//     {-9.5, -2.0, -11.0, -3.2},      // green
// };



	// Monitor monitor(data);
	// monitor.display();
	// cout<<"done"<<endl;
	// return 0;


	// float mn = TEMPERATURES[0][0], mx = TEMPERATURES[0][0];
	// for(int i=0; i<TEMPERATURES.size(); i++){
	// 	for(int j=0; j<TEMPERATURES[i].size(); j++){
	// 		mn = min(mn,TEMPERATURES[i][j]);
	// 		mx = max(mx,TEMPERATURES[i][j]);
	// 	}
	// }

	// cout<<mx<<" "<<mn<<endl;
	// return 0;




	init();

	while(true){
		int op;
		clearScreen();
		cout<<"Current preferences:"<<endl;
		cout<<"Country = "<<countryCode<<endl;
		cout<<"Date Range: "<<TIMESTAMPS[startDateIdx]<<" to "<<TIMESTAMPS[endDateIdx]<<endl;
		cout<<"Timescale: "<< xScales[xScaleIdx]<<endl;
		
		cout<<"-------------------------------------------------------"<<endl;

		cout<<"1. Change Country"<<endl;
		cout<<"2. Change Date Range: "<<endl;
		cout<<"3. Change Timescale"<<endl;
		cout<<"4. See candlesticks of the current preferences"<<endl;
		cout<<"5. Make prediction"<<endl;
		cout<<"0. exit"<<endl;
		cout<<"Choose an option: "; 
		cin>>op;

		while(op<0 or op>5){
			cout<<"Invalid option, choose again: "; 
			cin>>op;
		}

		if(op==0){
			cout<<"Program Ending... "<<endl;
			return 0;
		}

		if(op==1) changeCountry();
		if(op==2) changeDate();
		if(op==3) changeTimeScale();
		if(op==4) displayCandleSticks();
		if(op==5) {}


	}
	

	
	return 0;
}

