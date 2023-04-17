#include "pch.h"

using namespace System;

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "PIC.h"
#include "GUI.h"
#include "befehle.h"


using namespace System::Windows::Forms;


int progSpeicher[1024];
int dataSpeicher[128];
int stack[8];

[STAThread]
int main()
{
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  Application::Run(gcnew CppCLRWinFormsProject::PIC());

  return 0;
}