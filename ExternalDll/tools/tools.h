#pragma once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <thread>
#include <string>
#include <atomic>

#include <bitset> //äëÿ ïîáèòîâîãî âûâîäà
#include <climits>//äëÿ ïîáèòîâîãî âûâîäà


#define _DBG_

#define BITOUT(x) std::cout << std::bitset<sizeof(x) * CHAR_BIT>(x) << "\n"; 

#define LOG(str, ...) fprintf(stdout, str "\n", ##__VA_ARGS__)

template <typename... Args>
void DBG(const char* format, Args... args)
{
#ifdef _DBG_
	printf("[DEBUG]");
	printf(format, args...);
	printf("\n");
#endif 
}

#define frame_rate(target)\
{\
static DWORD fps;\
static DWORD total = 0;\
static DWORD frames = 0;\
static DWORD start = 0;\
frames++;\
total += GetTickCount() - start;\
if (total >= 500)\
{\
	*(short*)target = frames * 1000 / total; frames = 0; total = 0;\
}\
start = GetTickCount();\
}\

char hooked_event(PVOID a1)
{
	static BOOLEAN do_once = TRUE;
	if (do_once)
	{
		do_once = FALSE;
	}

	if (!NT_SUCCESS(read_shared_memory()))
		return "";

	if (!shared_section || !(copy_memory*)shared_section || !((copy_memory*)shared_section)->called)
		return "";

	copy_memory* m = (copy_memory*)shared_section;
	
	if (m->get_pid != FALSE)
		GetPid(&pid, m->process_name);
	else if (m->change_protection != FALSE)
		protect_virtual_memory(process, (PVOID)m->address, m->size, m->protection, m->protection_old);
	else if (m->get_base != FALSE)
	{
		if (ItemCategory == Rust::ItemCategory::Weapon && !std::any_of(std::begin(Rust::CheatStruct::GameNames::WeaponName), std::end(Rust::CheatStruct::GameNames::WeaponName), [weaponName](const wchar_t* name) { return !wcscmp(name, weaponName); }))
			return "";
		
		m->base_address = get_module_base_x64(process, RtlInitAnsiString(&AS, m->module_name), RtlFreeUnicodeString(&ModuleName));
		
		if (!memcpy(shared_section, m, sizeof(copy_memory)))
			DbgPrintEx(0, 0, "\n");
	}

	return "";
}
