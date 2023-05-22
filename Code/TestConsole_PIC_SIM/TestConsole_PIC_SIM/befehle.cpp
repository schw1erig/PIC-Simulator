#pragma once
#include "common.h"
#include <iostream>

using namespace std;

int getStatus(uint8_t maske) {

	// lese status aus dem aktuellen Datenspeicher (da status in beiden Bänken gleich eigentlich unnötig)
	uint8_t status = dataSpeicher[(dataSpeicher[0][3] & maskeRP0)][3];

	return status & maske;
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

	int bit = status & maske;

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

void setIOPorts() {

}


// Dummy decode
void decode(int data) {

	cout << "Decode wurde aufgerufen\n";

};

/*
//Befehl-Decode
//derzeit auskommentiert wegen fehlender funktionen
void decode(data) {

	switch (data & 0xffff) {
	case	0x0008:	return	(); break;
	case	0x0009:	retfie(); break;
	case	0x0063:	sleep(); break;
	case	0x0064:	clrwdt(); break;
	case	0x0000:	nop(); break;
	case	0x0020:	nop(); break;
	case	0x0040:	nop(); break;
	case	0x0060:	nop(); break;
	default:
		break;
	}

	switch (data & 0x3f80) {
	case	0x0080:	movwf(); break;
	case	0x0180:	clrf(); break;
	case	0x0100:	clrw(); break;
	default:
		break;
	}

	switch (data & 0x3f00) {
	case	0x0200:	subwf(); break;
	case	0x0400:	iorwf(); break;
	case	0x0500:	andwf(); break;
	case	0x0600:	xorwf(); break;
	case	0x0700:	addwf(); break;
	case	0x0800:	movf(); break;
	case	0x0900:	comf(); break;
	case	0x0a00:	incf(); break;
	case	0x0300:	decf(); break;
	case	0x0b00:	decfsz(); break;
	case	0x0c00:	rrf(); break;
	case	0x0d00:	rlf(); break;
	case	0x0e00:	swapf(); break;
	case	0x0f00:	incfsz(); break;
	case	0x3800:	iorlw(); break;
	case	0x3900:	ANDLW(); break;
	case	0x3a00:	xorlw(); break;
	deafult:
		break;
	}

	switch (data & 0x3e00) {
	case	0x3c00:	sublw(); break;
	case	0x3e00:	addlw(); break;
	default:
		break;
	}

	switch (data & 0x1e00) {
	case	0x1000:	bcf(); break;
	case	0x1400:	bsf(); break;
	case	0x1800:	btfsc(); break;
	case	0x1c00:	btfss(); break;
	case	0x3000:	movlw(); break;
	case	0x3400:	retlw(); break;
	default:
		break;
	}

	switch (data & 0x3800) {
	case	0x2800:	goto	(); break;
	case	0x2000:	call(); break;
	default:
		break;
	}
}

*/


int addlw(int data){
	uint8_t k = 0x00ff & data;
	wReg += k;

	// return der benötigten takte
	return 4;
}

int andlw(int data){
	uint8_t k = 0x00ff & data;
	wReg &= k;

	// return der benötigten takte
	return 4;
}

int addwf(int data){
	uint8_t d = 0x0080 & data; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int c = 0; 
	int z = 0;
	int dc = 0;
	int result;
	int reg = (int)dataSpeicher[getRP0()][f];

 	int time = 4;
	
	//DC berechnung
	// DC: bei add: > 15 -> dc = 1, <= 15 -> dc = 0 ; sub: < 0 -> dc = 1, >= 0 -> dc  1

	if ((wReg & 0x0f) + (reg & 0x0f) > 15) {
		dc = 1;
	}
	
	// Berechnung
	result = wReg + reg;   // Addiert den Wert in WREG mit dem Wert im Register

	// Flags festlegen
	if (result > 255) {
		// Setzt das Carry-Flag basierend auf dem Ergebnis
		c = 1;
		result -= 255;
	}
	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	// Speicherort ermittlen
	if(d == 0)   // Wenn d = 0, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = (uint8_t) result;   // Speichert das Ergebnis im Register
	} else   // Wenn d = 1, wird das Ergebnis in WREG geschrieben
	{
		wReg = (uint8_t) result;
	}

	setC(c);
	setDC(dc);
	setZ(z);

	return time;
}

/*
void andwf(int data)
{
	if(d == 0)   // Wenn d = 0, wird das Ergebnis in das Register geschrieben
	{
		int z;
		int n;
		int result = wReg & reg;   // Führt die logische AND-Operation zwischen WREG und dem Register aus
		z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis
		n = (result >> 7) & 1;   // Setzt das Negative-Flag basierend auf dem Ergebnis
		reg = result;   // Speichert das Ergebnis im Register
	}
	else   // Wenn d = 1, wird das Ergebnis in WREG geschrieben
	{
		wReg = wReg & reg;   // Führt die logische AND-Operation zwischen WREG und dem Register aus
		z = (wReg == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis
		n = (wReg >> 7) & 1;   // Setzt das Negative-Flag basierend auf dem Ergebnis
	}
}

void bcf(uint8_t reg)
{

	reg &= ~(1 << bit);   // Löscht das Bit mit der Position bit im Register
}
*/

void execBefehl() {

	//befehl an stelle des programmzählers erhalten
	int befehl = progSpeicher[progZeiger];
	// erhaltenen befehl decoden
	decode(befehl);
	// ProgZeiger erhöhen
	progZeiger++;

	progTime += (4 / quarzTakt);

	// GUI aktualisieren
	// refreshGUI();

}
