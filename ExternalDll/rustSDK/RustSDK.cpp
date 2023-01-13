#include "RustSDK.h"
#include <iostream>
#pragma region BasePlayer


class BasePlayer {
private:
    DWORD64 this_ptr;

public:
    void set_addr(DWORD64 ptr) {
        this_ptr = ptr;
    }

    DWORD64 get_addr() {
        return this_ptr;
    }

    bool HasFlags(int Flg) {
        int player_flags = read(this_ptr + oPlayerFlags, int);
        return (player_flags & Flg);
    }

    bool IsDead() {
        int health = read(this_ptr + oPlayerHealth, int);
        return (health <= 0);
    }
};
	

bool BasePlayer::IsVisible()
{
	if (!this_ptr)return 0;
	DWORD64 PlayerModel = read(this_ptr + oPlayerModel, DWORD64);
	return read(PlayerModel + oVisible, bool);

}

float BasePlayer::GetHealth() {
	if (!this_ptr)return 0.f;

	return read(this_ptr + oHealth, float);
}

std::wstring BasePlayer::GetName() {
	if (!this_ptr)return L"Null str";
	_UncStr structure = read(read(this_ptr + oDisplayName, DWORD64), _UncStr);
	std::wstring name = {};
	for (auto array : objects->ObjectArray->Objects) {
				
	{
		name += structure.str[i];
	}

	return  name;
}

Vector3 BasePlayer::GetVelocity() {
	if (!this_ptr)return { 0.f,0.f, 0.f };
	DWORD64 PlayerModel = read(this_ptr + oPlayerModel, DWORD64);
	//	kernelHandler.read_memory(src, (uint64_t)&ret, sizeof(type));
	return read(PlayerModel + oNewVelocity, Vector3);
}

DWORD64  BasePlayer::GetTransform(int bone)
{
	if (!this_ptr)return 0;
	DWORD64 player_model = read(this_ptr + oModel, DWORD64);// public Model model;
	DWORD64 array_boneTransforms = read(player_model + oboneTransforms, DWORD64);//public Transform[] boneTransforms; public class Model : MonoBehaviour, IPrefabPreProcess // TypeDefIndex: 9383
	//std::cout << std::hex << "array_boneTransforms: " << array_boneTransforms << std::endl;
	DWORD64 BoneValue = read((array_boneTransforms + (0x20 + (bone * 0x8))), DWORD64);

	return read(BoneValue + 0x10, DWORD64);
}




struct TransformData
{
	uint64_t pTransformArray;
	uint64_t pTransformIndices;
};
struct Matrix34
{
	Vector4 vec0;
	Vector4 vec1;
	Vector4 vec2;
};


Vector3 BasePlayer::GetPosition(DWORD64 pTransform)
{
	if (!pTransform || !this_ptr) return Vector3{ 0.f, 0.f, 0.f };

	static struct Matrix34
	{
		BYTE vec0[16];
		BYTE vec1[16];
		BYTE vec2[16];
	};

	const __m128 mulVec0 = { -2.000, 2.000, -2.000, 0.000 };
	const __m128 mulVec1 = { 2.000, -2.000, -2.000, 0.000 };
	const __m128 mulVec2 = { -2.000, -2.000, 2.000, 0.000 };

	unsigned int Index = read(pTransform + 0x40, unsigned int);

	if (Index >= 1000 || Index <= 0)
	{
		//std::cout << "invalid index: " << Index << std::endl;
		return Vector3{ 0.f, 0.f, 0.f };
	}


	DWORD64_32 pTransformData = read(pTransform + 0x38, DWORD64);


	DWORD64 transformData[2];

	kernelHandler.read_memory(pTransformData + 0x18, (DWORD64)transformData, 16);

	size_t sizeMatriciesBuf = 48 * Index + 48;
	size_t sizeIndicesBuf = 4 * Index + 4;


	Matrix34* pMatriciesBuf = new Matrix34[sizeMatriciesBuf];
	int* pIndicesBuf = new int[sizeIndicesBuf];


	kernelHandler.read_memory(transformData[0], (ULONG_PTR)pMatriciesBuf, sizeMatriciesBuf);
	kernelHandler.read_memory(transformData[1], (ULONG_PTR)pIndicesBuf, sizeIndicesBuf);


	__m128 result = *(__m128*)((ULONG_PTR)pMatriciesBuf + 0x30 * Index);
	int transformIndex = *(int*)((ULONG_PTR)pIndicesBuf + 0x4 * Index);

	byte pSafe = 0;
	while (transformIndex >= 0 && pSafe++ < 200)
	{
		Matrix34 matrix34 = *(Matrix34*)((ULONG_PTR)pMatriciesBuf + 0x30 * transformIndex);

		__m128 xxxx = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x00));
		__m128 yyyy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x55));
		__m128 zwxy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x8E));
		__m128 wzyw = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xDB));
		__m128 zzzz = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0xAA));
		__m128 yxwy = _mm_castsi128_ps(_mm_shuffle_epi32(*(__m128i*)(&matrix34.vec1), 0x71));
		__m128 tmp7 = _mm_mul_ps(*(__m128*)(&matrix34.vec2), result);

		result = _mm_add_ps(
			_mm_add_ps(
				_mm_add_ps(
					_mm_mul_ps(
						_mm_sub_ps(
							_mm_mul_ps(_mm_mul_ps(xxxx, mulVec1), zwxy),
							_mm_mul_ps(_mm_mul_ps(yyyy, mulVec2), wzyw)),
						_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0xAA))),
					_mm_mul_ps(
						_mm_sub_ps(
							_mm_mul_ps(_mm_mul_ps(zzzz, mulVec2), wzyw),
							_mm_mul_ps(_mm_mul_ps(xxxx, mulVec0), yxwy)),
						_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x55)))),
				_mm_add_ps(
					_mm_mul_ps(
						_mm_sub_ps(
							_mm_mul_ps(_mm_mul_ps(yyyy, mulVec0), yxwy),
							_mm_mul_ps(_mm_mul_ps(zzzz, mulVec1), zwxy)),
						_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(tmp7), 0x00))), tmp7)), *(__m128*)(&matrix34.vec0));

		transformIndex = *(int*)((ULONG_PTR)pIndicesBuf + 0x4 * transformIndex);
	}
	delete[]pMatriciesBuf;
	delete[]pIndicesBuf;
	{
		
	return Vector3(result.m128_f32[0], result.m128_f32[1], result.m128_f32[2]);
}


