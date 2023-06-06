#pragma once
#include "common.h"
#include <iostream>




using namespace std;



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


// BYTE-ORIENTED FILE REGISTER OPERATIONS
void addwf(int data) {
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;
	int reg = (int)dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt

	takte += 4; // standard f�r ben�tigte Takte 

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
	dataSpeicher[getRP0()][f] = (uint8_t)result;   // Speichert das Ergebnis im Register
}
else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
{
	wReg = (uint8_t)result;
}

setC(c);
setDC(dc);
setZ(z);

}


void andwf(int data)
{

	takte += 4; // standard f�r ben�tigte Takte 
	int z = 0;
	uint8_t result;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	result = wReg & reg;   // F�hrt die logische AND-Operation zwischen WREG und dem Register aus
	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;   // Speichert das Ergebnis im Register
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;
	}

	setZ(z);
}


void clrf(int data) {

	takte += 4;

	uint8_t f = (data & 0x7f);
	int z = 1;

	dataSpeicher[getRP0()][f] = 0;

	setZ(z);

}

void clrw(int data) {

	takte += 4;
	int z = 1;

	wReg = 0;

	setZ(z);
}

void comf(int data) {

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	int z;

	int comp = ~reg; //Bilde Complement
	z = (comp == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = comp;   // Speichere Comp im Register f
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = comp;   // F�hrt die logische AND-Operation zwischen WREG und dem Register aus
	}
	setZ(z);

}

void decf (int data) {


	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	uint8_t result = reg--;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;   // Speichere Comp im Register f
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   // F�hrt die logische AND-Operation zwischen WREG und dem Register aus
	}

	setZ(z);
}

void decfsz(int data) {


	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	uint8_t result = reg--;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;   // Speichere Comp im Register f
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   // F�hrt die logische AND-Operation zwischen WREG und dem Register aus
	}

	if (result == 0) nop();

	setZ(z);
}

void incf(int data) {


	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	uint8_t result = reg++;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;   
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setZ(z);
}

void incfsz(int data) {


	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	uint8_t result = reg++;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;  
	}
	else   // Wenn d = 1, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	if (result == 0) nop();

	setZ(z);
}

void iorwf(int data) {
	/*
	Inclusive OR the W register with contents of
	register �f�. If �d� is 0 the result is placed in the
	W register. If �d� is 1 the result is placed
	back in register �f�.
	*/

	takte += 4;

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	uint8_t result = wReg | reg;

	int z = (result == 0);

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;   
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setZ(z);

}

void movf(int data) {
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
	uint8_t reg = dataSpeicher[getRP0()][f]; // Register f Inhalt

	int z = 1;

	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = reg;   // Speichere Wert von �f im Register f
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = reg;   // speichere wert von Ref in WReg
	}

	setZ(z);

}

void movwf(int data) {
	//Move data from W register to register 'f'
	takte += 4;

	uint8_t f = 0x007f & data; // Register Pfad

	dataSpeicher[getRP0()][f] = wReg;

}

void nop() { 
	takte += 4; 
}

void rlf(int data) {

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f];
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
		dataSpeicher[getRP0()][f] = result;   
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;   
	}

	setC(newC);
	takte += 4;
}

void rrf(int data) {

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t reg = dataSpeicher[getRP0()][f];
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
		dataSpeicher[getRP0()][f] = result;
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;
	}

	setC(newC);
	takte += 4;
}

void subwf(int data) {

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;
	int reg = (int)dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt



	//DC berechnung
	// DC: bei add: > 15 -> dc = 1, <= 15 -> dc = 0 ; sub: < 0 -> dc = 1, >= 0 -> dc  0

	if ( ((reg & 0x0f) - (wReg & 0x0f)) < 0) {
		dc = 1; // durch "fehler" im PIC eigentlich falsch, m�sste = 1 sein
	}

	// Berechnung
	result = reg - wReg;   // subtrahiere wert im register f von wREG 

	// Flags festlegen
	if (result < 0) {
		// Setzt das Carry-Flag basierend auf dem Ergebnis
		c = 0; // durch "fehler" im PIC eigentlich falsch, m�sste = 1 sein
		result += 255;
	}
	else {
		c = 1;
	}

	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

// Speicherort ermittlen
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = (uint8_t)result;   // Speichert das Ergebnis im Register
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = (uint8_t)result;
	}

	// setze Flags
	setC(c);
	setDC(dc);
	setZ(z);

	// ERh�he Takte
	takte += 4;
}

void swapf(int data) {

	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	int reg = (int)dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt

	int resultLeft = reg << 4; 
	int resultRight = reg >> 4;
	int result = resultLeft | resultRight;

	// Speicherort ermittlen
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = (uint8_t)result;   // Speichert das Ergebnis im Register
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = (uint8_t)result;
	}
	
	takte += 4;
}


