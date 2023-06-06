#pragma once
#include <iostream>



void setIOPorts();

// Dummy decode
void decode(int data);

/*
//Befehl-Decode
//derzeit auskommentiert wegen fehlender funktionen
void decode(data);

*/




void addwf(int data);

void andwf(int data);

void addlw(int data);

void andlw(int data);

void bcf(int data);
void nop();

void execBefehl();

int popStack();
