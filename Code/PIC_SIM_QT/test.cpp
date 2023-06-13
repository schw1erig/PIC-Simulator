#include <iostream>
#include "common.h"

using namespace std;

//connect(this, SIGNAL(connected()), &main, SLOT(doSomething()));


void testSetStatus() {
    // Test der get und Set Status funktionen
    cout << "DC vorher: " << getDC() << "\n";
    cout << "status: " << (int) dataSpeicher[0][3] << "\n";
    setDC(1);
    cout << "DC soll 1: " << getDC() << "\n";
    cout << "status: " << (int) dataSpeicher[0][3] << "\n";
    setDC(1);
    cout << "DC soll 1 bleiben: " << getDC() << "\n";
    cout << "status: " << (int) dataSpeicher[0][3] << "\n";
    setDC(0);
    cout << "DC soll 0 werden: " << getDC() << "\n\n";
    cout << "status: " << (int) dataSpeicher[0][3] << "\n";
}

void testAddwf() {
    // Test von addwf
    wReg = 1;
    dataSpeicher[1][1] = 0x01;

    cout << "Addwf Debug: " << "\nwReg: " << (int)wReg << "\n + FReg: " << (int)dataSpeicher[1][1];
    setRP0(1);
    addwf(0x0081);

    cout << "\nErgebnisse:";
    //cout << "\nstatus reg: " << (int)dataSpeicher[0][3];
    cout << "\nwRegErg : " << (int)wReg;
    cout << "\nFRegErg: " << (int)dataSpeicher[1][1] << "\nC: " << getC() << "\nDC: " << getDC() << "\nZ: " << getZ() << "\n";
}


/*progAblauf::progAblauf(QObject *parent) :
    QObject(parent)
{
    MainWindow* instance = MainWindow::GetInstance();
    progAblauf* c = new progAblauf();
    MainWindow::connect(c, SIGNAL(testProgAblauf()), instance , SLOT(fillBox()));
    call();
}

void progAblauf::call()
{
    emit testProgAblauf();
}
*/
void testProgAblauf() {

    // Debug ausgabe des eingelesenen programms
    cout << "\n\n-----------------------------------------------------------------------------------------------------------";
    cout << "\nBefehle: \n";

    while (progSpeicher[progZeiger] != -1) {


        cout << hex << progSpeicher[progZeiger] << ", ";
        progZeiger++;

    }
    progZeiger = 0;

    // Test Schleife zum Programmdurchlauf
    cout << "\nStartProgramm\n";
    while (progSpeicher[progZeiger] != -1) {
        
        execBefehl();

    }
}

void testSyncDataSpeicher() {

    cout << "indirect bank 1 und bank 2: " << (int)dataSpeicher[0][14] << "; " << (int)dataSpeicher[1][0] << "\n";
    // Setze status auf bank 0 auf 8
    dataSpeicher[0][0] = 8;

    cout << "Nach dem setzen: indirect bank 1 und bank 2: " << (int)dataSpeicher[0][0] << "; " << (int)dataSpeicher[1][0] << "\n";

    syncDataSpeicher();

    cout << "Nach dem sync: indirect bank 1 und bank 2: " << (int)dataSpeicher[0][0] << "; " << (int)dataSpeicher[1][0] << "\n";


}

void testSetPS() {

    dataSpeicher[1][1] = 0;
    cout << getPS() << "\n";

}
