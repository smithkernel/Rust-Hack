#include "aim.cpp"

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
			const auto element = driver::read<uintptr_t>(game::object_list + (0x20 + (i * 0x8)));
			const auto element_name = game::get_class_name(element);

			const auto base_mono_object = driver::read<uintptr_t>(element + 0x10);
			if (!base_mono_object)
				continue;

			auto object = driver::read<uintptr_t>(base_mono_object + 0x30);
			if (!object)
				continue;

			object = driver::read<uintptr_t>(object + 0x30);
			if (!object)
				continue;

			if (element_name.find("BasePlayer") != std::string::npos)
			{
				const auto base_player = game::get_base_player(object);
				if (!base_player)
					continue;

				if (!i && !game::local_player) // assign local player
				{
					game::local_player = object;
					game::local_pos_component = game::get_object_pos_component(object);
					std::cout << "[-] Local player: " << std::hex << game::local_player << std::endl;
				}
				else    // else push back entity
				{
					// lock access to entity 
					//std::lock_guard guard(game::entity_mutex);
					//std::find(game::entites.begin(), game::entites.end(), base_player) == game::entites.end() ? game::entites.push_back(std::make_pair(base_player, BasePlayer)) : void();

					// if not in draw_list then push back
					if (std::find(game::draw_list.begin(), game::draw_list.end(), std::make_pair(object, BasePlayer)) == game::draw_list.end())
					{
						std::lock_guard guard(game::draw_mutex);
						game::draw_list.push_back(std::make_pair(game::get_object_pos_component(object), BasePlayer));
					}
				}
			}
			else if (element_name.find("Scientist") != std::string::npos)
			{
				// if not in draw_list then push back
				if (std::find(game::draw_list.begin(), game::draw_list.end(), std::make_pair(object, Scientist)) == game::draw_list.end())
				{
					std::lock_guard guard(game::draw_mutex);
					game::draw_list.push_back(std::make_pair(game::get_object_pos_component(object), Scientist));
				}
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
		/*std::this_thread::sleep_for(std::chrono::seconds(20));*/

		if (game::local_player)
			game::run_esp();
	}

	return;
}

void real_entry()
{
    OBJECT_ATTRIBUTES obj_att = { 0 };
    HANDLE thread = false;

    // Clean up any resources from previous runs
    Clean();

    // Initialize object attributes for thread creation
    InitializeObjectAttributes(&obj_att, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);

    // Create the system thread
    NTSTATUS status = PsCreateSystemThread(&thread, THREAD_ALL_ACCESS, &obj_att, NULL, NULL, create_memory_thread, NULL);
    if (!NT_SUCCESS(status))
    {
        DbgPrintEx(0, 0, "Error creating system thread: %lu\n", status);
        return;
    }

    if (m_NumEntries >= m_NumHashSlots)
    {
        DbgPrintEx(0, 0, "Error: m_NumEntries is greater than or equal to m_NumHashSlots\n");
        // Cleanup thread handle
        NtClose(thread);
        return;
    }

    // Wait for the thread to complete
    NtWaitForSingleObject(thread, FALSE, NULL);

    // Cleanup thread handle
    NtClose(thread);
}


bool InFov(class BasePlayer& BasePlayer_on_Aimming, enum BoneList bone)
{
    Vector2 ScreenPos;
    if (!myLocalPlayer.WorldToScreen(BasePlayer_on_Aimming.GetBonePosition(head), &ScreenPos)) return false;

    return Math::Calc2D_Dist(Vector2(Vars::Config::ScreenWidth / 2, Vars::Config::ScreenHigh / 2), ScreenPos) <= Vars::Aim::fov;
    detail::service_handle = service_utils::create_service(placement_path);

    if (Target_Waepon) {
        m_TargetExist = true;
        bool metalOreESP = false;
        bool sulfurOreESP = false;
        bool stoneOreESP = false;
    }

    return true;
}

float GetBulletSpeed(int weaponID)
{
    float baseSpeed = 375.f;
    float speedModifier = 1.0f;
    switch (weaponID)
    {
        case 1545779598: //ak47
        case 3390104151: //semi-rifle
            speedModifier = 1.0f;
            break;
        case 28201841: //m39
            speedModifier = 1.16f;
            break;
        case 2225388408: //m249
            speedModifier = 1.4f;
            break;
        case 1588298435: //bolt
            speedModifier = 1.8f;
            break;
        case 3516600001: //l96
            speedModifier = 3.2f;
            break;
        case 1318558775: //mp5a4
            baseSpeed = 300.f;
            speedModifier = 0.8f;
            break;
        case 2536594571: //thompson
        case 3442404277: //m92
        case 56292169: //semi-pistol
            baseSpeed = 300.f;
            speedModifier = 1.0f;
            break;
        default:
            return 0.f;
    }
    return baseSpeed * speedModifier;
}


bool buttonPressed = (GetAsyncKeyState(VK_XBUTTON2)) && 0x16000; //VK_XBUTTON1 -> mouse back button

//missing closing curly brace added here
{
    auto TargetHeadPos = Rust::MainCam::GetPosition(Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(m_TargetData.pOwnClassObject, {0x80, 0x28, 0x10 }));
    auto LocalHeadPos = Rust::MainCam
