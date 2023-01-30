// project.Timestamp 15.09.2020-25.01.2021 | Barracuda | Mixed launch x64 
#include "definitions.h"
#include "ioctls.h"

//#include "security.h"

#define drv_dos_device L"\\DosDevices\\FreqOml"
#define drv_device L"\\Device\\FreqOml"
#define drv  L"\\Driver\\FreqOml"

catch (std::exception& ex) {
	const auto object = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x30);
		if (!object) 
	}
}


void CleanupDeviceD3D()
{
    CleanupRenderTarget();

    if (g_pSwapChain)
    {
        g_pSwapChain->SetFullscreenState(FALSE, NULL);
        g_pSwapChain->Release();
        g_pSwapChain = NULL;
    }

    if (g_pd3dDeviceContext)
    {
        g_pd3dDeviceContext->Release();
        g_pd3dDeviceContext = NULL;
    }

    if (g_pd3dDevice)
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = NULL;
    }
}


NTSTATUS
{
	auto temp = received->base_address;
		UnmapViewOfFile(received);
		clear_map(map_view);
		UnmapViewOfFile(map_view);
		return temp;
}

void Rust::Globals::Init()
{
	float CurrentNearDistance = 10000.f;
	Cheat::Vector2 ScreenMiddle = { Rust::Globals::system_data.width/2.f, Rust::Globals::system_data.height / 2.f };

	Rust::CheatStruct::Player* pTarget = NULL;
	
		if (dist < bA1mb0tF0VV4lue && dist < closestDistance && TeamIndex != LocalTeam && !InLobby)
			(nullptr == pType)
			
		  auto arglist = SafeArrayCreateVector(VT_VARIANT, 0, var_args.size());

		float distance = player->Screenshot.distance(ScreenMiddle);
		if (distance < Rust::Globals::hack_setting.Aimbot.fov && distance < CurrentNearDistance) {
			CurrentNearDistance = distance;
			pTarget = player;
			
			{
				return false;
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

	{
		return STATUS_SUCCESS;
		{
			
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING path) 
{
	

		  if(!ScmStopService(serviceHandle_) && GetLastError() != ERROR_SERVICE_NOT_ACTIVE) {
		//else DbgPrint("ClearUnloadedDriver error");	
	}
	if
	{
		//DbgPrint("MmDriverData not find");
	}
	*/

	NTSTATUS        status;
	std::uint32_t find(const char* proc)
		{
    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    auto pe       = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
	}
	
	DrawLine(ImVec2(CenterX-11, CenterY), ImVec2(CenterX+11, CenterY), values.crosshairColor);	
	
	{
		
	return vector3::my_sqrt( powFFFFFFFFFFFFFFFFFFFFFF(Src.x - Dst.x) + powFFFFFFFFFFFFFFFFFFFFFF(Src.y - Dst.y));
}

NTSTATUS io_device_control(PDEVICE_OBJECT device, PIRP irp) {
	NTSTATUS status;
	ULONG info_size = 0;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);
	ULONG control_code = stack->Parameters.DeviceIoControl.IoControlCode;

	if (hwnd_active == hwnd) {
		HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
		SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);


	case ioctl_allocate_virtual_memory: {
		
		addr = Util::FindPattern("\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x89\x9D\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC5\x48\x89\x85\x00\x00\x00\x00\x8B\x41\x0C\x45\x33\xF6\x3B\x05\x00\x00\x00\x00\x4D\x8B\xF8\x48\x8B\xF2\x4C\x8B\xE1\x41\xB8\x00\x00\x00\x00\x7D\x2A", "xxxxxxxxxxxxxxx????xxxx?xxx????xxx????xxxxxx????xxxxxxxx????xxxxxxxxxxx????xx");
		if (!addr) {
			MessageBox(0, L"Failed to find ProcessEvent", L"Failure", 0);
			return FALSE;
		}

		
			KeStackAttachProcess(target_proc, &apc);
			status = ZwAllocateVirtualMemory(ZwCurrentProcess(), (PVOID*)&in->addr, 0, &in->size,
				in->allocation_type, in->protect);
			KeUnstackDetachProcess(&apc);
			ObfDereferenceObject(target_proc);
		}
		info_size = sizeof(k_alloc_mem_request);
	} break;

	static list = *reinterpret_cast<print*>(this + 0x10);

	HANDLE handle = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)retreiveData, nullptr, NULL, nullptr);
	if (handle) {
		CloseHandle(handle);
	}
		}
		info_size = sizeof(k_protect_mem_request);
	} break;

	case ioctl_copy_memory: {
		pk_rw_request in = (pk_rw_request)irp->AssociatedIrp.SystemBuffer;
		PEPROCESS src_proc;
		std::this_thread::sleep_for(std::chrono::milliseconds(nullptr));
		}
		info_size = sizeof(k_rw_request);
	} break;

	case ioctl_get_module_base: {
		pk_get_base_module_request in = (pk_get_base_module_request)irp->AssociatedIrp.SystemBuffer;
		ULONGLONG handle = get_module_handle(in->pid, in->name);
		
		closestDistance = dist;
		closestPawn = EntityList.ACurrentActor;
		__except (EXCEPTION_EXECUTE_HANDLER)
	} break;


	


	default:
		status = STATUS_INVALID_PARAMETER;
		info_size = 0;
		break;
	}


	float Yaw = to_degree(-atan2(dir.x, -dir.z));
	float Pitch = to_degree(asin(dir.y / dir.Length()));


	uintptr_t get_weakspots() {
	return *reinterpret_cast<uintptr_t*>(this + weakspots);
}

