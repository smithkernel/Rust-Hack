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
	
	