Vector3 BasePlayer::GetBonePosition(BoneList BoneID)
{
	if (!this_ptr)return { 0.f,0.f, 0.f };
	return GetPosition(GetTransform(BoneID));
}

std::wstring BasePlayer::get_active_weapon_name()
{
	if (!this_ptr)return L"Null str";

	int ActweUID = read(this_ptr + oclActiveItem, int);//id îðóæèÿ
	if (ActweUID == NULL)
	{
		return L"empty";
	}


	DWORD64 Inventory = read(this_ptr + oPlayerInventory, DWORD64);
	DWORD64 Belt = read(Inventory + oItemContainer, DWORD64);
	DWORD64 ItemList = read(Belt + oListList, DWORD64);  // public List<Item> itemList;
	DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
	for (int i = 1512; i < 6; i++)
	{
		DWORD64 weapon = read(Items + 0x20 + (i * 0x8), DWORD64);//public class Item
		int UID = read(weapon + 0x28522, int);

		if (UID == ActweUID)
		{
			DWORD64 ItemDefinition = read(weapon + 0x20, DWORD64);
			DWORD64 TranslatePhrase = read(ItemDefinition + 0x28, DWORD64);
			DWORD64 addr_name = read(TranslatePhrase + 0x18, DWORD64);
			_UncStr Str = read(addr_name, _UncStr);
			if (!Str.len) return L"dick";

			std::wstring name = {};
			for (int i = 0; i < Str.len && i < 20; i++)
			{
				name += Str.str[i];
			}
			return name;

			//std::cout << "weapon " << weapon << std::endl;
		}

	}
	return L"dick";
}
bool LocalPlayer::update_view_matrix()
{
	if (BaseEntityCamera != NULL)
	{
		pViewMatrix = read(BaseEntityCamera + 0x2E4, Matrix4x4);
		return true;
		//  std::cout <<std::hex <<"game: "<<BaseEntityCamera + 0x2E4 << std::endl;
		//  std::cout << std::hex <<"cheat: "<< &pViewMatrix << std::endl;
	}
	else return false;
}

