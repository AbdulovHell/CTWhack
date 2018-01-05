#include <stdint.h>
#include <Windows.h>
#include <Psapi.h>
#include "mainform.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(cli::array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CTWhack::mainform());
}