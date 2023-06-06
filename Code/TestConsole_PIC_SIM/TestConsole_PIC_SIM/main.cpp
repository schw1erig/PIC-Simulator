#include <iostream>
#include "common.h"

#include <string>


using namespace std;


// Programmspeicher
int progSpeicher[1024];
// Speicherbank [bank: 0-1] [register: 0-127]
uint8_t dataSpeicher[2][128];
// Stack
int stack[8];
// Speicher f�r das gesamte Program
string prog[1024];
// Zeile des Befehls der globalen Zeile zuordnen (erste globale zeile entspricht der 0ten zeile)
int matchZeile[1024];

uint8_t wReg = 0x00;

uint8_t wdt = 0x00; //Watchdog 
int wdtPre = 0; // Watchdog prescaler



uint8_t maskeC;
uint8_t maskeDC;
uint8_t maskeZ;
uint8_t maskePD;
uint8_t maskeTO;
uint8_t maskeRP0;
uint8_t maskeIRP;

int progZeiger = 0;
int stackZeiger = 0;

int quarzTakt = 4;  // in MHZ
int progTime = 0; // in Micro-Sekunden
int takte = 0;


int main()
{
    maskeC = 0x0001;
    maskeDC = 0x0002;
    maskeZ = 0x0004;
    maskePD = 0x0008;
    maskeTO = 0x0010;
    maskeRP0 = 0x0020;
    maskeIRP = 0x0080;

    // Power UP:
    // init dataSpeicher
    for (int i = 0; i < 127; i++) {
        dataSpeicher[0][i] = 0;
        dataSpeicher[1][i] = 0;
    }


    // PD und TO auf 1 bei Power on
    setPD(1);
    setTO(1);

    // Bits im Option reg auf 1 setzen
    dataSpeicher[1][1] = 0;

    // Programm einlesen
    //Pfad f�r die Datei festlegen
    string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim2.LST";
    //Datei einlesen
    einlesen(filename);
    //Eingelesene Datei ausgeben
    fileAusgeben();
    // Befehle aus dem Programm extrahieren
    extractBefehle();

    //testSetStatus();
    //estAddwf();

    testProgAblauf();

    return 0;
}