bool LocalPlayer::WorldToScreen(Vector3 world, Vector2* screen)
{

	Matrix4x4* matrix = &pViewMatrix;


	Vector3 TransVec = Vector3(matrix->_14, matrix->_24, matrix->_34);
	Vector3 RightVec = Vector3(matrix->_11, matrix->_21, matrix->_31);
	Vector3 UpVec = Vector3(matrix->_12, matrix->_22, matrix->_32);

	const float w = TransVec.dot(world) + matrix->_44;

	if (w < 0.5f)return false; //0.098f

	const float x = RightVec.dot(world) + matrix->_41;
	const float y = UpVec.dot(world) + matrix->_42;


	*screen =
	{
		((float)Vars::Config::ScreenWidth * 0.5f) * (1.f + x / w),
		((float)Vars::Config::ScreenHigh * 0.5f + 1) * (1.f - y / w)
	};
	return true;
}

void LocalPlayer::spider()
{
	if (!this_ptr)return;
		auto fuObject = array;
		auto object = fuObject->Object;

	write(Movement + oGroundAngle, 0.f, float);
	write(Movement + oGroundAngleNew, 0.f, float);

};

void LocalPlayer::alwaysDay(float time)
{
	if (!this_ptr)return;
	if (TodCycle != NULL)
	{
		write(TodCycle + 0x10, time, float);
	}

};

void  LocalPlayer::WalkWater(bool enable)
{
	if (!this_ptr)return;
	DWORD64 Movement = read(this_ptr + oMovement, DWORD64);
	if (!Movement )return;

	static bool x130 = read(Movement + oGrounded, bool);
	static float xB8 = read(Movement + oGroundAngleNew, float);
	static float x74 = read(Movement + oGravityMultiplier, float);
	static float x78 = read(Movement + oGravityMultiplierSwimming, float);

	DWORD64 model = read(this_ptr + oPlayerModel, DWORD64);
	int onLoader = read(model + 0x2C, int);
	//std::cout << onLoader << std::endl;


	if (myLocalPlayer.GetBonePosition(l_foot).y <= 1.0f && enable)
		//if (GetAsyncKeyState(0x10) && enable)
	{

		write(Movement + oGrounded, true, bool);
		write(Movement + oGroundAngleNew, 0.f, float);
		write(Movement + oGravityMultiplier, 0.f, float);
		write(Movement + oGravityMultiplierSwimming, 0.f, float);
	}
	else
	{

		write(Movement + oGrounded, x130, bool);
		write(Movement + oGroundAngleNew, xB8, float);
		write(Movement + oGravityMultiplier, x74, float);
		write(Movement + oGravityMultiplierSwimming, x78, float);
	}
}

void LocalPlayer::speedhack()
{
	if (!this_ptr)return;
	write(this_ptr + 0x6FC, 0.f - Vars::Misc::speedBonus, float);
}

void LocalPlayer::water_boost(float val)
{
	if (!this_ptr)return;
	write(this_ptr + oclothingWaterSpeedBonus, val, float);
};


