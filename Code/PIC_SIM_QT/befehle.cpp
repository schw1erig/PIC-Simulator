#include "common.h"
#include <iostream>


using namespace std;


void setIOPorts() {

}

void setProgZeiger(int zeiger) {

    // ProgZeiger erhöhen, falls max von 1024 erreicht, setze auf 0
    if (progZeiger < 1024) {
        progZeiger = zeiger;
    } else {
        progZeiger = 0;
    }
    // setze pcl entsprechend dem progZeiger
    setPCL((zeiger & 0x0f));
    //qDebug() << "PCL: " <<(int) getPCL();


}

//Befehl-Decode
//derzeit auskommentiert wegen fehlender funktionen
void decode(int data) {

	cout << "Decode aufgerufen:\n";

    // ProgZeiger erhöhen, falls max von 1024 erreicht, setze auf 0
    setProgZeiger(progZeiger+1);

	switch (data & 0xffff) {
	case	0x0008:	picReturn(data); break;
	case	0x0009:	retfie(data); break;
	case	0x0063:	sleep(data); break;
	case	0x0064:	clrwdt(data); break;
	case	0x0000:	nop(); break;
	case	0x0020:	nop(); break;
	case	0x0040:	nop(); break;
	case	0x0060:	nop(); break;
	default:
		break;
	}

	switch (data & 0xff80) {
	case	0x0080:	movwf(data); break;
	case	0x0180:	clrf(data); break;
	case	0x0100:	clrw(data); break;
	default:
		break;
	}

	switch (data & 0xff00) {
	case	0x0200:	subwf(data); break;
	case	0x0400:	iorwf(data); break;
	case	0x0500:	andwf(data); break;
	case	0x0600:	xorwf(data); break;
	case	0x0700:	addwf(data); break;
	case	0x0800:	movf(data); break;
	case	0x0900:	comf(data); break;
	case	0x0a00:	incf(data); break;
	case	0x0300:	decf(data); break;
	case	0x0b00:	decfsz(data); break;
	case	0x0c00:	rrf(data); break;
	case	0x0d00:	rlf(data); break;
	case	0x0e00:	swapf(data); break;
	case	0x0f00:	incfsz(data); break;
	case	0x3800:	iorlw(data); break;
	case	0x3900:	andlw(data); break;
	case	0x3a00:	xorlw(data); break;
	deafult:
		break;
	}

	switch (data & 0xfe00) {
	case	0x3c00:	sublw(data); break;
	case	0x3e00:	addlw(data); break;
	default:
		break;
	}

	switch (data & 0xfc00) {
	case	0x1000:	bcf(data); break;
	case	0x1400:	bsf(data); break;
	case	0x1800:	btfsc(data); break;
	case	0x1c00:	btfss(data); break;
	case	0x3000:	movlw(data); break;
	case	0x3400:	retlw(data); break;
	default:
		break;
	}

	switch (data & 0xf800) {
	case	0x2800:	picGoto(data); break;
	case	0x2000:	call(data); break;
	default:
		break;
	}

	

}




// BYTE-ORIENTED FILE REGISTER OPERATIONS
void addwf(int data) {
	cout << "addwf aufgerufen\n";
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;
	int reg = (int)getRegInhalt(f); // Reg an Stelle f inhalt
	cout << "Reg: " << reg << "\n";
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
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);

		// PC setzen mit PCL und PClath ersetzen
		if (f == 2) {

			progZeiger = 0;
			progZeiger |= (uint8_t) result;
			int pcLath5Bits = (dataSpeicher[getRP0()][0x0A]) & (0x1f);
			progZeiger |= (pcLath5Bits << 8);
		}			
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = (uint8_t)result;
	}

	setC(c);
	setDC(dc);
	setZ(z);

	takte += 4; // standard für benötigte Takte 

}


void andwf(int data)
{
	cout << "andwf aufgerufen\n";
	takte += 4; // standard für benötigte Takte 
	int z = 0;
	uint8_t result;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	result = wReg & reg;   // Führt die logische AND-Operation zwischen WREG und dem Register aus
	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);

	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;
	}

	setZ(z);
}


