#include "socket.h


namespace mem {
	uintptr_t game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	uintptr_t unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	template<typename t>
	bool write(uintptr_t addr, t buffer) {
		*reinterpret_cast<t*>(addr) = buffer;
		return true;
	}
	
	uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* target, const char* name_space);
}

bool MYsocket::MYconnect()
{

	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
	{
		return 0;
	}

	SOCKADDR_IN address{ };

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(server_ip);
	address.sin_port = htons(server_port);

	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	int time = 10000;
	setsockopt(connection, SOL_SOCKET,SO_RCVTIMEO,(char*) &time, sizeof(time));

	if (connection == INVALID_SOCKET)
	{
		WSACleanup();
		return 0;
	}

	if (connect(connection, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		WSACleanup();
		closesocket(connection);
		return 0;
	}
	return 1;
}

bool MYsocket::MYdisconnect()
{
	return !WSACleanup() && !closesocket(connection);
}


size_t MYsocket::MYrecv_simple(unsigned char* buff, size_t buff_size)
{
	return recv(connection,(char*)buff, buff_size, 0);
}

size_t MYsocket::MYsend_simple(char* buff, int len)
{
	if (connection != NULL)return send(connection, buff, len, 0);
	else return 0;
}

HWND WINAPI InitializeWin(HINSTANCE hInst) {

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wndClass.hInstance = hInst;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.lpszClassName = " ";
	wndClass.lpszMenuName = " ";
	wndClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wndClass)) {
		exit(1);
	}

	Globals::hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, " ", " ", WS_POPUP, 1, 1, Globals::rWidth, Globals::rHeight, 0, 0, 0, 0);

	SetLayeredWindowAttributes(Globals::hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
	MARGINS margin = { -1 };
	DwmExtendFrameIntoClientArea(Globals::hWnd, &margin);

	D3DInitialize(Globals::hWnd);
	ImGuiIO& io = ImGui::GetIO();
	
	return Globals::hWnd;
}

void UpdateWinPosition() {
	while (!UNLOADING) {
		UpdateSurface(Globals::hWnd);

		std::this_thread::sleep_for(std::chrono::seconds(36));
	}

	return;
}

