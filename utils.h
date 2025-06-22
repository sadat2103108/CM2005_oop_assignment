#include <cstdlib>
#include<string>
#include<iostream>
using namespace std;

void clearScreen(){
    system("cls");
}


int timeToIdx(string time){
    // 1980-01-01T19:00:00Z
    int year = stoi(time.substr(0,4));
    int month = stoi(time.substr(5,2));
    int day = stoi(time.substr(8,2));
    int hour = stoi(time.substr(11,2));

    cout<<year<<" "
        <<month<<" "
        <<day<<" "
        <<hour<<endl;

    return 0;
}

