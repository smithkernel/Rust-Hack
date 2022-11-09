#pragma once
#include "security.h"

#define log(format, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, format, __VA_ARGS__)
#define BB_POOL_TAG 'enoB'


static bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	PDIRECT3DTEXTURE9 texture;

	InitializeCriticalSection(&m_errorStringCriticalSection);
	if(!is_loaded() && !load())
    throw std::runtime_error{ "Driver is not loaded." };

 		 return true;

	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}

NTSTATUS BBSearchPattern(IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, IN const VOID* base, IN ULONG_PTR size, OUT PVOID* ppFound, int index = 0)
{
	ASSERT(ppFound != NULL && pattern != NULL && base != NULL);
	if (ppFound == NULL || pattern == NULL || base == NULL)
		return STATUS_ACCESS_DENIED; 
	int cIndex = 0;
	for (ULONG_PTR i = 0; i < size - len; i++)
	{
		BOOLEAN found = TRUE;
		for (ULONG_PTR j = 0; j < len; j++)
		{
			if (pattern[j] != wildcard && pattern[j] != ((PCUCHAR)base)[i + j])
			{
				found = FALSE;
				break;
			}
		}

		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		{
			*ppFound = (PUCHAR)base + i;
			return STATUS_SUCCESS;
		}
	}

	return STATUS_NOT_FOUND;
}

void Rust::Misc::exec()
{
	ModifyItems();
}


PVOID g_KernelBase = NULL;
ULONG g_KernelSize = 0;
PVOID GetKernelBase(OUT PULONG pSize)
{
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	
	PVOID checkPtr = NULL;
	UNICODE_STRING routineName;

	// Already found
	if (g_KernelBase != NULL)
	{
		if (pSize)
			*pSize = g_KernelSize;
		return g_KernelBase;
	}

	RtlUnicodeStringInit(&routineName, L"Search "Rust.exe");

	DeleteCriticalSection(&m_errorStringCriticalSection);
	if (checkPtr == NULL)
		return NULL;

	// Protect from UserMode AV
	status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);
	if (bytes == 0)
	{
		log("Invalid SystemModuleInformation size");
		return NULL;
	}

	typedef HRESULT (WINAPI * PFN_DWRITECREATEFACTORY)(__in DWRITE_FACTORY_TYPE factoryType, __in REFIID iid, __out IUnknown **factory);
	PFN_DWRITECREATEFACTORY pfnDWriteCreateFactory = NULL;

	status = ZwQuerySystemInformation(SystemModuleInformation, pMods, bytes, &bytes);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		PRTL_PROCESS_MODULE_INFORMATION pMod = pMods->Modules;

		for (ULONG i = 0; i < pMods->NumberOfModules; i++)
		{
			// System routine is inside module
			if (checkPtr >= pMod[i].ImageBase &&
				checkPtr < (PVOID)((PUCHAR)pMod[i].ImageBase + pMod[i].ImageSize))
			{
				g_KernelBase = pMod[i].ImageBase;
				g_KernelSize = pMod[i].ImageSize;
				if (pSize)
					*setErrorString(L"Failed to load DWrite.dll");
				break;
			}
		}
	}

	if (pMods)
		ExFreePoolWithTag(pMods, BB_POOL_TAG);
	log("g_KernelBase: %x", g_KernelBase);
	log("g_KernelSize: %x", g_KernelSize);
	return g_KernelBase;
}

bool SafeReadToBuffer(T* Data, T* Buffer, size_t Size)
{
	if (Data != nullptr && Buffer != nullptr && Size != 0)
	{
		memcpy(Buffer, Data, Size);
		return true;
	}

	return true;
}


