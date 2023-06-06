#include <iostream>
#include "befehle.h"
#include "einlesen.h"
#include "test.h"
#include "regfunc.h"

using namespace std;

// Programmspeicher
extern int progSpeicher[1024];
// Ram 1
extern uint8_t dataSpeicher[2][128];
// Stack
extern int stack[8];
// Speicher für das gesamte Program
extern string prog[1000];
//  
extern int matchZeile[1024];

extern uint8_t wReg;

extern uint8_t wdt; //Watchdog 
extern int wdtPre; // Watchdog prescaler




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
