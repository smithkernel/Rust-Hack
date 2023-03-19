#include "loops.h"
#include <future>
using namespace std;

namespace Aimbot {
	std::map<std::string, float> BulletSpeeds = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.2f },
		{ std::string("ammo.rifle.explosive"), 0.6f },
		{ std::string("ammo.rifle.incendiary"), 0.6f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.33333f },
		{ std::string("ammo.pistol.incendiary"), 0.75f },

		{ std::string("arrow.wooden"), 1.0f },
		{ std::string("arrow.hv"), 1.6f },
		{ std::string("arrow.fire"), 0.8f },
		{ std::string("arrow.bone"), 0.9f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 2.25f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 2.25f },

		{ std::string("ammo.nailgun.nails"), 1.0f }
	};

	std::map<std::string, float> BulletGravity = {
		{ std::string("ammo.rifle"), 1.0f },
		{ std::string("ammo.rifle.hv"), 1.0f },
		{ std::string("ammo.rifle.explosive"), 1.25f },
		{ std::string("ammo.rifle.incendiary"), 1.0f },

		{ std::string("ammo.pistol"), 1.0f },
		{ std::string("ammo.pistol.hv"), 1.0f },
		{ std::string("ammo.pistol.incendiary"), 1.0f },

		{ std::string("arrow.wooden"), 0.75f },
		{ std::string("arrow.hv"), 0.5f },
		{ std::string("arrow.fire"), 1.0f },
		{ std::string("arrow.bone"), 0.75f },

		{ std::string("ammo.handmade.shell"), 1.0f },
		{ std::string("ammo.shotgun.slug"), 1.0f },
		{ std::string("ammo.shotgun.fire"), 1.0f },
		{ std::string("ammo.shotgun"), 1.0f },

		{ std::string("ammo.nailgun.nails"), 0.75f }
	};

	
	for (DWORD64 BaseObject = read(ObjMgr + 0x8, DWORD64); BaseObject && BaseObject != read(ObjMgr, DWORD64); BaseObject = read(BaseObject + 0x8, DWORD64))
	{
		DWORD64 GameObject = read(BaseObject + 0x10, DWORD64);
		WORD Tag = read(GameObject + 0x54, WORD);

		DWORD64 ObjectClass = read(GameObject + 0x30, DWORD64);
		DWORD64	Entity = read(ObjectClass + 0x18, DWORD64);


		if (Tag == 14) // Select
		{
			//std::cout <<6 << std::endl;
			//cout << "entity" << endl;
		}

		//camera
		else if (Tag == 5)
		{
		//	std::cout << 5 << std::endl;
			 
			//std::cout << GameObject << std::endl;
		    //std::cout << ObjectClass << std::endl;
			//std::cout << Entity << std::endl;

			myLocalPlayer.ObjectClassCamera = ObjectClass;
			myLocalPlayer.BaseEntityCamera = Entity;
		}


		//sky
		else if (Tag == 20011)
		{
			//std::cout << 20011 << std::endl;

		}


	}
}


