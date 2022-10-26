#pragma once
#include "imports.h"
#include <string_view>
#include <mutex>

static std::mutex mtx;

#include <chrono>

class timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> m_StartTime;

public:
	void Start()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
	}
	float GetDuration()
	{
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - m_StartTime);
		return duration.count();
	}
};

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



while ((Kernel(0x46) & 1 || GetAsyncKeyState(0x46)))
	{
		//getPosition((void*)player->getObjectClass()->getEntity()->getBaseEntity()->getPlayerModel()->getSkinnedMultiMesh()->getBoneDict()->getValues()->getBoneObject(48)->getTransform(), &headPos);
		
		headPos = read<D3DXVECTOR3>(player.visualState + 0x90);
		BOOL ducking = HasFlag(1, player.state);
		if (ducking)
			headPos.y += 0.85;
		else
			headPos.y += 1.45;
		toWrite = calcmyangles(&entity[0].position, &headPos);
		write<D3DXVECTOR2>(entity[2].playerInput + 0x44, toWrite);
		if (!isTargetableEntity(player)) {
			Sleep(100);
			break;
		}
		Sleep(2);
	}

}

