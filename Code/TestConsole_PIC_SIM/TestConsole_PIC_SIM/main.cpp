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
// Speicher für das gesamte Program
string prog[1024];
// Zeile des Befehls der globalen Zeile zuordnen (erste globale zeile entspricht der 0ten zeile)
int matchZeile[1024];

uint8_t wReg = 0x00;

int wdt = 0; //Watchdog 
int pre = 0; // Watchdog prescaler


uint8_t maskeC = 0x0001;
uint8_t maskeDC = 0x0002;
uint8_t maskeZ = 0x0004;
uint8_t maskePD = 0x0008;
uint8_t maskeTO = 0x0010;
uint8_t maskeRP0 = 0x0020;
uint8_t maskeIRP = 0x0080;

int progZeiger = 0;
int stackZeiger = 0;

int quarzTakt = 4;  // in MHZ
int progTime = 0; // in Micro-Sekunden
int takte = 0;


int main()
{
    
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
    dataSpeicher[1][1] = 0xff;

    // Programm einlesen
    //Pfad für die Datei festlegen
    string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim1.LST";
    //Datei einlesen
    einlesen(filename);
    //Eingelesene Datei ausgeben
    fileAusgeben();
    // Befehle aus dem Programm extrahieren
    extractBefehle();

    // Eingelesenes Programm durchführen
    testProgAblauf();

    /*
    uint8_t test = 0;
    uint8_t test2 = test - 1;

    cout << "Test: " << (int) test << ", Test2: " << (int) test2 << "\n";
    */

    return 0;
}