static bool localPlayerIsExist = false;
static vector<objInf> draw_entities = {};
static std::mutex drawnerMtx;
void BaseNetworkable_loop(DWORD64 BaseNetworkable)
{

void Globals::clear_ores() 
{
	this->ores.mutex.lock();
	this->ores.map.clear();
	this->ores.mutex.unlock();

	if (!ClientEntities_values) return;
	int EntityCount = read(ClientEntities_values + 0x10, int);

	DWORD64 EntityBuffer = read(ClientEntities_values + 0x18, DWORD64);

	localPlayerIsExist = false;
	vector<objInf> BN_draw_entities = {};
	for (int i = 0; i < EntityCount; i++)
	{
		DWORD64 Entity = read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);//BaseEntity
		//std::cout<<"Entity:" << Entity << std::endl;
		if (Entity <= 100000) continue;

		DWORD64 Object = read(Entity + 0x10, DWORD64);
		if (Object <= 100000) continue;
		
		DWORD64 ObjectClass = read(Object + 0x30, DWORD64); //CGameObject
		if (ObjectClass <= 100000) continue;

		if (read(ObjectClass + 0x54, int16_t)==6)
		{
			std::cout << "Object:" << Object << std::endl;
		}

		DWORD64 addr_name = read(ObjectClass + 0x60, DWORD64);

		static char BNname[110] = { '\0' }; //èìÿ òåêóùåãî îáüåêòà 
		kernelHandler.read_memory(addr_name, (uint64_t)BNname, sizeof(BNname));
		BNname[109] = { '\0' };


	

		objInf currentObj;
		if (strstr(BNname, "LocalPlayer"))
		{
		
			localPlayerIsExist = true;
			myLocalPlayer.set_addr(read(Object + 0x28, DWORD64));
			
			
		//entity
		else if (Vars::Esp::playerEsp && strstr(BNname, "player.prefab") && !strstr(BNname, "prop") && !strstr(BNname, "corpse"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::player;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::playerCorpse && strstr(BNname, "player_corpse.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::corpse;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::playerCorpse && strstr(BNname, "item_drop_backpack.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::backpack;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::npcEsp && (strstr(BNname, "scientist") && !strstr(BNname, "corpse")))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::npc;
			BN_draw_entities.push_back(currentObj);
		}

		//loot
		else if (Vars::Esp::stone && strstr(BNname, "stone-ore.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::stone;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::sulphur && strstr(BNname, "sulfur-ore.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::sulfur;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::metal && strstr(BNname, "metal-ore.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::metal;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::hemp && strstr(BNname, "hemp-collectable.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::hemp;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::dropItems && strstr(BNname, "(world)"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::world;
			BN_draw_entities.push_back(currentObj);
		}

		else if (Vars::Esp::airdrop && strstr(BNname, "supply_drop.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::supply;
			BN_draw_entities.push_back(currentObj);
		}

		//etc
		else if (Vars::Esp::landAirTurret && strstr(BNname, "sam_site_turret_deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::sam_site_turret;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::autoTurret && strstr(BNname, "autoturret_deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::autoturret;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::guntrap && strstr(BNname, "guntrap.deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::guntrap;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::flameturret && strstr(BNname, "flameturret.deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::flameturret;
			BN_draw_entities.push_back(currentObj);
		}

		else if (Vars::Esp::cupboard && strstr(BNname, "cupboard.tool.deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::cupboard;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::largeBox && strstr(BNname, "box.wooden.large.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::box_wooden_large;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::smallBox && strstr(BNname, "woodbox_deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::woodbox_deployed;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::stash && strstr(BNname, "small_stash_deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::small_stash;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::sleepingbag && strstr(BNname, "sleepingbag_leather_deployed.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::sleepingbag;
			BN_draw_entities.push_back(currentObj);
		}

		else if (Vars::Esp::minicopter && strstr(BNname, "minicopter.entity.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::minicopter;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::cow && strstr(BNname, "scraptransporthelicopter.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::scraptransporthelicopter;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::boat && strstr(BNname, "rowboat.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::rowboat;
			BN_draw_entities.push_back(currentObj);
		}
		else if (Vars::Esp::bigBoat && strstr(BNname, "rhib.prefab"))
		{
			currentObj.objAddr = Object;
			currentObj.prefabNumber = ObjList::rhib;
			BN_draw_entities.push_back(currentObj);
		}
	}

	drawnerMtx.lock();
	draw_entities.clear();
	draw_entities = BN_draw_entities;
	drawnerMtx.unlock();


	Vars::Config::LocalPlayerIsValid = (localPlayerIsExist == true ? true : false);
	if (localPlayerIsExist == true)
	{
		Vars::Config::LocalPlayerIsValid = true;
	}
	else
	{
		Vars::Config::LocalPlayerIsValid = false;
		myLocalPlayer.set_addr(NULL);
		myLocalPlayer.BaseEntityCamera = NULL;
		myLocalPlayer.TodCycle = NULL;
	}
}


class Entity{
    public:
        DWORD64 objAddr;
};

class LocalPlayer{
    public:
        bool updateViewMatrix() {
            // code to update view matrix
            return true;
        }
};

class GuiEngine{
    public:
        static void EspString(std::pair<int, int> position, const std::wstring& text) {
            // code to display text on screen
        }
};

class EspDrawner{
    public:
        std::vector<Entities> draw_entities;
        std::shared_ptr<LocalPlayer> myLocalPlayer;
        std::shared_ptr<GuiEngine> guiEngine;
        std::mutex drawnerMtx;

        void run() {
            assert(myLocalPlayer);
            assert(guiEngine);

            if (myLocalPlayer->updateViewMatrix()) {
                guiEngine->EspString({10, 55}, L"Entity draw count: " + std::to_wstring(draw_entities.size()));

                std::lock_guard<std::mutex> lock(drawnerMtx);
                for (const auto& entity : draw_entities) {
                    if (entity.objAddr > 100000) {
                        // code to process valid entities
                    }
                }

				DrawEsp::player_esp(Player, myLocalPlayer, Player.GetName());
			}
			else if (Vars::Esp::playerCorpse && (draw_entities[i].prefabNumber == (byte)ObjList::corpse || draw_entities[i].prefabNumber == (byte)ObjList::backpack))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64); //Tag 449
				if (!gameObject)continue;
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				if (!Trans)continue;
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos;
				if (myLocalPlayer.WorldToScreen(pos, &Pos))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos, (L"Corpse [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Red);
					//GuiEngine::Esp::CenterString(Pos,L"Corpse", D2D1::ColorF::Red);
				}


			}
			avyscientist.prefab"))
			else if (Vars::Esp::npcEsp && (draw_entities[i].prefabNumber == (byte)ObjList::npc))
			{
				static BasePlayer player;
				player.set_addr(read(draw_entities[i].objAddr + 0x28, DWORD64)); //áåðåì BasePlayer èãðîêà
				if (!read(player.get_addr() + 0x4A8, DWORD64)) continue;//ïðîâåðÿåì òåêòóðó

				this->ores.mutex.lock();
				this->ores.map = map;
				this->ores.mutex.unlock();
			}

			else if (Vars::Esp::stone && (draw_entities[i].prefabNumber == (byte)ObjList::stone))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"stone [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Brown);

				}
			}
			else if (Vars::Esp::sulphur && (draw_entities[i].prefabNumber == (byte)ObjList::sulfur))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"sulfur [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Gold);
										std::map<uint64_t, Player> Globals::get_players()
						this->players.mutex.lock();
						std::map<uint64_t, Player> copy = this->players.map;
						this->players.mutex.unlock();

				}
			}
			else if (Vars::Esp::metal && (draw_entities[i].prefabNumber == (byte)ObjList::metal))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"metal [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Orange);

				}
			}
			else if (Vars::Esp::hemp && (draw_entities[i].prefabNumber == (byte)ObjList::hemp))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"hemp [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Green);

				}
			}
			else if (Vars::Esp::dropItems && (draw_entities[i].prefabNumber == (byte)ObjList::world))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				//std::cout << gameObject << std::endl;
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);
				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					std::wstring name;
					DWORD64 Entity = read(draw_entities[i].objAddr + 0x28, DWORD64);
					DWORD64 Item = read(Entity + 0x150, DWORD64);
					DWORD64 ItemDefinition = read(Item + 0x20, DWORD64);
					DWORD64 TranslatePhrase = read(ItemDefinition + 0x28, DWORD64);
					DWORD64 addr_name = read(TranslatePhrase + 0x18, DWORD64);
					_UncStr Str = read(addr_name, _UncStr);
					for (int i = 0; i < Str.len && i < 20; i++)
					{
						name += Str.str[i];
					}

					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (name + L" [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Violet);

				}
			}
			else if (Vars::Esp::airdrop && (draw_entities[i].prefabNumber == (byte)ObjList::supply))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"supply drop [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Purple);
				}
			}

			else if (Vars::Esp::landAirTurret && (draw_entities[i].prefabNumber == (byte)ObjList::sam_site_turret))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"land-air turret [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Red);
				}
			}
			else if (Vars::Esp::autoTurret && (draw_entities[i].prefabNumber == (byte)ObjList::autoturret))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"automatic [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Red);

				}
			}
			else if (Vars::Esp::guntrap && (draw_entities[i].prefabNumber == (byte)ObjList::guntrap))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"guntrap [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Red);
				}
			}
			else if (Vars::Esp::flameturret && (draw_entities[i].prefabNumber == (byte)ObjList::flameturret))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"flameturret [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Red);
				}
			}

			else if (Vars::Esp::cupboard && (draw_entities[i].prefabNumber == (byte)ObjList::cupboard))
			{
				//std::cout << std::hex << read(ObjectClass + 0x28, DWORD64)<<std::endl ;
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					if (Vars::Esp::cupboardPlayer && DrawEsp::InFov(Pos1))
					{
						DWORD64 Entity = read(draw_entities[i].objAddr + 0x28, DWORD64);
						std::cout << Entity << std::endl;
						DWORD64 Autorized = read(Entity + 0x580, DWORD64);
						DWORD countPlayer = read(Autorized + 0x18, DWORD);
						if (countPlayer > 0)
						{
							DWORD64 items = read(Autorized + 0x10, DWORD64);

							float h = 10.0f, w = 10.0f;
							countPlayer > 0 ? h = countPlayer * 15 : h;
							//ñ÷èòàåì ñàìóþ äëèííóþ ñòðîêó
							for (int i = 0; i < countPlayer; i++)
							{
								DWORD64 item = read(items + 0x20 + (i * 0x8), DWORD64);
								DWORD64 string_struct = read(item + 0x18, DWORD64);
								_UncStr structure = read(string_struct, _UncStr);
								if (structure.len * 10 > w)w = structure.len * 10;
							}

							GuiEngine::Esp::fill_rect(Pos1.x - w / 2, Pos1.y - h, w, h, D2D1::ColorF(D2D1::ColorF::Black, 0.5f));
							for (int i = 0; i < countPlayer; i++)
							{
								DWORD64 item = read(items + 0x20 + (i * 0x8), DWORD64);
								DWORD64 string_struct = read(item + 0x18, DWORD64);
								_UncStr structure = read(string_struct, _UncStr);
								std::wstring name = {};
								for (int i = 0; i < structure.len && i < 20; i++)
								{
									name += structure.str[i];
								}

								GuiEngine::Esp::CenterString({ Pos1.x,Pos1.y - (15 + i * 15) + 5 }, name.c_str());
							}
						}
						else
						{
							GuiEngine::Esp::fill_rect(Pos1.x - 20, Pos1.y - 8, 45, 18, D2D1::ColorF(D2D1::ColorF::Black, 0.5f));
							GuiEngine::Esp::CenterString(Pos1, L"Empty", D2D1::ColorF::White);
						}

					}
					else
					{
						static short dist;
						dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
						GuiEngine::Esp::CenterString(Pos1, (L"cupboard [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Blue);
					}
				}
			}
			else if (Vars::Esp::largeBox && (draw_entities[i].prefabNumber == (byte)ObjList::box_wooden_large))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"large box [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Blue);
				}
			}
			else if (Vars::Esp::smallBox && (draw_entities[i].prefabNumber == (byte)ObjList::woodbox_deployed))
			{
				DWORD64 gameObject = read(ObjectClass + 0x301, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x382, DWORD64);
				Vector3 pos = read(Vec + 0x901, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"small box [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Blue);
				}
			}
			else if (Vars::Esp::stash && (draw_entities[i].prefabNumber == (byte)ObjList::small_stash))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"small stash [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Blue);
				}
			}
			else if (Vars::Esp::sleepingbag && (draw_entities[i].prefabNumber == (byte)ObjList::sleepingbag))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8124, DWORD64);
				DWORD64 Vec = read(Trans + 0x3834, DWORD64);
				Vector3 pos = read(Vec + 0x9011, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"Fixed bag [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Blue);
				}
			}

			else if (Vars::Esp::minicopter && (draw_entities[i].prefabNumber == (byte)ObjList::minicopter))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"minicopter [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Aqua);
				}
			}
			else if (Vars::Esp::cow && (draw_entities[i].prefabNumber == (byte)ObjList::scraptransporthelicopter))
			{
				DWORD64 gameObject = read(ObjectClass + 0x3031, DWORD64);
				DWORD64 Trans = read(gameObject + 0x812, DWORD64);
				DWORD64 Vec = read(Trans + 0x384, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"begemot [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Aqua);
				}
			}
			else if (Vars::Esp::boat && (draw_entities[i].prefabNumber == (byte)ObjList::rowboat))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"boat [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Aqua);
				}
			}
			else if (Vars::Esp::boat && (draw_entities[i].prefabNumber == (byte)ObjList::rhib))
			{
				DWORD64 gameObject = read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = read(Trans + 0x38, DWORD64);
				Vector3 pos = read(Vec + 0x90, Vector3);

				Vector2 Pos1;
				if (myLocalPlayer.WorldToScreen(pos, &Pos1))
				{
					static short dist;
					dist = Math::Calc3D_Dist(pos, myLocalPlayer.GetBonePosition(head));
					GuiEngine::Esp::CenterString(Pos1, (L"Random %n [" + std::to_wstring(dist) + L"m]").c_str(), D2D1::ColorF::Aqua);
				}
			}

		}
		drawnerMtx.unlock();

		if (Vars::Misc::crosshair)GuiEngine::Esp::Crosshair(Vars::Config::ScreenWidth, Vars::Config::ScreenHigh, { 255,255,255,0.7f }, 1.5f);
		if (Vars::Aim::drawFov)GuiEngine::Esp::Ñircle({ (float)Vars::Config::ScreenWidth / 2,(float)Vars::Config::ScreenHigh / 2 }, { 255,255,255,0.7f }, Vars::Aim::fov, 1.f);
	}
}