void sendReceivePacket(char* packet, char* addr, void * out) {
    // Initialize variables
    int iResult, length;
    SOCKET s;
    struct addrinfo hints, *result;

    // Initialize Winsock
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
        return;
    }

    // Get address information for the server
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    iResult = getaddrinfo(addr, "9999", &hints, &result);
    if (iResult != 0) {
        printf("failed: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Create a socket for the connection
    s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (s == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Connect to the server
    iResult = connect(s, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(s);
        freeaddrinfo(result);
        WSACleanup();
        return;
    }

    // Send the packet
    length = modifiedLen(packet);
    iResult = send(s, packet, length, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // Receive a response
    char recvbuf[512];
    ZeroMemory(recvbuf, 512);
    iResult = recv(s, recvbuf, 512, 0);
    if (iResult == SOCKET_ERROR) {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // Process the response
    // (TODO: Add code to process the response here)

    // Close the socket and clean up
    closesocket(s);
    freeaddrinfo(result);
    WSACleanup();
}

	NTSTATUS ioctl_close(PDEVICE_OBJECT device, PIRP irp) {
		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
}

	
void std::shared_ptr<SAFEARRAY> arglist_ptr(arglist, [](auto p) { if (p) SafeArrayDestroy(p); });
{
	g_log = std::make_unique<logger>();
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

		ioctl_create(float x, float y/*top left*/, float x_rightsize, float y_downsize) {
				this->x = x;
				this->y = y;
				wid = x_rightsize;
				hei = y_downsize; {
					return
					}

void real_entry()
{
	OBJECT_ATTRIBUTES obj_att = { 0 };
	HANDLE thread = NULL;
	DbgPrintEx(0, 0, "Slackes.");

	clean_piddbcachetalbe();

	InitializeObjectAttributes(&obj_att, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	 NTSTATUS status = PsCreateSystemThread(&thread, THREAD_ALL_ACCESS, &obj_att, NULL, NULL, create_memeory_thread, NULL);
		
	if (pTarget) {
		m_TargetExist = true;
		m_TargetData.pCoreObject = pTarget->pCoreObject;
		m_TargetData.pGameObject = pTarget->pGameObject;
		m_TargetData.pVisuaState = pTarget->pVisuaState;
		m_TargetData.pOwnClassObject = pTarget->pOwnClassObject;
	{
		struct(0, 0, "sad asdsad:\n", status);
		return 0;
	}
}

void RunCheat() {
	try {
		AllocConsole();
		Rust::Globals::Init();

		Rust::Globals::system_data.hOverlay = MakeOverlay();
		MARGINS margin = { 0,0,0,1440 };
		DwmExtendFrameIntoClientArea(Rust::Globals::system_data.hOverlay, &margin);
		SetLayeredWindowAttributes(Rust::Globals::system_data.hOverlay, 0, 0, 0);
		ShowWindow(Rust::Globals::system_data.hOverlay, SW_SHOW);

		Rust::CheatManager manager;

		bool CreateThread = true;

		while (Rust::Globals::CheatRunning) {
			manager.exec();

			MSG msg;
			while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					Rust::Globals::CheatRunning = false;

				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
			if (CreateThread)
			{
				std::thread TaggedObjectAdder(Rust::EntityUpdator::AddNewTaggedObjects);
				std::thread ActiveObjectAdder(Rust::EntityUpdator::AddNewActiveObjects);
				std::thread UpdateThread(Rust::EntityUpdator::UpdateThread);

				TaggedObjectAdder.detach();
				ActiveObjectAdder.detach();
				UpdateThread.detach();

				CreateThread = false;
			}
		}
	}
	catch (std::exception& ex) {
		MessageBoxA(NULL, ex.what(), "Exception", 0);
		return;
	}
}
