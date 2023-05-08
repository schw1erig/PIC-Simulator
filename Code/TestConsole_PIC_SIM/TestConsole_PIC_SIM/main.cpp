#include <iostream>
#include "befehle.h"

#include <string>
#include "einlesen.h"

#include "common.h"

using namespace std;

// Programmspeicher
int progSpeicher[1024];
// Ram 1
uint8_t dataSpeicher0[128];
// Ram 2
uint8_t dataSpeicher1[128];
// Stack
int stack[8];
// Speicher für das gesamte Program
string prog[1000];
//  
int matchZeile[1024];

uint8_t wReg;
uint8_t maskeC;
uint8_t maskeDC;
uint8_t maskeZ;
uint8_t maskePD;
uint8_t maskeTO;
uint8_t maskeRP0;
uint8_t maskeIRP;

int main()
{
    maskeC = 0x0001;
    maskeDC = 0x0002;
    maskeZ = 0x0004;
    maskePD = 0x0008;
    maskeTO = 0x0010;
    maskeRP0 = 0x0020;
    maskeIRP = 0x0080;

    //Pfad für die Datei festlegen
    string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim2.LST";
    //Datei einlesen
    einlesen(filename);
    //Eingelesene Datei ausgeben
    fileAusgeben();
    // Befehle aus dem Programm extrahieren
    extractBefehle();

    return 0;
}

/*
int getStatus(uint8_t maske) {

    uint8_t status;

    if (getStatus(maskeRP0) == 1) {
         status = dataSpeicher0[3];
    }
    else {
        status = dataSpeicher1[3];
    }
    return status & maske;
}

void setStatus(uint8_t maske, int wert) {
    
    uint8_t status;

    int rp0 = getStatus(5);

    if (rp0 == 1) {
        status = dataSpeicher0[3];
    }
    else {
        status = dataSpeicher1[3];
    }

    int bit = status & maske;

    if (bit == wert) {
    } else if (bit == 0 && wert == 1) {
        status += (wert * maske);
    }
    else if (bit == 0 && wert == 1) {
        status -= (wert * maske);
    }

    if (rp0 == 1) {
        dataSpeicher0[3] = status;
    }
    else {
        dataSpeicher1[3] = status;
    }

}
*/