void clrf(int data) {
	cout << "clrf aufgerufen\n";

	takte += 4;

	uint8_t f = (data & 0x7f);
	int z = 1;
	uint8_t reg = getRegInhalt(f); //aktueller wert in reg f
	uint8_t result = 0;

	setRegInhalt(f, (uint8_t)result);

	setZ(z);

}

void clrw(int data) {
	cout << "clrw aufgerufen\n";

	takte += 4;
	int z = 1;

	wReg = 0;

	setZ(z);
}

void comf(int data) {
	cout << "comf aufgerufen\n";
	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	int z;

	uint8_t result = ~reg; //Bilde Complement
	z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{

		setRegInhalt(f, result);

	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;  
	}
	setZ(z);

}

void decf (int data) {
	cout << "decf aufgerufen\n";

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	uint8_t result = reg--;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);

	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setZ(z);
}

void decfsz(int data) {
	cout << "decfsz aufgerufen\n";

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	uint8_t result = reg--;

	int z = (result == 0);


	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);

	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   // Führt die logische AND-Operation zwischen WREG und dem Register aus
	}

	if (result == 0) nop();

	setZ(z);
}

void incf(int data) {
	cout << "incf aufgerufen\n";

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	uint8_t result = reg++;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);

	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setZ(z);
}

void incfsz(int data) {
	cout << "incfsz aufgerufen\n";

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	uint8_t result = reg++;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 1, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	if (result == 0) nop();

	setZ(z);
}

void iorwf(int data) {
	cout << "iorwf aufgerufen\n";
	/*
	Inclusive OR the W register with contents of
	register ’f’. If ’d’ is 0 the result is placed in the
	W register. If ’d’ is 1 the result is placed
	back in register ’f’.
	*/

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt

	uint8_t result = wReg | reg;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setZ(z);

}

void movf(int data) {
	cout << "movf aufgerufen\n";
	/* 
	The contents of register f is moved to a
	destination dependant upon the status
	of d.If d = 0, destination is W register.If
	d = 1, the destination is file register f
	itself.d = 1 is useful to test a file register
	since status flag Z is affected.
	*/
	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f); // Register f Inhalt
	uint8_t result = reg;

	int z = 1;

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   // speichere wert von Ref in WReg
	}

	setZ(z);

}

void movwf(int data) {
	cout << "movwf aufgerufen\n";
	//Move data from W register to register 'f'
	takte += 4;

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f);
	uint8_t result = wReg;

	setRegInhalt(f, (uint8_t)result);

}

void nop() { 
	cout << "nop aufgerufen\n";
	takte += 4; 
	//timer erhöhen
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}
}

void rlf(int data) {
	cout << "rlf aufgerufen\n";
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f);
	uint8_t result;
	int c = getC();
	int newC;

	if (reg & 0x80) {
		newC = 1;
	}
	else {
		newC = 0;
	}

	result = reg << 1;

	result |= c; // setze erstes Bit auf den wert des vorherigen carrys
	
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setC(newC);
	takte += 4;
}

void rrf(int data) {
	cout << "rrf aufgerufen\n";
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = getRegInhalt(f);
	uint8_t result;
	int c = getC();
	int newC;

	if (reg & 0x01) {
		newC = 1;
	}
	else {
		newC = 0;
	}

	result = reg >> 1;

	if (c == 1) {
		result |= 0x80;
	}

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;
	}

	setC(newC);
	takte += 4;
}

void subwf(int data) {
	cout << "subwf aufgerufen\n";
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;
	int reg = (int)getRegInhalt(f); // Reg an Stelle f inhalt



	//DC berechnung
	// DC: bei add: > 15 -> dc = 1, <= 15 -> dc = 0 ; sub: < 0 -> dc = 1, >= 0 -> dc  0

	if ( ((reg & 0x0f) - (wReg & 0x0f)) < 0) {
		dc = 1; // durch "fehler" im PIC eigentlich falsch, müsste = 1 sein
	}

	// Berechnung
	result = reg - wReg;   // subtrahiere wert im register f von wREG 

	// Flags festlegen
	if (result < 0) {
		// Setzt das Carry-Flag basierend auf dem Ergebnis
		c = 0; // durch "fehler" im PIC eigentlich falsch, müsste = 1 sein
		result += 255;
	}
	else {
		c = 1;
	}

	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

// Speicherort ermittlen
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = (uint8_t)result;
	}

	// setze Flags
	setC(c);
	setDC(dc);
	setZ(z);

	// ERhöhe Takte
	takte += 4;
}

