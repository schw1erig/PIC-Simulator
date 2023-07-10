#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "common.h"

using namespace std;

void resetPIC() {

    qDebug() << "reset" ;

    goLoop = 0;
    // PD und TO auf 1 bei Power on
    setPD(1);
    setTO(1);

    // Bits im Option reg auf 1 setzen
    dataSpeicher[1][1] = 0xff;

    // Bits im Intcon reg auf 0 setzen
    dataSpeicher[0][0x0B] = 0x00;
    dataSpeicher[1][0x0B] = 0x00;

    // ProgZeiger reset
    setProgZeiger(0);
    setPCL(0);
    setPCLATH(0);

    // Watchdog zurücksetzen
    wdt = 0;
    wdtReset = 0;
    // Interne Vorteiler variable auf basis der PS bits setzen
    setPreVar(getPS());
}

void wdtResetPIC() {

    qDebug() << "Wdt reset" ;
    wdtReset = 1;
    goLoop = 0;

    setTO(0);

    // Bits im Option reg auf 1 setzen
    dataSpeicher[1][1] = 0xff;

    // Bits im Intcon reg auf 0 setzen
    dataSpeicher[0][0x0B] = 0x00;
    dataSpeicher[1][0x0B] = 0x00;

    // ProgZeiger reset
    setProgZeiger(0);

    // Interne Vorteiler variable auf basis der PS bits setzen
    setPreVar(getPS());

}

void bootPIC() {

    qDebug() << "boot aufgerufen";

    // init dataSpeicher
    for (int i = 0; i < 127; i++) {
        dataSpeicher[0][i] = 0x00;
        dataSpeicher[1][i] = 0x00;
    }

    // Eingabe array mit default wert füllen
    for (int i = 0; i < 1024; i++) {
        prog[i] = "no";
    }

    // init progSpeicher mit -1 um eindeutig zu erkenn en welche fleder leer sind
    for (int i = 0; i < 1024; i++) {
        progSpeicher[i] = -1;
    }

    // matchZeile array mit default wert füllen
    for (int i = 0; i < 1024; i++) {
        matchZeile[i] = 0;
    }

    // init stack
    for (int i = 0; i < 8; i++) {
        stack[i] = 0;
    }

    // ProgZeiger reset
    setProgZeiger(0);

    // Stack zeiger reset
    stackZeiger = 0;

    // Bits im Option reg auf 1 setzen
    dataSpeicher[1][1] = 0xff;

    // Bits im TRIS reg auf 1 setzen
    dataSpeicher[1][5] = 0xff;
    dataSpeicher[1][6] = 0xff;

    // Bits im Intcon reg auf 0 setzen
    dataSpeicher[0][0x0B] = 0x00;
    dataSpeicher[1][0x0B] = 0x00;

    // PD und TO auf 1 bei Power on
    setPD(1);
    setTO(1);

    // w Reg zurücksetzen
    wReg = 0x00;
    // Watchdog zurücksetzen
    wdt = 0;
    wdtActive = 1;
    wdtReset = 0;

    // Interne Vorteiler variable auf basis der PS bits setzen
    setPreVar(getPS());

    // Takte und Timings reset
    quarzTakt = 4.0000;
    progTime = 0;
    takte = 0;
    deltaTime = 0;
    progTime_before = 0;
}


void einlesen(string filename) {

    // Eingabe array mit default wert füllen
    for (int i = 0; i < 1024; i++) {
        prog[i] = "no";
    }

    ifstream file(filename);
    int counter = 0;
    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            //qDebug() << line << "\n";
            prog[counter] = line;
            counter++;
        }
        maxZeilen = counter;
        qDebug() << maxZeilen;
        file.close();
    }
}

void fileAusgeben() {
    for (int i = 0; i < 1024; i++) {
        if (prog[i] != "no") {
            //qDebug() << prog[i] << "\n";
        }
    }
}

void extractBefehle() {

    // Befehle extrahieren
    int zeile = 0;
    string sZeiger;
    int iZeiger;
    string sBefehl;
    int iBefehl;
    int globZeile = 0;
    string sGlobZeiger;
    int iGlobZeiger;

    // ProgSpeicher array mit default wert füllen
    // init progSpeicher mit -1 um eindeutig zu erkenn en welche fleder leer sind
    for (int i = 0; i < 1024; i++) {
        progSpeicher[i] = -1;
    }

    // matchZeile array mit default wert füllen
    for (int i = 0; i < 1024; i++) {
        matchZeile[i] = 0;
    }

    while (prog[zeile] != "no") {

        sZeiger = "";
        sBefehl = "";
        sGlobZeiger = "";

        //qDebug() << "Zu behandelnde Zeile: " << zeile + 1 << "\n";
        //qDebug() << "Erstes Zeichen : " << prog[zeile][0] << ";\n";
        if (prog[zeile][0] != '0') {
            //qDebug() << "Befehl Not found\n";
        }
        else {
            //qDebug() << "Befehl Found\n";
            // Zeilenummer aus ersten 4 Zeichen ermitteln
            for (int i = 0; i < 4; i++) {
                sZeiger = sZeiger + prog[zeile][i];
                ////qDebug() << "Zeiger schleife: " << sZeiger << "\n";
            }
            // Zeilennummer von hex string in int umwandeln
            iZeiger = stol(sZeiger, nullptr, 16);
            //qDebug() << "int zeiger: " << iZeiger << "\n";

            // Befehl aus den nöchsten 4 Zeichen auslesen
            for (int i = 5; i < 9; i++) {
                sBefehl = sBefehl + prog[zeile][i];
                ////qDebug() << "sBefehl schleife: " << sBefehl << "\n";
            }
            // Umwandlung von hex string in int 
            iBefehl = stol(sBefehl, nullptr, 16);
            //qDebug() << "iBefehl in hex: " << hex << iBefehl << "\n";

            //Speichern im Programspeicher
            progSpeicher[iZeiger] = iBefehl;
            //qDebug() << "im Progspeicher: " << progSpeicher[iZeiger] << "\n";


            // Globale Zeilennummer ermitteln
            for (int i = 20; i < 26; i++) {
                sGlobZeiger = sGlobZeiger + prog[zeile][i];
                ////qDebug() << "sGlobZeiger Schleife: " << sGlobZeiger << "\n";
            }

            // Globale Zeilennummer in int umwandeln
            iGlobZeiger = stoi(sGlobZeiger);
            //qDebug() << "int zeiger: " << iGlobZeiger << "\n";

            // Speichern im matchZeile Array (-1, da array in dem das programm gespeichert ist mit Zeile 1 bei Index 0 beginnt)
            matchZeile[iZeiger] = iGlobZeiger - 1;
            //qDebug() << "Ausgabe Zeile im Array_: "  << dec << matchZeile[iZeiger] << "\n";

        }
        // Nach abarbeitung oder ignorieren Zeilennummer erhöhen
        zeile++;
        //qDebug() << "\n";
    }

    addSpaces();

}

void addSpaces() {
    // zusätzliche Leerzeichen einfügen, wenn in eienr zeile kein befehl steht
    //qDebug() << "addSpaces aufgerufen\n";
    int zeile = 0;
    char first;
    string newZeile = "";

    while (prog[zeile] != "no" && zeile < 1024) {

        first = prog[zeile][0];

        if ( first != '0') {
            newZeile = "         " + prog[zeile];
            prog[zeile] = newZeile;
        }

        zeile++;
    }
}
