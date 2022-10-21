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

namespace mem {
	uintptr_t game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	uintptr_t unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}


static void Driver_hook()
{
	static hook_virtual_function(const char* classname, const char* function_to_hook, void* target, const char* name_space);
	static const auto control = static_cast<uint64_t(__stdcall*)()>(control_function);
	control();
	
	if(FAILED(hResult)) {
		m_lastError = L"Failed to create glyph sheet texture";
	}
	
	return true;
}


