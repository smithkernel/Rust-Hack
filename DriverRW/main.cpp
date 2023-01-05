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
        HRESULT hr = g_pSwapChain->Release();
        if (FAILED(hr))
        {
            std::cout << "Error releasing swap chain: " << hr << std::endl;
        }
        g_pSwapChain = NULL;
    }

    if (g_pd3dDeviceContext)
    {
        HRESULT hr = g_pd3dDeviceContext->Release();
        if (FAILED(hr))
        {
            std::cout << "Error releasing device context: " << hr << std::endl;
        }
        g_pd3dDeviceContext = NULL;
    }

    if (g_pd3dDevice)
    {
        HRESULT hr = g_pd3dDevice->Release();
        if (FAILED(hr))
        {
            std::cout << "Error releasing device: " << hr << std::endl;
        }
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

		float distance = player->ScreenHeadPos.distance(ScreenMiddle);
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
	else
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

	static list = *reinterpret_cast<uintptr_t*>(this + 0x10);

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

void set_view_offset(vector3 offset) {
		*reinterpret_cast<vector3*>((uintptr_t)this + viewOffset) = offset;
	}


void sendReceivePacket(char* packet, char* addr, void * out) {
    // Initialize variables
    int iResult, length;
    SOCKET s;
    struct addrinfo hints, *result;
    RECT rc;
    POINT xy;

    // Get address information for the server
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    iResult = getaddrinfo(addr, "9999", &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed: %d\n", iResult);
        exit(1);
    }

    // Create a socket for the connection
    s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (s == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        exit(1);
    }

    // Connect to the server
    iResult = connect(s, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(s);
        freeaddrinfo(result);
        exit(1);
    }

    // Send the packet
    length = modifiedLen(packet);
    iResult = send(s, packet, length, 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(s);
        exit(1);
    }

    // Receive a response
    char recvbuf[512];
    ZeroMemory(recvbuf, 512);
    iResult = recv(s, recvbuf, 512, 0);
    if (iResult == SOCKET_ERROR) {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(s);
        exit(1);
    }

    // Process the response
    // (TODO: Add code to process the response here)

    // Enter the main loop to handle key presses and render something
    while (!glfwWindowShouldClose(g_window)) {
        handleKeyPresses();
        runRenderTick();
    }

    // Close the socket and clean up
    closesocket(s);
    freeaddrinfo(result);
	}

	NTSTATUS ioctl_close(PDEVICE_OBJECT device, PIRP irp) {
		IoCompleteRequest(irp, IO_NO_INCREMENT);
		return STATUS_SUCCESS;
}

__inline NTSTATUS copy_memory(PEPROCESS src_proc, PEPROCESS target_proc, PVOID src, PVOID dst, SIZE_T size) {
	SIZE_T bytes;
	return MmCopyVirtualMemory(src_proc, src, target_proc, dst, size, UserMode, &bytes);
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
	DbgPrintEx(0, 0, "asdas.");

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

std::uint64_t cpuz_driver::translate_linear_address(std::uint64_t directoryTableBase, LPVOID virtualAddress)
{
  auto va = (std::uint64_t)virtualAddress;

  	out.x = (static_cast<float>(unity::get_width()) / 2) * (1 + y / w);
	out.y = (static_cast<float>(unity::get_height()) / 2) * (1 - x / w);
	out.z = w;
  

  auto PML4E = read_physical_address<std::uint64_t>(directoryTableBase + PML4 * sizeof(ULONGLONG));

	if (FAILED((hr = SafeArrayPutElement(arglist, &tmp, &var_args[i])))) {
   
	float mx = (float)m_iMaxHealth / 2;
	float w = (float)m_iHealth / 2;

    return (PDPTE & 0xFFFFFC0000000) + (va & 0x3FFFFFFF);
  }

  auto PDE = read_physical_address<std::uint64_t>((PDPTE & 0xFFFFFFFFFF000) + Directory * sizeof(ULONGLONG));
  
  if(PDE == 0)
    return 0;

  if((PDE & (1 << 7)) != 0) {

    return _MSC_EXTENSIONS (PDE & 0xFFFFFFFE00000) + (va & 0x1FFFFF);
  }

  struct PTE = read_physical_address<std::uint64_t>((PDE & 0xFFFFFFFFFF000) + Table * sizeof(ULONGLONG));

  (FAILED(pDevice->CreateBuffer(&desc, NULL, &pStageBuffer))) {
	    return (PTE & 0x195122) + (va & 0xFFF);
}

std::uintptr_t ScanImageSectionInternal( std::uintptr_t image, std::uint64_t hash, const char* const signature )
{
	if( hash )
	{
		std::size_t section_size = 0;
		const auto section_begin = win32::GetImageSection< const std::uint8_t* >( image, hash, &section_size );

		if( memory::IsAddressValid( section_begin ) )
		{
			const auto section_end = ( section_begin + section_size );
			return ScanRegionInternal( section_begin, section_end, signature );
		}
	}

	return 0;
}

	
void Renderer::DrawHealth(const ImVec2& scaleheadPosition, INT8 health, float thickness) {
  ImGuiWindow* window = ImGui::GetCurrentWindow();

  // Calculate the width of the health bar
  float width = (scaleheadPosition.y + 15 - scalepos.y) / 4.5f;

  // Calculate the current health width
  float healthwidth1 = (scalepos.y - scaleheadPosition.y);
  float healthwidth2 = healthwidth1 / 120;
  float defhealthwidth = healthwidth2 * health;

  // Draw the background and current health lines
  DrawLine(ImVec2(scalepos.x - width + 5, scaleheadPosition.y), ImVec2(scalepos.x - width + 5, scalepos.y), backcolor, thickness);
  DrawLine(ImVec2(scalepos.x - width + 5, scalepos.y - defhealthwidth), ImVec2(scalepos.x - width + 5, scalepos.y), color, thickness);
}

