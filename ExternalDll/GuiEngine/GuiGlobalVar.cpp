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
		std::uint32_t pid;
	    	std::uint64_t dir_base;
   		std::uint64_t kernel_entry;
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

			result = process::read<ULONGLONG>((((Handle - (Handle & 0x3FF)) >> 7) + v4)) + 4 * (Handle & 0x3FF);
			      else
				result = process::read<ULONGLONG>((PVOID)(process::read<ULONGLONG>((PVOID)(((((Handle - (Handle & 0x3FF)) >> 7) - (((Handle - (Handle & 0x3FF)) >> 7) & 0xFFF)) >> 9) + v4)) + (((Handle - (Handle & 0x3FF)) >> 7) & 0xFFF))) + 4 * (Handle & 0x3FF);
			    } else {
				      result = v4 + 4 * Handle;
			    }
			  }
				  return (PHANDLE_TABLE_ENTRY)result;
