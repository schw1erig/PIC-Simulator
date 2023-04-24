#pragma once


//using namespace System;
//using namespace System::Windows::Forms;


int aus = 0;

void decode() {

	int data = 0x03;

	switch (data & 0x02) {
	
	case 0x02: aus = 1; break;

	default:
		break;
	}
} 


int getAus() {
	return aus;
}





