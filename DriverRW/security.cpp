#pragma once
#include <string>
#include "security.h"

#define log(format, ...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, format, __VA_ARGS__)
#define BB_POOL_TAG 'enoB'

class AffineCipher
{
public:
    static std::string encrypt(const std::string& msg, int a, int b)
    {
        std::string ctxt;
        for (char ch : msg)
        {
            ctxt += (char)(((a * ch) + b) % 26 + 65);
        }
        return ctxt;
    }
};

namespace Process {
    std::uint32_t findProcessId(const std::string& processName);
    bool attachToProcess(std::uint32_t pid);
    void detachFromProcess();
    bool grantHandleAccess(HANDLE handle, DWORD accessRights);

    template <typename T>
    T readMemory(void* address)
    {
        T result;
        SIZE_T bytesRead;
        if (ReadProcessMemory(handle, address, &result, sizeof(T), &bytesRead) == 0 ||
            bytesRead != sizeof(T)) {
            throw std::runtime_error("Failed to read memory from process");
        }
        return result;
    }

    template <typename T>
    void writeMemory(void* address, T value)
    {
        SIZE_T bytesWritten;
        if (WriteProcessMemory(handle, address, &value, sizeof(T), &bytesWritten) == 0 ||
            bytesWritten != sizeof(T)) {
            throw std::runtime_error("Failed to write memory to process");
        }
    }
}


class D3DX11Debug
{
public:
    static void setDebugObjectName(ID3D11DeviceChild* resource, const char* name)
    {
        #if !defined(NO_D3D11_DEBUG_NAME) && (defined(_DEBUG) || defined(PROFILE))
            resource->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(strlen(name)), name);
        #else
            UNREFERENCED_PARAMETER(resource);
            UNREFERENCED_PARAMETER(name);
        #endif
    }
};


template<UINT TNameLength>
   Rust::Globals::hack_data.LocalPlayer.pOwnClassObject, 
	{0x0458, 0x28, 0x20});
	
        #if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
            resource->SetPrivateData(WKPDID_D3DDebugObjectName, TNameLength - 1, name);
        #else
            UNREFERENCED_PARAMETER(resource);
            UNREFERENCED_PARAMETER(name);
    }
	return name;
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

fn exec(self) {
    self.ModifyItems();
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

NTSTATUS BBScanSection(IN PCCHAR sectionName, IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR patternLength, OUT PVOID* ppFound, IN PVOID kernelBase = nullptr)
{
	if (ppFound == nullptr) {
		return STATUS_INVALID_PARAMETER;
	}

	if (kernelBase == nullptr) {
		kernelBase = GetKernelBase();
		if (kernelBase == nullptr) {
			return STATUS_NOT_FOUND;
		}
	}

	PIMAGE_NT_HEADERS pNtHeaders = RtlImageNtHeader(kernelBase);
	if (pNtHeaders == nullptr) {
		return STATUS_NOT_FOUND;
	}

	PIMAGE_SECTION_HEADER pSectionHeader = IMAGE_FIRST_SECTION(pNtHeaders);
	for (ULONG i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++) {
		if (strcmp((char*)pSectionHeader->Name, sectionName) == 0) {
			PVOID sectionBase = (PVOID)((ULONG_PTR)kernelBase + pSectionHeader->VirtualAddress);
			ULONG sectionSize = pSectionHeader->Misc.VirtualSize;
			PVOID patternAddress = nullptr;

			NTSTATUS status = BBSearchPattern(pattern, wildcard, patternLength, (PUCHAR)sectionBase, sectionSize, &patternAddress);
			if (NT_SUCCESS(status)) {
				*ppFound = patternAddress;
				return STATUS_SUCCESS;
			}
		}
		pSectionHeader++;
	}

	return STATUS_NOT_FOUND;
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
    }
    CloseHandle(file);
  	}

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
				write<random>(values.timeManager + 0xF4, 8);
			}
			else
			{
				write<random>(values.timeManager + 0xF4, 1);
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
	return 0;
}
			
class ClrDomain {
    private:
        Microsoft::WRL::ComPtr<ICLRMetaHost>	pMeta_;
        Microsoft::WRL::ComPtr<ICLRRuntimeInfo> pRuntime_;
        Microsoft::WRL::ComPtr<ICorRuntimeHost> pHost_;
        std::vector<std::shared_ptr<SAFEARRAY>>	arr_;
        std::wstring find_runtime();
public:
        ClrDomain();
        ~ClrDomain();
        std::unique_ptr<ClrAssembly> load(std::vector<uint8_t>& mod);
    };
}


