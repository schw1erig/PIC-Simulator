#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string file = "D:\GitHub\PIC-Simulator\TestProg_PicSim_20210420\TPicSim1.LST";

void inlesen() {
	ifstream infile(file);



    string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int a, b;
        if (!(iss >> a >> b)) { break; } // error

        // process pair (a,b)
    }
	

}
