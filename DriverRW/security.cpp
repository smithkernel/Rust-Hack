#pragma once
#include "security.h"

#define log(format, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, format, __VA_ARGS__)
#define BB_POOL_TAG 'enoB'


static bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	PDIRECT3DTEXTURE9 texture;

	HRESULT hr = D3DXCreateTextureFromFileA(pDevice, filename, &texture);
	if (hr != S_OK)
		return false;

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
		return STATUS_ACCESS_DENIED; //STATUS_INVALID_PARAMETER;
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

		if (found != FALSE && cIndex++ == index)
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
	NTSTATUS status = STATUS_SUCCESS;
	ULONG bytes = 0;
	PRTL_PROCESS_MODULES pMods = NULL;
	PVOID checkPtr = NULL;
	UNICODE_STRING routineName;

	// Already found
	if (g_KernelBase != NULL)
	{
		if (pSize)
			*pSize = g_KernelSize;
		return g_KernelBase;
	}

	RtlUnicodeStringInit(&routineName, L"NtOpenFile");

	checkPtr = MmGetSystemRoutineAddress(&routineName);
	if (checkPtr == NULL)
		return NULL;

	// Protect from UserMode AV
	status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);
	if (bytes == 0)
	{
		log("Invalid SystemModuleInformation size");
		return NULL;
	}

	pMods = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, bytes, BB_POOL_TAG);
	RtlZeroMemory(pMods, bytes);

	status = ZwQuerySystemInformation(SystemModuleInformation, pMods, bytes, &bytes);

	if (NT_SUCCESS(status))
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
					*pSize = g_KernelSize;
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

	return false;
}


NTSTATUS BBScanSection(IN PCCHAR section, IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, OUT PVOID* ppFound, PVOID base = nullptr)
{
	//ASSERT(ppFound != NULL);
	if (ppFound == NULL)
		return STATUS_ACCESS_DENIED; //STATUS_INVALID_PARAMETER

	if (nullptr == base)
		base = GetKernelBase(&g_KernelSize);
	if (base == nullptr)
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
				return status;
			}
			//we continue scanning because there can be multiple sections with the same name.
		}
	}

	return STATUS_ACCESS_DENIED; //STATUS_NOT_FOUND;
}
extern "C" bool LocatePiDDB(PERESOURCE * lock, PRTL_AVL_TABLE * table)
{
	PVOID PiDDBLockPtr = nullptr, PiDDBCacheTablePtr = nullptr;
	if (!NT_SUCCESS(BBScanSection("PAGE", PiDDBLockPtr_sig, 0, sizeof(PiDDBLockPtr_sig) - 1, reinterpret_cast<PVOID*>(&PiDDBLockPtr)))) {
		log("Unable to find PiDDBLockPtr sig.");
		return false;
	}

	if (!NT_SUCCESS(BBScanSection("PAGE", PiDDBCacheTablePtr_sig, 0, sizeof(PiDDBCacheTablePtr_sig) - 1, reinterpret_cast<PVOID*>(&PiDDBCacheTablePtr)))) {
		log("Unable to find PiDDBCacheTablePtr sig");
		return false;
	}

	PiDDBCacheTablePtr = PVOID((uintptr_t)PiDDBCacheTablePtr + 3);

	*lock = (PERESOURCE)(ResolveRelativeAddress(PiDDBLockPtr, 3, 7));
	*table = (PRTL_AVL_TABLE)(ResolveRelativeAddress(PiDDBCacheTablePtr, 3, 7));

	return true;
}

PDIRECT3DTEXTURE9 my_texture;
PDIRECT3DTEXTURE9 my_texture2;
#include "globals.h"
ImFont* main_font;

}



PMM_UNLOADED_DRIVER MmUnloadedDrivers;
PULONG				MmLastUnloadedDriver;

BOOLEAN bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return 0;

	return (*szMask) == 0;
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
	/*
	 *	nt!MmLocateUnloadedDriver:
	 *	fffff801`51c70394 4c8b15a57e1500  mov     r10,qword ptr [nt!MmUnloadedDrivers (fffff801`51dc8240)]
	 *	fffff801`51c7039b 4c8bc9          mov     r9 ,rcx
	 */
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

	MmUnloadedDrivers = *(PMM_UNLOADED_DRIVER*)ResolveRelativeAddress(MmUnloadedDriversInstr, 3, 7);
	MmLastUnloadedDriver = (PULONG)ResolveRelativeAddress(MmLastUnloadedDriverInstr, 2, 6);
	/*log("MmUnloadedDrivers ModuleEnd: %x", MmUnloadedDrivers->ModuleEnd);
	log("MmUnloadedDrivers ModuleStart: %x", MmUnloadedDrivers->ModuleStart);
	log("MmUnloadedDrivers Name: %s", MmUnloadedDrivers->Name);
	log("MmUnloadedDrivers UnloadTime: %x", MmUnloadedDrivers->UnloadTime);*/

	//log("MmUnloadedDrivers Addr: %x", MmUnloadedDrivers);
	//log("MmLastUnloadedDriver Addr: %x", MmLastUnloadedDriver);
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

