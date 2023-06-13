#include <iostream>
#include "common.h"

#include <string>


using namespace std;

// Globale Variablen
// Programmpfad
string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim1.LST";
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

uint8_t wReg;

double wdt; //Watchdog 
uint8_t pre = 0; // Watchdog prescaler

int progZeiger;
int stackZeiger;

int quarzTakt;  // in MHZ
int progTime; // in Micro-Sekunden
int deltaTime; // in micro-sekunden
int progTime_before; // in micro-sekunden
int takte;

uint8_t maskeC = 0x0001;
uint8_t maskeDC = 0x0002;
uint8_t maskeZ = 0x0004;
uint8_t maskePD = 0x0008;
uint8_t maskeTO = 0x0010;
uint8_t maskeRP0 = 0x0020;
uint8_t maskeIRP = 0x0080;

int main()
{
    
    // Power UP:
    bootPIC();
    // Programm einlesen
    einlesen(filename);
    //Eingelesene Datei ausgeben
    fileAusgeben();
    // Befehle aus dem Programm extrahieren
    extractBefehle();
    // Eingelesenes Programm durchführen
    testProgAblauf();

    return 0;
}


