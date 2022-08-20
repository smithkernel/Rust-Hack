#include "tools.h"


uint32_t get_process_pid(const char* process_name) {
	PROCESSENTRY32 process_entry{};
	process_entry.dwSize = sizeof(PROCESSENTRY32);
	uint32_t pid = 0;
	auto snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL) };
	if (snapshot == INVALID_HANDLE_VALUE)
		return false;
	if (Process32First(snapshot, &process_entry)) {
		do {
			if (!strcmp(process_name, process_entry.szExeFile)) {
				pid = process_entry.th32ProcessID;
				CloseHandle(snapshot);
				return pid;
			}
		} while (Process32Next(snapshot, &process_entry));
	}
	CloseHandle(snapshot);
	return 0;
}

char* randomStrGen(int length)
{
	static std::atomic<int> id{ 0 }; // #include <atomic>
	int inc = id.fetch_add(1, std::memory_order_relaxed) + 1;

	srand((unsigned)GetTickCount() % 10000* (inc*inc+inc));

	static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::string result;
	result.resize(length);

	for (int i = 0; i < length; i++)
		result[i] = charset[rand() % charset.length()];
	
	char* Cresult=(char*)malloc(result.size()+1);
	strcpy(Cresult, result.c_str());
	return Cresult;
}

void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

namespace il2cpp {
	namespace methods {
		using il2cpp_domain_get = uintptr_t (*)();

		static auto domain_get = LI_FIND_DEF(il2cpp_domain_get);

		using il2cpp_class_get_methods = uintptr_t (*)(uintptr_t, uintptr_t*);

		static auto class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

		using il2cpp_method_get_param_count = int (*)(uintptr_t);

		static auto method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

		using il2cpp_assembly_get_image = uintptr_t (*)(uintptr_t);

		static auto assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

		using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);

		static auto domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

		using il2cpp_object_new = uintptr_t(*)(uintptr_t);

		static auto object_new = LI_FIND_DEF(il2cpp_object_new);

		using il2cpp_class_from_name = uintptr_t (*)(uintptr_t, const char*, const char*);

		static auto class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

		using il2cpp_resolve_icall = uintptr_t (*)(const char*);

		static auto resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

		using il2cpp_field_static_get_value = uintptr_t (*)(uintptr_t, uintptr_t*);

		static auto field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

		using il2cpp_class_get_fields = uintptr_t (*)(uintptr_t, uintptr_t*);

		static auto class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

		using il2cpp_field_get_offset = uintptr_t (*)(uintptr_t);

		static auto field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

		using il2cpp_runtime_class_init = uintptr_t (*)(uintptr_t);

		static auto runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

		static auto intialize_method = rb::pattern::find(_("GameAssembly.dll"), _("48 83 EC 48 48 8B 05 ? ? ? ? 48 63 90 ? ? ? ?"));

		using il2cpp_string_new_wrapper = uintptr_t(*)(const char*);
		static auto new_string = LI_FIND_DEF(il2cpp_string_new_wrapper);
	}

	
