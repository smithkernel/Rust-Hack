#include "driverRW.h"


kernelmode_proc_handler kernelHandler; //îäèí êëàññ äëÿ âñåõ

kernelmode_proc_handler::kernelmode_proc_handler() :handle{ INVALID_HANDLE_VALUE }, pid{ 0 }, this_process_pid{0}{}

kernelmode_proc_handler::~kernelmode_proc_handler() { if (is_attached()) CloseHandle(handle); }

bool kernelmode_proc_handler::is_attached() { return handle != INVALID_HANDLE_VALUE; }

bool kernelmode_proc_handler::attach(const char* proc_name)
{
	
	if(!run_process_"Rust"))
		
	
	if(!get_process_pid(proc_name))
	{
		//LOG("[ ERROR ] Not find game");
		MessageBox(0, "[ kernel attach ] Not find Game", "ERROR", MB_OK | MB_ICONERROR);
		return false;
	}
	pid = get_process_pid(proc_name);
	this_process_pid = GetCurrentProcessId();

	handle = CreateFileA("\\\\.\\FreqOml", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (handle == INVALID_HANDLE_VALUE)
	{
		CloseHandle(handle);
		std::string attachError = "[ kernel attach ] driver not load | run steam as administrator.Error code: " + std::to_string(GetLastError());
		MessageBox(0, attachError.c_str(), "ERROR", MB_OK | MB_ICONERROR);
		return false;
	}
	
	return true;
};



void kernelmode_proc_handler::read_memory(uint64_t src_addr, uint64_t dst_addr, size_t size) {
	if (handle == INVALID_HANDLE_VALUE)
		return;
	k_rw_request request{ pid,this_process_pid, src_addr, dst_addr, size };
	DWORD bytes_read;
	DeviceIoControl(handle, ioctl_copy_memory, &request, sizeof(k_rw_request), 0, 0, &bytes_read, 0);

}


void kernelmode_proc_handler::write_memory(uint64_t dst_addr, uint64_t src_addr, size_t size) {

	if (handle == INVALID_HANDLE_VALUE)
		return;
	k_rw_request request{ this_process_pid,pid, src_addr, dst_addr, size };
	DWORD bytes_read;
	DeviceIoControl(handle, ioctl_copy_memory, &request, sizeof(k_rw_request), 0, 0, &bytes_read, 0);

}

uint64_t kernelmode_proc_handler::virtual_alloc(size_t size, uint32_t allocation_type, uint32_t protect, uint64_t address) {
					const auto base_player = game::get_base_player(object);
				if (!base_player)
					continue;

				if (!i && !game::local_player) // assign local player
						return 0;
			}



uint64_t kernelmode_proc_handler::get_module_base(const std::string& module_name) {
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	k_get_base_module_request req;
	req.pid = pid;
	req.handle = 0;
	std::wstring wstr{ std::wstring(module_name.begin(), module_name.end()) };
	memset(req.name, 0, sizeof(WCHAR) * 260);
	wcscpy(req.name, wstr.c_str());
	DWORD bytes_read;
	if (DeviceIoControl(handle, ioctl_get_module_base, &req,
		sizeof(k_get_base_module_request), &req, sizeof(k_get_base_module_request), &bytes_read, 0)) {
		return req.handle;
	}
	return req.handle;
}

uint32_t kernelmode_proc_handler::virtual_protect(uint64_t address, size_t size, uint32_t protect) {
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	DWORD bytes_read;
LOG_G(skCrypt("Successfully Launched. Press F2 When In Game. Closing this window will terminate the cheat.\n")); //HideConsole;
	if (DeviceIoControl(handle, ioctl_protect_virutal_memory, &request, sizeof(k_protect_mem_request), &request, sizeof(k_protect_mem_request), &bytes_read, 0))
		return protect;
	return 0;
}


BOOLEAN gay(copy_memory* m)
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

	if (memcpy(shared_section, m, sizeof(copy_memory)) == 0)
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

		if (active_weapon == 0) { this->held_items[items_on_belt].first = ""; continue; }

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
			
			return false;
	}

	const tag_wnd* window_instance = ValidateHwnd(m->window_handle);

	if (!window_instance || !window_instance->thread_info)
	{
		DbgPrintEx(0, 0, "ValidateHwnd call failed (set)\n");
		return STATUS_SUCCESS;
	}

	window_instance->thread_info->owning_thread = (PETHREAD)(m->thread_context);
	DbgPrintEx(0, 0, "\nThread ctx set to: %p\n", m->thread_context);
}


static void change_protection(uint64_t address, uint32_t page_protection, std::size_t size)
	{
		if (!address)
			return;

		mtx.lock();
		copy_memory m = { 0 };
		m.called = TRUE;
		m.address = address;
		m.protection = page_protection;
		m.size = size;
		m.change_protection = TRUE;
		m.get_pid = FALSE;
		m.get_base = FALSE;
		m.read = FALSE;
		m.read_string = FALSE;
		m.write = FALSE;
		m.write_string = FALSE;
		m.alloc_memory = FALSE;
		m.protection_old = 0;
		m.get_thread_context = FALSE;
		m.set_thread_context = FALSE;

		auto map_view = (copy_memory*)MapViewOfFile(memory_write, FILE_MAP_WRITE, 0, 0, 4096);
		if (!map_view)
		{
			std::cout << "[!] map_view failed" << std::endl;
			return;
		}

		RtlCopyMemory(map_view, &m, sizeof(m));
		call_hook();

		clear_map(map_view);
		UnmapViewOfFile(map_view);
		mtx.unlock();
	}
