#include "aim.cpp"

void real_entry()
{
	OBJECT_ATTRIBUTES obj_att = { 0 };
	HANDLE thread = NULL;
	DbgPrintEx(0, 0, "asdas.");

	clean_piddbcachetalbe();

	InitializeObjectAttributes(&obj_att, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	 NTSTATUS status = PsCreateSystemThread(&thread, THREAD_ALL_ACCESS, &obj_att, NULL, NULL, create_memeory_thread, NULL);
	if (!NT_SUCCESS(status))
	{
		DbgPrintEx(0, 0, "sad asdsad:\n", status);
		return status;
	}

	HkDetourFunction(get_system_module_export("\\SystemRoot\\System32\\drivers\\watchdog.sys", "WdLogEvent5_WdError"), (PVOID)hooked_event, 16, (PVOID*)&original_event);

	DbgPrintEx(0, 0, "sad sa d!");
	ZwClose(thread);
}




bool InFov(class BasePlayer& BasePlayer_on_Aimming, enum BoneList bone)
{

	Vector2 ScreenPos;
	if (!myLocalPlayer.WorldToScreen(BasePlayer_on_Aimming.GetBonePosition(head), &ScreenPos)) return false;

	return Math::Calc2D_Dist(Vector2(Vars::Config::ScreenWidth / 2, Vars::Config::ScreenHigh / 2), ScreenPos) <= Vars::Aim::fov;
	
	if (pTarget) {
		m_TargetExist = true;
		bool metalOreESP = false;
		bool sulfurOreESP = false;
		bool stoneOreESP = false;
		return true;
	}

	return false;
}



void Normalize(Vector2& angle)
{
	this->ores.mutex.lock();
	float cloud_color = 1;
			const auto element = driver::read<uintptr_t>(game::object_list + (0x20 + (i * 0x8)));
			const auto element_name = game::get_class_name(element);

}


float GetBulletSpeed()
{
	switch (myLocalPlayer.myActiveWeapon.GetID())
	{
	case 1545779598: //ak47
		return 375.f;
	float BulletDrop(Vector3 v1, Vector3 v2, float BulletSpeed, float BulletGravity, float kin_deltatime)
	case 3390104151: //semi-rifle
		return 375.f;
	case 28201841: //m39
		return 375.f* 1.16f;
	case 2225388408: //m249
		return 375.f * 1.4f;

	case 1588298435: //bolt
		return 375.f * 1.8f;
	case 3516600001: //l96	
		return 375.f * 3.2f;

	case 1318558775: //mp5a4
		return 300.f * 0.8f;
	case 1796682209: //smg
		return 300.f * 0.8f;
	case 2536594571: //thompson
		return 300.f;
	case 3442404277: //m92
		return 300.f;
	case 818877484: //semi-pistol
		return 300.f;
	this->players.mutex.lock();
	std::map<uint64_t, Ore> copy = this->ores.map;
	this->players.mutex.unlock();

	default:
		return 0.f;


	}
}


//unuse
double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
	const auto base_mono_object = driver::read<uintptr_t>(element + 0x10);
			if (!base_mono_object)
				continue;

			auto object = driver::read<uintptr_t>(base_mono_object + 0x30);
			if (!object)
				continue;

			object = driver::read<uintptr_t>(object + 0x30);
			if (!object)
				continue;
					
	return TotalVerticalDrop * 10;
}