void swapf(int data) {
	cout << "swapf aufgerufen\n";
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int reg = (int)getRegInhalt(f); // Reg an Stelle f inhalt

	int resultLeft = reg << 4; 
	int resultRight = reg >> 4;
	int result = resultLeft | resultRight;

	// Speicherort ermittlen
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{

		setRegInhalt(f, (uint8_t)result);

	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = (uint8_t)result;
	}
	
	takte += 4;
}


void xorwf(int data) {
	cout << "xorwf aufgerufen\n";
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	uint8_t reg = getRegInhalt(f); // Reg an Stelle f inhalt

	uint8_t result;

	result = wReg ^ reg;

	
	// Speicherort ermittlen
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		setRegInhalt(f, (uint8_t)result);
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;
	}

	setZ(1);

}


// Bitorientierten Befehle

void bcf(int data) {
	cout << "bcf aufgerufen\n";
	// Löscht Bit b in Adresse f

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg = getRegInhalt(f);
	uint8_t result;

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	// Führe Operation aus
	result = reg & ~(1u << b); //löschen des bten bits mit komplement und UND

	setRegInhalt(f, (uint8_t)result);

	takte += 4;
}

void bsf(int data) {
	cout << "bsf aufgerufen\n";
	// Setzt Bit b in Adresse f

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg = getRegInhalt(f);
	uint8_t result;

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	// Führe Operation aus
	result = reg | (1u << b); //setzen des bten bits: mit oder

	setRegInhalt(f, (uint8_t)result);

	takte += 4;
}

void btfsc(int data) {
	cout << "btfsc aufgerufen\n";
	// Testet Bit b an Adr. f und springt, wenn es 0 ist

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg = getRegInhalt(f);

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	if ((reg & b) > 0) {
		// bit b in reg an stelle f = 1 -> do nothing + next befehl
	}
	else {
		// bit b in reg an stelle f = 0, führe nop() aus und überspringe den nächsten befehl
        setProgZeiger(progZeiger+1);
		nop();
	}

	takte += 4;
	
}

void btfss(int data) {
	cout << "btfss aufgerufen\n";
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg = getRegInhalt(f);

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	if ((reg & b) == 0) {
		// bit b in f = 0-> do nothing + next befehl
	}
	else {
		// bit b in f = 1, führe nop() aus und überspringe den nächsten befehl
        setProgZeiger(progZeiger+1);
		nop();
	}

	takte += 4;

}


void addlw(int data) {
	cout << "addlw aufgerufen\n";
	// Add literal and W
	uint8_t k = 0x00ff & data;
	

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;

	//DC berechnung
	// DC: bei add: > 15 -> dc = 1, <= 15 -> dc = 0 ; sub: < 0 -> dc = 1, >= 0 -> dc  1

	if ((wReg & 0x0f) + (k & 0x0f) > 15) {
		dc = 1;
	}

	// Berechnung
	result = (int) wReg + (int) k;   // Addiert den Wert in WREG mit dem Wert im Register

	// Flags festlegen
	if (result > 255) {
		// Setzt das Carry-Flag basierend auf dem Ergebnis
		c = 1;
		result -= 255;
	}

	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	// Schreibe in W reg

	wReg = (uint8_t)result;

	// Setze flags
	setC(c);
	setDC(dc);
	setZ(z);

	takte += 4;

}

