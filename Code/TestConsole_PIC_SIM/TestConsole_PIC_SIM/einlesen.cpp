#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

string file = "D:\GitHub\PIC-Simulator\TestProg_PicSim_20210420\TPicSim1.LST";

void einlesen(string filename, string prog[]) {

    ifstream file(filename);
    int counter = 0;
    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            //cout << line << "\n";
            prog[counter] = line;
            counter++;
        }
        file.close();
    }
}

void fileAusgeben(string prog[]) {
    for (int i = 0; i < 1000; i++) {
        if (prog[i] != "no") {
            cout << prog[i] << "\n";
        }
    }
}

