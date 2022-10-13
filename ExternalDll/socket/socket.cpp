#include "socket.h


namespace mem {
	uintptr_t game_assembly_base = LI_MODULE_SAFE_(_("GameAssembly.dll"));
	uintptr_t unity_player_base = LI_MODULE_SAFE_(_("UnityPlayer.dll"));
	template<typename t>
	t read(uintptr_t addr) {
		if (addr < 0xffffff)
			return t();
		if (addr > 0x7fffffff0000)
			return t();

		return *reinterpret_cast<t*>(addr);
	}

	template<typename t>
	bool write(uintptr_t addr, t buffer) {
		*reinterpret_cast<t*>(addr) = buffer;
		return true;
	}
	
	uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* target, const char* name_space);
}

bool MYsocket::MYconnect()
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


	int time = 10000;
	setsockopt(connection, SOL_SOCKET,SO_RCVTIMEO,(char*) &time, sizeof(time));

	if (connection == INVALID_SOCKET)
	{
		WSACleanup();
		return 0;
	}

	if (connect(connection, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		WSACleanup();
		closesocket(connection);
		return 0;
	}
	return 1;
}

void Rust::CheatManager::exec()
{
	//if in game 
	try {
		if (!m_previousInGame && IsinGame()) {
			Rust::EntityUpdator::UpdateLocalPlayerAndCameraData();
			m_previousInGame = true;
		}
		else if (m_previousInGame && !IsinGame()) {
			m_previousInGame = false;
		}

		m_visual.BeginDraw();
		m_visual.DrawOtherVisuals();
		
		//do something with tagged object
		try {
			Rust::Globals::hack_data.TaggedObject.mutex.lock();

			m_visual.DrawTaggedObject();
			m_aimbot.exec();
			m_misc.exec();

			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
		}
		catch (Cheat::MemoryManager::MemException& ex) {
			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
		}

		//do something with active object when you can
		try {
			Rust::Globals::hack_data.ActiveObjects.mutex.lock();

			m_visual.DrawActiveObject();

			Rust::Globals::hack_data.ActiveObjects.mutex.unlock();

		}
		catch (Cheat::MemoryManager::MemException& ex) {
			Rust::Globals::hack_data.TaggedObject.mutex.unlock();
		}
		
		m_visual.EndDraw();
	}
	catch (Cheat::cexception& ex) {
		throw ex;
	}