void andlw(int data){
	cout << "andlw aufgerufen\n";
	
	int z = 0;
	uint8_t result;

	uint8_t k = 0x00ff & data; // Register Pfad

	result = wReg & k;   // Führt die logische AND-Operation zwischen WREG und k aus
	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	// Schreibe Ergebniss in das wReg
	wReg = result;

	// Setze Flags
	setZ(z);

	// Erhöhe Takte
	takte += 4; // standard für benötigte Takte 
}

void call(int data) {
	cout << "call aufgerufen\n";
	// Unterprogrammaufruf an Adresse k

	int k = data & 0x07ff;

	cout << "k: " << k << "\n";

	// First, return address (PC + 1) is pushed onto the stack.

	pushStack(progZeiger);
	cout << "stack[0]: " << stack[0] << "\n";

	// The eleven bit immediate address is loaded into PC bits <10:0>.
    setProgZeiger(k);
	
	//The upper bits of the PC are loaded from PCLATH. 
	
	int pclath3 = getPCLATH() & 0x08;
	int pclath4 = getPCLATH() & 0x10;

	if (pclath3 > 0) {

		progZeiger |= (1u << 14);

	}
	else {

		progZeiger &= ~(1u << 14);
		progZeiger &= 0x1fff;

	}


	if (pclath4 > 0) {

		progZeiger |= (1u << 15);

	}
	else {

		progZeiger &= ~(1u << 15);
		progZeiger &= 0x1fff;

	}

	cout <<"ProgZeiger nach PCLATH: " << progZeiger << "\n";

	takte += 8;

    // Timer erhöhen falls TOCS 0 da doppelte befehlslaufzeit
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}


}

void clrwdt(int data) {
	cout << "clrwdt aufgerufen\n";
	// löscht den Watchdog

	/*
	CLRWDT instruction resets the Watchdog
	Timer. It also resets the prescaler
	of the WDT. Status bits TO and PD are
	set.
	*/
	
	wdt = 0x00;
	// prescaler zurücksetzen
	setPreVar(getPS());

	setTO(1);
	setPD(1);

}

void picGoto(int data) {
	cout << "picGoto aufgerufen\n";
	// Sprung zur Adresse k
	
	/*
	GOTO is an unconditional branch. The
	eleven bit immediate value is loaded
	into PC bits <10:0>. The upper bits of
	PC are loaded from PCLATH<4:3>.
	GOTO is a two cycle instruction.
	*/

	int k = data & 0x07ff;

    setProgZeiger(k);

	cout << "PCLATH: " << getPCLATH() << "\n";

	int pclath3 = getPCLATH() & 0x08;
	int pclath4 = getPCLATH() & 0x10;

	if (pclath3 > 0) {

		progZeiger |= (1u << 14);

	}
	else {

		progZeiger &= ~(1u << 14);
		progZeiger &= 0x1fff;

	}


	if (pclath4 > 0) {

		progZeiger |= (1u << 15);

	}
	else {

		progZeiger &= ~(1u << 15);
		progZeiger &= 0x1fff;

	}

	takte += 8;

	// Timer erhöhen da doppelte befehlslaufzeit
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}

}


void iorlw(int data) {
	cout << "iorlw aufgerufen\n";
	// Literal wird mit dem W-Reg. ODER verknüpft

	uint8_t k = 0x00ff & data; // Literal k Pfad

	// Führe verorderung durch
	uint8_t result = wReg | k;

	// Bestimme z auf basis des ergebniss 
	int z = (result == 0);

	// Schreibe in wReg
	wReg = result;
	
	// Setze Flags
	setZ(z);

	// Erhöhe Takte
	takte += 4;

}

void movlw(int data) {
	cout << "movlw aufgerufen\n";
	// The eight bit literal ’k’ is loaded into W register.The don’t cares will assemble as 0’s.
	
	uint8_t k = 0xff & data; // Register Pfad

	// kopiere k zu wReg
	wReg = k;

	takte += 4;

}

void retfie(int data) {
	cout << "retfie aufgerufen\n";
	// Rückkehr aus der Interruptroutine, setzte GIE

	progZeiger = popStack();

	setGIE(1);

	takte += 8;

	// Timer erhöhen da doppelte befehlslaufzeit
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}

}

