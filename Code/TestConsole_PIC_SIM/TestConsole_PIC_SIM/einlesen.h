#pragma once
#include <string>

using namespace std;

void einlesen(string filename, string prog[]);
void fileAusgeben(string prog[]);
void extractBefehle(string prog[], int progSpeicher[], int matchZeile[]);
