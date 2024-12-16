#include "headers.h"

#define MINS_IN_DAY 1440

void displayTime(int mins){
    int hour, minutes;
    hour = mins/60;
    minutes = mins%60;
    printf("%d%d:%d%d\n",hour/10, hour%10, minutes/10,minutes%10);
}


int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    a %= MINS_IN_DAY;
    b %= MINS_IN_DAY;
    a += 60;
    b += 60;

    int at, bt;
    at = a;
    bt = b;
    while(at != bt){
        at += a;
        bt += b;
        at%=MINS_IN_DAY;
        bt%=MINS_IN_DAY;
    }
    displayTime(bt);
}