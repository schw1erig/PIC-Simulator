#include <iostream>
#include "common.h"

using namespace std;

void testSetStatus() {
    // Test der get und Set Status funktionen
    cout << "DC vorher: " << getDC() << "\n";
    setDC(1);
    cout << "DC soll 1: " << getDC() << "\n";
    setDC(1);
    cout << "DC soll 1 bleiben: " << getDC() << "\n";
    setDC(0);
    cout << "DC soll  werden 0: " << getDC() << "\n\n";
}

void testAddwf() {
    // Test von addwf
    wReg = 254;
    dataSpeicher[0][1] = 3;

    cout << "Addwf Debug: 254 + 3 = 2 (FReg), c = 1" << "\nwReg: " << (int)wReg << "\nFReg: " << (int)dataSpeicher[0][1];

    addwf(0x0001);

    cout << "\nErgebnisse:";
    cout << "\nstatus reg: " << (int)dataSpeicher[0][3];
    cout << "\nwRegErg : " << (int)wReg;
    cout << "\nFRegErg: " << (int)dataSpeicher[0][1] << "\nC: " << getC() << "\nDC: " << getDC() << "\nZ: " << getZ() << "\n";
}