/*
20151101 JALCARAZ SPACESHOOTER2D-RELOADED3 SINISTARENGINE.0.001.01
Motor carga desantendida de scripts de LUA.

http://stackoverflow.com/questions/21067779/lua-scripts-stored-in-memory

https://csl.name/post/lua-and-cpp/

https://eliasdaler.wordpress.com/2013/11/30/lua_and_cpp_pt3/

http://rubenlaguna.com/wp/2012/11/26/first-steps-lua-cplusplus-integration/

*/


#include "GLLuaScriptManager.h"


void GLLuaScriptManager::loadLuaLibraries(){


    //L=lua_open();
    //luaopen_io(L);
    //luaopen_base(L);
    //luaopen_table(L);
    //luaopen_string(L);
    //luaopen_math(L);
    //luaopen_loadlib(L);
    //luaL_openlibs(L);


    L = luaL_newstate();
    luaL_openlibs(L);

    INFOLOG("GLLuaScriptManager::loadLuaLibraries --> LUA LIBRARIES UPLOADED");

}

void GLLuaScriptManager::processLuaDefFile(char *gamezipfile){

      char buff[100];
      ConfigFile config(gamezipfile);

      std::string lua_file = "";
      std::string lua_functions = "";

      std::string lua_param = "";
      std::string lua_type = "";
      std::string lua_value = "";

      std::string path = "";

      std::string script_id = "";

      int num_files_lua = 0;
      int num_functions = 0;
      int num_param_input = 0;
      int num_param_output = 0;


      num_files_lua = config.read<int>("num_files");

      for(int i=1; i<= num_files_lua; i++){

            sprintf(buff, "%i_lua_file", i);
            path = buff;
            lua_file = config.read<std::string>(path);
            char* lua_file_cpy = new char[lua_file.length()+1];
            strcpy(lua_file_cpy, lua_file.c_str());

            //luaL_dofile(L, lua_file.c_str()); //regiistramos el fichero
            int status = (luaL_loadfile(L, lua_file_cpy) || lua_pcall(L, 0, 0, 0));
            //int status = 1;

            if (status){

               WARNLOGPTWO("GLuaScriptManager::processLuaDefFile --> ERROR EN EL SCRIPT %s ERROR %s", lua_file_cpy, lua_tostring(L, -1));

            }else{

                DEBUGLOGPONE("GLuaScriptManager::processLuaDefFile --> SCRIPT COMPILADO CORRECTAMENTE %s", lua_file.c_str());

                sprintf(buff, "%i_lua_functions", i);
                path = buff;

                num_functions = config.read<int>(path);

                for(int j=1; j<= num_functions; j++){

                    GLLuaScript *gLuaScript = new GLLuaScript(L);

                    /////////////////////////////////////////////////////////
                    sprintf(buff,"%i_lua_function_%i",i,j);
                    path = buff;
                    lua_functions = config.read<std::string>(path);
                    char* lua_functions_cpy = new char[lua_functions.length()+1];
                    strcpy(lua_functions_cpy, lua_functions.c_str());
                    /////////////////////////////////////////////////////////

                    /////////////////////////////////////////////////////////
                    sprintf(buff, "%i_lua_function_%i_id",i,j);
                    path = buff;
                    script_id = config.read<std::string>(path);
                    char* c_script_id_cpy = new char[script_id.length()+1];
                    strcpy(c_script_id_cpy, script_id.c_str());
                    /////////////////////////////////////////////////////////


                    sprintf(buff,"%i_lua_iparams_%i",i,j);
                    path = buff;
                    num_param_input = config.read<int>(path);

                    for(int z=1; z<=num_param_input; z++){

                        sprintf(buff,"%i_lua_iparam_name_%i_%i",i,j,z);
                        path = buff;
                        lua_param = config.read<std::string>(path);
                        char* lua_paramI_cpy = new char[lua_param.length()+1];
                        strcpy(lua_paramI_cpy, lua_param.c_str());
                        std::string lua_paramI_cpy_str(lua_paramI_cpy);

                        sprintf(buff,"%i_lua_iparam_type_%i_%i",i,j,z);
                        path = buff;
                        lua_type = config.read<std::string>(path);
                        char* lua_typeI_cpy = new char[lua_type.length()+1];
                        strcpy(lua_typeI_cpy, lua_type.c_str());
                        std::string lua_typeI_cpy_str(lua_typeI_cpy);

                        sprintf(buff,"%i_lua_iparam_value_%i_%i",i,j,z);
                        path = buff;
                        lua_value = config.read<std::string>(path);
                        char* lua_valueI_cpy = new char[lua_value.length()+1];
                        strcpy(lua_valueI_cpy, lua_value.c_str());
                        std::string lua_valueI_cpy_str(lua_valueI_cpy);

                        gLuaScript->setInputParameter(lua_paramI_cpy_str, lua_typeI_cpy_str, lua_valueI_cpy_str);
                        gLuaScript->inputParameterToList(lua_paramI_cpy_str);

                    }

                    sprintf(buff,"%i_lua_oparams_%i",i,j);
                    path = buff;
                    num_param_output = config.read<int>(path);

                    for(int z=1; z<=num_param_input; z++){

                        sprintf(buff,"%i_lua_oparam_name_%i_%i",i,j,z);
                        path = buff;
                        lua_param = config.read<std::string>(path);
                        char* lua_paramO_cpy = new char[lua_param.length()+1];
                        strcpy(lua_paramO_cpy, lua_param.c_str());
                        std::string lua_paramO_cpy_str(lua_paramO_cpy);

                        sprintf(buff,"%i_lua_oparam_type_%i_%i",i,j,z);
                        path = buff;
                        lua_type = config.read<std::string>(path);
                        char* lua_typeO_cpy = new char[lua_type.length()+1];
                        strcpy(lua_typeO_cpy, lua_type.c_str());
                        std::string lua_typeO_cpy_str(lua_typeO_cpy);


                        sprintf(buff,"%i_lua_oparam_value_%i_%i",i,j,z);
                        path = buff;
                        lua_value = config.read<std::string>(path);
                        char* lua_valueO_cpy = new char[lua_value.length()+1];
                        strcpy(lua_valueO_cpy, lua_value.c_str());
                        std::string lua_valueO_cpy_str(lua_valueO_cpy);

                        gLuaScript->setOutputParameter(lua_paramO_cpy_str, lua_typeO_cpy_str, lua_valueO_cpy_str);
                        gLuaScript->outputParameterToList(lua_paramO_cpy_str);

                    }

                    gLuaScript->setFileName(lua_file_cpy);
                    gLuaScript->setFunction(lua_functions_cpy);
                    DATA_TYPE->setLuaScript(c_script_id_cpy, gLuaScript);

                    DEBUGLOGPTHREE("GLuaScriptManager::processLuaDefFile --> SCRIPT %s ID %s FUNCTION %s ", lua_file_cpy, c_script_id_cpy, lua_functions_cpy);
                }
           }//else
      }

      INFOLOGPONE("GLuaScriptManager::processLuaDefFile --> NUMERO FICHEROS SCRIPT CARGADOS (%d)",num_files_lua);

      config.close();
}



/*

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
*/
