#include "common.h"
#include <iostream>
#include <QDebug>

using namespace std;


int getFlanke(int oldValue, int newValue) {

    //steigend: 0; fallend: 1

    if(newValue > oldValue) {
        // steigende Flanke
        qDebug() << "steigende Flanke";
        return 0;
    } else if(newValue < oldValue) {
        //fallende Flanke
        qDebug() << "fallende Flanke";
        return 1;
    } else{
        qDebug() << "error Flanke";
        return -1;
    }
}


