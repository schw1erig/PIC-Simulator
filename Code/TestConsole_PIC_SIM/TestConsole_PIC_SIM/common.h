
using namespace std;

// Programmspeicher
extern int progSpeicher[1024];
// Ram 1
extern uint8_t dataSpeicher0[128];
// Ram 2
extern uint8_t dataSpeicher1[128];
// Stack
extern int stack[8];
// Speicher f�r das gesamte Program
extern string prog[1000];
//  
extern int matchZeile[1024];

extern uint8_t wReg;

extern uint8_t maskeC;
extern uint8_t maskeDC;
extern uint8_t maskeZ;
extern uint8_t maskePD;
extern uint8_t maskeTO;
extern uint8_t maskeRP0;
extern uint8_t maskeIRP;