#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "common.h"

using namespace std;

void resetPIC() {

    // init dataSpeicher
    for (int i = 0; i < 127; i++) {
        dataSpeicher[0][i] = 0;
        dataSpeicher[1][i] = 0;
    }

    // TO auf 0, bei normalem power up TO = 1
    setTO(0);

    // Bits im Option reg auf 1 setzen
    dataSpeicher[1][1] = 0xff;

    // init stack
    for (int i = 0; i < 8; i++) {
        stack[i] = 0;
    }

    // ProgZeiger reset
    progZeiger = 0;

    // Stack zeiger reset
    stackZeiger = 0;

    // w Reg zurücksetzen
    wReg = 0;
    // Watchdog zurücksetzen
    wdt = 0;
    // Interne Vorteiler variable auf basis der PS bits setzen
    setPreVar(getPS());

    // Takte und Timings reset
    quarzTakt = 4;
    progTime = 0;
    takte = 0;
    deltaTime = 0;
    progTime_before = 0;

}

void bootPIC() {

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
        matchZeile[i] = NULL;
    }

    // init stack
    for (int i = 0; i < 8; i++) {
        stack[i] = 0;
    }

    // ProgZeiger reset
    progZeiger = 0;

    // Stack zeiger reset
    stackZeiger = 0;

    // Bits im Option reg auf 1 setzen
    dataSpeicher[1][1] = 0xff;

    // PD und TO auf 1 bei Power on
    setPD(1);
    setTO(1);

    // w Reg zurücksetzen
    wReg = 0x00;
    // Watchdog zurücksetzen
    wdt = 0;
    // Interne Vorteiler variable auf basis der PS bits setzen
    setPreVar(getPS());

    // Takte und Timings reset
    quarzTakt = 4;
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
            //cout << line << "\n";
            prog[counter] = line;
            counter++;
        }
        file.close();
    }
}

void fileAusgeben() {
    for (int i = 0; i < 1024; i++) {
        if (prog[i] != "no") {
            cout << prog[i] << "\n";
        }
    }
}

void extractBefehle() {

    // Befehle extrahieren
// noch fehlend: Array, welches nummer derbefehle auf tatsächliche zeile im programm mappt
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
        matchZeile[i] = NULL;
    }

    while (prog[zeile] != "no") {

        sZeiger = "";
        sBefehl = "";
        sGlobZeiger = "";

        cout << "Zu behandelnde Zeile: " << zeile + 1 << "\n";
        cout << "Erstes Zeichen : " << prog[zeile][0] << ";\n";
        if (prog[zeile][0] != '0') {
            cout << "Befehl Not found\n";
        }
        else {
            cout << "Befehl Found\n";
            // Zeilenummer aus ersten 4 Zeichen ermitteln
            for (int i = 0; i < 4; i++) {
                sZeiger = sZeiger + prog[zeile][i];
                //cout << "Zeiger schleife: " << sZeiger << "\n";
            }
            // Zeilennummer von hex string in int umwandeln
            iZeiger = stol(sZeiger, nullptr, 16);
            cout << "int zeiger: " << iZeiger << "\n";

            // Befehl aus den nöchsten 4 Zeichen auslesen
            for (int i = 5; i < 9; i++) {
                sBefehl = sBefehl + prog[zeile][i];
                //cout << "sBefehl schleife: " << sBefehl << "\n";
            }
            // Umwandlung von hex string in int 
            iBefehl = stol(sBefehl, nullptr, 16);
            cout << "iBefehl in hex: " << hex << iBefehl << "\n";

            //Speichern im Programspeicher
            progSpeicher[iZeiger] = iBefehl;
            cout << "im Progspeicher: " << progSpeicher[iZeiger] << "\n";


            // Globale Zeilennummer ermitteln
            for (int i = 20; i < 26; i++) {
                sGlobZeiger = sGlobZeiger + prog[zeile][i];
                //cout << "sGlobZeiger Schleife: " << sGlobZeiger << "\n";
            }

            // Globale Zeilennummer in int umwandeln
            iGlobZeiger = stoi(sGlobZeiger);
            cout << "int zeiger: " << iGlobZeiger << "\n";

            // Speichern im matchZeile Array (-1, da array in dem das programm gespeichert ist mit Zeile 1 bei Index 0 beginnt)
            matchZeile[iZeiger] = iGlobZeiger - 1;
            cout << "Ausgabe Zeile im Array_: "  << dec << matchZeile[iZeiger] << "\n";

        }
        // Nach abarbeitung oder ignorieren Zeilennummer erhöhen
        zeile++;
        cout << "\n";
    }
}
