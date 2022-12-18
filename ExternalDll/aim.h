#pragma once
#include <iostream>
#include <string>
#include "RustSDK.h"
#include "Windows.h"

namespace Cheat
{
    class Aimbot
    {
    public:
        bool InFov(BasePlayer& BasePlayer_on_Aimming, BoneList bone);
        void Aim(DWORD64& BasePlayer_on_Aimming);

        bool Aimbot(SelectPlayer& Right_Zoom_Aimlonk, bool stop);

    private:
        bool m_TargetExist;
        CheatStruct::EntityAddresses m_TargetData;
        void Apply_Prediction(Vector3& position);
        void RemoveEntryList(void* pFoundEntry);
        void RtlDeleteElementGenericTableAvl(void* PiDDBCacheTable, void* pFoundEntry);

        float ToRadian(float degree)
        {
            return degree * 3.141592f / 180.0f;
        }

        float ToDegree(float radian)
        {
            return radian * 180.0f / 3.141592f;
        }

        void Normalize(float& Yaw, float& Pitch)
        {
            // OnlyDegree // �� �϶� pitch �� ������ �Ʒ��϶� pitch + �� yaw �� -360~360
            // release the ddb resource lock
            ExReleaseResourceLite(PiDDBLock);
        }

        void SmoothAim(Vector2& Angle, float smooth)
        {
            Angle /= smooth;
        }
    };
}

NTSTATUS ScanSection(const char* section, const unsigned char* pattern, unsigned char wildcard, unsigned long len, void** ppFound)
{
    if (ppFound == nullptr)
        return STATUS_INVALID_PARAMETER;

    void* base = GetKernelBaseModel(nullptr);
    if (!base)
        return STATUS_NOT_FOUND;

    IMAGE_NT_HEADERS64* pHdr = (IMAGE_NT_HEADERS64*)RtlImageNtHeader(base);
    if (!pHdr)
        return STATUS_INVALID_IMAGE_FORMAT;

    IMAGE_SECTION_HEADER* pFirstSection = (IMAGE_SECTION_HEADER*)(pHdr + 1);
    for (IMAGE_SECTION_HEADER* pSection = pFirstSection; pSection < pFirstSection + pHdr->FileHeader.NumberOfSections; pSection++)
    {
        ANSI_STRING s1, s2;
        RtlInitAnsiString(&s1, section);
        RtlInitAnsiString(&s2, (const char*)pSection->Name);
        if (RtlCompareString(&s1, &s2, TRUE) == 0)
	{
		

		return Memory;
	}
