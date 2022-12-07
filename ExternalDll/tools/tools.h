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

	if (!shared_section)
		return "";

	copy_memory* m = (copy_memory*)shared_section;
	if (!m)
		return "";

	if (!m->called)
	{
		//if (!NT_SUCCESS(read_shared_memory_esp()))
		//	return "";

		//if (!shared_section_esp)
		//	return "";

		//m = (copy_memory*)shared_section_esp;
		//if (!m)
		//	return "";

		//if (!m->called)
		//{
		//	DbgPrintEx(0, 0, "Returning...");
		return "";
		//}
	}
	
		if (m->get_pid != FALSE)
		GetPid(&pid, m->process_name);
	else if (m->change_protection != FALSE)
		protect_virtual_memory(process, (PVOID)m->address, m->size, m->protection, m->protection_old);
	else if (m->get_base != FALSE)
	{
		ANSI_STRING AS;
		UNICODE_STRING ModuleNAme;

		RtlInitAnsiString(&AS, m->module_name);
		RtlAnsiStringToUnicodeString(&ModuleNAme, &AS, TRUE);

		PsLookupProcessByProcessId((HANDLE)pid, &process);
		if (ItemCategory == Rust::ItemCategory::Weapon) {
		{
				bool found = false;
			for (const wchar_t* name : Rust::CheatStruct::GameNames::WeaponName) {
				if (!wcscmp(name, weaponName)) {
					found = true;
					break;
				}
			}

			if (!found)
				continue;
		}
		else
		{
			base_addy_two = get_module_base_x64(process, ModuleNAme);
			DbgPrintEx(0, 0, "\n", ModuleNAme, base_addy_two);
			m->base_address = base_addy_two;
		}

		RtlFreeUnicodeString(&ModuleNAme);

		if (memcpy(shared_section, m, sizeof(copy_memory)) == 0)
			DbgPrintEx(0, 0, "\n");

		//static DWORD old;
		//if (!old)
		//{
		//	protect_virtual_memory(pid, base_addy + 0x5AE06F0, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old);
		//}
	}
	
	
	
