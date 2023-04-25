//#include "PIC.h"
//#include "GUI.h"
#include <iostream>
#include "befehle.h"

#include <string>
#include "einlesen.h"


//using namespace System;
//using namespace System::Windows::Forms;
using namespace std;


// int main(array<System::String ^> ^args)
// {
//    return 0;
// }


int progSpeicher[1024];
int dataSpeicher1[128];
int dataSpeicher2[128];
int stack[8];
string prog[1000];



//[STAThread]
int main()
{
    //Forms befehle
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false);
	//Application::Run(gcnew CppCLRWinFormsProject::PIC());

    //Fill eingabe array mit default wert
    for (int i = 0; i < 1000; i++) {
        prog[i] = "no";
    }

    //Pfad für die Datei festlegen
    string filename = "D:/GitHub/PIC-Simulator/TestProg_PicSim_20210420/TPicSim2.LST";
    //Datei einlesen
    einlesen(filename, prog);
    //Eingelesene Datei ausgeben
    fileAusgeben(prog);

    // Befehle extrahieren
    // noch fehlend: Array, welches nummer derbefehle auf tatsächliche zeile im programm mappt
    int zeile = 0;
    string sZeiger;
    int iZeiger;
    string sBefehl;
    int iBefehl;
    while (prog[zeile] != "no") {
        
        sZeiger = "";
        sBefehl = "";

        cout << "Zu behandelnde Zeile: " << zeile + 1 << "\n";
        cout << "Erstes Zeichen : " << prog[zeile][0] << ";\n";
        if (prog[zeile][0] != '0') {
            cout << "Befehl Not found\n";
        }
        else {
            cout << "Befehl Found\n";
            // Zeilenummer aus ersten 4 Zeichen ermitteln
            for(int i = 0; i < 4; i++) {
                sZeiger = sZeiger + prog[zeile][i];
                cout << "Zeiger schleife: " << sZeiger << "\n";
            }
            // Zeilennummer in int umwandeln
            iZeiger = stoi(sZeiger);
            cout << "int zeiger: " << iZeiger << "\n";
            cout << "zeiger: " << iZeiger << "\n";

            // Befehl aus den nöchsten 4 Zeichen auslesen
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
        }
        // Nach abarbeitung oder ignorieren Zeilennummer erhöhen
        zeile++;
        cout << "\n";
    }
    return 0;
}