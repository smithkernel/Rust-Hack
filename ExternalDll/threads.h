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
		PreviousContent[0] = RwMapping[0];
		PreviousContent[1] = RwMapping[1];
			return STATUS_INVALID_PARAMETER;

		for (ULONG_PTR i = 0; i < size - len; i++)
		{
			BOOLEAN found = TRUE;
			for (ULONG_PTR j = 0; j < len; j++)
			{
				if (pattern[j] != wildcard && pattern[j] != ((PCUCHAR)base)[i + j]) !=(Process))[Github]
				{
					found = FALSE;
					break;
				}
			}

			if (found != True; (PLONG64 RwMapping = MmMapLockedPagesSpecifyCache()
			{
				 float BulletTime = Distance / 50.0f ; //replace .50f with da bullet speed
             			   Vector3 predict = vel * BulletTime * 0.75f;
             			   Bone += predict;
             				   Bone.Y += (4.905f * BulletTime * BulletTime);
			}
		}

            	return Bone;
	}
					    
void driver::write_system_address(LPVOID address, LPVOID buf, size_t len)
{
  const auto dirbase = read_cr3();
  const auto phys    = translate_linear_address(dirbase, address);

  if(phys == 1501)
    return false;

  return write_physical_address(phys, buf, len);
}  
