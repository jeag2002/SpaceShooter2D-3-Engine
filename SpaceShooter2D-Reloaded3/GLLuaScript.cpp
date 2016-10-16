#include "GLLuaScript.h"


void GLLuaScript::executeLuaCollScript(){



}




void GLLuaScript::executeLuaScript(){

    //lua_pcall(L, 0, LUA_MULTRET, 0);

    lua_State *L = lua_open();
    luaL_openlibs(L);
    //luaL_loadString
    if (luaL_loadfile(L, name_file) || lua_pcall(L, 0, 0, 0)) {
        printf("Error al compilar el script %s ::= %s \r\n", name_file, lua_tostring(L, -1));
    }else{
        printf("Script compilado %s \r\n", name_file);
    }


    lua_getglobal(L, name_function);
    if(!lua_isfunction(L,-1))
    {
        printf("Funcion No Cargada Correctamente %s\r\n",name_function);
        lua_pop(L,1);
    }else{

        printf("Funcion Recuperada %s\r\n",name_function);
        for(int i=0; i<ilParams.size();i++){
            parameterDataType dummy = getInputParameterDef(ilParams[i]);
            printf("input parameters name-(%s) type-(%s) value-(%s)\r\n",(std::get<0>(dummy)).c_str(),(std::get<1>(dummy)).c_str(),(std::get<2>(dummy)).c_str());
            std::string typeParam = (std::get<1>(dummy));
            std::string inputParam = (std::get<2>(dummy));

            if ((strncmp(typeParam.c_str(), FLOAT, strlen(FLOAT))==0) ||
            (strncmp(typeParam.c_str(), DOUBLE, strlen(DOUBLE))==0) ||
            (strncmp(typeParam.c_str(), INTEGER, strlen(INTEGER))==0)){
                lua_pushnumber(L,atof(inputParam.c_str()));
            }else if (strncmp(typeParam.c_str(), STRING, strlen(STRING))==0) {
                lua_pushstring(L,inputParam.c_str());
            }else{

            }


        }

        if (lua_pcall(L,ilParams.size(), olParams.size(),0)){
             printf("error running function %s: %s\r\n",name_function,lua_tostring(L, -1));
        }

        for(int j=0; j<olParams.size(); j++){

            parameterDataType dummy = getOutputParameterDef(olParams[j]);
            std::string typeParam = (std::get<1>(dummy));

            if ((strncmp(typeParam.c_str(), FLOAT, strlen(FLOAT))==0) ||
            (strncmp(typeParam.c_str(), DOUBLE, strlen(DOUBLE))==0) ||
            (strncmp(typeParam.c_str(), INTEGER, strlen(INTEGER))==0)){

                if (!lua_isnumber(L, -1)) {
                    printf("function %s must return a number \r\n",name_function);
                }else{
                    double returnValue = lua_tonumber(L, -1);

                    char buffer[12];
                    int i = 20;
                    snprintf(buffer, 12,"%f",returnValue);
                    std::string bufferStr(buffer);
                    std::get<2>(dummy) = bufferStr;

                    printf("function %s ::= %f \r\n",name_function,returnValue);
                }
            }else if (strncmp(typeParam.c_str(), STRING, strlen(STRING))==0) {

                if (!lua_isstring(L, -1)) {
                    printf("function %s must return a string \r\n",name_function);
                }else{
                    std::string returnValue = lua_tostring(L, -1);
                    std::get<2>(dummy) = returnValue;
                    printf("function %s ::= %s \r\n",name_function,returnValue.c_str());
                }

            }else{

            }

            updateOutputParameter(olParams[j],dummy);

        }

        lua_pop(L,1);
    }

    lua_close(L);
}
