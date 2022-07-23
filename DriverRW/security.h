#include <ntdef.h>
#include <ntifs.h>
#include <ntddk.h>
#include <WinDef.h>

#include "definitions.h"



   void clearCache(UNICODE_STRING DriverName, ULONG timeDateStamp);
   NTSTATUS ClearUnloadedDriver(
	   _In_ PUNICODE_STRING	DriverName,
	   _In_ BOOLEAN			AccquireResource
   );

   NTSTATUS FindMmDriverData(VOID);

bool utils::ReadFileToMemory(const std::string& file_path, std::vector<uint8_t>* out_buffer)
{
	std::ifstream file_ifstream(file_path, std::ios::binary);
	if (!file_ifstream)
		return false;

	out_buffer->assign((std::istreambuf_iterator<char>(file_ifstream)), std::istreambuf_iterator<char>());
	file_ifstream.close();
	return true;
}

bool utils::CreateFileFromMemory(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);
	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();
		return false;
	}
	file_ofstream.close();
	return true;
}

