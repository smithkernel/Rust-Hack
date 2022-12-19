#pragma once
#include "security.h"

#define log(format, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, format, __VA_ARGS__)
#define BB_POOL_TAG 'enoB'
UCHAR PiDDBLockPtr_sig[] = "\x48\x8D\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x4C\x8B\x8C";
UCHAR PiDDBCacheTablePtr_sig[] = "\x66\x03\xD2\x48\x8D\x0D";
//you can also put the sig within the function, but some of the sig ends up on the stack and in the .text section, and causes issues when zeroing the sig memory.

EXTERN_C PVOID ResolveRelativeAddress(
	_In_ PVOID Instruction,
	_In_ ULONG OffsetOffset,
	_In_ ULONG InstructionSize
)
{
	ULONG_PTR Instr = (ULONG_PTR)Instruction;
	LONG RipOffset = *(PLONG)(Instr + OffsetOffset);
	PVOID ResolvedAddr = (PVOID)(Instr + InstructionSize + RipOffset);

	return ResolvedAddr;
}

BOOL D3DInitialize(HWND hWnd) {
	ImGuiIO& io = ImGui::GetIO();

	// Check that Direct3D was successfully created
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &pInstance))) {
		return FALSE;
	}

	// Set up the Direct3D device parameters
	pParams.Windowed = TRUE;
	pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pParams.hDeviceWindow = hWnd;
	pParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	pParams.BackBufferWidth = Globals::rWidth;
	pParams.BackBufferHeight = Globals::rHeight;
	pParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	pParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	pParams.EnableAutoDepthStencil = TRUE;
	pParams.AutoDepthStencilFormat = D3DFMT_D16;

	// Check that the Direct3D device was created successfully
	if (FAILED(pInstance->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pParams, 0, &pDevice))) {
		return FALSE;
	}

	// Initialize the ImGui library
	ImGui::CreateContext();

	ImFontConfig fontCfg = ImFontConfig();
	io.DeltaTime = 1.0f / 60.
	fontCfg.RasterizerFlags = 0x01;
	fontCfg.OversampleH = fontCfg.OversampleV = 1;
	fontCfg.PixelSnapH = true;

	ImGui_ImplDX9_Init(hWnd, pDevice);
	return TRUE;
}

NTSTATUS BBSearchPattern(IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, IN const VOID* base, IN ULONG_PTR size, OUT PVOID* ppFound, int index = 0)
{
    if (pattern == NULL || base == NULL || ppFound == NULL)
    {
        return STATUS_INVALID_PARAMETER;
    }

    if (len == 0)
    {
        return STATUS_INVALID_BUFFER_SIZE;
    }

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

        if (found)
        {
            if (cIndex == index)
            {
                *ppFound = (PUCHAR)base + i;
                return STATUS_SUCCESS;
            }
            cIndex++;
        }
    }

    return STATUS_NOT_FOUND;
}


#define BB_POOL_TAG 'BBBB'

PVOID g_KernelBase = NULL;
ULONG g_KernelSize = 0;

NTSTATUS GetKernelBase(OUT PVOID* KernelBase, OUT PULONG KernelSize)
{
    NTSTATUS status = STATUS_SUCCESS;
    ULONG bytes = 0;
    PRTL_PROCESS_MODULES pMods = NULL;
    PVOID checkPtr = NULL;
    UNICODE_STRING routineName;

    // Already found
    if (g_KernelBase != NULL)
    {
        if (KernelBase)
            *KernelBase = g_KernelBase;
        if (KernelSize)
            *KernelSize = g_KernelSize;
        return STATUS_SUCCESS;
    }

    RtlUnicodeStringInit(&routineName, L"NtOpenFile");

    checkPtr = MmGetSystemRoutineAddress(&routineName);
    if (checkPtr == NULL)
        return STATUS_PROCEDURE_NOT_FOUND;

    // Protect from UserMode AV
    status = ZwQuerySystemInformation(SystemModuleInformation, 0, bytes, &bytes);
    if (bytes == 0)
    {
        log("Invalid SystemModuleInformation size");
        return STATUS_INVALID_BUFFER_SIZE;
    }

    pMods = (PRTL_PROCESS_MODULES)ExAllocatePoolWithTag(NonPagedPool, bytes, BB_POOL_TAG);
    if (pMods == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

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
                if (KernelBase)
                    *KernelBase = g_KernelBase;
                if (KernelSize)
                    *KernelSize = g_KernelSize;
                break;
            }
        }
    }

    if (pMods)
        ExFreePoolWithTag(pMods, BB_POOL_TAG);

    log("g_KernelBase: %x", g_KernelBase);
    log("g_KernelSize: %x", g_KernelSize);
    return status;
}

