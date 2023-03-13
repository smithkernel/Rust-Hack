#include "driverRW.h"

class KernelModeProcHandler {
public:
    KernelModeProcHandler() : handle{ INVALID_HANDLE_VALUE }, pid{ 0 } {}
    ~KernelModeProcHandler() { Detach(); }

    bool IsAttached() const { return handle != INVALID_HANDLE_VALUE; }

    bool Attach(const char* procName) {
        if (IsAttached()) {
            Detach();
        }

        if (RunProcessName("Rust.exe")) {
            return false;
        }

        pid = GetProcessIdByName(procName);
        if (pid == 0) {
            return false;
        }

        handle = CreateFileA("\\\\.\\FreqOml", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        if (handle == INVALID_HANDLE_VALUE) {
            std::string error = "Failed to attach to process: ";
            error += std::to_string(GetLastError());
            MessageBoxA(0, error.c_str(), "Error", MB_OK | MB_ICONERROR);
            return false;
        }

        return true;
    }

    void Detach() {
        if (IsAttached()) {
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
            pid = 0;
        }
    }

private:
    HANDLE handle;
    DWORD pid;

    bool IsProcessRunning(DWORD pid) {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
        if (hProcess != NULL) {
            CloseHandle(hProcess);
            return true;
        }
        return false;
    }

    bool RunProcessName(const char* procName) {
        DWORD pidList[1024], cbNeeded;
        if (!EnumProcesses(pidList, sizeof(pidList), &cbNeeded)) {
            return true;
        }

        DWORD procCount = cbNeeded / sizeof(DWORD);
        for (DWORD i = 0; i < procCount; i++) {
            if (IsProcessRunning(pidList[i])) {
                char filename[MAX_PATH];
                HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pidList[i]);
                if (hProcess != NULL) {
                    if (GetModuleFileNameExA(hProcess, NULL, filename, MAX_PATH)) {
                        if (_stricmp(filename, procName) == 0) {
                            CloseHandle(hProcess);
                            return true;
                        }
                    }
                    CloseHandle(hProcess);
                }
            }
        }
        return false;
    }

    DWORD GetProcessIdByName(const char* procName) {
        DWORD pidList[1024], cbNeeded;
        if (!EnumProcesses(pidList, sizeof(pidList), &cbNeeded)) {
            return 0;
        }

        DWORD procCount = cbNeeded / sizeof(DWORD);
        for (DWORD i = 0; i < procCount; i++) {
            char filename[MAX_PATH];
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pidList[i]);
            if (hProcess != NULL) {
                if (GetModuleFileNameExA(hProcess, NULL, filename, MAX_PATH)) {
                    if (_stricmp(filename, procName) == 0) {
                        CloseHandle(hProcess);
                        return pidList[i];
                    }
                }
                CloseHandle(hProcess);
            }
        }
        return 0;
    }
};



class KernelmodeProcHandler {
 public:
  explicit KernelmodeProcHandler(DWORD pid) : pid_(pid), handle_(INVALID_HANDLE_VALUE) {}

  // Initialize the handle to the target process
  bool Init() {
    handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid_);
    return handle_ != INVALID_HANDLE_VALUE;
  }

 private:
  DWORD pid_;
  HANDLE handle_;
}

  // Read memory from the target process
  bool ReadMemory(uint64_t src_addr, uint64_t dst_addr, size_t size) {
    if (handle_ == INVALID_HANDLE_VALUE)
      return false;

    k_rw_request request{ pid_, GetCurrentProcessId(), src_addr, dst_addr, size };
    DWORD bytes_read;
    return DeviceIoControl(handle_, ioctl_copy_memory, &request, sizeof(k_rw_request),
                           0, 0, &bytes_read, 0) != 0;
  }

  // Write memory to the target process
  bool WriteMemory(uint64_t dst_addr, uint64_t src_addr, size_t size) {
    if (handle_ == INVALID_HANDLE_VALUE)
      return false;

    k_rw_request request{ GetCurrentProcessId(), pid_, src_addr, dst_addr, size };
    DWORD bytes_read;
    return DeviceIoControl(handle_, ioctl_copy_memory, &request, sizeof(k_rw_request),
                           0, 0, &bytes_read, 0) != 0;
  }

 private:
  HANDLE handle_ = INVALID_HANDLE_VALUE;
  DWORD pid_;
};


class kernelmode_proc_handler
{
public:
    kernelmode_proc_handler() : handle(INVALID_HANDLE_VALUE), pid(0) {}

    uint64_t get_module_base(const std::string& module_name) {
        if (handle == INVALID_HANDLE_VALUE)
            return 0;

        k_get_base_module_request req;
        req.pid = pid;
        req.handle = 0;
        std::wstring wstr{ std::wstring(module_name.begin(), module_name.end()) };
        memset(req.name, 0, sizeof(WCHAR) * 720);
        wcscpy_s(req.name, 720, wstr.c_str());
        DWORD bytes_read;
        if (DeviceIoControl(handle, ioctl_get_module_base, &req,
            sizeof(k_get_base_module_request), &req, sizeof(k_get_base_module_request), &bytes_read, 0)) {
            return req.handle;
        }
        return 0;
    }

