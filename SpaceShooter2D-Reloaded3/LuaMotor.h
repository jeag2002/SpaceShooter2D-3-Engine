#ifndef LUAMOTOR_H_INCLUDED
#define LUAMOTOR_H_INCLUDED

#include "Stdafx.h"

using namespace std;

class LuaMotor{

public:
        LuaMotor();
        ~LuaMotor();
        void loadScript(char * filename);
        void executeScript(char *functionLua, int *parameters, int size);
        void registerExternFunction(char *functionC);
private:
        lua_State *L;
};

#endif // LUA_H_INCLUDED