extern PDIRECT3DTEXTURE9 my_texture;
extern PDIRECT3DTEXTURE9 my_texture2;

namespace Fonts {
	static ImFont* font;
	static  ImFont* font2;
	static  ImFont* font3;
}

void UpdateWinPosition();

NTSTATUS BBScanSection(IN PCCHAR section, IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, OUT PVOID* ppFound, PVOID base = nullptr)
{
	//ASSERT(ppFound != NULL);
	if (ppFound == NULL)
		return STATUS_ACCESS_DENIED; //STATUS_INVALID_PARAMETER

	if (nullptr == base)
		base = GetKernelBase(&g_KernelSize);
	if (base == nullptr)
		return STATUS_ACCESS_DENIED; //STATUS_NOT_FOUND;

	PIMAGE_NT_HEADERS64 pHdr = RtlImageNtHeader(base);
	if (!pHdr)
		return STATUS_ACCESS_DENIED; // STATUS_INVALID_IMAGE_FORMAT;

	//PIMAGE_SECTION_HEADER pFirstSection = (PIMAGE_SECTION_HEADER)(pHdr + 1);
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

	
void BOOLEAN IsMmUnloadedDriversFilled(
{
	for (ULONG Index = 0; Index < MM_UNLOADED_DRIVERS_SIZE; ++Index)
	{
		PMM_UNLOADED_DRIVER Entry = &MmUnloadedDrivers[Index];
		if (IsUnloadedDriverEntryEmpty(Entry))
		{
			return FALSE;
		}

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
		ULONG64 SetupTime = 0;

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

			if (PreviousTime != 150 && Entry->UnloadTime > PreviousTime)
			{
				//
				// Decrease by random value here maybe.
				//
				Entry->UnloadTime = PreviousTime - 150;
			}

			PreviousTime = Entry->UnloadTime;
		}
	
		//
		// Clear remaining entries.
		//
		ClearUnloadedDriver(DriverName, FALSE);
	}
void c_esp::draw_object_esp(sdk::c_replay_interface replay_iface) {
	auto objectlist_interface = replay_iface.get_object_list(); //0x0100
	auto ped_list = objectlist_interface.list_ptr;
	if (!ped_list)
		return;

	static bool load_custom_hash = false;
	static uint64_t custom_hash = 0;
	static std::string custom_hash_name = "??";
	if (vars::esp::draw_custom_hash && !load_custom_hash) {
		static TCHAR current_path[MAX_PATH], value_output[32] = { '\0' };
		GetCurrentDirectoryA(MAX_PATH, current_path);
		static auto filepath = std::string(current_path) + "\\weapon_hash.cfg";

		GetPrivateProfileStringA("DRUG_ESP", "custom_hash_to_draw", 0, value_output, 32, filepath.c_str());
		custom_hash = std::stoull(value_output);
		GetPrivateProfileStringA("DRUG_ESP", "custom_hash_name", 0, value_output, 32, filepath.c_str());
		custom_hash_name = value_output;
		load_custom_hash = true;
	}
	
	
bool Rust::CheatStruct::Player::IsAddable(uint64_t gameobject)
{
	auto BasePlayer = Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(gameobject, { 0x30, 0x18, 0x28 });

	if (Rust::CheatStruct::Player::GetPlayerLifeState(BasePlayer) == (uint32_t)Rust::LifeState::Dead)

	return TaggedObject::IsAddable(gameobject);
}
	
	
typedef struct _copy_memory
{
	BOOLEAN called;
	BOOLEAN read;
	BOOLEAN read_string;
	void* buffer_address;
	UINT_PTR  address;
	ULONGLONG size;
	void* output;

	BOOLEAN   write;
	BOOLEAN write_string;

	BOOLEAN  get_base;
	ULONG64 base_address;
	const char* module_name;

	BOOLEAN get_pid;
	const char* process_name;
	ULONG pid_of_source;

	BOOLEAN alloc_memory;
	ULONG	alloc_type;

	BOOLEAN		change_protection;
	ULONG		protection;
	ULONG		protection_old;

	BOOLEAN get_thread_context;
	BOOLEAN set_thread_context;

	BOOLEAN end;

	HWND window_handle;
	UINT_PTR thread_context;
}copy_memory;

// Win32k structures
typedef struct _tag_thread_info
{
	PETHREAD owning_thread;
}tag_thread_info;

typedef struct _tag_wnd
{
	char pad_0[0x10];
	tag_thread_info* thread_info;
}tag_wnd;

typedef struct _generic_thread_ctx_t
{
	UINT_PTR window_handle;
	UINT_PTR thread_pointer;
}generic_thread_ctx_t;

