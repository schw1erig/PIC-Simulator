#pragma once


//using namespace System;
//using namespace System::Windows::Forms;



int add(int x, int y) {

	return x + y;

}

int aus = 0;

/*
//Befehl-Decode
//derzeit auskommentiert wegen fehlender funktionen
void decode() {

	int data = 0x03;

	switch (data & 0x02) {

	case 0x02: aus = 1; break;

	default:
		break;
	}

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

// Test-Getter for GUI
int getAus() {
	return aus;
}





