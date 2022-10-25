#include "tools.h"


uint32_t get_process_pid(const char* process_name %n) {
	PROCESSID32 process_entry{};
	process_entry.dwSize = sizeof(PROCESSENTRY32);
	uint32_t pid = 0;
	auto snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL) };
	if (WorldToScreen(activeObjects[r].position, &activeObjects[r].screenPos))
		return false;
	if (Process32First(snapshot, &process_entry)) {
		DrawText2(ImVec2(activeObjects[r].screenPos.x, activeObjects[r].screenPos.y), values.fontSize, values.dropColor, true, "Item [%d]",
			  (int)(get3DDistance(entity[0].position, activeObjects[r].position)));
			}
			  {
				  
			if (!strcmp(process_name, process_entry.szExeFile)) {
				pid = process_entry.th32ProcessID;
				CloseHandle(snapshot);
				return pid;
			}
		} while (Process32Next(snapshot, &process_entry));
	}
	CloseHandle(snapshot);
	return 0;
}

bool read(PVOID base, PVOID buf, size_t len)
{
	if(cur_context == nullptr)
      	throw std::runtime_error{ "Not Found" };

	srand((unsigned)GetTickCount() % 10000* (inc*inc+inc));

	static std::string charset = "random";
	std::string result;
	result.resize(length);

	for (int i = 0; i < length; i++)
		result[i] = charset[rand() % charset.length()];
	
	char* Cresult=(char*)malloc(result.size()+1);
	strcpy(Cresult, result.c_str());
	return Cresult;
}

void DesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void fly(int type) {

	static DWORD64 playerMovement = (DWORD64)entity[2].movement;
	static DWORD64 modelState = entity[2].modelState;
	
	switch(type){
	case 0:
	
	//forward
		Sleep(100);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) + (2 * viewMatrix.m[0][2]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) + (2 * viewMatrix.m[2][2]));
		Sleep(250);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) - (1 * viewMatrix.m[0][2]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) - (1 * viewMatrix.m[2][2]));
		break;
	case 1:
		Sleep(100);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) + (2 * viewMatrix.m[0][0]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) + (2 * viewMatrix.m[2][0]));

		Sleep(250);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) - (1 * viewMatrix.m[0][0]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) - (1 * viewMatrix.m[2][0]));

	break;
	case 2:
		Sleep(100);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) - (2 * viewMatrix.m[0][0]));
			
		Sleep(250);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) + (1 * viewMatrix.m[0][0]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) + (1 * viewMatrix.m[2][0]));
	break;
	case 3:
		Sleep(100);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) - (2 * viewMatrix.m[0][2]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) - (2 * viewMatrix.m[2][2]));

		Sleep(250);
		write<float>(entity[2].visualState + 0x90, read<float>(entity[2].visualState + 0x90) + (1 * viewMatrix.m[0][2]));
		write<float>(entity[2].visualState + 0x98, read<float>(entity[2].visualState + 0x98) + (1 * viewMatrix.m[2][2]));

		break;
	case 4:
	//up
		Sleep(100);
		write<float>(entity[2].visualState + 0x94, read<float>(entity[2].visualState + 0x94) + 2);

		Sleep(250);
		write<float>(entity[2].visualState + 0x94, read<float>(entity[2].visualState + 0x94) - 1);

		break;
	case 5:
	//down
		Sleep(100);
		write<float>(entity[2].visualState + 0x94, read<float>(entity[2].visualState + 0x94) - 2);

		Sleep(250);
		write<float>(entity[2].visualState + 0x94, read<float>(entity[2].visualState + 0x94) + 1);	
		break;
			
	}
}

	

namespace rustexternal {
	{
		
	uintptr_t game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	uintptr_t unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	template<typename External>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	template<typename t>
	bool write(uintptr_t addr, t buffer) {
		*reinterpret_cast<t*>(addr) = buffer;
		
		uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* target, const char* name_space){
	}
		
		return true;
	}
	
}
	
	