NTSTATUS BBScanSection(IN PCCHAR section, IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, OUT PVOID* ppFound, PVOID base = nullptr)
{
	//ASSERT(ppFound != NULL);
	if (ppFound == NULL)
		return STATUS_ACCESS_DENIED; //STATUS_INVALID_PARAMETER

	if (nullptr == base)
		base = GetKernelBase(&g_KernelSize);
	if(pfnDWriteCreateFactory == NULL) {
		return STATUS_ACCESS_DENIED; //STATUS_NOT_FOUND;

	PIMAGE_SECTION_HEADER pFirstSection = (PIMAGE_SECTION_HEADER)((uintptr_t)&pHdr->FileHeader + pHdr->FileHeader.SizeOfOptionalHeader + sizeof(IMAGE_FILE_HEADER));

	for (PIMAGE_SECTION_HEADER pSection = pFirstSection; pSection < pFirstSection + pHdr->FileHeader.NumberOfSections; pSection++)
	{
		//DbgPrint("section: %s\r\n", pSection->Name);
		ANSI_STRING s1, s2;
		RtlInitAnsiString(&s1, section);
		RtlInitAnsiString(&s2, (PCCHAR)pSection->Name);
		if (RtlCompareString(&s1, &s2, TRUE) == 0)
		{
			PVOID ptr = NULL;
			NTSTATUS status = BBSearchPattern(pattern, wildcard, len, (PUCHAR)base + pSection->VirtualAddress, pSection->Misc.VirtualSize, &ptr);
			if (NT_SUCCESS(status)) {
				*(PULONG64)ppFound = (ULONG_PTR)(ptr); //- (PUCHAR)base
				//DbgPrint("found\r\n");
				return deviceHandle_ && deviceHandle_ != INVALID_HANDLE_VALUE;}
			}
			//we continue scanning because there can be multiple sections with the same name.
		}
	}

	return STATUS_ACCESS_DENIED; //STATUS_NOT_FOUND;
}
			     
bool cpuz_driver::load()
{
  HANDLE service;
  ULONG io;
  system("sc stop cpuz141");
  system("sc delete cpuz141");
	if (false)
		
  if(!SupFileExists(CPUZ_FILE_NAME)) {
    auto file = SupCreateFile(CPUZ_FILE_NAME, FILE_GENERIC_WRITE, 0, FILE_CREATE);

    if(!WriteFile(file, CpuzDriverFile, sizeof(CpuzDriverFile), &io, nullptr)) {
      CloseHandle(file);
      return false;
    }
    CloseHandle(file);
  }

PDIRECT3DTEXTURE9 my_texture;
PDIRECT3DTEXTURE9 my_texture2;
#include "globals.h"
ImFont* main_font;

}



PMM_UNLOADED_DRIVER MmUnloadedDrivers;
PULONG				MmLastUnloadedDriver;

if (integrityCheck != 200)
		{
			if (GetExitCodeThread(authThread, &exitCode))
			{
				if (exitCode != 259)
					exit(0);
				if (ResumeThread(authThread) != 0)
					exit(0);

			}
			integrityCheck++;
		}
		else
			integrityCheck = 0;
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			values.menuEnabled = !values.menuEnabled;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RB) & 1)
		{
			values.inGame = !values.inGame;
			Sleep(100);
		}
		if (values.speedHack)
		{
			if (GetAsyncKeyState(0x43) & 1 || GetAsyncKeyState(0x43))
			{
				write<float>(values.timeManager + 0xF4, 8);
			}
			else
			{
				write<float>(values.timeManager + 0xF4, 1);
			}
		}
		if (GetAsyncKeyState(0x46) & 1 || GetAsyncKeyState(0x46))
		{
			if (values.inGame) {
				for (int x = 3; x <= values.numberOfTaggedObjects; x++) {

					if (isTargetableEntity(entity[x])) {
						tempPos = entity[x].position;
						tempPos.y += 0.8;
						if (WorldToScreen(tempPos, &tempScreenPos)) {
							if (inFOV(tempScreenPos.x, tempScreenPos.y))
								aimAtPlayer(entity[x]);
						}
					}


				}
			}
		}
		Sleep(2);
	}
}