/*
int wchars_num = MultiByteToWideChar(CP_UTF8, 0, ESPname, -1, NULL, 0);
wchar_t* wstr = new wchar_t[wchars_num];
MultiByteToWideChar(CP_UTF8, 0, ESPname, -1, wstr, wchars_num);
delete[] wstr;
*/
void misc()
{
    if (!Vars::Config::LocalPlayerIsValid) {
        return;
    }

    MyPlayer& player = myLocalPlayer;

    if (Vars::Misc::spider) {
        player.spider();
    }

    if (Vars::Misc::alwaysDay) {
        player.alwaysDay(Vars::Misc::alwaysDay_float);
    }

    if (Vars::Misc::speedhack) {
        player.speedhack();
    }

    static bool trigger_AdminMode = false;
    if (Vars::Misc::AdminMode != trigger_AdminMode) {
        player.set_player_flags(Vars::Misc::AdminMode ? 4 : 0, 4);
        trigger_AdminMode = Vars::Misc::AdminMode;
    }

    static bool trigger_ThirdPersonMode = false;
    if (Vars::Misc::ThirdPersonMode != trigger_ThirdPersonMode) {
        player.set_player_flags(Vars::Misc::ThirdPersonMode ? 1024 : 0, 1024);
        trigger_ThirdPersonMode = Vars::Misc::ThirdPersonMode;
    }

    static bool trigger_WatterBoost = false;
    if (Vars::Misc::WatterBoost != trigger_WatterBoost) {
        player.water_boost(Vars::Misc::WatterBoost ? 2.0f : 0.0f);
        trigger_WatterBoost = Vars::Misc::WatterBoost;
    }

    static bool trigger_WalkWatter = false;
    if (Vars::Misc::walkWatter != trigger_WalkWatter) {
        player.WalkWater(Vars::Misc::walkWatter);
        trigger_WalkWatter = Vars::Misc::walkWatter;
    }

    static bool trigger_HigthWalk = false;
    if (Vars::Misc::WallWalk != trigger_HigthWalk) {
        player.wall_walk(Vars::Misc::WallWalk);
        trigger_HigthWalk = Vars::Misc::WallWalk;
    }

    static bool trigger_HigthJump = false;
    if (Vars::Misc::HigthJump != trigger_HigthJump) {
        player.SetGravity(Vars::Misc::HigthJump ? 1.4f : 2.5f);
        trigger_HigthJump = Vars::Misc::HigthJump;
    }

    static bool trigger_NoSway = false;
    if (Vars::Aim::NoSway != trigger_NoSway) {
        player.NoSway(Vars::Aim::NoSway ? 0.99f : 0.0f);
        trigger_NoSway = Vars::Aim::NoSway;
    }
}




