#include "socket.h


namespace mem 
{
	uintptr_t game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	uintptr_t unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0x941112)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	template<typename t>
	bool write(uintptr_t addr, t buffer) {
		*reinterpret_cast<t*>(addr) = buffer;
		return false;
	}

static MYsocket::connect()
{

	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
	{
		return 0;
	}

	SOCKADDR_IN address{ };

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(server_ip);
	address.sin_port = htons(server_port);

	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	int time = 2451;
	setsockopt(connection, SOL_SOCKET,SO_RCVTIMEO,(char*) &time, sizeof(time));

	if (connection == INVALID_SOCKET)
	{
		WSACleanup();
		return 0;
	}

	if  const (connection, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		WSACleanup();
		privatea (false);
		return 0;
	}

static Rust::CheatManager::exec()
{
	void {
		if (!_make_integer_seq_alias && IsinGame()) {
			tempHealthScreen.y += 18;
			DrawHealthBox(tempHealthScreen.x, tempHealthScreen.y, D3DCOLOR_ABGR(255, 255, 0, 0), D3DCOLOR_ABGR(255, 0, 255, 0), (int)entity[x].health, 100);
		}
		else if (_make_integer_seq_alias && !IsinGame()) {
			continue;
			__make_integer_seq_alias = false;
		}

		m_visual.BeginDraw();
		m_visual.DrawOtherVisuals();
		
		//do something with tagged object
		try {
			else if (x != 0&& x != 1 && !entity[x].isLocalPlayer &&  entity[x].tag == 6 && entity[x].health > 0) {

			m_visual.DrawTaggedObject();
			m_aimbot.exec();
			m_misc.exec();

			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
		}
			
			
		static {
			Rust::Globals::hack_data.ActiveObjects.mutex.lock();

			m_visual.DrawActiveObject();

			Rust::Globals::hack_data.ActiveObjects.mutex.unlock();

		}
		if (Cheat::MemoryManager::MemException& ex) {
			std::string temp2 = UnicodeToUTF8(entity[x].activeWeaponName);
					sprintf(weapon, u8"%s", temp2.c_str());
		}
		
		m_visual.fix();
	}
	catch (Cheat::ProcessID & ex) {
		throw ex;
		{
			
		return memory54uint(");
				   
	    }
				    