void xorwf(int data) {
	
	uint8_t d = (0x0080 & data) > 0; // d bit
	uint8_t f = 0x007f & data; // Register Pfad

	uint8_t reg = dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt

	uint8_t result;

	result = wReg ^ reg;

	
	// Speicherort ermittlen
	if (d == 1)   // Wenn d = 1, wird das Ergebnis in das Register geschrieben
	{
		dataSpeicher[getRP0()][f] = result;   // Speichert das Ergebnis im Register
	}
	else   // Wenn d = 0, wird das Ergebnis in WREG geschrieben
	{
		wReg = result;
	}

	setZ(1);

}

/*
// Bitorientierten Befehle

void bcf(int data) {

	// L�scht Bit b in Adresse f

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg;

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	if (f == 0x00) {

		// indirekte adressierung

		int bank = (f & 0xf0) > 0;
		int fsr = getFSR() & 0x0f;
		reg = dataSpeicher[bank][fsr];
		reg &= ~(1u << b); //l�schen des bten bits mit komplement und UND
		dataSpeicher[bank][fsr] = reg; // Speichere ergebniss im register 

	}
	else {

		// direkte Adressierung
		reg = dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt
		reg &= ~(1u << b); //l�schen des bten bits mit komplement und UND
		dataSpeicher[getRP0()][f] = reg;

	}

	takte += 4;
}

void bsf(int data) {

	// Setzt Bit b in Adresse f

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg;

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	if (f == 0x00) {

		// indirekte adressierung

		int bank = (f & 0xf0) > 0;
		int fsr = getFSR() & 0x0f;
		reg = dataSpeicher[bank][fsr];

		reg |= (1u << b); //setzen des bten bits: mit UND
		dataSpeicher[bank][fsr] = reg; // Speichere ergebniss im register 

	}
	else {

		// direkte Adressierung
		reg = dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt
		reg |= (1u << b); //setzen des bten bits: mit UND
		dataSpeicher[getRP0()][f] = reg;

	}

	takte += 4;
}

void btfsc(int data) {
	// Testet Bit b an Adr. f und springt, wenn es 0 ist

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg;

	// register ermitteln
	if (f == 0x00) {

		// indirekte adressierung

		int bank = (f & 0xf0) > 0;
		int fsr = getFSR() & 0x0f;
		reg = dataSpeicher[bank][fsr];

	}
	else {

		// direkte Adressierung
		reg = dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt
		reg |= (1u << b); //setzen des bten bits: mit UND
		dataSpeicher[getRP0()][f] = reg;

	}

	if ((reg & b) > 0) {
		// bit b in reg an stelle f = 1 -> do nothing + next befehl
	}
	else {
		// bit b in reg an stelle f = 0, f�hre nop() aus und �berspringe den n�chsten befehl
		progZeiger++;
		nop();
		
	}

	takte += 4;
	
}

void btfss(int data) {

	uint8_t f = 0x007f & data; // Register Pfad
	uint8_t b = 0x0380 & data;
	uint8_t reg;

	b = b >> 7; // shiften der bits nach ganz rechts um die korrekte zahl zu erhalten

	// register ermitteln
	if (f == 0x00) {

		// indirekte adressierung

		int bank = (f & 0xf0) > 0;
		int fsr = getFSR() & 0x0f;
		reg = dataSpeicher[bank][fsr];

	}
	else {

		// direkte Adressierung
		reg = dataSpeicher[getRP0()][f]; // Reg an Stelle f inhalt
		reg |= (1u << b); //setzen des bten bits: mit UND
		dataSpeicher[getRP0()][f] = reg;

	}

	if ((f & b) == 0) {
		// bit b in f = 0-> do nothing + next befehl
	}
	else {
		// bit b in f = 1, f�hre nop() aus und �berspringe den n�chsten befehl
		progZeiger++;
		nop();
		
	}

	takte += 4;

}
*/




