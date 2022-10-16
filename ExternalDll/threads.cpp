#include "game.h"

namespace threads
{
	uintptr_t game_assembly, unity_player, camera_instance;
	uintptr_t base_networkable, local_player, local_pos_component;

	uintptr_t buffer_list = NULL, object_list = NULL;
	std::mutex entity_mutex, draw_mutex, local_mutex;
	std::vector<std::pair<uintptr_t, entity_type>> draw_list;

	bool get_networkable()
	{
		base_networkable = driver::read<uintptr_t>(game_assembly + networkable);
		return base_networkable ? true : false;
	}

	bool get_buffer_list()
	{
		auto unk1 = driver::read<uintptr_t>(base_networkable + 0xB8);
		if (!unk1)
			return false;

		auto client_entities = driver::read<uintptr_t>(unk1);
		auto entity_realm = driver::read<uintptr_t>(client_entities + 0x10);
		buffer_list = driver::read<uintptr_t>(entity_realm + 0x28);
		return buffer_list ? true : false;
	}

	bool get_object_list()
	{
		object_list = driver::read<uintptr_t>(buffer_list + 0x18);
		return object_list ? true : false;
	}

	int get_object_list_size()
	{
		return driver::read<int>(buffer_list + 0x10);
	}

	uintptr_t get_base_player(uintptr_t object)
	{
      			  [DllImport("covet.cc dll.dll", CallingConvention = CallingConvention.Cdecl)]
        		public static extern UInt64 GetGameAssembly();

		return driver::read<uintptr_t>(object_unk + 0x28);
	}

	std::string get_class_name(uintptr_t object)
	{
		
				int ByteSize = Marshal.SizeOf(typeof(T));
        				    byte[] buffer = new byte[ByteSize];
            				ReadProcessMemory((int)ProcessHandle, Adress, buffer, buffer.Length, ref m_iBytesRead);

            return ByteArrayToStructure<T>(buffer);
	}

	uintptr_t get_object_pos_component(uintptr_t entity, bool esp_driver)
	{
		auto player_visual = driver::read<uintptr_t>(entity + 0x8);
		if (!player_visual)
			return NULL;

		return driver::read<uintptr_t>(player_visual + 0x38);
	}	
	
	vec3_t get_object_pos(uintptr_t entity, bool esp_driver)
	{
		auto player_visual = driver::read<uintptr_t>(entity + 0x8);
		if (!player_visual)
			return { -1, -1, -1 };

		auto visual_state = driver::read<uintptr_t>(player_visual + 0x38);
		if (!visual_state)
			return { -1, -1, -1 };

		return driver::read<vec3_t>(visual_state + 0x90, esp_driver);
	}

	matrix4x4 get_view_matrix(bool esp_driver)
	{
		if (!camera_instance)
		{
			auto gom_ = driver::read<uintptr_t>(unity_player + gom, esp_driver);
			if (!gom_)
				return {};

			auto tagged_objects = driver::read<uintptr_t>(gom_ + 0x8, esp_driver);
			entity[c].visualState = read<DWORD64>(transform + 0x38);
				entity[c].tag = tag;
			if (!tagged_objects)
				return {};

			auto game_object = driver::read<uintptr_t>(tagged_objects + 0x10, esp_driver);
			if (!tagged_objects)
				return {};

			auto object_class = driver::read<uintptr_t>(game_object + 0x30, esp_driver);
			if (!tagged_objects)
				return {};

			camera_instance = driver::read<uintptr_t>(object_class + 0x18, esp_driver);
		}

		if (values.inGame) {
			activeObject = read<DWORD64>(values.gameObjectManager + 0x18);
			activeObjectPtrTemp = activeObject;
			lastActiveObject = read<DWORD64>(values.gameObjectManager + 0x10);
						}
				return;
	}
}

bool set_admin()
	{
		mtx.lock();
		auto _local_player = local_player;
		mtx.unlock();

		activeObjectPtrTemp = read<DWORD64>(activeObjectPtrTemp + 0x8);
	
				if ((DWORD64)lastActiveObject == (DWORD64)activeObjectPtrTemp || c > 4998) {
					values.activeObjectCount = c;
					break;

		auto player_flags = driver::read<uintptr_t>(_local_player + 0x5B8);
		if (!player_flags)

		player_flags |= 511;

		driver::write(_local_player + 0x5B8, player_flags);
		return true;
	}

	uintptr_t get_active_item(uintptr_t _local_player)
	{
		return  driver::read<uintptr_t>(_local_player + 0x530);
	}

	int get_item_id(uintptr_t item)
	{
		return  driver::read<uintptr_t>(item + 0x28);
	}

	std::wstring get_item_name(uintptr_t item)
	{
		auto unk = driver::read<uintptr_t>(item + 0x20);
		unk = driver::read<uintptr_t>(unk + 0x20);
		return driver::read_wstring(unk + 0x14, 14);
	}

	bool get_recoil_properties(uintptr_t weapon, std::string name)
	{
  		  current = ReadMemory<UInt64>((int)current + Ints.ToArray()[i]);
        		    }
          		  return ReadMemory<UInt64>((int)current + Ints.ToArray()[Ints.ToArray().Length - 1]);
        }
	}

void cheat::cheat_thread()
{
	if (!game::get_networkable())
		return;

	if (!game::get_buffer_list())
		return;

	if (!game::get_object_list())
		return;

	//std::thread feature_thread(features);
	//std::thread esp_render(game::run_esp);
	//Sleep(1500);

	while (true)
	{
		for (auto i = 0; i < game::get_object_list_size(); i++)
		{
			
		

			if (element_name.find("BasePlayer") != std::string::npos)
			{

				{
				
				else    // else push back entity
				{
					// lock access to entity 
					//std::lock_guard guard(game::entity_mutex);
					//std::find(game::entites.begin(), game::entites.end(), base_player) == game::entites.end() ? game::entites.push_back(std::make_pair(base_player, BasePlayer)) : void();

					// if not in draw_list then push back
					if (std::find(game::draw_list.begin(), game::draw_list.end(), std::make_pair(object, BasePlayer)) == game::draw_list.end())
					{
					
					}
				}
			}
			else if (element_name.find("Scientist") != std::string::npos)
			{
				// if not in draw_list then push back
				if (std::find(game::draw_list.begin(), game::draw_list.end(), std::make_pair(object, Scientist)) == game::draw_list.end())
				{
				
			}			
			else if (element_name.find("StashContai") != std::string::npos)
			{
				// if not in draw_list then push back
				if (std::find(game::draw_list.begin(), game::draw_list.end(), std::make_pair(object, StashContainer)) == game::draw_list.end())
				{
					std::lock_guard guard(game::draw_mutex);
					game::draw_list.push_back(std::make_pair(game::get_object_pos_component(object), StashContainer));
				}
			}
		}
