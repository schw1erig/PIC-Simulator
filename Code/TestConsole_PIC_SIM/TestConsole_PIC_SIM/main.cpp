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
string prog[1000];
// Zeile des Befehls der globalen Zeile zuordnen
int matchZeile[1024];

uint8_t wReg = 0;
int pcl = 0;
int gie = 0;


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

    // init dataSpeicher
    for (int i = 0; i < 127; i++) {
        dataSpeicher[0][i] = 0;
        dataSpeicher[1][i] = 0;
    }

    //Pfad für die Datei festlegen
    string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim2.LST";
    //Datei einlesen
    einlesen(filename);
    //Eingelesene Datei ausgeben
    fileAusgeben();
    // Befehle aus dem Programm extrahieren
    extractBefehle();

    testSetStatus();
    
    testAddwf();

    cout << "Test: " << (5 > 0);

    return 0;
}


