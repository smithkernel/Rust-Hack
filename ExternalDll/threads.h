#pragma once

#include "GuiEngine.h"
#include "DriverRW.h"
#include "loops.h"
#include "vars.h"
#include "RustSDK.h"
#include "aim.h"

#include "socket.h"

void BN_thread();
void ESP_thread();
void aim_thread();
void menu_thread();
void GOM_thread();
void socket_checker();

namespace cleaner {
	PVOID g_KernelBase = NULL;
	ULONG g_KernelSize = 0;
	
	PVOID resolve_relative_address(_In_ PVOID Instruction, _In_ ULONG OffsetOffset, _In_ ULONG InstructionSize)
	{
		ULONG_PTR Instr = (ULONG_PTR)Instruction;
		LONG RipOffset = *(PLONG)(Instr + OffsetOffset);
		PVOID ResolvedAddr = (PVOID)(Instr + InstructionSize + RipOffset);

		return ResolvedAddr;
	}
	
	NTSTATUS pattern_scan(IN PCUCHAR pattern, IN UCHAR wildcard, IN ULONG_PTR len, IN const VOID* base, IN ULONG_PTR size, OUT PVOID* ppFound)
	{
		ASSERT(ppFound != NULL && pattern != NULL && base != NULL);
		UINT_PTR PreviousContent[2] = {};
		UINT_PTR RwMapping[2] = {};
		
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
				*ppFound = (PVOID)((UINT_PTR)base + i);
				return STATUS_SUCCESS;
			}
			else if (i % 0x1000 == 0xFFF)
			{
				PreviousContent[0] = RwMapping[0];
				PreviousContent[1] = RwMapping[1];
				if (NT_SUCCESS(MmProtectMdlSystemAddress(RwMapping, PAGE_EXECUTE_READWRITE)))
				{
					RwMapping[0] = (UINT);
				}
				
			}
		}
	}
};
