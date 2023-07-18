#include "LUAModule.h"
#include "LowLevelSystem.h"

using namespace DavinciEngine;

LUAModule *LUAModule::m_pLUAModule = nullptr;

LUAModule::LUAModule()
{
	// Create the LUA state and connect to tolua
	m_pLUAState = luaL_newstate();
	tolua_LuaInterface_open(m_pLUAState);

	// Load LUA standard libraries for functionality
	luaL_openlibs(m_pLUAState);
}

LUAModule::~LUAModule()
{
	lua_close(m_pLUAState);
}

LUAModule *LUAModule::GetInstance()
{
	if(!m_pLUAModule){
		m_pLUAModule = new LUAModule();
	}
	return m_pLUAModule;
}

void LUAModule::Destroy()
{
	if(m_pLUAModule){
		delete m_pLUAModule;
		m_pLUAModule = nullptr;
	}
}

lua_State *LUAModule::GetLuaState(){
	return m_pLUAState;
}

bool LUAModule::RunScript(const char *scriptFile)
{
	int luaResult;

	// Load the script file into the LUA State
	luaResult = luaL_loadfile(m_pLUAState, scriptFile);

	// Check to see if the script file was loaded successfully
	if (luaResult != LUA_OK) {
		const char* errmsg = lua_tostring(m_pLUAState, -1);
		if (!errmsg) {
			errmsg = "No LUA error message.";
		}
		Error("LUA Error %i: %s", luaResult, errmsg);
		return false;
	}

	// Run the script that was loaded into the state
	luaResult = lua_pcall(m_pLUAState, 0, LUA_MULTRET, 0);

	// Check for any errors returned from the script
	if (luaResult != LUA_OK) {
		const char* errmsg = lua_tostring(m_pLUAState, -1);
		if (!errmsg) {
			errmsg = "No LUA error message.";
		}
		Error("LUA Error %i: %s", luaResult, errmsg);
		return false;
	}
	return true;
}