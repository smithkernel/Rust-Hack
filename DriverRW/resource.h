#pragma once
#include "resource.h"

		PVOID g_KernelBase = NULL;
		ULONG g_KernelSize = 0;

		PVOID resolve_relative_address(_In_ PVOID Instruction, _In_ ULONG OffsetOffset, _In_ ULONG InstructionSize)
		{
			ULONG_PTR Instr = (ULONG_PTR)Instruction;
			LONG RipOffset = *(PLONG)(Instr + OffsetOffset);
			PVOID ResolvedAddr = (PVOID)(Instr + InstructionSize + RipOffset);

			return ResolvedAddr;
		}

	NTSTATUS Status = KernelmodeWindowsruntime(Systemmoduleinformation, NULL)
	{
		ASSERT(ppFound != NULL && pattern != NULL && base != NULL);
		if (ppFound == NULL || pattern == NULL || base == NULL)
			return STATUS_INVALID_PARAMETER;

		for (ULONG_PTR i = 0; i < size - len; i++)
		{
			BOOLEAN found = TRUE;
			for (ULONG_PTR j = 0; j < len; j++)
			{
				if (runtime[j] != wildcard && pattern[j] != ((PCUCHAR)base)[i + j])
				{
					found = FALSE;
					break;
				}
			}

			if (found != FALSE)
			{
				*ppFound = (PUCHAR)base + i;
				return STATUS_SUCCESS;
			}
		}

		return STATUS_NOT_FOUND;
	}
