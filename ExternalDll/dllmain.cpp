// project.Timestamp 15.09.2020-25.01.2021 | Barracuda | Mixed launch x64 
//Debug injection support.1-load driver. 2-start debug
#include <iostream>
#include <Windows.h>

#include "GuiEngine.h"
#include "threads.h"
#include "driverRW.h"
#include "tools.h"





using namespace std;

/*
void HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs: [30h] ;
		mov eax, [eax + 0Ch];
		mov dwPEB_LDR_DATA, eax;
		mov esi, [eax + 0Ch];
		mov edx, [eax + 10h];
	LoopInLoadOrderModuleList:
		lodsd;
		mov esi, eax;
		mov ecx, [eax + 18h];
		cmp ecx, hModule;
		jne SkipA
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InMemoryOrderModuleList
			SkipA :
		cmp edx, esi
			jne LoopInLoadOrderModuleList
			InMemoryOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 14h]
			mov edx, [eax + 18h]
			LoopInMemoryOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 10h]
			cmp ecx, hModule
			jne SkipB
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp InInitializationOrderModuleList
			SkipB :
		cmp edx, esi
			jne LoopInMemoryOrderModuleList
			InInitializationOrderModuleList :
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax + 1Ch]
			mov edx, [eax + 20h]
			LoopInInitializationOrderModuleList :
			lodsd
			mov esi, eax
			mov ecx, [eax + 08h]
			cmp ecx, hModule
			jne SkipC
			mov ebx, [eax]
			mov ecx, [eax + 4]
			mov[ecx], ebx
			mov[ebx + 4], ecx
			jmp Finished
			SkipC :
		cmp edx, esi
			jne LoopInInitializationOrderModuleList
			Finished :
		popfd;
		popad;
	}
}
*/
void EraseHeader(HINSTANCE hModule)
{
	if (!hModule)
		return;

	DWORD size, protect;


	PIMAGE_DOS_HEADER pDoH = (PIMAGE_DOS_HEADER)(hModule);
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	size = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, size, PAGE_READWRITE, &protect))
		for (DWORD i = 0; i < size; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 1;

	size = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, size, PAGE_READWRITE, &protect))
		for (DWORD i = 0; i < size; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 1;

	return;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
        #ifndef _DEBUG 
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
        #endif
	
		EraseHeader(hModule);
		//HideModule(hModule);

		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//SetConsoleTitle("DEBUG CONSOLE");

		while (!get_process_pid("RustClient.exe"))Sleep(1000);
	
		if (!kernelHandler.attach("RustClient.exe"))
		{
			MessageBox(0, "ERROR attach", "ERROR", MB_OK | MB_ICONERROR);
			return 1;
		}


		
		
		/*
		DWORD64 baseProjectile = kernelHandler.get_module_base("GameAssembly.dll") + 0x588DD0;	
		char a = 0x99;
        kernelHandler.virtual_protect(baseProjectile, 1, PAGE_EXECUTE_READWRITE);
		kernelHandler.write_memory(kernelHandler.get_module_base("GameAssembly.dll") + 0x588DD0, (uint64_t)(LPBYTE)&a, sizeof(a));
	   */
	   

	
		
			//return FALSE;
		while (Vars::Config::BaseNetworkable == NULL || Vars::Config::GameObjectManager == NULL)
		{
			Vars::Config::GameObjectManager = read(kernelHandler.get_module_base("UnityPlayer.dll") + oGameObjectManager, DWORD64);
			Vars::Config::BaseNetworkable = read(kernelHandler.get_module_base("GameAssembly.dll") + oBaseNetworkable, DWORD64);
			Sleep(1);

			cout <<"GameObjectManager:"<< std::hex << Vars::Config::GameObjectManager << endl;
			cout << "BaseNetworkable:" << std::hex << Vars::Config::BaseNetworkable << endl;
		}
	
while (transformIndex >= 0)
		{
			Matrix34 matrix34 = *(Matrix34*)((ULONGLONG)pMatriciesBuf + 0x30 * transformIndex);

			__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));	// xxxx
			__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));	// yyyy
			__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));	// zwxy
			__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));	// wzyw
			__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));	// zzzz
			__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));	// yxwy
			__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

			result = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
						tmp7)), *(__m128*)(&matrix34.vec0));

			transformIndex = *(int*)((ULONGLONG)pIndicesBuf + 0x4 * transformIndex);
		}

bool Rust::CheatManager::IsinGame()
{
	return false;
}

Cheat::Vector3 Rust::MainCam::GetPosition(uint64_t pTransform)
{
	__m128 result;

	const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

	TransformAccessReadOnly pTransformAccessReadOnly = Rust::Globals::hack_data.RustMemory->Read<TransformAccessReadOnly>(pTransform + 0x38);
	unsigned int index = Rust::Globals::hack_data.RustMemory->Read<unsigned int>(pTransform + 0x40);
	TransformData transformData = Rust::Globals::hack_data.RustMemory->Read<TransformData>(pTransformAccessReadOnly.pTransformData + 0x18);

	SIZE_T sizeMatriciesBuf = sizeof(Matrix34) * index + sizeof(Matrix34);
	SIZE_T sizeIndicesBuf = sizeof(int) * index + sizeof(int);

	// Allocate memory for storing large amounts of data (matricies and indicies)
	PVOID pMatriciesBuf = malloc(sizeMatriciesBuf);
	PVOID pIndicesBuf = malloc(sizeIndicesBuf);
	
	void create_memeory_thread()
{
	if (!NT_SUCCESS(create_shared_memory()))
	{
		DbgPrintEx(0, 0, ":\n");
		return;
	}	
	
	if (!NT_SUCCESS(create_shared_memory_esp()))
	{
		DbgPrintEx(0, 0, ":\n");
		return;
	}
	PsTerminateSystemThread(STATUS_SUCCESS);
}