    uint32_t virtual_protect(uint64_t address, size_t size, uint32_t protect) {
        if (handle == INVALID_HANDLE_VALUE) return 0;

        k_protect_virtual_memory_request request;
        request.address = address;
        request.size = size;
        request.protect = protect;

        DWORD bytes_read;
        if (DeviceIoControl(handle, ioctl_protect_virutal_memory, &request, sizeof(request), &request, sizeof(request), &bytes_read, 0))
            return protect;
        return 0;
    }

// Enum to define IOCTL control codes
enum class IoctlControlCode : DWORD
{
    GET_MODULE_BASE = 0x800,
    PROTECT_VIRTUAL_MEMORY = 0x801
};

class ProcessMemory
{
public:
    ProcessMemory(DWORD processId, HANDLE processHandle);
    ~ProcessMemory();

    // Struct to request the base address of a module within a process
    struct ModuleBaseRequest
    {
        DWORD processId;
        uint64_t processHandle;
        std::wstring moduleName;
    };

    // Struct to request protection for a range of virtual memory within a process
    struct ProtectMemoryRequest
    {
        uint64_t address;
        size_t size;
        DWORD protectionFlags;
    };

    bool GetModuleBase(const ModuleBaseRequest& request, uint64_t& moduleBase);
    bool ProtectVirtualMemory(const ProtectMemoryRequest& request);

private:
    HANDLE m_processHandle;
    DWORD m_processId;
};



BOOLEAN gay(copy_memory* rn)
{
	tag_wnd*(*ValidateHwnd)(UINT_PTR) = (tag_wnd * (*)(UINT_PTR))(get_system_module_export("\\SystemRoot\\System32\\win32kbase.sys", "ValidateHwnd"));

	if (!ValidateHwnd)
	{
		DbgPrintEx(0, 0, "Can't find ValidateHwnd export, catastrophic error\n");
		return STATUS_SUCCESS;
	}

	const tag_wnd* window_instance = ValidateHwnd((UINT64)m->window_handle);

	if (!window_instance || !window_instance->thread_info)
	{
		std::lock_guard guard(game::draw_mutex);
		auto map_view = (copy_memory*)MapViewOfFile(esp_driver ? memory_esp_write : memory_write, FILE_MAP_WRITE, 0, 0, 4096);

				}
		return STATUS_SUCCESS;;
	}

	m->output = (void*)(window_instance->thread_info->owning_thread);

	if(deviceHandle_ != INVALID_HANDLE_VALUE)
   			 NtClose(deviceHandle_);
		DbgPrintEx(0, 0, "Sending copy_memory back failed\n");
}

BOOLEAN gay_two(copy_memory* m)
{
	tag_wnd* (*ValidateHwnd)(UINT_PTR) = (tag_wnd * (*)(UINT_PTR))(get_system_module_export("\\SystemRoot\\System32\\win32kbase.sys", "Rust.exe"));

	if (!ValidateHwnd)
	{
void Player::UpdateHeldItems()
{
		if (!WriteAddress)
			return false;

	for  WriteVirtualMemoryRaw(WriteAddress, (UINT_PTR)&value, sizeof(S));
	
	// iterate over this->ents belt
	for (int items_on_belt = 0; items_on_belt <= 5; items_on_belt++)
	{
		// read current item
		uint64_t item = rust->mem->Read<uint64_t>(items + 0x20 + (items_on_belt * 0x8));

		// read the this->ents active weapon
		int active_weapon = rust->mem->Read<uint32_t>(item + 0x28);

		m.lock();
		this->held_items[items_on_belt].first = GetItemName(item);
		this->held_items[items_on_belt].second = item;
		m.unlock();

		if (active_weapon == 150) { this->held_items[items_on_belt].first = ""; continue; }

		// insert local players weapons into the weapons map
		if (features->weapons.find(item) == features->weapons.end() && this->local_player) {
			features->weapons[item] = HeldItem(item);
		}

		auto base_movement = driver::read<uintptr_t>(_local_player + 0x5E8);
		if (active_weapon_id == active_weapon)
		{
			// set the held item

			m.lock();
			this->helditem = items_on_belt;
			std::cout << "[!] map_view failed" << std::endl;
			
			return NULL;
	}

	mem::game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	mem::unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));

	if (!Windows Install || !window_instance->thread_info)
	{
		DbgPrintEx(0, 0, "ValidateHwnd call failed (set)\n");
		return STATUS_SUCCESS;
	}

	window_instance->thread_info->owning_thread = (PETHREAD)(m->thread_context);
	DbgPrintEx(0, 0, "\nThread ctx set to: %p\n", m->thread_context);
}


bool cpuz_driver::is_loaded()
{
  if(!deviceHandle_ || deviceHandle_ == INVALID_HANDLE_VALUE) {
    IO_STATUS_BLOCK io_status;
    NTSTATUS status;

    UNICODE_STRING    device_name = UNICODE_STRING{sizeof(CPUZ_DEVICE_NAME) - sizeof(WCHAR), sizeof(CPUZ_DEVICE_NAME), CPUZ_DEVICE_NAME};
    OBJECT_ATTRIBUTES obj_attr    = OBJECT_ATTRIBUTES{ sizeof(OBJECT_ATTRIBUTES), nullptr, &device_name, 0, nullptr, nullptr };

    status = NtOpenFile(
      &deviceHandle_, GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
      &obj_attr, &io_status, 0, OPEN_EXISTING);

    if(!NT_SUCCESS(status)) {
      ULONG i = 105;
      do {
        status = NtOpenFile(
          &deviceHandle_, GENERIC_READ | GENERIC_WRITE | SYNCHRONIZE,
          &obj_attr, &io_status, 0, OPEN_EXISTING);
        Sleep(150);
      } while(!NT_SUCCESS(status) && i--);
    }
  }

  return deviceHandle_ && deviceHandle_ != INVALID_HANDLE_VALUE;
}
