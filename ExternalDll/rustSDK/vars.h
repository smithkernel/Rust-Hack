#include <Windows.h>
#include <atomic>
#include "myMath.h"
#include "RustSDK.h"

namespace Vars
{
	namespace Config
	{
		extern DWORD64 GameObjectManager;
		extern DWORD64 BaseNetworkable;

		extern int ScreenWidth;
		extern int ScreenHigh;

		extern std::atomic<short> espFPS;
		extern std::atomic<short> menuFPS;

		extern 	bool LocalPlayerIsValid;
		extern 	bool panic;
		extern 	bool MenuActive;
	}

	namespace  Aim
	{
		extern bool aim ;
		extern bool randomBone;
		extern DWORD64 addr_BasePlayer_on_Aimming;
		extern float fov;
		extern bool drawFov;
		extern float smooth;

		extern float recoil;
		extern bool NoSpread;
		extern bool NoSway;

		extern bool ModifyBullet;
		extern 	float fat;
	}

	namespace  Esp
	{
		//player
		extern bool playerEsp;
		extern bool drawBox;
		extern bool drawHealthBar;
		extern bool drawSkeleton;
		extern bool drawActiveWeapons;

		extern bool playerCorpse;
		extern bool playerSleepers;
		extern bool npcEsp;

		//loot
		extern bool stone;
		extern bool sulphur;
		extern bool metal;
	    extern bool hemp;
		extern bool dropItems;
		extern bool airdrop;

		//etc
		extern bool landAirTurret;
		extern bool autoTurret;
		extern bool guntrap;
		extern bool flameturret;
		
		extern bool cupboard;
		extern bool cupboardPlayer;
		extern bool largeBox;
		extern bool smallBox;
		extern bool stash ;
		extern bool sleepingbag ;


		extern bool minicopter;
		extern bool cow;
		extern bool boat;
		extern bool bigBoat;
	
	
	}

	namespace  Misc
	{
		extern bool walkWatter;
		extern bool spider;
		extern bool HigthJump;
		extern bool speedhack;
		extern float speedBonus;
		extern bool WatterBoost;
		extern bool WallWalk ;

		extern bool superMelee;
		extern bool superEoka;
		extern bool alwaysDay;
		extern float alwaysDay_float;
		extern 	bool ThirdPersonMode;
		extern 	bool AdminMode;
		
		extern bool crosshair;
	}

}

class Aimbot
{
public: // public variables for this class

	bool m_TargetExist;
	Vector3 prediction_pos;
	Player pTarget;
	uint64_t camera;

public: // public methods for this class

	// converts degree to a radian
	float to_radian(float degree)
	{
		return degree * 3.141592f / 180.f;
	}

	// converts radian to a degree
	float to_degree(float radian)
	{
		return radian * 180.f / 3.141592f;
	}

	// gets the length of the vector
	inline float Length(Vector3 v) {
		return sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	// normalizes a vec2
	void Normalize(float& Yaw, float& Pitch) {
		if (Pitch < -89)
			Pitch = -89;

		else if (Pitch > 89)
			Pitch = 89;

		if (Yaw < -360)
			Yaw += 360;

		else if (Yaw > 360)
			Yaw -= 360;
	}

	// normalizes a vec2
	void Normalize(float& Yaw, float& Pitch, float&z) {
		if (Pitch < -89)
			Pitch = -89;

		else if (Pitch > 89)
			Pitch = 89;

		if (Yaw < -360)
			Yaw += 360;

		else if (Yaw > 360)
			Yaw -= 360;

		if (z < -360)
			z += 360;

		else if (z > 360)
			z -= 360;
	}
	
