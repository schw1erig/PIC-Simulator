#include <iostream>
#include "befehle.h"
#include "einlesen.h"
#include "test.h"
#include "regfunc.h"
#include <QDebug>
#include "mainwindow.h"

using namespace std;

extern int test;

// Programmpfad
extern string filename;
// Programmspeicher
extern int progSpeicher[1024];
// Ram 1
extern uint8_t dataSpeicher[2][128];
// Stack
extern int stack[8];
// Speicher fuer das gesamte Program
extern string prog[1024];
//  
extern int matchZeile[1024];

extern uint8_t wReg;

extern double wdt; //Watchdog
extern int wdtActive;
extern int pre; //  prescaler/vorteiler

extern int maxZeilen;


extern uint8_t maskeC;
extern uint8_t maskeDC;
extern uint8_t maskeZ;
extern uint8_t maskePD;
extern uint8_t maskeTO;
extern uint8_t maskeRP0;
extern uint8_t maskeIRP;

extern int progZeiger;
extern int stackZeiger;
extern int quarzTakt;
extern int progTime;
extern int takte;
extern int deltaTime;
extern int progTime_before;
