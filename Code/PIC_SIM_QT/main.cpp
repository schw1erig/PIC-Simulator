#include <iostream>
#include "mainwindow.h"
#include "common.h"
#include <QDebug>

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <string>

// Globale Variablen
// Programmpfad
//string filename = "G:/Ausbildung/Git/PIC-Simulator/TestProg_PicSim_20210420/TPicSim1.LST";
string filename = "";
// Programmspeicher
int progSpeicher[1024];
// Speicherbank [bank: 0-1] [register: 0-127]
uint8_t dataSpeicher[2][128];
// Stack
int stack[8];
// Speicher f�r das gesamte Program
string prog[1024];
// Zeile des Befehls der globalen Zeile zuordnen (erste globale zeile entspricht der 0ten zeile)
int matchZeile[1024];

uint8_t wReg;

double wdt; //Watchdog
int wdtActive;
int pre = 0; // Watchdog prescaler

int progZeiger;
int stackZeiger;

int quarzTakt;  // in MHZ
int progTime; // in Micro-Sekunden
int deltaTime; // in micro-sekunden
int progTime_before; // in micro-sekunden
int takte;

uint8_t maskeC = 0x0001;
uint8_t maskeDC = 0x0002;
uint8_t maskeZ = 0x0004;
uint8_t maskePD = 0x0008;
uint8_t maskeTO = 0x0010;
uint8_t maskeRP0 = 0x0020;
uint8_t maskeIRP = 0x0080;



int main(int argc, char *argv[])
{

    bootPIC();
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "PIC_SIM_QT_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