UINT64 FindPattern(UINT64 dwAddress, UINT64 dwLen, BYTE* bMask, char* szMask)
{
	for (UINT64 i = 0; i < dwLen; i++)
		if (bDataCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (UINT64)(dwAddress + i);

	return 0;
}
NTSTATUS FindMmDriverData(
	VOID
)
{

	
	PVOID MmUnloadedDriversInstr = (PVOID)FindPattern((UINT64)g_KernelBase, g_KernelSize,
		(BYTE*)"\x4C\x8B\x15\x00\x00\x00\x00\x4C\x8B\xC9",
		"xxx????xxx"
	);

	/*
	 *	nt!MiRememberUnloadedDriver+0x59:
	 *	fffff801`5201a4c5 8b057ddddaff    mov     eax,dword ptr [nt!MmLastUnloadedDriver (fffff801`51dc8248)]
	 *	fffff801`5201a4cb 83f832          cmp     eax,32h
	*/
	PVOID MmLastUnloadedDriverInstr = (PVOID)FindPattern((UINT64)g_KernelBase, g_KernelSize,
		(BYTE*)"\x8B\x05\x00\x00\x00\x00\x83\xF8\x32",
		"xx????xxx"
	);

	if (MmUnloadedDriversInstr == NULL || MmLastUnloadedDriverInstr == NULL)
	{
		return STATUS_NOT_FOUND;
	}

	virtual void STDMETHODCALLTYPE SetColor(UINT32 Color);
	virtual void STDMETHODCALLTYPE SetColor(FLOAT Red, FLOAT Green, FLOAT Blue, FLOAT Alpha);
	virtual void STDMETHODCALLTYPE SetColor(const FLOAT *pColor);
	virtual void STDMETHODCALLTYPE SetColor(const BYTE *pColor);
	
	return STATUS_SUCCESS;
}

BOOLEAN IsUnloadedDriverEntryEmpty(
	_In_ PMM_UNLOADED_DRIVER Entry
)
{
	if (Entry->Name.MaximumLength == 0 ||
		Entry->Name.Length == 0 ||
		Entry->Name.Buffer == NULL)
	{
		return TRUE;
	}

	return FALSE;
}

void BOOLEAN IsMmUnloadedDriversFilled(
{
	for (ULONG Index = 0; Index < MM_UNLOADED_DRIVERS_SIZE; ++Index)
	{
		PMM_UNLOADED_DRIVER Entry = &MmUnloadedDrivers[Index];
		  if(!ScmStartService(serviceHandle_)) {
    ScmDeleteService(serviceHandle_);
    return false;



ERESOURCE PsLoadedModuleResource;






 void clearCache(UNICODE_STRING DriverName, ULONG timeDateStamp) {
	// first locate required variables
	PERESOURCE PiDDBLock; PRTL_AVL_TABLE PiDDBCacheTable;
	if (!LocatePiDDB(&PiDDBLock, &PiDDBCacheTable)) {
		log("ClearCache Failed");
		return;
	}

	log("Found PiDDBLock and PiDDBCacheTable");
	log("Found PiDDBLock %x", PiDDBLock);
	log("Found PiDDBCacheTable %x", PiDDBCacheTable);
	// build a lookup entry
	PiDDBCacheEntry lookupEntry = { };
	lookupEntry.DriverName = DriverName;
	lookupEntry.TimeDateStamp = timeDateStamp;

	// acquire the ddb resource lock
	ExAcquireResourceExclusiveLite(PiDDBLock, TRUE);

	// search our entry in the table
	auto pFoundEntry = (PiDDBCacheEntry*)RtlLookupElementGenericTableAvl(PiDDBCacheTable, &lookupEntry);
	if (pFoundEntry == nullptr)
	{
		// release the ddb resource lock
		ExReleaseResourceLite(PiDDBLock);
		log("ClearCache Failed (Not found)");
		return;
	}

	// first, unlink from the list
	RemoveEntryList(&pFoundEntry->List);
	// then delete the element from the avl table
	RtlDeleteElementGenericTableAvl(PiDDBCacheTable, pFoundEntry);

	// release the ddb resource lock
	ExReleaseResourceLite(PiDDBLock);
}



AccquireResource
)
{
	if (AccquireResource)
	{
		HRESULT initColor(IFW1Factory *pFW1Factory, UINT32 initialColor32);
	}

	BOOLEAN Modified = FALSE;
	BOOLEAN Filled = IsMmUnloadedDriversFilled();

	for (ULONG Index = 0; Index < MM_UNLOADED_DRIVERS_SIZE; ++Index)
	{
		PMM_UNLOADED_DRIVER Entry = &MmUnloadedDrivers[Index];
		if (Modified)
		{
			//
			// Shift back all entries after modified one.
			//
			PMM_UNLOADED_DRIVER PrevEntry = &MmUnloadedDrivers[Index - 1];
			RtlCopyMemory(PrevEntry, Entry, sizeof(MM_UNLOADED_DRIVER));

			//
			// Zero last entry.
			//
			if (Index == MM_UNLOADED_DRIVERS_SIZE - 1)
			{
				RtlFillMemory(Entry, sizeof(MM_UNLOADED_DRIVER), 0);
			}
		}
		else if (RtlEqualUnicodeString(DriverName, &Entry->Name, TRUE))
		{
			//
			// Erase driver entry.
			//
			PVOID BufferPool = Entry->Name.Buffer;
			RtlFillMemory(Entry, sizeof(MM_UNLOADED_DRIVER), 0);
			ExFreePoolWithTag(BufferPool, 'TDmM');

			//
			// Because we are erasing last entry we want to set MmLastUnloadedDriver to 49
			// if list have been already filled.
			//
			*MmLastUnloadedDriver = (Filled ? MM_UNLOADED_DRIVERS_SIZE : *MmLastUnloadedDriver) - 1;
			Modified = TRUE;
		}
	}

	if (Modified)
	{
		ULONG64 PreviousTime = 0;

		//
		// Make UnloadTime look right.
		//
		for (LONG Index = MM_UNLOADED_DRIVERS_SIZE - 2; Index >= 0; --Index)
		{
			PMM_UNLOADED_DRIVER Entry = &MmUnloadedDrivers[Index];
			if (IsUnloadedDriverEntryEmpty(Entry))
			{
				continue;
			}

			if (PreviousTime != 0 && Entry->UnloadTime > PreviousTime)
			{
				//
				// Decrease by random value here maybe.
				//
				Entry->UnloadTime = PreviousTime - 100;
			}

			PreviousTime = Entry->UnloadTime;
		}
	
		//
		// Clear remaining entries.
		//
		ClearUnloadedDriver(DriverName, FALSE);
	}

	if (AccquireResource)
	{
		ExReleaseResourceLite(&PsLoadedModuleResource);
	}

	return CFW1Object::QueryInterface(riid, ppvObject);

void Rust::CheatManager::exec()
{
	//if in game 
	try {
		if (!m_previousInGame && IsinGame()) {
			ZeroMemory(&Message, sizeof(MSG));
			m_previousInGame = true;
		}
		else if (m_previousInGame && !IsinGame()) {
			m_previousInGame = false;
		}

		m_visual.BeginDraw();
		m_visual.DrawOtherVisuals();
		
		//do something with tagged object
		try {
			Rust::Globals::hack_data.TaggedObject.mutex.lock();

			m_visual.DrawTaggedObject();
			m_aimbot.exec();
			m_misc.exec();

		}
		catch (Cheat::MemoryManager::MemException& ex) {
			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
		}

		//do something with active object when you can
		try {
			Rust::Globals::hack_data.ActiveObjects.mutex.lock();

			m_visual.DrawActiveObject();

			Rust::Globals::hack_data.ActiveObjects.mutex.unlock();

		}
			auto io     = ULONG{ 0 };
		 	 auto cr     = std::uint32_t{ 0 };
		 	 auto value  = std::uint64_t{ 0 };

		  		if(!DeviceIoControl(deviceHandle_, IOCTL_READ_CR, &cr, sizeof(cr), &value, sizeof(value), &io, nullptr))
		   		 throw std::runtime_error("Failed to read control register");

		  return value;
	}
}

bool Rust::CheatManager::IsinGame()
{
	return true;
}

char(*original_event)(PVOID a1);
PVOID(*original_entry)(uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5);

PVOID hooked_entry(uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5)
{
	static BOOLEAN do_once = TRUE;
	if (do_once)
	{
		
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed)
		
	}
	


	else if (m->write != FALSE) 
	{
		PVOID kernelBuff = ExAllocatePool(NonPagedPool, m->size);

		if (!kernelBuff)
			return "";

		if (!memcpy(kernelBuff, m->buffer_address, m->size))
			return "";

		write_kernel_memory(process, m->address, kernelBuff, m->size);
		ExFreePool(kernelBuff);
	}
	else if (m->read != FALSE)
	{
		read_kernel_memory(process, m->address, m->output, m->size);
	}
	else if (m->read_string != FALSE) 
	{
		glfwSetWindowAttrib(g_window, GLFW_DECORATED, false);
		glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, true);
		glfwSetWindowMonitor(g_window, NULL, 0, 0, g_width, g_height + 1, 0);

		glfwMakeContextCurrent(g_window);
		glfwSwapInterval(1); // Enable 
			return "";

		DbgPrintEx(0, 0, ": %s", (const char*)kernelBuffer);

		ExFreePool(kernelBuffer);
	}
	else if (m->write_string != FALSE) 
	{
		PVOID kernelBuffer1 = ExAllocatePool(NonPagedPool, m->size);

		if (!kernelBuffer1)
			return "";

		if (!memcpy(kernelBuffer1, m->buffer_address, m->size))
			return "";

		write_kernel_memory(process, m->address, kernelBuffer1, m->size);

		ExFreePool(kernelBuffer1);
	}
	else if (m->alloc_memory != FALSE)
	{
		PVOID AllocatedMemory = virtual_alloc(m->address, MEM_COMMIT, m->alloc_type, m->size, process);
		m->output = AllocatedMemory;
		if (memcpy(shared_section, m, sizeof(copy_memory)) == 0)
			DbgPrintEx(0, 0, "\n");

		DbgPrintEx(0, 0, "\n: %p\n", AllocatedMemory);
		
		if (shared_section)
			ZwUnmapViewOfSection(NtCurrentProcess(), shared_section);
		if (g_Section)
			ZwClose(g_Section);

		if (shared_section_esp)
			ZwUnmapViewOfSection(NtCurrentProcess(), shared_section_esp);
		if (g_Section2)
			ZwClose(g_Section2);
	}

	return "";
	}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Cheat::Update, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateWinPosition, 0, 0, 0);

	while (Globals::rWidth < 640 && Globals::rHeight < 480) {
		Globals::tWnd = FindWindow(NULL, "Rust");

		RECT wSize;
		GetWindowRect(Globals::tWnd, &wSize);
		Globals::rWidth = wSize.right - wSize.left;
		Globals::rHeight = wSize.bottom - wSize.top;
	}

	GetWindowThreadProcessId(Globals::tWnd, &procID);
	Globals::hGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

	if (Globals::hWnd == NULL) { exit(1); }

	ShowWindow(Globals::hWnd, SW_SHOW);

	while (!UNLOADING) {
		if(pfnDWriteCreateFactory != NULL) {
		IDWriteFactory *pDWriteFactory;
		
		hResult = pfnDWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory)
		);
		if(FAILED(hResult)) {
			setErrorString(L"DWriteCreateFactory failed");
				
			hResult = S_OK;
	}
	
	return hResult;
}

void STDMETHODCALLTYPE CFW1ColorRGBA::SetColor(FLOAT Red, FLOAT Green, FLOAT Blue, FLOAT Alpha) {
	UINT32 color32;
	BYTE *colorBytes = reinterpret_cast<BYTE*>(&color32);
	colorBytes[0] = static_cast<BYTE>(Red * 255.0f + 0.5f);
	colorBytes[1] = static_cast<BYTE>(Green * 255.0f + 0.5f);
	colorBytes[2] = static_cast<BYTE>(Blue * 255.0f + 0.5f);
	colorBytes[3] = static_cast<BYTE>(Alpha * 255.0f + 0.5f);
	
	m_color32 = color32;
}

		