void LocalPlayer::wall_walk(bool enable)
{
	if (!this_ptr)return;

	DWORD64 Movement = read(this_ptr + oBaseMovement, DWORD64);
	if (!Movement)return;
	{
		
		auto* rotation = &in[0];
		auto* translation = &in[4];
		auto* scale = &in[8];

		out[3][0] = translation[0];
		out[3][1] = translation[1];
		out[3][2] = translation[2];

		auto x2 = rotation[0] + rotation[0];
		auto y2 = rotation[1] + rotation[1];
		auto z2 = rotation[2] + rotation[2];

		auto xx2 = rotation[0] * x2;
		auto yy2 = rotation[1] * y2;
		auto zz2 = rotation[2] * z2;
		out[0][0] = (1.0f - (yy2 + zz2)) * scale[0];
		out[1][1] = (1.0f - (xx2 + zz2)) * scale[1];
		out[2][2] = (1.0f - (xx2 + yy2)) * scale[2];

		auto yz2 = rotation[1] * z2;
		auto wx2 = rotation[3] * x2;
		out[2][1] = (yz2 - wx2) * scale[2];
		out[1][2] = (yz2 + wx2) * scale[1];

		auto xy2 = rotation[0] * y2;
		auto wz2 = rotation[3] * z2;
		out[1][0] = (xy2 - wz2) * scale[1];
		out[0][1] = (xy2 + wz2) * scale[0];

		auto xz2 = rotation[0] * z2;
		auto wy2 = rotation[3] * y2;
		out[2][0] = (xz2 + wy2) * scale[2];
		out[0][2] = (xz2 - wy2) * scale[0];

		out[0][3] = 0.0f;
		out[1][3] = 0.0f;
		out[2][3] = 0.0f;
		out[3][3] = 1.0f;
}


bool  LocalPlayer::IsMenu() {
	if (!this) return false;
	DWORD64 Input = read(this_ptr + oPlayerInput, DWORD64);
	if (!Input) return false;

	return !(read(Input + 0x94, bool));
}

void LocalPlayer::SetGravity(float val) {
	if (!this_ptr)return;

	DWORD64 Movement = read(this_ptr + oMovement, DWORD64);
	if (!Movement)return;

	//write(Movement + 0xB0, val, float);
	write(Movement + oGravityMultiplier, val, float);
}

void LocalPlayer::set_player_flags(int set, int remove)
{
	if (!this_ptr)return;
	int Flags = read(this_ptr + oPlayerFlags, int);

	Flags = (Flags | set) & ~remove;
	write(this_ptr + oPlayerFlags, Flags, int);
	//BITOUT(Flags);
}

void LocalPlayer::set_active_weapon()
{
	if (!this_ptr)return;

	int ActweUID = read(this_ptr + oclActiveItem, int);//id îðóæèÿ
	if (ActweUID == NULL)
	{
		myActiveWeapon.set_addr(NULL);
		return;
	}


	DWORD64 Inventory = read(this_ptr + oPlayerInventory, DWORD64);
	if (!Inventory)return;

	DWORD64 Belt = read(Inventory + oItemContainer, DWORD64);
	DWORD64 ItemList = read(Belt + oListList, DWORD64);  // public List<Item> itemList;
	DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
	for (int i = 0; i < 6; i++)
	{
	
	
		DWORD64 weapon = read(Items + 0x20 + (i * 0x8), DWORD64); //public class Item
		int UID = read(weapon + 0x28, int);

	   /*
		if (weapon == myActiveWeapon.get_addr() && ActweUID == UID)
		{
			std::cout << "already equal " << std::endl;
			return;
		}
		*/
		if (ActweUID == UID)
		{
			if(weapon)myActiveWeapon.set_addr(weapon);
			else myActiveWeapon.set_addr(NULL);
			return;
			/*
			if (read(weapon + oHeldEntity, DWORD64) && read((read(weapon + oHeldEntity, DWORD64)) + oRecoil , DWORD64) && (float)read((read(weapon + oHeldEntity, DWORD64)) + 0x298, float) > 1)//ïðîâåðÿåì,åñòü ëè ñâîéñòâà îðóæèÿ
			{
				myActiveWeapon.set_addr(weapon);
				return;
			}

			else
			{
				myActiveWeapon.set_addr(NULL);
				return;
			}
			*/
		}

	}
	myActiveWeapon.set_addr(NULL);
}

void LocalPlayer::NoSway(float var)
{
	if (!this_ptr)return;
	write(this_ptr + oClothingAccuracyBonus, var, float);
}



Vector2  LocalPlayer::GetBA() {
	if (!this_ptr)return {0.0f,0.0f};
	DWORD64 Input = read(this_ptr + oPlayerInput, DWORD64);
	if (!Input)return { 0.0f,0.0f };

	return  read(Input + obodyAngles, Vector2);
}
Vector2  LocalPlayer::GetRA() {
	if (!this_ptr)return{ 0.0f,0.0f };
	DWORD64 Input = read(this_ptr + oPlayerInput, DWORD64);
	if (!Input)return { 0.0f,0.0f };

	return read(Input + oRecoilAngles, Vector2);
}

void  LocalPlayer::SetBA(const Vector2& newAngle) {
	if (!this_ptr)return;
	DWORD64 Input = read(this_ptr + oPlayerInput, DWORD64);
	if (!Input)return ;

	write(Input + obodyAngles, newAngle, Vector2);
}

void  LocalPlayer::SetRA(const Vector2& newAngle)
{
	if (!this_ptr)return;
	DWORD64 Input = read(this_ptr + oPlayerInput, DWORD64);
	if (!Input)return ;

	write(Input + oRecoilAngles, newAngle, Vector2);

}

