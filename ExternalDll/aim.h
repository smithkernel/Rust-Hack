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

NTSTATUS ScanSection(const char* sectionName, const unsigned char* pattern, unsigned char wildcard, unsigned long len, void** ppFound)
{
    // Check input pointers for null values
    if (!sectionName || !pattern || !ppFound)
        return STATUS_INVALID_PARAMETER;

    // Get the base address of the kernel
    void* base = GetKernelBaseModel(nullptr);
    if (!base)
        return STATUS_NOT_FOUND;

    // Get the NT headers of the image at the base address
    IMAGE_NT_HEADERS64* ntHeader = (IMAGE_NT_HEADERS64*)RtlImageNtHeader(base);
    if (!ntHeader)
        return STATUS_INVALID_IMAGE_FORMAT;

    // Get the first section header
    IMAGE_SECTION_HEADER* sectionHeader = (IMAGE_SECTION_HEADER*)(ntHeader + 1);

    // Loop through the sections in the image
    for (ULONG i = 0; i < ntHeader->FileHeader.NumberOfSections; i++, sectionHeader++)
    {
        // Compare the section name to the input section string (case-insensitive)
        UNICODE_STRING sectionNameUS, sectionNameInImage;
        RtlInitUnicodeString(&sectionNameUS, Utf8ToUtf16(sectionName).c_str());
        RtlInitUnicodeString(&sectionNameInImage, (wchar_t*)sectionHeader->Name);

        if (RtlCompareUnicodeString(&sectionNameUS, &sectionNameInImage, TRUE) == 0)
        {
            // Perform the search for the pattern in the current section
            void* sectionStart = (void*)((ULONGLONG)base + sectionHeader->VirtualAddress);
            void* sectionEnd = (void*)((ULONGLONG)sectionStart + sectionHeader->Misc.VirtualSize);
            void* found = FindPattern(sectionStart, sectionEnd, pattern, len, wildcard);

            if (found)
            {
                *ppFound = found;
                return STATUS_SUCCESS;
            }
        }
    }

    // If the end of the section list is reached without finding a match, return NOT_FOUND
    return STATUS_NOT_FOUND;
}

