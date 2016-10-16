#ifndef GLLUASCRIPTMANAGER_H_INCLUDED
#define GLLUASCRIPTMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "ConfigFile.h"
#include "GLLuaScript.h"

class GLLuaScriptManager{

public:

     GLLuaScriptManager(){
        GLOBAL_TYPE = NULL;
        DATA_TYPE = NULL;
        gLogEngine = NULL;
     };

     GLLuaScriptManager(GlobalNew *_GLOBAL_TYPE, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
         GLOBAL_TYPE = _GLOBAL_TYPE;
         DATA_TYPE = _ENTITY_DATA;
         gLogEngine = _log;
         loadLuaLibraries();
     };

     void processLuaDefFile(char *gamezipfile);
    ~GLLuaScriptManager(){};

private:

    lua_State *L;
    GlobalNew *GLOBAL_TYPE;
    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;

    void loadLuaLibraries();

};

#endif // GLLUASCRIPTMANAGER_H_INCLUDED
