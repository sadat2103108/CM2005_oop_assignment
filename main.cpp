#include <bits/stdc++.h>
#include "Monitor.h"
#include "processCSV.h"
#include "SparseTable.h"
#include "PrefixSum.h"
#include "utils.h"

using namespace std;

map<string, int> COUNTRIES; //country initials and their index number
// vector<tm> TIMESTAMPS; // all 
vector<string> TIMESTAMPS; // all 
vector<vector<float>> TEMPERATURES;

vector<SparseTable> stMins;	  // for efficiently finding min value of a range
vector<SparseTable> stMaxs;	  // for efficiently finding max value of a range
vector<PrefixSum> prefixSums; // for efficiently finding sum of a range

int COUNTRY_INDEX;

void init()
{
	clearScreen();

	cout<<"WAIT FOR INITIAL LOADING ..."<<endl;
	loadFromCSV(COUNTRIES, TIMESTAMPS, TEMPERATURES);
	clearScreen();
	

	int i = 0;
	int n = COUNTRIES.size();
	for (const auto &countryTemps : TEMPERATURES)
	{
		cout<<"SETTING UP DATA FOR COUNTRY: "<<i+1<<"/"<<n<<endl;
		stMins.emplace_back(countryTemps, "min"); // directly use float vector
		stMaxs.emplace_back(countryTemps, "max"); // directly use float vector
		prefixSums.emplace_back(countryTemps);	  // prefix sum supports float directly
		clearScreen();

		i++;
	}
}



int main(){

	init();

	int op;
	while(true){
		cout<<"1. Choose a country"<<endl;
		cout<<"2. Exit"<<endl;
		cout<<"Enter your option: "; cin>>op;

		if(op==2){
			cout<<"Closing program..."<<endl;
			exit(0);
		}

		clearScreen();
		string country;
		cout<<"Countries: "<<endl;
		for(auto it: COUNTRIES){
			cout<<it.first<<" ";
		} 
		cout<<endl;
		cout<<"Choose your country (e.g. "<<(*COUNTRIES.begin()).first<<"): ";
		cin>>country;

		COUNTRY_INDEX = COUNTRIES[country];

		cout<<"index="<<COUNTRY_INDEX<<endl;
		
		cin.get();

	}

	
	return 0;
}

/*

	vector<Candlestick> data = {
		{72.5, 85.2, 68.1, 78.3},   // green
		{64.7, 70.0, 60.2, 66.8},   // green
		{55.1, 58.9, 49.3, 52.7},   // red
		{47.0, 53.3, 43.1, 50.9},   // green
		{89.4, 92.0, 85.6, 87.2},   // red
		{38.6, 42.5, 35.0, 41.8},   // green
		{22.0, 29.4, 18.5, 24.2},   // green
		{66.3, 69.9, 61.0, 63.7},   // red
		{15.4, 20.1, 12.2, 19.0},   // green
		{-5.3, 1.5, -12.4, -2.8},   // green
		{90.6, 95.7, 87.0, 91.2},   // red
		{76.1, 80.3, 72.5, 77.8},   // green
		{59.2, 65.0, 57.4, 61.1},   // green
		{82.3, 85.9, 78.6, 79.4},   // red
		{12.7, 18.2, 10.0, 16.3},   // green
		{-12.5, -5.1, -18.9, -10.3} // green
	};

*/