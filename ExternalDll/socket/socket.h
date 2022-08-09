#pragma once
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")




#pragma warning(disable: 4996)


class MYsocket
{
private:
	SOCKET connection = 0;
	u_short server_port;
	const char* server_ip;

public:
	MYsocket(u_short server_port, const char* server_addr) :server_port(server_port), server_ip(server_addr) {};

	bool MYconnect();
	bool MYdisconnect();


	size_t MYrecv_simple(unsigned char* buff, size_t buff_size);
	size_t MYsend_simple(char* buff, int len);

};

NTKERNELAPI
PPEB
PsGetProcessPeb(
	IN PEPROCESS Process
);


NTSTATUS NTAPI MmCopyVirtualMemory
(
	PEPROCESS SourceProcess,
	PVOID SourceAddress,
	PEPROCESS TargetProcess,
	PVOID TargetAddress,
	SIZE_T BufferSize,
	KPROCESSOR_MODE PreviousMode,
	PSIZE_T ReturnSize
);


NTSTATUS NTAPI ZwProtectVirtualMemory(
	HANDLE ProcessHandle,
	PVOID * BaseAddress,
	PULONG ProtectSize,
	ULONG NewProtect,
	PULONG OldProtect
);

NTSYSAPI
PIMAGE_NT_HEADERS
NTAPI
RtlImageNtHeader(PVOID Base);

NTSTATUS ZwQuerySystemInformation(ULONG InfoClass, PVOID Buffer, ULONG Length, PULONG ReturnLength);
NTKERNELAPI
PVOID
NTAPI
RtlFindExportedRoutineByName(
	_In_ PVOID ImageBase,
	_In_ PCCH RoutineNam
);

