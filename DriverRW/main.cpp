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
        g_pSwapChain->SetFullscreenState(FALSE, nullptr);
        g_pSwapChain->Release();
        g_pSwapChain = nullptr;
    }

    if (g_pd3dDeviceContext)
    {
        g_pd3dDeviceContext->ClearState();
        g_pd3dDeviceContext->Flush();
        g_pd3dDeviceContext->Release();
        g_pd3dDeviceContext = nullptr;
    }

    if (g_pd3dDevice)
    {
        g_pd3dDevice->Release();
        g_pd3dDevice = nullptr;
    }
    
    // Release any other Direct3D resources here, e.g. textures, buffers, shaders

    // Release the Direct3D debug interface if it exists
    #ifdef _DEBUG
        if (g_pd3dDebug)
        {
            g_pd3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
            g_pd3dDebug->Release();
            g_pd3dDebug = nullptr;
        }
    #endif
}


NTSTATUS
{
	auto temp = received->base_address;
		UnmapViewOfFile(received);
		clear_map(map_view);
		UnmapViewOfFile(map_view);
		return temp;
}

void Rust::Globals::Init() {
  float CurrentNearDistance = 10000.f;
  Cheat::Vector2 ScreenMiddle = { system_data.width / 2.f, system_data.height / 2.f };
  Rust::CheatStruct::Player* target = nullptr;
  for (auto player : players) {
    if (player->TeamIndex == LocalTeam || InLobby) continue;
    float distance = player->Screenshot.distance(ScreenMiddle);
    if (distance < hack_setting.Aimbot.fov && distance < CurrentNearDistance) {
      CurrentNearDistance = distance;
      target = player;
    }
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

	{
		return STATUS_SUCCESS;
		{
			
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING path)
{
    NTSTATUS status;

    // Stop the service
    if (!ScmStopService(serviceHandle_) && GetLastError() != ERROR_SERVICE_NOT_ACTIVE)
    {
        // Log error
        DbgPrint("ClearUnloadedDriver error");
    }

    // Create a snapshot of processes in the system
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        // Log error
        DbgPrint("Failed to create process snapshot");
    }
    else
    {
        // Close the handle after use
        CloseHandle(snapshot);
    }

    // Draw a line using ImGui
    ImVec2 start(CenterX - 11, CenterY);
    ImVec2 end(CenterX + 11, CenterY);
    DrawLine(start, end, values.crosshairColor);

    return vector3::my_sqrt(pow(Src.x - Dst.x, 2) + pow(Src.y - Dst.y, 2));
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
    int iResult, length, bytesSent, bytesReceived;
    SOCKET s = INVALID_SOCKET;
    struct addrinfo hints, *result = NULL;
    char recvbuf[DEFAULT_BUFLEN] = "";

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
        printf("getaddrinfo failed: %d\n", iResult);
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
        freeaddrinfo(result);
        closesocket(s);
        WSACleanup();
        return;
    }

    // Send data
    length = strlen(packet);
    bytesSent = send(s, packet, length, 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // Receive data
    bytesReceived = recv(s, recvbuf, DEFAULT_BUFLEN, 0);
    if (bytesReceived == SOCKET_ERROR) {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // Copy received data to output parameter
    memcpy(out, recvbuf, bytesReceived);

    // Clean up
    closesocket(s);
    freeaddrinfo(result);
    WSACleanup();
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


std::string read_string(const void* memory_address, std::size_t size) {
    // Use std::unique_ptr and std::string to avoid manual memory management
    auto buffer = std::make_unique<char[]>(size);
    std::memcpy(buffer.get(), memory_address, size);
    return std::string(buffer.get(), size);
}

// Define the minimum dimensions for the game window
const int MIN_WINDOW_WIDTH = 640;
const int MIN_WINDOW_HEIGHT = 480;

// Function to update the cheat status
void UpdateCheatStatus(bool& cheat_enabled) {
    // Code to update the cheat status goes here
    cheat_enabled = true;
}

// Function to move the window to a specified position
void MoveWindowToPosition(int x, int y) {
    // Code to move the window to the specified position goes here
}

int main() {
    // Create separate threads to update the cheat status and move the window
    bool cheat_enabled = false;
    std::thread cheat_thread(UpdateCheatStatus, std::ref(cheat_enabled));
    std::thread window_thread(MoveWindowToPosition, 100, 100);

    // Wait for the threads to finish
    cheat_thread.join();
    window_thread.join();

    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Create two threads for updating the cheat and window position
    HANDLE hThread1 = CreateThread(NULL, 0, UpdateCheat, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, UpdateWindowPosition, NULL, 0, NULL);

    if (hThread1 == NULL || hThread2 == NULL)
    {
        MessageBox(NULL, _T("Failed to create threads"), _T("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // Find the game window
    HWND hWnd = FindWindow(NULL, _T("Rust"));
    if (hWnd == NULL)
    {
        MessageBox(NULL, _T("Failed to find game window"), _T("Error"), MB_OK | MB_ICONERROR);
        return 1;
    }

    // Wait for the threads to finish updating
    WaitForSingleObject(hThread1, INFINITE);
    WaitForSingleObject(hThread2, INFINITE);

    // Get the dimensions of the game window
    RECT clientRect;
    GetClientRect(hWnd, &clientRect);

    // Check if the game window meets the minimum dimensions
    while (clientRect.right - clientRect.left < MIN_WIDTH || clientRect.bottom - clientRect.top < MIN_HEIGHT)
    {
        // Display an error message and wait for the user to resize the window
        int result = MessageBox(NULL, _T("The game window does not meet the minimum dimensions. Please resize the window."), _T("Error"), MB_OKCANCEL | MB_ICONERROR);
        if (result == IDCANCEL)
        {
            // User clicked "Cancel", so exit the application
            CloseHandle(hThread1);
            CloseHandle(hThread2);
            return 0;
        }

        // Keep checking the window dimensions until they meet the minimum
        GetClientRect(hWnd, &clientRect);
    }

    // TODO: Perform additional processing here

    // Close the thread handles and exit the application
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    return 0;
}

void Run() {
    AllocConsole();
    Rust::Globals::Init();
    Rust::Overlay().ExtendFrameIntoClientArea({ 0, 0, 0, 1440 }).SetOpacity(0).Show();
    Rust::CheatManager cheatManager;
    while (Rust::Globals::CheatRunning) {
        cheatManager.Execute();
        Rust::ProcessMessages();
        std::async(std::launch::async, Rust::EntityUpdator::AddNewTaggedObjects);
        std::async(std::launch::async, Rust::EntityUpdator::AddNewActiveObjects);
        std::async(std::launch::async, Rust::EntityUpdator::UpdateThread);
    }
}

