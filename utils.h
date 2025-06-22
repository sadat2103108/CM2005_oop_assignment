#include <cstdlib>
#include<string>
#include<iostream>
using namespace std;

void clearScreen(){
    system("cls");
}



// int timeToIdx(string time){
    // 1980-05-05T07:00:00Z
    // int year = stoi(time.substr(0,4));
    // int month = stoi(time.substr(5,2));
    // int day = stoi(time.substr(8,2));
// }

int timeToIdx(int year, int month, int day){

    bool leap = (year%4==0)? true: false; 
    year-=1980;

    int offset = ceil(year/4.0);

    if(year%4==0){
        if(month>2) offset++;
    }

    int monthSum[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

    int total = year*365 + monthSum[month-1] + day + offset;


    return (total-1)*24;
}

