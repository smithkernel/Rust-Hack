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

	
void aimAtPlayer(Entity player) {
	D3DXVECTOR2 toWrite = { 0,0 };
	D3DXVECTOR3 headPos = { 0,0,0 };
	D3DXVECTOR3 bodyPos = { 0,0,0 };


	while ((GetAsyncKeyState(0x46) & 1 || GetAsyncKeyState(0x46)))
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

	
	struct clr {
	float a, r, g, b;
	clr() = default;
	clr(float r, float g, float b, float a = 255) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	clr(uint32_t color) {
		this->a = (color >> 24) & 0xff;
		this->r = (color >> 16) & 0xff;
		this->g = (color >> 8) & 0xff;
		this->b = (color & 0xff);
	}
	clr from_uint(uint32_t uint) {
		return clr(uint);
	}

	void random_color(int iTick)
	{
		this->r = sin(3.f * iTick + 0.f) * 127 + 128;
		this->g = sin(3.f * iTick + ((2.f * M_PI) / 3)) * 127 + 128;
		this->b = sin(3.f * iTick + ((4.f * M_PI) / 3)) * 127 + 128;
		this->a = 255;
		// decrease 0.3f if you want it smoother
	}

	static clr black(float a = 255) { return { 0, 0, 0, a }; }
	static clr white(float a = 255) { return { 255, 255, 255, a }; }
	static clr red(float   a = 255) { return { 255, 0, 0, a }; }
	static clr green(float a = 255) { return { 0, 255, 0, a }; }
	static clr blue(float  a = 255) { return { 0, 0, 255, a }; }
};

static void rainbow(clr& clr_)
{

}
