#include <iostream>
#include "befehle.h"

#include <string>
#include "einlesen.h"

using namespace std;

// Programmspeicher
int progSpeicher[1024];
// Ram 1
int dataSpeicher1[128];
// Ram 2
int dataSpeicher2[128];
// Stack
int stack[8];
// Speicher für das gesamte Program
string prog[1000];
//  
int matchZeile[1024];



int main()
{

    

    //Pfad für die Datei festlegen
    string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim2.LST";
    //Datei einlesen
    einlesen(filename, prog);
    //Eingelesene Datei ausgeben
    fileAusgeben(prog);

    // Befehle aus dem Programm extrahieren
    extractBefehle(prog, progSpeicher, matchZeile);

    return 0;
}