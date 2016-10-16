#include "LuaMotor.h"

//#include "Utils.h"

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


//http://www.cprogramming.com/tutorial/function-pointers.html
//http://cc.byexamples.com/2008/07/15/calling-lua-function-from-c/
//http://forums.verlihub-project.org/viewtopic.php?f=26&t=4307


 LuaMotor::LuaMotor(void){
    L=lua_open();
    luaopen_io(L);
    luaopen_base(L);
    luaopen_table(L);
    luaopen_string(L);
    luaopen_math(L);
    //luaopen_loadlib(L);
    luaL_openlibs(L);
 }


 void LuaMotor::loadScript(char * filename){
    //LUA 5.1
    //if (luaL_dofile(L, filename)!=0){
    //LUA 5.0.3
    if (luaL_loadfile(L,filename)!=0){
        printf("%s",lua_tostring(L,-1));
        //exit(-1);
    }
 }

 void LuaMotor::registerExternFunction(char *functionC){
       lua_register(L, functionC, NULL);
 }

 void LuaMotor::executeScript(char *functionLua, int *parameters, int size){

       lua_getglobal(L, functionLua);

       if(!lua_isfunction(L,-1)){
            printf("funcion %s no reconocida", functionLua);
            lua_pop(L,1);
       }

       for(int i=0; i<size; i++ ){
            lua_pushnumber(L, parameters[i]);
       }

       if (lua_pcall(L, size, 1, 0) != 0) {
            printf("error ejecucion funcion %s: %s",functionLua,lua_tostring(L, -1));
            //exit(-1);
       }

        if (!lua_isnumber(L, -1)) {
            printf("funcion %s no devuelve un valor valida",functionLua);
            //exit(-1);
        }

        printf("funcion %s ejecutada correctamente",functionLua);
        lua_pop(L, 1);
 }

 LuaMotor::~LuaMotor(){
    lua_close(L);
 }


