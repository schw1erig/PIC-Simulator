#pragma once
#include <iostream>


int getFSR();

//-----
int getPCL();
void setPCL(uint8_t wert);

int getPCLATH();
void setPCLATH(uint8_t wert);

//----
void setGIE(int wert);
void setEEIE(int wert);
void setT0IE(int wert);
void setINTE(int wert);
void setRBIE(int wert);
void setT0IF(int wert);
void setINTF(int wert);
void setRBIF(int wert);
//----
int getGIE(int wert);
int getEEIE(int wert);
int getT0IE(int wert);
int getINTE(int wert);
int getRBIE(int wert);
int getT0IF(int wert);
int getINTF(int wert);
int getRBIF(int wert);
int getINTCON(uint8_t maske);
void setINTCON(uint8_t maske, int wert);

//----------
int getStatus(uint8_t maske);
int getC();
int getDC();
int getZ();
int getPD();
int getTO();
int getRP0();
//---
void setStatus(uint8_t maske, int wert);
void setC(int wert);
void setDC(int wert);
void setZ(int wert);
void setPD(int wert);
void setTO(int wert);
void setRP0(int wert);

//-----------------