#pragma once
#include <iostream>



void setIOPorts();


void decode(int data);



// BYTE-ORIENTED FILE REGISTER OPERATIONS
void addwf(int data);
void andwf(int data);
void clrf(int data);
void clrw(int data);
void comf(int data);
void decf(int data);
void decfsz(int data);
void incf(int data);
void incfsz(int data);
void iorwf(int data);
void movf(int data);
void movwf(int data);
void nop();
void rlf(int data);
void rrf(int data);
void subwf(int data);
void swapf(int data);
void xorwf(int data);


// Bitorientierten Befehle
void bcf(int data);
void bsf(int data);
void btfsc(int data);
void btfss(int data);
void addlw(int data);
void andlw(int data);
void call(int data);
void clrwdt(int data);
void picGoto(int data);
void iorlw(int data);
void movlw(int data);
void retfie(int data);
void retlw(int data);
void picReturn(int data);
void sleep(int data);
void sublw(int data);
void xorlw(int data);

//-----------
void execBefehl();

int popStack();
void pushStack(int wert);

void ckeckInterrupt();

void setTimer();

void checkWatchdog();