void retlw(int data) {
	cout << "retlw aufgerufen\n";
	// Rückkehr aus einem Unterprogramm, lädt k in W


	/*
		The W register is loaded with the eight
		bit literal ’k’. The program counter is
		loaded from the top of the stack (the
		return address). This is a two cycle
		instruction.
	*/

	uint8_t k = data % 0xff;

	wReg = k;

	progZeiger = popStack();

	takte += 8;

	// Timer erhöhen da doppelte befehlslaufzeit
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}
}

void picReturn(int data) {
	cout << "picReturn aufgerufen\n";
	// Rückkehr aus einem Unterprogramm


	/*
		Return from subroutine. The stack is
		POPed and the top of the stack (TOS)
		is loaded into the program counter. This
		is a two cycle instruction.
	*/

	progZeiger = popStack();

	takte += 8;

	// Timer erhöhen da doppelte befehlslaufzeit
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}

}

void sleep(int data) {
	cout << "sleep aufgerufen\n";
	// Geht in den Stand By Modus

	setPD(0);

	setTO(1);

	wdt = 0;
	pre = 0;

	takte += 4;

	// go to sleep
	//See Section 14.8 for more details.

}


void sublw(int data) {
	cout << "sublw aufgerufen\n";
	// Subtrahiert W vom Literal k

	uint8_t k = 0x00ff & data; // Literal k Pfad

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;
	

	//DC berechnung
	// DC: bei add: > 15 -> dc = 1, <= 15 -> dc = 0 ; sub: < 0 -> dc = 1, >= 0 -> dc  0

	if (((k & 0x0f) - (wReg & 0x0f)) < 0) {
		dc = 1; // durch "fehler" im PIC eigentlich falsch, müsste = 1 sein
	}

	// Berechnung
	result = k - wReg;   // subtrahiere wert im register f von wREG 

	// Flags festlegen
	if (result < 0) {
		// Setzt das Carry-Flag basierend auf dem Ergebnis
		c = 0; // durch "fehler" im PIC eigentlich falsch, müsste = 1 sein
		result += 255;
	}
	else {
		c = 1;
	}

	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	// Schreibe result in wReg
	wReg = (uint8_t)result;
	
	// Setze Flags
	setC(c);
	setDC(dc);
	setZ(z);

	// Erhöhe Takte  
	takte += 4;

}

void xorlw(int data) {
	cout << "xorlw aufgerufen\n";
	// EXCLUSIV ODER Verknüpfung von W und k

	uint8_t k = 0x00ff & data; // Literal k Pfad

	// Ergebniss ermitteln
	uint8_t result = wReg ^ k;


	// Speichern im wReg
	wReg = result;
	

	// Flags setzen
	setZ(1);

	// Takte erhöhen
	takte += 4;

}


void execBefehl() {
	cout << "\nZeile: (beginnend bei 1)" << dec << matchZeile[progZeiger] + 1 << "\n";
	cout << "execBefehl aufgerufen\n";
	

	//befehl an stelle des programmzählers erhalten
	int befehl = progSpeicher[progZeiger];
	
	// erhaltenen befehl decoden und ausführen
	decode(befehl);
	
	syncDataSpeicher();

	// vorherige Laufzeit speichern,
	progTime_before = progTime;
	//aktuelle Laufzeit bestimmen
	progTime = (takte / quarzTakt); // progTime in mikrosekunden
	//delta für den abgearbeiteten befehl berechnen
	deltaTime = progTime - progTime_before;
	// delta zu watchdog addieren
	wdt += (deltaTime/1000); // convert time to milli seconds and add time to wdt

	checkWatchdog();
	setTimer();
	ckeckInterrupt();
	// GUI aktualisieren
	// refreshGUI();

}

int popStack() {
	cout << "popStack aufgerufen\n";
    int top = stack[0];
    /*
	// i < 7 , da vor dem letzten element aufgehört werden muss, sonst zeigerüberlauf 
	for (int i = 0; i < 7; i++) {	
		stack[i + 1] = stack[i];

	}

	stack[7] = 0;
	
	return top;
    */

    if(stackZeiger == 0) {
        stackZeiger = 7;
    } else {
       stackZeiger--;
    }

    top = stack[stackZeiger];

    return top;


}

