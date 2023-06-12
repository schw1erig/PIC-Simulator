#pragma once
#include "common.h"
#include <iostream>

using namespace std;



void syncDataSpeicher() {

	// status 
	// intcon 
	// PCL
	// PCLATH
	//über deren setFuntionen bereits syncron

	// sync indirect
	dataSpeicher[!getRP0()][0] = dataSpeicher[getRP0()][0];

	// sync fsr
	dataSpeicher[!getRP0()][4] = dataSpeicher[getRP0()][4];

	// sync anwendungsbereich
	for (int i = 12; i < 64; i++) {
		dataSpeicher[!getRP0()][i] = dataSpeicher[getRP0()][i];
	}


}

int getFSR() {

	return dataSpeicher[getRP0()][4];

}


//-----------------------
// PCLL und PCLATH functions
int getPCL() {

	return dataSpeicher[getRP0()][0x02];

}

void setPCL(uint8_t wert) {

	dataSpeicher[0][0x02] = wert;
	dataSpeicher[1][0x02] = wert;

}

int getPCLATH() {

	return (int) dataSpeicher[getRP0()][0x0A];

}

void setPCLATH(uint8_t wert) {

	dataSpeicher[0][0x0A] = wert;
	dataSpeicher[1][0x0A] = wert;

}

//------------------------------------------------
// INTCON reg functions

void setGIE(int wert) {

	setINTCON(0x80, wert);

}

void setEEIE(int wert) {

	setINTCON(0x40, wert);

}

void setT0IE(int wert) {

	setINTCON(0x20, wert);

}

void setINTE(int wert) {

	setINTCON(0x10, wert);

}

void setRBIE(int wert) {

	setINTCON(0x08, wert);

}

void setT0IF(int wert) {

	setINTCON(0x04, wert);

}

void setINTF(int wert) {

	setINTCON(0x02, wert);

}

void setRBIF(int wert) {

	setINTCON(0x01, wert);

}

//----
int getGIE() {

	return getINTCON(0x80);

}

int getEEIE() {

	return getINTCON(0x40);

}

int getT0IE() {

	return getINTCON(0x20);

}

int getINTE() {

	return getINTCON(0x10);

}

int getRBIE() {

	return getINTCON(0x08);

}

int getT0IF() {

	return getINTCON(0x04);

}

int getINTF() {

	return getINTCON(0x02);

}

int getRBIF() {

	return getINTCON(0x01);

}



int getINTCON(uint8_t maske) {

	// lese intcon aus dem aktuellen Datenspeicher (da status in beiden Bänken gleich eigentlich unnötig)
	uint8_t reg = dataSpeicher[getRP0()][0x0B];

	return ((reg & maske) > 0);

}

void setINTCON(uint8_t maske, int wert) {

	uint8_t reg;

	reg = dataSpeicher[0][0x0B];

	if (wert == 0) {
		reg &= ~(maske);
	}
	else if (wert == 1) {
		reg |= maske;
	}

	dataSpeicher[0][0x0B] = reg;
	dataSpeicher[1][0x0B] = reg;

}

//-------------------------------------------------
// Option reg functions

void setPreVar(int wert) {
	if (getPSA() == 0) {
		//pre an timer
		switch(wert) {
		case 0: pre = 2; break;
		case 1: pre = 4; break;
		case 2: pre = 8; break;
		case 3: pre = 16; break;
		case 4: pre = 32; break;
		case 5: pre = 64; break;
		case 6: pre = 128; break;
		case 7: pre = 256; break;
		default: break;
		}
	}
	else {
		// pre an watchdog
		switch (wert) {
		case 0: pre = 1; break;
		case 1: pre = 2; break;
		case 2: pre = 4; break;
		case 3: pre = 8; break;
		case 4: pre = 16; break;
		case 5: pre = 32; break;
		case 6: pre = 64; break;
		case 7: pre = 128; break;
		default: break;
		}
	}
}

int getTOCS() {
	return getOption(0x20);
}
int getPSA() {
	return getOption(0x08);
}
int getPS() {
	return (4 * (getOption(0x04)) + (2 * getOption(0x02)) + (1 * getOption(0x01)));
}
int getOption(uint8_t maske) {

	// lese option aus dem Datenspeicher (da status in beiden Bänken gleich eigentlich unnötig)
	uint8_t reg = dataSpeicher[1][1];
	//cout << "getoption called: Maske: " << (int) maske << "ergebnis: " << ((reg & maske) > 0) << "\n";
	return ((reg & maske) > 0);
}
void setOption(uint8_t maske, int wert) {

	uint8_t reg = dataSpeicher[1][1];

	if (wert == 0) {
		reg &= ~(maske);
	}
	else if (wert == 1) {
		reg |= maske;
	}

	dataSpeicher[1][1] = reg;

}


//------------------------------------------------
// Status reg functions

int getStatus(uint8_t maske) {

	// lese status aus dem aktuellen Datenspeicher (da status in beiden Bänken gleich eigentlich unnötig)
	uint8_t status = dataSpeicher[(dataSpeicher[0][3] & maskeRP0)][3];

	return ((status & maske) > 0);
}

int getC() {
	return getStatus(maskeC);
}

int getDC() {
	return getStatus(maskeDC);
}

int getZ() {
	return getStatus(maskeZ);
}

int getPD() {
	return getStatus(maskePD);
}

int getTO() {
	return getStatus(maskeTO);
}

int getRP0() {
	return getStatus(maskeRP0);
}



void setStatus(uint8_t maske, int wert) {

	uint8_t status;

	status = dataSpeicher[0][3];

	int bit = (status & maske) > 0;

	if (bit == wert) {
	}
	else if (bit == 0 && wert == 0) {
		status &= ~(maske);
	}
	else if (bit == 0 && wert == 1) {
		status |= maske;
	}
	else if (bit == 1 && wert == 0) {
		status ^= maske;
	}

	dataSpeicher[0][3] = status;
	dataSpeicher[1][3] = status;

}

void setC(int wert) {

	setStatus(maskeC, wert);

}

void setDC(int wert) {

	setStatus(maskeDC, wert);

}

void setZ(int wert) {

	setStatus(maskeZ, wert);

}

void setPD(int wert) {

	setStatus(maskePD, wert);

}

void setTO(int wert) {

	setStatus(maskeTO, wert);

}

void setRP0(int wert) {

	setStatus(maskeRP0, wert);

}