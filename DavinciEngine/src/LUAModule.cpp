#include "LUAModule.h"
#include "LowLevelSystem.h"
#include "DavinciEngine.h"

using namespace DavinciEngine;

LUAModule* LUAModule::m_pLUAModule = nullptr;

LUAModule::LUAModule()
{
	// Create the LUA state and connect to tolua
	m_LUAState.open_libraries(sol::lib::base,
		sol::lib::package,
		sol::lib::string,
		sol::lib::math,
		sol::lib::table,
		sol::lib::os,
		sol::lib::debug);

	// Load LUA standard libraries for functionality
	BindEngine();
}

LUAModule::~LUAModule()
{}

LUAModule* LUAModule::GetInstance()
{
	if (!m_pLUAModule) {
		m_pLUAModule = new LUAModule();
	}
	return m_pLUAModule;
}

void LUAModule::Destroy()
{
	if (m_pLUAModule) {
		delete m_pLUAModule;
		m_pLUAModule = nullptr;
	}
}

sol::state& LUAModule::GetLuaState() {
	return m_LUAState;
}

void LUAModule::BindEngine()
{
	m_LUAState.new_usertype<DavinciEngine::Davinci>("Davinci",
		"SetGameMode", &DavinciEngine::Davinci::SetGameMode,
		"LoadActor", &DavinciEngine::Davinci::LoadActor
	);

	auto engine = DavinciEngine::Davinci::Engine_GetInstance();
	m_LUAState["Engine"] = engine;
}

bool LUAModule::RunScript(const char* scriptFile)
{
	std::string path(scriptFile);

	sol::load_result script = m_LUAState.load_file(path);

	if (!script.valid())
	{
		sol::error err = script;
		Error("Lua Load Error: %s", err.what());
		return false;
	}

	sol::protected_function_result result = script();

	if (!result.valid())
	{
		sol::error err = result;
		Error("Lua Runtime Error: %s", err.what());
		return false;
	}

	return true;
}