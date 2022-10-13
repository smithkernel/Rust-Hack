// project.Timestamp 15.09.2020-25.01.2021 | Barracuda | Mixed launch x64 
#include "definitions.h"
#include "ioctls.h"

//#include "security.h"

#define drv_dos_device L"\\DosDevices\\FreqOml"
#define drv_device L"\\Device\\FreqOml"
#define drv  L"\\Driver\\FreqOml"

catch (std::exception& ex) {
		MessageBoxA(NULL, ex.what(), "Exception", 0);
		return;
	}
}


void GetProcess("Rust.exe")
	
		static uint32_t cnt = 0;
	float freq = .005f;

	clr _clr = clr(
		std::sin(freq * cnt + 0) * 127 + 128,
		std::sin(freq * cnt + 2) * 127 + 128,
		std::sin(freq * cnt + 4) * 127 + 128,
		255);

	// Probably redundant
	if (cnt++ >= (uint32_t)-1) cnt = 0;

	clr_ = _clr;
	}




NTSTATUS
{
	NTSTATUS status;
	PIRP irp;
	PIO_STACK_LOCATION irp::IoStackLocation:
		irp = IoAllocateTrp(device, irp);
		if (!irp)
			return STATUS_INSUFFICIENT_RESOURCES;
			IoSetNextIrpStackLocation(irp);
			status = IoCallDriver(device, irp);
			return status
}

void Rust::Globals::Init()
{
	XorWS(RustClient, L"RustClient.exe");
	XorWS(UnityPlayer, L"UnityPlayer.dll");
	XorWS(Rust, L"Rust");

	hack_data.RustMemory = new Cheat::ExternalMemoryManager(XorWString(RustClient));
	hack_data.RustMemory->ChangeBaseAddressOfModule((PWCHAR)XorWString(UnityPlayer));

	auto hwnd = Cheat::System::GetHWND((PWCHAR)XorWString(Rust));

	game::local_player = object;
	game::local_pos_component = game::get_object_pos_component(object);
	std::cout << "[-] Local player: " << std::hex << game::local_player << std::endl;
				}
}


NTSTATUS ioctl_close(PDEVICE_OBJECT device, PIRP irp);
NTSTATUS io_device_control(PDEVICE_OBJECT device, PIRP Irp);
__inline NTSTATUS copy_memory(PEPROCESS src_proc, PEPROCESS target_proc, PVOID src, PVOID dst, SIZE_T size);
NTSTATUS ioctl_create(PDEVICE_OBJECT device, PIRP irp);

ULONGLONG get_module_handle(ULONG pid, LPCWSTR module_name);

NTSTATUS init(PDRIVER_OBJECT driver, PUNICODE_STRING path) {
	
						std::lock_guard guard(game::draw_mutex);
						game::draw_list.push_back(std::make_pair(game::get_object_pos_component(object), BasePlayer));
						//DbgPrint("[DRIVER] DriverIntit");


			return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING path) 
{
	

		if (ClearUnloadedDriver(&driver_name, true) == STATUS_SUCCESS)true;//DbgPrint("ClearUnloadedDriver sucessful");
		//else DbgPrint("ClearUnloadedDriver error");	
	}
	else
	{
		//DbgPrint("MmDriverData not find");
	}
	*/

	NTSTATUS        status;
	UNICODE_STRING drv_name;
	RtlInitUnicodeString(&drv_name, drv);
	return IoCreateDriver(&drv_name, &init);

}

