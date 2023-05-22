#pragma once
#include <iostream>

int getStatus(uint8_t maske);
int getC();
int getDC();
int getZ();
int getPD();
int getTO();
int getRP0();


void setStatus(uint8_t maske, int wert);

void setC(int wert);

void setDC(int wert);

void setZ(int wert);

void setPD(int wert);

void setTO(int wert);

void setRP0(int wert);

void setIOPorts();

// Dummy decode
void decode(int data);

/*
//Befehl-Decode
//derzeit auskommentiert wegen fehlender funktionen
void decode(data);

*/


int addlw(int data);

int andlw(int data);

int addwf(int data);

void andwf(int data);

void bcf(uint8_t reg);


void execBefehl();
