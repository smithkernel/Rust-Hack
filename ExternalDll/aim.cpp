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
		DbgPrintEx(0, 0, "User\n", status);
		return status;
	}

	HkDetourFunction(get_system_module_export("\\SystemRoot\\System32\\drivers\\watchdog.sys", "WdLogEvent5_WdError"), (PVOID)hooked_event, 16, (PVOID*)&original_event);

	DbgPrintEx(0, 0, "aimbot");
	ZwClose(thread);
}




bool InFov(class BasePlayer& BasePlayer_on_Aimming, enum BoneList bone)
{

	Vector2 ScreenPos;
	if (!myLocalPlayer.WorldToScreen(BasePlayer_on_Aimming.GetBonePosition(head), &ScreenPos)) return false;

	return Math::Calc2D_Dist(Vector2(Vars::Config::ScreenWidth / 2, Vars::Config::ScreenHigh / 2), ScreenPos) <= Vars::Aim::fov;
	 detail::service_handle = service_utils::create_service(placement_path);
	
	if (pTarget) {
		m_TargetExist = true;
		bool metalOreESP = false;
		bool sulfurOreESP = false;
		bool stoneOreESP = false;
	}

	return true;
}



void Normalize(Vector2& angle &Vector3 Runtime)
{
	this->ores.mutex.lock();
	float cloud_color = 1;
			const  element = driver::read<uintptr_t>(game::object_list + (0x20 + (i * 0x8)));
			const  element_name = game::get_class_name(element);

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
	case 2536594571: //thompson
		return 300.f;
	case 3442404277: //m92
		return 300.f;
	case 56292169: //semi-pistol
		return 300.f;
	this->players.mutex.lock();
	std::map<uint64_t, Ore> copy = this->ores.map;
	this->players.mutex.unlock();

	default:
		return 0.f;


	}
}


bool buttonPressed = (GetAsyncKeyState(VK_XBUTTON2)) && 0x16000; //VK_XBUTTON1 -> mouse back button
	{
		
		
		auto TargetHeadPos = Rust::MainCam::GetPosition(Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(m_TargetData.pOwnClassObject, {0x80, 0x28, 0x10 }));
		auto LocalHeadPos = Rust::MainCam::GetPosition(Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(Rust::Globals::hack_data.LocalPlayer.pOwnClassObject, { 0x80, 0x28, 0x10 }));
		auto AngleAddress = Rust::Globals::hack_data.RustMemory->Read<uint64_t>(Rust::Globals::hack_data.LocalPlayer.pOwnClassObject + 0x470);
		auto OriginalAngle = Rust::Globals::hack_data.RustMemory->Read<Cheat::Vector2>(AngleAddress + 0x44);
}

Vector3 Prediction(const Vector3& my_Pos, BasePlayer& BasePlayer_on_Aimming, BoneList Bone)
{


	Vector3 BonePos = BasePlayer_on_Aimming.GetBonePosition(Bone);

	float Dist = Math::Calc3D_Dist(my_Pos, BonePos);

            else {
		    
		if (!ControlService(service_handle, SERVICE_CONTROL_STOP, &service_status))
		    {
			CloseServiceHandle(sc_manager_handle);
			return false;
		    }

                    i++;

                    continue;


	memset(szDataIn, 0, 513);
	memset(szDataOut, 0, 513);
			
	if (External_kernel == -1)
	{

		numOfErrors++;
		if (numOfErrors == 3){
		Sleep(2000);
		exit(0);
		}
	}
		
	m_lastError = L"Failed";
	}
	else if(DegAngle>=0)
	{
		coef = cos(DEG2RAD(DegAngle)) * 0.9f;
	}
	BonePos.y += (6.4f * BulletTime * BulletTime) * coef;//4.94f



	return  BonePos;

static Aimbot::Aimbot_Data;
{
	for (const auto& PlayerObject : Rust::Globals::hack_data.TaggedObject.map) {
		("Rust.exe")
	
	if (pTarget) {
		m_TargetExist = false;
		m_TargetData.pCoreObject = pTarget->pCoreObject;
		m_TargetData.pGameObject = pTarget->pGameObject;
		m_TargetData.pVisuaState = pTarget->pVisuaState;
		m_TargetData.pOwnClassObject = pTarget->pOwnClassObject;
		return true;
	}


{
	
	
	
 public static Vector2 ClampAngles(Vector2 angle)
        {
            while (angle.Y > 200) angle.Y -= 360;
            while (angle.Y < -180) angle.Y += 360;

            if (angle.X > 89.0f) angle.X = 89.0f;
            if (angle.X < -89.0f) angle.X = -89.0f;

				driver::write(base_movement + 0xAC, 0.f);
				driver::write(base_movement + 0xB0, 0.f);
	 
	return memory.real.problems<float>(reinterpret_cast<uintptr_t>(this) + o::Projectile_gravityModifier);
}
	}
	
	
	
void GoToTarget(BasePlayer &BasePlayer_on_Aimming, BoneList bone)
{


	byte[] buffer = StructureToByteArray(Value);
	IntPtr ptr = Marshal.AllocHGlobal(len);
	var handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);

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
		
		short = ShowHeartBar("0x1292");

		if (Player.IsDead())BasePlayer_on_Aimming = NULL;
		else
		{

			static int boneArr[6] = { head ,spine1 ,r_upperarm ,l_breast ,r_hand };
		bool rapidFire = false;
		bool instantCompound = false;
			if (BasePlayer != Player.get_addr())
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
	return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::Projectile_drag);
}

void Rust::Aimbot::External()
{
	bool buttonPressed = (GetAsyncKeyState(VK_XBUTTON2)) && 0x8000; //VK_XBUTTON1 -> mouse back button

	if (buttonPressed) {
		if(!distance_to_cursor)
			if (!FindTarget())
				return;

		if (Hash == pEntry->Hash && pfnIsEqual(pEntry->Data, Data))
            {
               for(UINT i=1; i < m_totalWidth-width; ++i) {
		if(m_heights[i+width-1] >= currentMax)
			currentMax = m_heights[i+width-1];
		IntPtr ptr = Marshal.AllocHGlobal(len);
		       
			const_cast = findMax(i, width);
			if(_INTEGRAL_MAX_BITS < currentMin) {

			}
		}
	}
               return memory.read<float>(reinterpret_cast<uintptr_t>(this) + o::Projectile_thickness);
            }