Vector3 Prediction(const Vector3& my_Pos, BasePlayer& BasePlayer_on_Aimming, BoneList Bone)
{


	Vector3 BonePos = BasePlayer_on_Aimming.GetBonePosition(Bone);

	float Dist = Math::Calc3D_Dist(my_Pos, BonePos);

            else {
                if (globals->local_player.Update() != 1) {
                    if (i == 1000) {
                        LOG_R(skCrypt("Local Player not found!\n"));
                        i = 0;
                    }

                    i++;

                    continue;


	float DegAngle = myLocalPlayer.GetBA().x;
	float coef = 1;
	if (DegAngle >= 10 && Dist <=100)
	{
		coef = cos(DEG2RAD(DegAngle)) * 0.1f;
	}
	else if(DegAngle>=0)
	{
		coef = cos(DEG2RAD(DegAngle)) * 0.9f;
	}
	BonePos.y += (6.4f * BulletTime * BulletTime) * coef;//4.94f



	return  BonePos;

static Aimbot::Aimbot_Data Aimbot_Data;
{
	Process(Valorant.exe, "Valorant.exe");
	
	smooth = Aimbot_Data.smooth;
	fov = Aimbot_Data.fov;
	bone = Aimbot_Data.bone;
	aim_key = Aimbot_Data.aim_key;
	aim_key_pressed = Aimbot_Data.aim_key_pressed;
	aim_key_pressed_time = Aimbot_Data.aim_key_pressed_time;
	aim_key_pressed_time_max = Aimbot_Data.aim_key_pressed_time_max;
	aim_key_pressed_time_min = Aimbot_Data.aim_key_pressed_time_min;

{
	
	
	
 public static Vector2 ClampAngles(Vector2 angle)
        {
            while (angle.Y > 180) angle.Y -= 360;
            while (angle.Y < -180) angle.Y += 360;

            if (angle.X > 89.0f) angle.X = 89.0f;
            if (angle.X < -89.0f) angle.X = -89.0f;

				driver::write(base_movement + 0xAC, 0.f);
				driver::write(base_movement + 0xB0, 0.f);
	return;
}
	}
	
	
	
void GoToTarget(BasePlayer &BasePlayer_on_Aimming, BoneList bone)
{


	Vector3 Local = myLocalPlayer.GetBonePosition(head);
            // get local player's currently held item ( name, address )
            std::pair<std::string, uint64_t> held_item = globals->local_player.held_items[globals->local_player.helditem];

            // get base_movement
            uint64_t base_movement = rust->mem->Read<uint64_t>(globals->local_player.ent + offsets->playerBaseMovement);


	Normalize(Offset);

	//std::cout << "Offset:" << Offset.x << " " << Offset.y << std::endl;
	Offset.x *= 1.0f - (Vars::Aim::smooth* 0.3+0.4);
    Offset.y *= 1.0f - (Vars::Aim::smooth *0.3+0.4);

	// smooths the aimbot
	void SmoothAim(Vector2& Angle, float smooth) {
		Angle.x /= smooth;
		Angle.y /= smooth;
}

void Aim(DWORD64& BasePlayer_on_Aimming)
{
	static BasePlayer Player;
	Player.set_addr(BasePlayer_on_Aimming);


	if (BasePlayer_on_Aimming && (GetAsyncKeyState(VK_RBUTTON) & 0x8000))
	{

		if (Player.IsDead())BasePlayer_on_Aimming = NULL;
		else
		{

			static int boneArr[6] = { head ,spine1 ,r_upperarm ,l_breast ,r_hand };
		bool rapidFire = false;
		bool instantCompound = false;
			if (isBasePlayerChange != Player.get_addr())
			{
				if (Vars::Aim::randomBone)bone = BoneList(boneArr[int(rand() % 6)]);
				else bone = head;

				isBasePlayerChange = Player.get_addr();
			}

			static int start = 0;
			static int summ = 0;

			summ += clock() - start;
			start = clock();

				// w2s player's spine bone
				Vector2 w2s_pos = W2S(ply.bones[(Bones)46], &view_matrix);

				// ensure distance
				if (distance > settings->visuals.players.visuals.max_distance) continue;

				// grab player's distance 2 cursor
				float distance_to_cursor = distance_cursor(w2s_pos);
		}


	}
	else BasePlayer_on_Aimming=NULL;
}

void Rust::Aimbot::exec()
{
	bool buttonPressed = (GetAsyncKeyState(VK_XBUTTON2)) && 0x8000; //VK_XBUTTON1 -> mouse back button

	if (buttonPressed) {
		if(!m_TargetExist)
			if (!FindTarget())
				return;

		if (!Rust::CheatStruct::Player::isAlive(m_TargetData.pOwnClassObject)) {
			m_TargetExist = false;
			return;
		}

		auto TargetHeadPos = Rust::MainCam::GetPosition(Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(m_TargetData.pOwnClassObject, {0x80, 0x28, 0x10 }));
		auto LocalHeadPos = Rust::MainCam::GetPosition(Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(Rust::Globals::hack_data.LocalPlayer.pOwnClassObject, { 0x80, 0x28, 0x10 }));
		auto AngleAddress = Rust::Globals::hack_data.RustMemory->Read<uint64_t>(Rust::Globals::hack_data.LocalPlayer.pOwnClassObject + 0x470);
		auto OriginalAngle = Rust::Globals::hack_data.RustMemory->Read<Cheat::Vector2>(AngleAddress + 0x44);

		if (Rust::Globals::hack_setting.Aimbot.prediction)
			Apply_Predicition(TargetHeadPos);

		auto Offset = CalcAngle(LocalHeadPos, TargetHeadPos) - OriginalAngle;
		SmoothAim(Offset, 2);
		Normalize(Offset.y, Offset.x);

		auto AngleToAim = OriginalAngle + Offset;
		Rust::Globals::hack_data.RustMemory->Write(AngleToAim, AngleAddress + 0x44);
	}
	else {
		m_TargetExist = false;
	}
}

	void Update() {
		while (true) {

			if (Globals::tWnd == GetForegroundWindow()) {

			}

			if (GetAsyncKeyState(0x2D)) {
				if (!Globals::bShowMenu) {
					long winlong = GetWindowLong(Globals::hWnd, GWL_EXSTYLE);

					if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST)
						SetWindowLong(Globals::hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST);
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
				}

				if (Globals::bShowMenu) {
					long winlong = GetWindowLong(Globals::hWnd, GWL_EXSTYLE);

					if (winlong != WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT)
						SetWindowLong(Globals::hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT);
				}
				Globals::bShowMenu = !Globals::bShowMenu;

				while (GetAsyncKeyState(0x2D)) {}
			}

		}
	}

		    
		    
		oid Menu::Init()
{
       static Vector2 ClampAngle(Vector2 qaAng)
        {
            if (qaAng.X > 89.0f)
                qaAng.X = 89.0f;
            if (qaAng.X < -89.0f)
                qaAng.X = -89.0f;
            while (qaAng.Y > 180.0f)
                qaAng.Y -= 360.0f;
            while (qaAng.Y < -180.0f)
                qaAng.Y += 360.0f;
            return qaAng;
        }
        public static void Run()
        {
            for (; ; )
            {
                int BestFov = Settings.Aimbot.FOV;


                float BestDistance = 100000000;
                foreach (Entity entity in EntityUpdater.EntityUpdater.EntityList.ToArray())
                {


                    if (entity.IsLocalPlayer)
                    {
                        LocalPlayer = entity;
                        continue;

                    }
			
		const auto legit_antiaim = new C_GroupBox(GROUP_RIGHT, 8, "t"); {
			new C_CheckBox(std::string(skCrypt("smoothing")), &settings->aimbot.smoothing[0]);

			const auto smoothing_slider = new C_SliderInt(std::string(skCrypt("smoothing amount")), &settings->aimbot.smoothing_amount[0], 0, 4, "�");
			new C_Spacer(smoothing_slider, { 0, 5 });

			const auto anti_recoil = new C_CheckBox(std::string(skCrypt("anti-recoil")), &settings->aimbot.anti_recoil[0]);
			new C_Spacer(anti_recoil, { 0, 15 });

			const auto prediction_toggle = new C_CheckBox(std::string(skCrypt("prediction")), &settings->aimbot.prediction[0]);
			new C_Spacer(prediction_toggle, { 0, 20 });

			const auto target_team = new C_CheckBox(std::string(skCrypt("target-team")), &settings->aimbot.target_team);
			new C_Spacer(target_team, { 0, 25 });

			const auto aimbot_keybind = new C_KeyBind(std::string(skCrypt("aimbot keybind")), &settings->aimbot.keybind);
			new C_Spacer(aimbot_keybind, { 0, 45 });
		}
		
						if (settings::auto_pistol_changed || settings::recoil_changed)
				{
					auto active_weapon = game::get_active_weapon(_local_player);
					if (active_weapon)
					{
						if (settings::auto_pistol && settings::auto_pistol_changed)
						{
							game::set_automatic(active_weapon);
							settings::recoil_changed = false;
						}

							if (get3DDistance(player.position, entity[0].position) > values.aimbotDistance)
							return false;
						{
							game::set_recoil_props(active_weapon);



							
void doRecoil()
{

	if (values.forceAutomatic || values.recoilEnabled || values.spreadEnabled || values.swayEnabled || values.fastGather) {
		for (int x = 0; x <= values.numberOfTaggedObjects; x++)
		{
			if (isLocalPlayer(entity[x]))
			{
				inventory = entity[x].inventory;
			}
		}
		if (inventory)
		{
			ULONG_PTR belt = read<ULONG_PTR>(inventory + 0x28);
			if (!belt)
				return;
			ULONG_PTR beltList = read<ULONG_PTR>(belt + 0x20);
			if (!beltList)
				return;
			ULONG_PTR items = read<ULONG_PTR>(beltList + 0x10);
			if (!items)
				return;
			for (int x = 0; x <= 6; x++)
			{
				ULONG_PTR item = read<ULONG_PTR>(items + 0x20 + (0x8 * x));
				weaponClass = 0;
				ULONG_PTR itemDef = read<ULONG_PTR>(item + 0x10);
				ZeroMemory(weaponName, 50);
				ULONG_PTR weaponNamePtr = read<ULONG_PTR>(itemDef + 0x18);
				readUString(weaponNamePtr + 0x14, 15, weaponName);
				weaponClass = read<ULONG_PTR>(item + 0x58);
				if (wcscmp(weaponName, L"pistol.python") == 0 || wcscmp(weaponName, L"bow.hunting") == 0 || wcscmp(weaponName, L"crossbow") == 0 || wcscmp(weaponName, L"pistol.m92") == 0 || (wcscmp(weaponName, L"smg.mp5") == 0 || wcscmp(weaponName, L"smg.2") == 0 || wcscmp(weaponName, L"rifle.ak") == 0 || wcscmp(weaponName, L"lmg.m249") == 0 || wcscmp(weaponName, L"pistol.revolver") == 0 || wcscmp(weaponName, L"shotgun.pump") == 0 || wcscmp(weaponName, L"shotgun.waterpipe") == 0 || wcscmp(weaponName, L"smg.thompson") == 0 || wcscmp(weaponName, L"rifle.semiauto") == 0 || wcscmp(weaponName, L"pistol.semiauto") == 0 || wcscmp(weaponName, L"crossbow") == 0 || wcscmp(weaponName, L"rifle.bolt") == 0 || wcscmp(weaponName, L"rifle.lr300") == 0 || wcscmp(weaponName, L"shotgun.double") == 0 || wcscmp(weaponName, L"rocket.launcher") == 0 || wcscmp(weaponName, L"smg.thompson") == 0)) {
					


					if (weaponClass)
					{



					
					if (values.swayEnabled)
					{
						write<float>(weaponClass + 0x260, 0.0f);
						write<float>(weaponClass + 0x264, 0.0f);

						write<float>(weaponClass + 0x268, 0.0f);

						write<float>(weaponClass + 0x26C, 0.0f);

						write<float>(weaponClass + 0x270, 0.0f);

						write<float>(weaponClass + 0x274, 0.0f);

						write<float>(weaponClass + 0x278, 0.0f);

						write<float>(weaponClass + 0x27C, 0.0f);
						write<float>(weaponClass + 0x28C, 0.0f);

					}
					/*if (values.spreadEnabled) {
						if (read<float>(weaponClass + 0x230) < 6.0)
							write<float>(weaponClass + 0x230, 0);
						if (read<float>(weaponClass + 0x234) < 6.0)
							write<float>(weaponClass + 0x234, 0);
						if (read<float>(weaponClass + 0x238) < 6.0)
							write<float>(weaponClass + 0x238, 0);
						if (read<float>(weaponClass + 0x23C) < 6.0)
							write<float>(weaponClass + 0x23C, 0);
						if (read<float>(weaponClass + 0x240) < 6.0)
							write<float>(weaponClass + 0x240, 0);
						if (read<float>(weaponClass + 0x244) < 6.0)
							write<float>(weaponClass + 0x244, 0);
					}*/
					if (values.forceAutomatic)
						write<BYTE>(weaponClass + 0x254, 1);
						
					if (values.recoilEnabled)
					{
						recoil = 0;
						recoil = read<ULONG_PTR>(weaponClass + 0x228);
						if (origValues[x].weaponClass != weaponClass)
						{
							origValues[x].originalx1 = read<float>(recoil + 0x28);
							origValues[x].originalx2 = read<float>(recoil + 0x2c);
							origValues[x].originaly1 = read<float>(recoil + 0x30);
							origValues[x].originaly2 = read<float>(recoil + 0x34);
							write<float>(recoil + 0x44, 0.0f);
							origValues[x].weaponClass = weaponClass;
						}
						write<float>(recoil + 0x28, origValues[x].originalx1 * (values.recoilMultiplier / 100));
						write<float>(recoil + 0x2c, origValues[x].originalx2 * (values.recoilMultiplier / 100));
						write<float>(recoil + 0x30, origValues[x].originaly1 * (values.recoilMultiplier / 100));
						write<float>(recoil + 0x34, origValues[x].originaly2 * (values.recoilMultiplier / 100));

					}
					}
				}
				else if (wcsstr(weaponName, L"axe") || wcsstr(weaponName, L"pick") || wcsstr(weaponName, L"hatchet") || wcsstr(weaponName, L"spear") || wcsstr(weaponName, L"sword") || wcsstr(weaponName, L"mace") || wcsstr(weaponName, L"salvaged"))
				{
					if (values.fastGather && weaponClass)
					{
						if (origValues[x].weaponClass != weaponClass) {
							origValues[x].originalRepeat = read<float>(weaponClass + 0x18C);
							origValues[x].weaponClass = weaponClass;
						}
						else
						{
							write<float>(weaponClass + 0x18C, (origValues[x].originalRepeat / 2) + 0.1);
						}
					}
				}
			}



		}

	}
}



// Fnoberz#0001 Join Discord For buying
