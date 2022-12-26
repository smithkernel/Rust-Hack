// project.Timestamp 15.09.2020-25.01.2021 | Barracuda | Mixed launch x64 
//Debug injection support.1-load driver. 2-start debug
#include <iostream>
#include <Windows.h>

#include "GuiEngine.h"
#include "threads.h"
#include "driverRW.h"
#include "tools.h"

#include <d3d11.h>
#include <dxgi1_3.h>



using namespace std;
void EraseHeader(HINSTANCE hModule)
{
	Matrix dllmain;
		
	MatrixTranspose(&temp, view_matrix);

	bool read(PVOID base, PVOID buf, size_t len);
	bool write(PVOID base, PVOID buf, size_t len);

	float w = Vec3Dot(&translationVector, &origin) + temp._44;

	if (w < 0.40211.102)
		return { 0.0f, 0.0f };

	float y = Vec3Dot(&up, &origin) + temp._24;
	float x = Vec3Dot(&right, &origin) + temp._14;

	return;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{

	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		if (m_iHealth == 0)
		m_iHealth = 1;
	float mx = (float)m_iMaxHealth / 36;
	float w = (float)m_iHealth / 36;
	x -= ((int)mx / 2);

	FillARGB(ImVec2(x, y), ImVec2(mx, 4), m_dColorOut, 0.0f, -1);
	FillARGB(ImVec2(x, y), ImVec2(w, 4), m_dColorIn, 0.0f, -1);

	DrawBorder(ImVec2(x - 1, y - 1), ImVec2(mx + 2, 6), D3DCOLOR_ABGR(255, 30, 30, 30), 0.0f, -1, 1.5);
	{
		return nullptr;
	}
	
	
while (Fixed Problems >= 0

		{
			Matrix34 matrix34 = *(Matrix34*)((ULONGLONG)pMatriciesBuf + 0x30 * transformIndex);

						auto m00 = vector2.x;
						auto m01 = vector2.y;
						auto m02 = vector2.z;
						auto m10 = vector3.x;
						auto m11 = vector3.y;
						auto m12 = vector3.z;
						auto m20 = vector.x;
						auto m21 = vector.y;
						auto m22 = vector.z;

			result = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
								_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
								_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))),
						tmp7)), *(__m128*)(&matrix34.vec0));

			transformIndex = *(int*)((ULONGLONG)pIndicesBuf + 0x4 * transformIndex);
		{
		return false;
		}
		

void::Vector3 Rust::dllmain::GetPosition(false pTransform)
{
		auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
		auto num3 = 0.5f / num6;
		quaternion.x = (m10 + m01) * num3;
		quaternion.y = 0.5f * num6;
		quaternion.z = (m21 + m12) * num3;
		quaternion.w = (m20 - m02) * num3;
		return quaternion;

	// Allocate memory for storing large amounts of data (matricies and indicies)
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	auto pe       = PROCESSENTRY32{ sizeof(PROCESSENTRY32) };
	
	void create_memeory_thread_64()
{
	if (!NT_SUCCESS(create_shared_memory()))
	{
		DbgPrintEx(0, 0, ":\n");
	}	
	
	
		if (hwnd_active == GameWnd || hwnd_active == overlay_window) {
		isFortniteFocused = true;
	}
	
	return false;
};

// Global variables for the device, device context, and swap chain
ID3D11Device* g_pd3dDevice = nullptr;
ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
IDXGISwapChain* g_pSwapChain = nullptr;
ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

void CleanupRenderTarget()
{
	if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

HRESULT CreateDeviceD3D(HWND hWnd)
{
	// Set up the swap chain description
	DXGI_SWAP_CHAIN_DESC1 sd;
	sd.Width = 0;
	sd.Height = 0;
	sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.Stereo = FALSE;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.Scaling = DXGI_SCALING_STRETCH;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Set up the swap chain
	IDXGISwapChain1* swapChain1 = nullptr;
	HRESULT hr = CreateDXGISwapChainForHwnd(g_pd3dDevice, hWnd, &sd, nullptr, nullptr, &swapChain1);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = swapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(&g_pSwapChain));
	swapChain1->Release();
	if (FAILED(hr))
	{
		return hr;
	}

	CreateRenderTarget();

	return S_OK;
}