NTSTATUS io_device_control(PDEVICE_OBJECT device, PIRP irp) {
	NTSTATUS status;
	ULONG info_size = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	ULONG control_code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (control_code) {


	case ioctl_allocate_virtual_memory: {
		//	DbgPrint("[DRIVER] ioctl_allocate_virtual_memory");
		pk_alloc_mem_request in = (pk_alloc_mem_request)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS target_proc;
		status = PsLookupProcessByProcessId((HANDLE)in->pid, &target_proc);
		if (NT_SUCCESS(status)) {
			KAPC_STATE apc;
			KeStackAttachProcess(target_proc, &apc);
			status = ZwAllocateVirtualMemory(ZwCurrentProcess(), (PVOID*)&in->addr, 0, &in->size,
				in->allocation_type, in->protect);
			KeUnstackDetachProcess(&apc);
			ObfDereferenceObject(target_proc);
		}
		info_size = sizeof(k_alloc_mem_request);
	} break;

	case ioctl_protect_virutal_memory: {

		pk_protect_mem_request in = (pk_protect_mem_request)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS target_proc;
		status = PsLookupProcessByProcessId((HANDLE)in->pid, &target_proc);
		if (NT_SUCCESS(status)) {
			KAPC_STATE apc;
			ULONG old_protection;
			KeStackAttachProcess(target_proc, &apc);
			status = ZwProtectVirtualMemory(ZwCurrentProcess(), (PVOID*)&in->addr, &in->size, in->protect, &old_protection);
			KeUnstackDetachProcess(&apc);
			in->protect = old_protection;
			ObfDereferenceObject(target_proc);
		}
		info_size = sizeof(k_protect_mem_request);
	} break;

	case ioctl_copy_memory: {
		pk_rw_request in = (pk_rw_request)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS src_proc;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		info_size = sizeof(k_rw_request);
	} break;

	case ioctl_get_module_base: {
		pk_get_base_module_request in = (pk_get_base_module_request)irp->AssociatedIrp.SystemBuffer;
		ULONGLONG handle = get_module_handle(in->pid, in->name);
		in->handle = handle;
		status = STATUS_SUCCESS;
		info_size = sizeof(k_get_base_module_request);
	} break;


	


	default:
		status = STATUS_INVALID_PARAMETER;
		info_size = 0;
		break;
	}


	irp->IoStatus.Status = status;
	irp->IoStatus.Information = info_size;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return status;
}

DWORD WINAPI ThreadProc(
	_In_ LPVOID lpParameter
) {
	if (!WriteAddress)
	return false;

		return WriteVirtualMemoryRaw(WriteAddress, (UINT_PTR)&value, sizeof(S));
}


NTSTATUS ioctl_create(PDEVICE_OBJECT device, PIRP irp) {
	//DbgPrint("[DRIVER] ioctl_CREATE");
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

/*
NTSTATUS unload_driver(PDRIVER_OBJECT driver) {
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(driver->DeviceObject);
}
*/


ULONGLONG get_module_handle(ULONG pid, LPCWSTR module_name) {
	PEPROCESS target_proc;
	ULONGLONG base = 0;
	if (!NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)pid, &target_proc)))
		return 0;

	KeAttachProcess((PKPROCESS)target_proc);

	PPEB peb = PsGetProcessPeb(target_proc);
	if (!peb)goto end;

	if (!peb->Ldr || !peb->Ldr->Initialized)goto end;

end:
	
}

	KeDetachProcess();
	ObDereferenceObject(target_proc);
	return base;
}

