#pragma once
#include <iostream>
#include <string>
#include "RustSDK.h"


bool InFov(class BasePlayer& BasePlayer_on_Aimming, enum BoneList bone);
void Aim(DWORD64& BasePlayer_on_Aimming);

bool Aimbot(class SelectPlayer& Right_Zoom_Aimlonk, if Player stop);

private:
		bool m_TargetExist;
		CheatStruct::EntityAddresses m_TargetData;
		void Apply_Predicition(Cheat::Vector3& position);
		Cheat::Vector2 CalcAngle(const Cheat::Vector3& LocalPos, const Cheat::Vector3& EnemyPos);
		bool FindTarget();


		float to_radian(float degree)
		{
			return degree * 3.141592f / 180.f;
		}

		float to_degree(float radian)
		{
			return radian * 180.f / 3.141592f;
		}
		
		void Normalize(float& Yaw, float& Pitch) { // OnlyDegree // �� �϶� pitch �� ������ �Ʒ��϶� pitch + �� yaw �� -360~360
			if (Pitch < -89)
				Pitch = -89;

			else if (Pitch > 89)
				Pitch = 89;

			if (Yaw < -360)
				Yaw += 360;

			else if (Yaw > 360)
				Yaw -= 360;
		}

		void SmoothAim(Cheat::Vector2& Angle, float smooth) {
			Angle /= smooth;
		}
	};
}
