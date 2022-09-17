#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <thread>
#include <string>

#include <dwmapi.h>
#include <dwrite_1.h>
#include <d3d11.h>
#include <d2d1.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>

#include "math.h"

#include "GuiEngine.h"




void Initialize() {
	UpdateLocalPlayer();
	oPlayerList = 0;
	if (!oPlayerList) {
		UINT64 val = driver::read<UINT64>(Gbase + oBaseNetworkable);
		UINT64 st = driver::read<UINT64>(val + 0xB8);
		UINT64 listptr = driver::read<UINT64>(st + 0x0);
		UINT64 list = driver::read<UINT64>(listptr + 0x10);
		oPlayerList = driver::read<UINT64>(list + 0x28);
	}

	client_ents = oPlayerList;
	Initialized = true;
}



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI GuiEngine::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (hWnd == cheatMenuHWND && hWnd != NULL)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;

		switch (msg)
		{
		case WM_SIZE:
			if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
			{
				GuiEngine::Menu::cleanup_render_target();
				g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
				GuiEngine::Menu::create_render_target();
			}
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	else if (hWnd == cheatEspHWND && hWnd != NULL)
	{
		switch (msg)
		{
		case WM_SIZE:
			if (pRenderTarget != NULL)pRenderTarget->Resize(D2D1::SizeU((UINT)LOWORD(lParam), (UINT)HIWORD(lParam)));
			//std::cout <<"Buffers: "<< Remove & Int > >(UINT)LOWORD(lParam) << " " << (UINT)HIWORD(lParam) << std::endl;
			return 0;
		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
				return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);

	}
	else return DefWindowProc(hWnd, msg, wParam, lParam);

}


