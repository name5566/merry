#include "MerryCommand.h"
#include "MerryLua.h"
#include "MerryInformationDialog.h"

MerryCommand::MerryCommand(int commandID, const wxString& commandName, int funcRef, const wxString& triggerKey)
{
	m_commandID = commandID;
	m_commandName = commandName;
	m_commandFunc = funcRef;
	m_triggerKey = triggerKey;
}

MerryCommand::~MerryCommand()
{
	if (!g_lua)
		return;

	lua_State* L = g_lua->GetLua();
	assert(L);
	luaL_unref(L, LUA_REGISTRYINDEX, m_commandFunc);
}

void MerryCommand::ExecuteCommand(const wxString& commandArg) const
{
	if (!g_lua)
		return;

	lua_State* L = g_lua->GetLua();
	assert(L);

	lua_rawgeti(L, LUA_REGISTRYINDEX, m_commandFunc);
	assert(lua_isfunction(L, -1));
	lua_pushstring(L, commandArg.c_str());
	if (lua_pcall(L, 1, 0, 0))
	{
		new MerryInformationDialog(
			wxString::Format(wxT("Command %s execute failed"), m_commandName),
			wxString(lua_tostring(L, -1), wxConvLocal)
		);
		lua_pop(L, 1);
	}
}