BOOLEAN IsMmUnloadedDriversFilled(
	VOID
)
{
	for (ULONG Index = 0; Index < MM_UNLOADED_DRIVERS_SIZE; ++Index)
	{
		PMM_UNLOADED_DRIVER Entry = &MmUnloadedDrivers[Index];
		if (IsUnloadedDriverEntryEmpty(Entry))
		{
			return FALSE;
		}
	}

	return TRUE;
}



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
	log("ClearCache Sucessful");
}




NTSTATUS ClearUnloadedDriver(
	_In_ PUNICODE_STRING	DriverName,
	_In_ BOOLEAN			AccquireResource
)
{
	if (AccquireResource)
	{
		ExAcquireResourceExclusiveLite(&PsLoadedModuleResource, TRUE);
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

	return Modified ? STATUS_SUCCESS : STATUS_NOT_FOUND;
}

void Rust::CheatManager::exec()
{
	//if in game 
	try {
		if (!m_previousInGame && IsinGame()) {
			Rust::EntityUpdator::UpdateLocalPlayerAndCameraData();
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

			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
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
		catch (Cheat::MemoryManager::MemException& ex) {
			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
		}
		
		m_visual.EndDraw();
	}
	catch (Cheat::cexception& ex) {
		throw ex;
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
		do_once = FALSE;
	}
	
	if (!NT_SUCCESS(read_shared_memory_esp()))
	{
		return NULL;
	}

	if (!shared_section_esp)
		return original_entry(a1, a2, a3, a4, a5);

	copy_memory* m = (copy_memory*)shared_section_esp;
	if (!m)
		return original_entry(a1, a2, a3, a4, a5);

	if (!m->called)
		return original_entry(a1, a2, a3, a4, a5);

	if (m->read != FALSE)
	{
		read_kernel_memory(process, m->address, m->output, m->size);
	}
	else if (m->read_string != FALSE)
	{
		PVOID kernelBuffer = ExAllocatePool(NonPagedPool, m->size);

		if (!kernelBuffer)
			return original_entry(a1, a2, a3, a4, a5);

		if (!memcpy(kernelBuffer, m->buffer_address, m->size))
			return original_entry(a1, a2, a3, a4, a5);

		read_kernel_memory(process, m->address, kernelBuffer, m->size);

		RtlZeroMemory(m->buffer_address, m->size);

		if (!memcpy(m->buffer_address, kernelBuffer, m->size))
		{
			ExFreePool(kernelBuffer);
			return original_entry(a1, a2, a3, a4, a5);
		}
		ExFreePool(kernelBuffer);
	}
	else if (m->end != FALSE)
	{
		if (shared_section_esp)
			ZwUnmapViewOfSection(NtCurrentProcess(), shared_section_esp);
		if (g_Section2)
			ZwClose(g_Section2);
	}

	return original_entry(a1, a2, a3, a4, a5);
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
		PVOID kernelBuffer = ExAllocatePool(NonPagedPool, m->size);

		if (!kernelBuffer)
			return "";

		if (!memcpy(kernelBuffer, m->buffer_address, m->size))
			return "";

		read_kernel_memory(process, m->address, kernelBuffer, m->size);

		RtlZeroMemory(m->buffer_address, m->size);

		if (!memcpy(m->buffer_address, kernelBuffer, m->size))
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

	INITIALIZED = TRUE;

	while (!UNLOADING) {
		if (PeekMessage(&uMessage, Globals::hWnd, 0, 0, PM_REMOVE)) {
			DispatchMessage(&uMessage);
			TranslateMessage(&uMessage);
		}

		if (UNLOADING) {
			HWND hMsg = FindWindow(NULL, "Info");

			if (hMsg) {
				std::this_thread::sleep_for(std::chrono::seconds(3));
				SendMessageA(hMsg, WM_CLOSE, 0, 0);
			}
		}
	}
	
	
	}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	switch (uMessage) {
	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &MARGIN);
		break;

	case WM_PAINT:
		D3DRender();
		break;

	case WM_DESTROY:
		ImGui::Shutdown();
		DeleteObject(wndClass.hbrBackground);
		DestroyCursor(wndClass.hCursor);
		DestroyIcon(wndClass.hIcon);
		DestroyIcon(wndClass.hIconSm);

		PostQuitMessage(1);
		break;

	default:
		ImGui_ImplWin32_WndProcHandler(hWnd, uMessage, wParam, lParam);
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
		break;
	}

	return 0;
}
	
	