void addlw(int data) {
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

void andlw(int data)
{

	
	int z = 0;
	uint8_t result;

	uint8_t k = 0x00ff & data; // Register Pfad

	result = wReg & k;   // F�hrt die logische AND-Operation zwischen WREG und k aus
	z = (result == 0);   // Setzt das Zero-Flag basierend auf dem Ergebnis

	// Schreibe Ergebniss in das wReg
	wReg = result;

	// Setze Flags
	setZ(z);

	// Erh�he Takte
	takte += 4; // standard f�r ben�tigte Takte 
}

void call(int data) {
	// Unterprogrammaufruf an Adresse k

	int k = data & 0x07ff,

	// First, return address (PC + 1) is pushed onto the stack.
	pushStack(progZeiger + 1);

	// The eleven bit immediate address is loaded into PC bits <10:0>.
	progZeiger = k;

	//The upper bits of the PC are loaded from PCLATH. 

	progZeiger |= ((getPCLATH() & 0x18) < 14);

	takte += 8;

}

void clrwdt(int data) {
	// l�scht den Watchdog

	/*
	CLRWDT instruction resets the Watchdog
	Timer. It also resets the prescaler
	of the WDT. Status bits TO and PD are
	set.
	*/
	
	wdt = 0x00;
	wdtPre = 0;

	setTO(1);
	setPD(1);

}

void goTo(int data) {

	// Sprung zur Adresse k
	
	/*
	GOTO is an unconditional branch. The
	eleven bit immediate value is loaded
	into PC bits <10:0>. The upper bits of
	PC are loaded from PCLATH<4:3>.
	GOTO is a two cycle instruction.
	*/

	int k = data & 0x07ff;

	progZeiger = k;

	progZeiger |= ((getPCLATH() & 0x18) < 14);

	takte += 8;

}


void iorlw(int data) {
	// Literal wird mit dem W-Reg. ODER verkn�pft

	uint8_t k = 0x00ff & data; // Literal k Pfad

	// F�hre verorderung durch
	uint8_t result = wReg | k;

	// Bestimme z auf basis des ergebniss 
	int z = (result == 0);

	// Schreibe in wReg
	wReg = result;
	
	// Setze Flags
	setZ(z);

	// Erh�he Takte
	takte += 4;

}

void movlw(int data) {
	// The eight bit literal �k� is loaded into W register.The don�t cares will assemble as 0�s.
	
	uint8_t k = 0xff & data; // Register Pfad

	// kopiere k zu wReg
	wReg = k;

	takte += 4;

}

void retfie(int data) {
	// R�ckkehr aus der Interruptroutine, setzte GIE

	progZeiger = popStack();
	
	setGIE(1);

	takte += 8;
}

void retlw(int data) {
	// R�ckkehr aus einem Unterprogramm, l�dt k in W


	/*
		The W register is loaded with the eight
		bit literal �k�. The program counter is
		loaded from the top of the stack (the
		return address). This is a two cycle
		instruction.
	*/

	uint8_t k = data % 0xff;

	wReg = k;

	progZeiger = popStack();

	takte += 8;
}

void pic_return(int data) {
	// R�ckkehr aus einem Unterprogramm


	/*
		Return from subroutine. The stack is
		POPed and the top of the stack (TOS)
		is loaded into the program counter. This
		is a two cycle instruction.
	*/

	progZeiger = popStack();

	takte += 8;
}

void sleep(int data) {
	// Geht in den Stand By Modus

	setPD(0);

	setTO(1);

	wdt = 0;
	wdtPre = 0;

	takte += 4;

	// go to sleep
	//See Section 14.8 for more details.

}


void sublw(int data) {
	// Subtrahiert W vom Literal k

	uint8_t k = 0x00ff & data; // Literal k Pfad

	int c = 0;
	int z = 0;
	int dc = 0;
	int result;
	

	//DC berechnung
	// DC: bei add: > 15 -> dc = 1, <= 15 -> dc = 0 ; sub: < 0 -> dc = 1, >= 0 -> dc  0

	if (((k & 0x0f) - (wReg & 0x0f)) < 0) {
		dc = 1; // durch "fehler" im PIC eigentlich falsch, m�sste = 1 sein
	}

	// Berechnung
	result = k - wReg;   // subtrahiere wert im register f von wREG 

	// Flags festlegen
	if (result < 0) {
		// Setzt das Carry-Flag basierend auf dem Ergebnis
		c = 0; // durch "fehler" im PIC eigentlich falsch, m�sste = 1 sein
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

	// Erh�he Takte  
	takte += 4;




}

void xorlw(int data) {
	// EXCLUSIV ODER Verkn�pfung von W und k

	uint8_t k = 0x00ff & data; // Literal k Pfad

	// Ergebniss ermitteln
	uint8_t result = wReg ^ k;


	// Speichern im wReg
	wReg = result;
	

	// Flags setzen
	setZ(1);

	// Takte erh�hen
	takte += 4;

}


void execBefehl() {

	//befehl an stelle des programmz�hlers erhalten
	int befehl = progSpeicher[progZeiger];
	// erhaltenen befehl decoden
	decode(befehl);
	
	// ProgZeiger erh�hen, falls max von 1024 erreicht, setze auf 0
	progZeiger++;
	if (progZeiger == 1024) progZeiger = 0;
 	setPCL(progZeiger & 0xff);

	progTime += (takte / quarzTakt); // progTime in mikrosekunden

	// GUI aktualisieren
	// refreshGUI();

}

int popStack() {

	int top = stack[0];
	
	// i < 7 , da vor dem eletzte nelement aufgeh�rt werden muss, sonst zeiger�berlauf 
	for (int i = 0; i < 7; i++) {	
		stack[i + 1] = stack[i];

	}

	stack[7] = 0;
	
	return top;

}

void pushStack(int wert) {

	for (int i = 7; i > 0; i--) {
		stack[i] = stack[i-1];
	}

	stack[0] = wert;

}