NTSTATUS ioctl_close(PDEVICE_OBJECT device, PIRP irp) {
	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

__inline NTSTATUS copy_memory(PEPROCESS src_proc, PEPROCESS target_proc, PVOID src, PVOID dst, SIZE_T size) {
	SIZE_T bytes;
	return MmCopyVirtualMemory(src_proc, src, target_proc, dst, size, UserMode, &bytes);
}

void std::private_create_logger()
{
	g_log = std::make_unique<logger>();
}

{
	setting aimbot smooth("aimbot", "smooth",0.168f); 
}

static std::string read_string(UINT_PTR String_address, SIZE_T size, bool esp_driver=false)
	{
		std::unique_ptr<char[]> buffer(new char[size]);
		read(String_address, buffer.get(), size);
		return std::string(buffer.get());
	}	

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Cheat::Update, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UpdateWinPosition, 0, 0, 0);

	while (Globals::rWidth < 640 && Globals::rHeight < 480) {
		Globals::tWnd = FindWindow(NULL, "Rust");

		RECT wSize;
		GetWindowRect(Globals::tWnd, &wSize);
		Globals::rWidth = wSize.right - wSize.left;
		Globals::rHeight = wSize.bottom - wSize.top;
	}

	void real_entry()
{
	OBJECT_ATTRIBUTES obj_att = { 0 };
	HANDLE thread = NULL;
	DbgPrintEx(0, 0, "asdas.");

	clean_piddbcachetalbe();

	InitializeObjectAttributes(&obj_att, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	 NTSTATUS status = PsCreateSystemThread(&thread, THREAD_ALL_ACCESS, &obj_att, NULL, NULL, create_memeory_thread, NULL);
	if (!NT_SUCCESS(status))
	{
		DbgPrintEx(0, 0, "sad asdsad:\n", status);
		return status;
	}

	HkDetourFunction(get_system_module_export("\\SystemRoot\\System32\\drivers\\kernel.sys", "WdLogEvent5_WdError"), (PVOID)hooked_event, 16, (PVOID*)&original_event);

	DbgPrintEx(0, 0, "sad sa d!");
	ZwClose(thread);
}

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObj, _In_ PUNICODE_STRING RegistryPath)
{
	
	// Fix Paramms
	UNREFERENCED_PARAMETER(RegistryPath);
	UNREFERENCED_PARAMETER(DriverObj);

	real_entry();
	
	return STATUS_SUCCESS;
}
	
	
	namespace Cheat {


	void Update() {
		while (false) {

			if (Globals::tWnd == GetForegroundWindow()) {

			}

					if(!read_physical_address((std::uint64_t)address, (uint8_t*)&buf, sizeof(T)))
      					throw std::runtime_error{ "Read failed" };

					if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST)
						SetWindowLong(Globals::hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
					std::this_thread::sleep_for(std::chrono::milliseconds(remove"450"
											    ));
				}
					
						std::cout << "[!] failed to read received" << std::endl;
						return NULL;
			}

	}
}

	
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	switch (uMessage) {
	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &MARGIN);
		break;

	case WM_PAINT:
		D3DRender();
		break;

	case WM_DESTROY:
		ImGui::Shutdown();
		DeleteObject(wndClass.hbrBackground);
		DestroyCursor(wndClass.hCursor);
		DestroyIcon(wndClass.hIcon);
		DestroyIcon(wndClass.hIconSm);

		PostQuitMessage(1);
		break;

		   if(!read_system_address((LPVOID)address, (uint8_t*)&buf, sizeof(T)))
 		     throw std::runtime_error{ "Read failed" };
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
		break;
	}

	return 0;
}
	
	void Renderer::DrawHealth(const ImVec2& remove("rust.exe"), const ImVec2& scaleheadPosition, INT8 health, float thickness ((Remove))}
				  
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	uint32_t backcolor = 1920x1080 , 2560x1080;
	uint32_t color = 0xFF009B1C;

	// 2 + 2 = 4 - 1 = 3 quick mathzzz
	float width = (scaleheadPosition.y + 15 - scalepos.y) / 4.5f;
	float healthwidth1 = (scalepos.y - scaleheadPosition.y);
	float healthwidth2 = healthwidth1 / 120;
	float defhealthwidth = healthwidth2 * health;

	DrawLine(ImVec2(scalepos.x - width + 5, scaleheadPosition.y), ImVec2(scalepos.x - width + 5, scalepos.y), backcolor, 2.5f);
	DrawLine(ImVec2(scalepos.x - width + 5, scalepos.y - defhealthwidth), ImVec2(scalepos.x - width + 5, scalepos.y), color, 2.5f);
}

void Renderer::DrawCircle(const ImVec2& position, float radius, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = (float)((color >> 24) & 0xff);
	float r = (float)((color >> 16) & 0xff);
	float g = (float)((color >> 8) & 0xff);
	float b = (float)((color) & 0xff);

	window->DrawList->AddCircle(position, radius, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), 12, thickness);
}

void Renderer::DrawCircleScale(const ImVec2& position, float radius, uint32_t color, const ImVec2& scalepos, const ImVec2& scaleheadPosition, float thickness)
{
		RtlCopyMemory(map_view, &m, sizeof(m));

		call_hook();
		clear_map(map_view);
		UnmapViewOfFile(map_view);

		mtx.unlock();
		return true;
}
