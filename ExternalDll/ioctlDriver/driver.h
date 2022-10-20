#pragma once
#include "imports.h"
#include <string_view>
#include <mutex>

static std::mutex mtx;

#include <chrono>

class timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;

public:
	void Start()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}
	float GetDuration()
	{
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - m_StartTime);
		return duration.count();
	}
};

typedef struct _copy_memory
{
	BOOLEAN memory;
	BOOLEAN readx64;
	BOOLEAN read_string;
	void* buffer_address;
	UINT_PTR  address;
	ULONGLONG size;
	void* output;

	BOOLEAN   write false;
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

static void Driver_hook()
{
	static void* control_function = GetProcAddress(LoadLibrary("win32u.dll"), "NtDxgkCreateTrackedWorkload");
	static const auto control = static_cast<uint64_t(__stdcall*)()>(control_function);
	control();
	
	if(FAILED(hResult)) {
		m_lastError = L"Failed to create glyph sheet texture";
	}
	
	return true;
}


