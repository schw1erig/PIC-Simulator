#include <iostream>

uint8_t getRegPfad(uint8_t pfad);
uint8_t getRegInhalt(uint8_t pfad);
void setRegInhalt(uint8_t pfad, uint8_t result);

//--------------
void syncDataSpeicher();

//----------
int getFSR();

//----------
int getPCL();
void setPCL(uint8_t wert);

int getPCLATH();
void setPCLATH(uint8_t wert);

//----------
void setGIE(int wert);
void setEEIE(int wert);
void setT0IE(int wert);
void setINTE(int wert);
void setRBIE(int wert);
void setT0IF(int wert);
void setINTF(int wert);
void setRBIF(int wert);
//----
int getGIE();
int getEEIE();
int getT0IE();
int getINTE();
int getRBIE();
int getT0IF();
int getINTF();
int getRBIF();
int getINTCON(uint8_t maske);
void setINTCON(uint8_t maske, int wert);

//----------
void setPreVar(int wert);
int getTOCS();
int getPSA();
int getPS();
int getOption(uint8_t maske);
void setOption(uint8_t maske, int wert);
//----------
int getStatus(uint8_t maske);
int getC();
int getDC();
int getZ();
int getPD();
int getTO();
int getRP0();
//----
void setStatus(uint8_t maske, int wert);
void setC(int wert);
void setDC(int wert);
void setZ(int wert);
void setPD(int wert);
void setTO(int wert);
void setRP0(int wert);

//-----------------
