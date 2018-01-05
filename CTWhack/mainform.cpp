#include <stdint.h>
#include <Windows.h>
#include <Psapi.h>
#include "mainform.h"

CTWhack::mainform::mainform(void)
{
	InitializeComponent();
	//
	//TODO: добавьте код конструктора
	//
	defAsm = new uint8_t(6);
	InfManaEnabled->Enabled = false;
	groupBox1->Enabled = false;
}

bool CTWhack::mainform::Connect()
{
	try {
		if (hCTW != NULL) CloseHandle(hCTW);
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		HANDLE hProcess;
		struct _MODULEINFO modinfo;
		DWORD dummy;
		HMODULE hModule;
		wchar_t szProcessName[MAX_PATH] = TEXT("<unknown>");

		EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
		cProcesses = cbNeeded / sizeof(DWORD);
		if (cProcesses <= 0)
			throw gcnew Exception("Error EnumProcesses");
		for (DWORD i = 0; i < cProcesses; i++) {
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
			if (hProcess) {
				if (EnumProcessModulesEx(hProcess, &hModule, sizeof(HMODULE), &dummy, LIST_MODULES_64BIT)) {
					if (GetModuleBaseName(hProcess, hModule, szProcessName, sizeof(szProcessName) / sizeof(TCHAR))) {
						String^ str = gcnew String(szProcessName);
						if ("CraftWorld.exe" == str) {
							if (GetModuleInformation(hProcess, hModule, &modinfo, sizeof(MODULEINFO))) {
								CTWStartAddr = (uint32_t)modinfo.lpBaseOfDll;
								hCTW = hProcess;
								hCTWwnd = FindWindow(L"CIrrDeviceWin32", L"CraftTheWorld");
								bConn = true;
								return true;
							}
							//else
							//	throw gcnew Exception("GetModuleInformation");
						}
					}
					//else
					//	throw gcnew Exception("GetModuleBaseName");
				}
				//else
				//	throw gcnew Exception("EnumProcessModulesEx");
			}
			//else
			//	throw gcnew Exception("OpenProcess");
			CloseHandle(hProcess);
		}
		throw gcnew Exception("Игра не найдена");
	}
	catch (Exception^ e) {
		MessageBoxA(0, (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(e->Message), "Exception", 0);
		return false;
	}
	return false;
}

System::Void CTWhack::mainform::InfManaEnabled_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	uint32_t AsmAddr = CTWStartAddr + AsmOffset;
	if (InfManaEnabled->Checked) {
		uint8_t nops[6] = { 0x90,0x90, 0x90, 0x90, 0x90, 0x90 };
		WriteProcessMemory(hCTW, (void*)AsmAddr, nops, 6, NULL);
	}
	else {
		WriteProcessMemory(hCTW, (void*)AsmAddr, defAsm, 6, NULL);
	}
}

System::Void CTWhack::mainform::AttachToGameBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Connect()) {
		InfManaEnabled->Enabled = true;
		groupBox1->Enabled = true;

		uint32_t AsmAddr = CTWStartAddr + AsmOffset;
		ReadProcessMemory(hCTW, (void*)AsmAddr, defAsm, 6, NULL);
		if (defAsm[0] == 0x90) {
			this->InfManaEnabled->CheckedChanged -= gcnew System::EventHandler(this, &mainform::InfManaEnabled_CheckedChanged);
			InfManaEnabled->Checked = true;
			this->InfManaEnabled->CheckedChanged += gcnew System::EventHandler(this, &mainform::InfManaEnabled_CheckedChanged);
			InfManaEnabled->Enabled = false;
		}

		uint32_t CAddr = CTWStartAddr + CounterOffset;
		ReadProcessMemory(hCTW, (void*)CAddr, &CAddr, 4, NULL);
		CounterAddr = CAddr + 0x24;
	}
	else {
		InfManaEnabled->Enabled = false;
		groupBox1->Enabled = false;
	}
}

System::Void CTWhack::mainform::FreezeTimeEnabled_CheckedChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	if (FreezeTimeEnabled->Checked) {
		float tempTime = 0;
		ReadProcessMemory(hCTW, (void*)CounterAddr, &tempTime, 4, NULL);
		timer = tempTime;
	}
	timer1->Enabled = FreezeTimeEnabled->Checked;
}

System::Void CTWhack::mainform::UpdateCounter(System::Object ^ sender, System::EventArgs ^ e)
{
	float tempTime = timer;
	WriteProcessMemory(hCTW, (void*)CounterAddr, &tempTime, 4, NULL);
}

System::Void CTWhack::mainform::Set1sBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	FreezeTimeEnabled->Checked = false;
	float tempTime = 1;
	WriteProcessMemory(hCTW, (void*)CounterAddr, &tempTime, 4, NULL);
}

System::Void CTWhack::mainform::Set30mBtn_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	FreezeTimeEnabled->Checked = false;
	float tempTime = 30 * 60;
	WriteProcessMemory(hCTW, (void*)CounterAddr, &tempTime, 4, NULL);
}
