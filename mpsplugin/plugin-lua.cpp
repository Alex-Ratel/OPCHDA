extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "OpcMP_JSON.h"
#include "usclasses.h"
#include "usfunc.h"
#include "usplugin.h"
#include "usvariant.h"
static int Hello (lua_State *L) {	//��������, ���������� �� Lua-��������, ������ ��������� ������ ���� �������� - ����� ������� lua_State, ������� �������� ���������� � ��������� Lua
	char *Message="Hello from dll";
	lua_pushstring(L,Message);
	return 1;
}
static int Add (lua_State *L) {	//��������, ���������� �� Lua-��������, ������ ��������� ������ ���� �������� - ����� ������� lua_State, ������� �������� ���������� � ��������� Lua
	int a = luaL_checknumber(L,1);
	int b = luaL_checknumber(L,2);
	int c = a+b;
	lua_pushnumber(L,c);
	return 1;
}

//������ luaL_reg, ���������� ������ �������, ������� ����� ����� �������  �� �������. � ����� ������ ������� ����� ����.
static const struct luaL_reg userfunctions[] = {
	{"Hello",Hello},
	{"Add",Add},
	{NULL, NULL},	//��� ������ ������ ��������� ��������� ������� ������� luaL_reg
};
OpcMP_status_t PLUGIN_LUAAPI(OpcMP_plugin_t * plugin,OpcMP_Handle *LuaApi)
{
	*LuaApi = (OpcMP_Handle)&userfunctions[0]; 
	return OPCMP_SUCCESS;
}
extern "C" OPCMP_PLUGIN_EXPORT OpcMP_status_t OPCMP_PLUGIN_LUAAPI( OpcMP_plugin_t * plugin ,OpcMP_Handle *LuaApi);
OpcMP_status_t  OPCMP_PLUGIN_LUAAPI(OpcMP_plugin_t * plugin,OpcMP_Handle *LuaApi)
{
	return PLUGIN_LUAAPI(plugin,LuaApi);
}
