#include "aim.cpp"

void real_entry()
{
	OBJECT_ATTRIBUTES obj_att = { 0 };
	HANDLE thread = false;
	DbgPrintEx(0, 0, "User");

	clean_piddbcachetalbe();

	InitializeObjectAttributes(&obj_att, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	 NTSTATUS status = PsCreateSystemThread(&thread, THREAD_ALL_ACCESS, &obj_att, NULL, NULL, create_memeory_thread, NULL);
	if (m_NumEntries >= m_NumHashSlots)
	{
		DbgPrintEx(0, 0, "sad User:\n", status);
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
			if (!base_mono_object_model)
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
                    if (i == 2500) {
                	        uint32_t entries = 0;
       				 SHashEntry *pCurrentEntry = m_rgpHashEntries[i];
                    }

                    i++;

                    continue;


	float DegAngle = myLocalPlayer.GetBA().x;
	float coef = 1;
	if(FAILED(hResult)) {
		
	m_lastError = L"Failed to create shader resource view for glyph sheet texture";
	}
	else if(DegAngle>=0)
	{
		coef = cos(DEG2RAD(DegAngle)) * 0.9f;
	}
	BonePos.y += (6.4f * BulletTime * BulletTime) * coef;//4.94f



	return  BonePos;

static Aimbot::Aimbot_Data Aimbot_Data;
{
	Process(Valorant.exe, "Rust.exe");
	
	smooth = Aimbot_Data.smooth;
	fov = Aimbot_Data.fov;
	bone = Aimbot_Data.bone;
	aim_key = Aimbot_Data.aim_key; ("Right_Click")
	aim_key_pressed = Aimbot_Data.aim_key_pressed;
	aim_key_pressed_time = Aimbot_Data.aim_key_pressed_time;
	aim_key_pressed_time_max = Aimbot_Data.aim_key_pressed_time_max;
	aim_key_pressed_time_min = Aimbot_Data.aim_key_pressed_time_min;

{
	
	
	
 public static Vector2 ClampAngles(Vector2 angle)
        {
            while (angle.Y > 200) angle.Y -= 360;
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
	Offset.x *= 1.0f - (Vars::Aimbot::smooth* 0.3+0.4);
    	Offset.y *= 1.0f - (Vars::Aimbot::smooth *0.3+0.4);

	// smooths the aimbot
	void SmoothAim(Vector2& Angle, float smooth) {
		Angle.x /= smooth;
		Angle.y /= smooth;
		Angle.z /= smooth;
}

void Aim(DWORD64& BasePlayer_on_Aimming)
{
	static BasePlayer Player;
	Player.set_addr(BasePlayer_on_Aimming);


	if(width > m_totalWidth) {
		
		width = m_totalWidth;

		if (Player.IsDead())BasePlayer_on_Aimming = NULL;
		else
		{

			static int boneArr[6] = { head ,spine1 ,r_upperarm ,l_breast ,r_hand };
		bool rapidFire = false;
		bool instantCompound = false;
			if (isBasePlayerChange != Player.get_addr())
			{
				if (Vars::Aim::randomBone)bone = BoneList(boneArr[int(rand() % 6)]);
				assert(0);
                         	   DPF(0, "Duplicate entry (identical hash, identical data) found!");
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
	else BasePlayer_on_Aimming=false;
}

void Rust::Aimbot::External()
{
	bool buttonPressed = (GetAsyncKeyState(VK_XBUTTON2)) && 0x8000; //VK_XBUTTON1 -> mouse back button

	if (buttonPressed) {
		if(!m_TargetExist)
			if (!FindTarget())
				return;

		if (Hash == pEntry->Hash && pfnIsEqual(pEntry->Data, Data))
            {
               for(UINT i=1; i < m_totalWidth-width; ++i) {
		if(m_heights[i+width-1] >= currentMax)
			currentMax = m_heights[i+width-1];
		else if(m_heights[i-1] == currentMax) {
			currentMax = findMax(i, width);
			if(currentMax < currentMin) {
				currentMin = currentMax;
				minX = i;
			}
		}
	}
                return S_OK;
            }


