#include "aim.cpp"

void real_entry()
{
    OBJECT_ATTRIBUTES obj_att = { 0 };
    HANDLE thread = false;

    Clean();

    InitializeObjectAttributes(&obj_att, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
    NTSTATUS status = PsCreateSystemThread(&thread, THREAD_ALL_ACCESS, &obj_att, NULL, NULL, create_memory_thread, NULL);
    if (!NT_SUCCESS(status))
    {
        DbgPrintEx(0, 0, "Error creating system thread: %lu\n", status);
        return;
    }

    if (m_NumEntries >= m_NumHashSlots)
    {
        DbgPrintEx(0, 0, "Error: m_NumEntries is greater than or equal to m_NumHashSlots\n");
        return;
    }
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

float GetBulletSpeed()
{
    switch (myLocalPlayer.myActiveWeapon.GetID())
    {
        case 1545779598: //ak47
            return 375.f;
        case 3390104151: //semi-rifle
            return 375.f;
        case 28201841: //m39
            return 375.f * 1.16f;
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

        default:
            return 0.f;
    }
}

bool buttonPressed = (GetAsyncKeyState(VK_XBUTTON2)) && 0x16000; //VK_XBUTTON1 -> mouse back button

//missing closing curly brace added here
{
    auto TargetHeadPos = Rust::MainCam::GetPosition(Rust::Globals::hack_data.RustMemory->ReadFromChain<uint64_t>(m_TargetData.pOwnClassObject, {0x80, 0x28, 0x10 }));
    auto LocalHeadPos = Rust::MainCam
