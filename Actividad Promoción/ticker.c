#include "ticker.h"

typedef struct{
    clock_t lastTime;
    clock_t timeOut;
    _eTypeTimer mode;
    OnTimer doTimer;
    unsigned char isActive;
}_sTimer;

static _sTimer myTimer[10];
static int nTimer = 0;
static clock_t currentTime = 0;

int TimerAdd(){
    if(nTimer < 10){
        myTimer[nTimer].doTimer = NULL;
        nTimer++;
        return nTimer;
    }
    return 0;
}

void TimerConnect(int aTimeId, OnTimer aOnTimerFun){
    if(nTimer != 0){
        myTimer[aTimeId-1].doTimer = aOnTimerFun;
    }
}

void TimerStart(int aTimerId, int ms, _eTypeTimer mode){
    if(myTimer[aTimerId-1].isActive)
        return;
    myTimer[aTimerId-1].isActive = 1;
    myTimer[aTimerId-1].timeOut = ms;
    myTimer[aTimerId-1].mode = mode;
    myTimer[aTimerId-1].lastTime = clock();
}

void TimerStop(int aTimerId){
    myTimer[aTimerId-1].isActive = 0;
}

void TickerTask(){
    currentTime = clock();
    for(int i=0; i<nTimer; i++){
        if(myTimer[i].isActive){
            if((currentTime-myTimer[i].lastTime) >= myTimer[i].timeOut){
                if(myTimer[i].doTimer != NULL)
                    myTimer[i].doTimer();
                if(myTimer[i].mode == PERIODIC)
                    myTimer[i].lastTime = currentTime;
                else
                    myTimer[i].isActive = 0;
            }
        }

    }
}
