#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

string file = "D:\GitHub\PIC-Simulator\TestProg_PicSim_20210420\TPicSim1.LST";

void einlesen(string filename, string prog[]) {

    // Eingabe array mit default wert f�llen
    for (int i = 0; i < 1000; i++) {
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

void fileAusgeben(string prog[]) {
    for (int i = 0; i < 1000; i++) {
        if (prog[i] != "no") {
            cout << prog[i] << "\n";
        }
    }
}

void extractBefehle(string prog[], int progSpeicher[], int matchZeile[]) {

    // Befehle extrahieren
// noch fehlend: Array, welches nummer derbefehle auf tats�chliche zeile im programm mappt
    int zeile = 0;
    string sZeiger;
    int iZeiger;
    string sBefehl;
    int iBefehl;
    int globZeile = 0;
    string sGlobZeiger;
    int iGlobZeiger;

    // ProgSpeicher array mit default wert f�llen
    for (int i = 0; i < 1024; i++) {
        progSpeicher[i] = 0;
    }

    // matchZeile array mit default wert f�llen
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
                cout << "Zeiger schleife: " << sZeiger << "\n";
            }
            // Zeilennummer in int umwandeln
            iZeiger = stoi(sZeiger);
            cout << "int zeiger: " << iZeiger << "\n";
            cout << "zeiger: " << iZeiger << "\n";

            // Befehl aus den n�chsten 4 Zeichen auslesen
            for (int i = 5; i < 9; i++) {
                sBefehl = sBefehl + prog[zeile][i];
                cout << "sBefehl schleife: " << sBefehl << "\n";
            }
            // Umwandlung von hex string in int 
            iBefehl = stol(sBefehl, nullptr, 16);
            cout << "iBefehl: " << iBefehl << "\n";

            //Speichern im Programspeicher
            progSpeicher[iZeiger] = iBefehl;
            cout << "im Progspeicher: " << progSpeicher[iZeiger] << "\n";


            // Globale Zeilennummer ermitteln
            for (int i = 20; i < 26; i++) {
                sGlobZeiger = sGlobZeiger + prog[zeile][i];
                cout << "sGlobZeiger Schleife: " << sGlobZeiger << "\n";
            }

            // Globale Zeilennummer in int umwandeln
            iGlobZeiger = stoi(sGlobZeiger);
            cout << "int zeiger: " << iGlobZeiger << "\n";

            // Speichern im matchZeile Array (-1, da array in dem das programm gespeichert ist mit Zeile 1 bei Index 0 beginnt)
            matchZeile[iZeiger] = iGlobZeiger - 1;
            cout << "Ausgabe Zeile im Array_: " << matchZeile[iZeiger] << "\n";

        }
        // Nach abarbeitung oder ignorieren Zeilennummer erh�hen
        zeile++;
        cout << "\n";
    }


}