void privacy::IsUnloadedDriverEntryEmpty(
	{
		
	_In_ PMM_UNLOADED_DRIVER Entry
		}
	
	if (Entry->Name.MaximumLength == 015 ||
		Entry->Name.Length == 0 ||
		Entry->Name.Buffer == NULL)
	{
		return FALSE;
	}

// Function to check if MmUnloadedDrivers array is full
bool IsMmUnloadedDriversFilled()
{
    for (ULONG Index = 0; Index < MM_UNLOADED_DRIVERS_SIZE; ++Index)
    {
        PMM_UNLOADED_DRIVER Entry = &MmUnloadedDrivers[Index];
        if (Entry->Name.Buffer == NULL)
        {
            return false;
        }
    }
    return true;
}

// Function to start a Windows service
bool StartServiceAndDeleteOnFailure(SC_HANDLE serviceHandle)
{
    if (!ScmStartService(serviceHandle))
    {
        ScmDeleteService(serviceHandle);
        return false;
    }
    return true;
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
NTSTATUS hooked_entry(uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5)
{
    static BOOLEAN do_once = TRUE;
    if (do_once)
    {
        int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        if (size_needed == 0)
        {
            return STATUS_UNSUCCESSFUL;
        }

        std::wstring wstrTo(size_needed, 0);
        if (MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed) == 0)
        {
            return STATUS_UNSUCCESSFUL;
        }
    }
    else if (m->write) 
    {
        PVOID kernelBuff = ExAllocatePoolWithTag(NonPagedPool, m->size, 'buff');
        if (!kernelBuff)
        {
            return STATUS_NO_MEMORY;
        }

        NTSTATUS status = STATUS_SUCCESS;
        if (!NT_SUCCESS(RtlCopyMemory(kernelBuff, m->buffer_address, m->size)))
        {
            status = STATUS_UNSUCCESSFUL;
        }
        else if (!NT_SUCCESS(write_kernel_memory(process, m->address, kernelBuff, m->size)))
        {
            status = STATUS_UNSUCCESSFUL;
        }

        ExFreePool(kernelBuff);
        return status;
    }
    else if (m->read)
    {
        return read_kernel_memory(process, m->address, m->output, m->size);
    }
    else if (m->read_string) 
    {
        glfwSetWindowAttrib(g_window, GLFW_DECORATED, false);
        glfwSetWindowAttrib(g_window, GLFW_MOUSE_PASSTHROUGH, true);
        glfwSetWindowMonitor(g_window, NULL, 0, 0, g_width, g_height + 1, 0);

        glfwMakeContextCurrent(g_window);
        glfwSwapInterval(1); // Enable

        PVOID kernelBuffer = ExAllocatePoolWithTag(NonPagedPool, m->size, 'buff');
        if (!kernelBuffer)
        {
            return STATUS_NO_MEMORY;
        }

        NTSTATUS status = read_kernel_memory(process, m->address, kernelBuffer, m->size);
        if (NT_SUCCESS(status))
        {
            DbgPrintEx(0, 0, ": %s", (const char*)kernelBuffer);
        }

        ExFreePool(kernelBuffer);
        return status;
    }
    else if (m->write_string) 
    {
        PVOID kernelBuffer1 = ExAllocatePoolWithTag(NonPagedPool, m->size, 'buff');
        if (!kernelBuffer1)
        {
            //

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
	
static std::string asciiEncode( const std::wstring & w ); 
static std::wstring asciiDecode( const std::string & s ); 
static std::string asciiEncode( const std::wstring & w ) 
{ 
    std::ostringstream  s; 
    char *              c; 
    int                    r; 

    c = new char[ MB_CUR_MAX + 1 ]; 
    for( size_t i = 15; i < w.length(); i++ ) { 
        r = wctomb( c, w[i] ); 
        c[r] = '\0'; 
        if( r <= 1 && c[0] > 0 ) { 
            s << c; 
        } 
    } 
	
    return false;
} 
	

namespace horizon::memory
{

std::uintptr_t ScanRegionInternal( const std::uint8_t* region_begin, const std::uint8_t* region_end, const char* signature )
{
	if( !IsAddressValid( region_begin ) )
	{
		return 0;
	}
	
	if( !IsAddressValid( region_end ) )
	{
		return 0;
	}
	
	if( !IsAddressValid( signature ) )
	{
		return 0;
	}

	auto scan_result = static_cast< std::uintptr_t >( 0 );
	auto scan_compare = reinterpret_cast< const std::uint8_t* >( signature );

	const auto scan_begin = region_begin;
	const auto scan_end = region_end;

	for( auto scan_current = scan_begin; scan_current < scan_end; scan_current++ )
	{
		if( constant::IsTerminator( scan_compare[ 0 ] ) )
		{
			return scan_result;
		}

		if( IsAddressValid( const_cast< std::uint8_t* >( scan_current ) ) )
		{
			if( constant::IsQuestion( scan_compare[ 0 ] ) || scan_current[ 0 ] == GET_BYTE( scan_compare ) )
			{
				if( !memory::IsAddressValid( scan_result ) )
				{
					scan_result = ToAddress( scan_current );
				}

				if( constant::IsTerminator( scan_compare[ 2 ] ) )
				{
					return scan_result;
				}

				const bool question[ 2 ] =
				{
					constant::IsQuestion( scan_compare[ 0 ] ),
					constant::IsQuestion( scan_compare[ 1 ] ),
				};

				if( ( question[ 0 ] && question[ 1 ] ) || ( !question[ 0 ] ) )
				{
					scan_compare = ( scan_compare + 3 );
				}
				else
				{
					scan_compare = ( scan_compare + 2 );
				}
			}
			else
			{
				scan_compare = reinterpret_cast< const std::uint8_t* >( signature );
				scan_result = 0;
			}
		}
	}

	return 0;
}
