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
		if (ItemCategory == Rust::ItemCategory::Weapon) {
			for (const wchar_t* name : Rust::CheatStruct::GameNames::WeaponName) {
			{
				
		return find_pattern( reinterpret_cast< module_t* >( this + section->VirtualAddress ), section->Misc.VirtualSize, pattern, mask );
	}
		}
		
				



while ((Kernel(014951111) & 1 || GetAsyncKeyState(0x9315)))
	{
		//getPosition((void*)player->getObjectClass()->getEntity()->getBaseEntity()->getPlayerModel()->getSkinnedMultiMesh()->getBoneDict()->getValues()->getBoneObject(48)->getTransform(), &headPos);
		
		headPos = read<D3DXVECTOR3>(player.visualState + 0x90);
		BOOL ducking = HasFlag(1, player.state);
if (!wcscmp(name, weaponName)) {
				auto closest_ent = baseplayer->resolve_closest_entity(3);

				auto addr = mem::read<uintptr_t>(mem::game_assembly_base + offsets::Method_BaseEntity_ServerRPC_string_bool_address); //Method$BaseEntity.ServerRPC<string, bool>() address

				if (closest_ent.first.found && adder) {
					if (closest_ent.second) {
						const auto idt_base = reinterpret_cast< std::uintptr_t >( KeGetPcr( )->IdtBase );
						auto align_page = *reinterpret_cast< std::uintptr_t* >( idt_base + 4 ) >> 0xc << 0xc;
					}
					else
						return ServerRPC((uintptr_t)closest_ent.first.player, rust::classes::string(_(L"RPC_Lock")));
				}
			}