void pushStack(int wert) {

	cout << "pushStack aufgerufen\n";
    /*
	for (int i = 7; i > 0; i--) {
		stack[i] = stack[i-1];
	}
    */
    // schreibe auf stack an stelle stackZeiger
    stack[stackZeiger] = wert;

    //erhöhe StackZeiger, falls = 7, dann setze diesen auf 0
    if(stackZeiger == 7) {
       stackZeiger = 0;
    } else {
       stackZeiger++;
    }

}

void ckeckInterrupt() {

	if(getGIE()) {

		if ((getT0IE() && getT0IF()) || (getINTE() && getINTF()) || (getRBIE() && getRBIF())) {

            pushStack(progZeiger);

            setProgZeiger(0x0004);
			setGIE(0);

		}

	}


}

void setTimer() {

	//quelle für timer(option->clock source)
	if (getTOCS() == 0) {
		// erhöhe Timer
		dataSpeicher[0][1]++;
		if (dataSpeicher[0][1] == 0) {
			setT0IF(1);
		}
	}
	else {
        // Flanke an pin prüfen!!!
		//vorteiler bei timer psa?
		if (getPSA() == 0) {
			//erhöhe vorteiler(als 	rückwärtszähler)
			
				if (pre != 0) {

					pre--;

				}
				else {
					// erhöhe Timer wenn pre == 0
					dataSpeicher[0][1]++;
					if (dataSpeicher[0][1] == 0) {
						setT0IF(1);
					}
					// setze prescaler zurück
					pre = getPS();
				}
		}
		else {
			// erhöhe Timer
			dataSpeicher[0][1]++;
			if (dataSpeicher[0][1] == 0) {
				setT0IF(1);
			}
		}
	}
}

void checkWatchdog() {

	if (wdt > 18) {
		// watchdog  abgelaufen?
		if (getPSA() == 1) {
			//vorteiler bei watchdog?
			if (pre != 0) {
				// Preskaler nicht abgelaufen
				//erhöhe vorteiler(als 	rückwärtszähler)
				pre--;
				// setze watchdog zurück
				wdt = 0;
			}
			else {
				// watchdog mit pre, beide abgelaufen
				// watchdog reset
				resetPIC();
				//Popup Watchdog reset
			}
		}
		else {
			// watchdog ohne pre abgelaufen
			// watchdog reset
			resetPIC();
			//Popup Watchdog reset
		}
	}
	else {
		// No Reset!!
	}


	//vorteiler bei watchdog?
	/*if (getPSA() == 1) {
		setPreVar(getPS());
		if (wdt >= (18 * pre)) {
			// watchdog reset
			// 
			// init dataSpeicher
			for (int i = 0; i < 127; i++) {
				dataSpeicher[0][i] = 0;
				dataSpeicher[1][i] = 0;
			}

			// Eingabe array mit default wert füllen
			for (int i = 0; i < 1024; i++) {
				prog[i] = "no";
			}

			progZeiger = 0;

			// Bits im Option reg auf 1 setzen
			dataSpeicher[1][1] = 0xff;

			// TO auf 0, bei normalem power up TO = 1
			setTO(0);


		}
		else {
			// no watchdog reset

		}
	}
	else {

		if (wdt >= 18) {
			// watchdog reset
				// init dataSpeicher
			for (int i = 0; i < 127; i++) {
				dataSpeicher[0][i] = 0;
				dataSpeicher[1][i] = 0;
			}

			// Eingabe array mit default wert füllen
			for (int i = 0; i < 1024; i++) {
				prog[i] = "no";
			}

			progZeiger = 0;

			// Bits im Option reg auf 1 setzen
			dataSpeicher[1][1] = 0xff;

			// TO auf 0, bei normalem power up TO = 1
			setTO(0);


		}
		else {
			// no watchdog reset


		}

	}*/
}


