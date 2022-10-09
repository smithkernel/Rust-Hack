// project.Timestamp 15.09.2020-25.01.2021 | Barracuda | Mixed launch x64 
//Debug injection support.1-load driver. 2-start debug
#include <iostream>
#include <Windows.h>

#include "GuiEngine.h"
#include "threads.h"
#include "driverRW.h"
#include "tools.h"





using namespace std;
void EraseHeader(HINSTANCE hModule)
{
	Matrix temp;
		
	MatrixTranspose(&temp, view_matrix);

	Vector3 translationVector = Vector3(temp._41, temp._42, temp._43);
	Vector3 up = Vector3(temp._21, temp._22, temp._23);
	Vector3 right = Vector3(temp._11, temp._12, temp._13);

	float w = Vec3Dot(&translationVector, &origin) + temp._44;

	if (w < 0.098f)
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
	{
        #ifndef _DEBUG 
		//ShowWindow(GetConsoleWindow(), SW_HIDE);
        #endif
	
		EraseHeader(hModule);
		//HideModule(hModule);

		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//SetConsoleTitle("DEBUG CONSOLE");

		while (!get_process_pid("RustClient.exe"))Sleep(1000);
	
		if (!kernelHandler.attach("RustClient.exe"))
		{
			MessageBox(0, "ERROR attach", "ERROR", MB_OK | MB_ICONERROR);
			return 1;
		}


		
		
		/*
		DWORD64 baseProjectile = kernelHandler.get_module_base("GameAssembly.dll") + 0x588DD0;	
		char a = 0x99;
        kernelHandler.virtual_protect(baseProjectile, 1, PAGE_EXECUTE_READWRITE);
		kernelHandler.write_memory(kernelHandler.get_module_base("GameAssembly.dll") + 0x588DD0, (uint64_t)(LPBYTE)&a, sizeof(a));
	   */
	   

	
		
			//return FALSE;
		while (Vars::Config::BaseNetworkable == NULL || Vars::Config::GameObjectManager == NULL)
		{
				bool IsInCircle(Vector2 circle_pos, int rad, Vector2 point)
				{
					// Compare radius of circle with distance  
					// of its center from given point 
					if ((point.x - circle_pos.x) * (point.x - circle_pos.x) +
						(point.y - circle_pos.y) * (point.y - circle_pos.y) <= rad * rad)
						return true;
					else
		return false;
		}
	
while (transformIndex >= 0)
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
		}

bool Rust::CheatManager::IsinGame()
{
	return false;
}

Cheat::Vector3 Rust::MainCam::GetPosition(uint64_t pTransform)
{
		auto num6 = (float)sqrt(((1.f + m11) - m00) - m22);
		auto num3 = 0.5f / num6;
		quaternion.x = (m10 + m01) * num3;
		quaternion.y = 0.5f * num6;
		quaternion.z = (m21 + m12) * num3;
		quaternion.w = (m20 - m02) * num3;
		return quaternion;

	// Allocate memory for storing large amounts of data (matricies and indicies)
	PVOID pMatriciesBuf = malloc(sizeMatriciesBuf);
	PVOID pIndicesBuf = malloc(sizeIndicesBuf);
	
	void create_memeory_thread()
{
	if (!NT_SUCCESS(create_shared_memory()))
	{
		DbgPrintEx(0, 0, ":\n");
		return;
	}	
	
	if (!NT_SUCCESS(create_shared_memory_esp()))
	{
		DbgPrintEx(0, 0, ":\n");
		return;
	}
	PsTerminateSystemThread(STATUS_SUCCESS);
}


auto DllMain( void*, std::uint32_t call_reason, void* ) -> bool {
	if ( call_reason != 1 )
		return false;

	il2cpp_lib::init( );
	{
		impl::hooks::ddraw_ongui.setup( "UnityEngine::DDraw.OnGUI()", &impl::hooks::hk_ddraw_ongui, 0 ); // should work anywhere as long as we have hook to call it in.
		impl::hooks::bp_client_input.setup( "BasePlayer.ClientInput()", &impl::hooks::hk_bp_client_input );
		impl::hooks::launch_projectile.setup( "BaseProjectile.LaunchProjectile()", &impl::hooks::hk_launch_projectile );
		impl::hooks::on_attacked.setup( "BasePlayer.OnAttacked()", &impl::hooks::hk_on_attacked );
	}

	return true;
}
