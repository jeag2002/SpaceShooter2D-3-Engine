#ifndef GLLUASCRIPT_H_INCLUDED
#define GLLUASCRIPT_H_INCLUDED

extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <cstring>

#define FLOAT "float"
#define DOUBLE "double"
#define INTEGER "int"
#define STRING "string"

class GLLuaScript{

public:

    typedef struct{
        float rel_pos_x;
        float rel_pos_y;
    }relMovement_GL;

    typedef struct{
        relMovement_GL nodes[20];
        int num_nodes;
    }relMovementPol_GL;

    typedef struct{

        unsigned int uniqueID;
        float pos_X;
        float pos_Y;
        float x_diff;
        float y_diff;
        int orientation;
        int actAnim;
        int numAnim;
        relMovementPol_GL limits;
    }idInputEntityElement;

    typedef struct{
        relMovementPol_GL mapLevel[20];
        int num_mapLevel;
    }mapLevel;

    typedef struct{
        unsigned int uniqueID;
        float pos_X;
        float pos_Y;
        relMovementPol_GL limits;
        int live;
        int score;
        int shield;
        int fire;
        int inc;
        int orientation;
        bool shoot;
    }idOutputEntityElement;


    GLLuaScript(){
        L = NULL;
    }

    GLLuaScript(lua_State *_L){
        L = _L;
    };

    ~GLLuaScript(){
    };

    char *getFileName(){return name_file;};
    void setFileName(char *_name_file){name_file = _name_file;};

    char *getFunction(){return name_function;};
    void setFunction(char *_name_function){name_function = _name_function;};

    void executeLuaScript();
    void executeLuaCollScript();


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //INPUT PARAMS
    void setInputParameter(std::string nom_parameter, std::string type_parameter, std::string value_parameter){
        parameterDataType pIData(nom_parameter, type_parameter, value_parameter);
        std::pair<std::string, parameterDataType> elem(nom_parameter, pIData);
        iParams.insert(elem);
    };

    void updateInputParameter(std::string nom_parameter, std::tuple<std::string, std::string, std::string> value){
        iParams[nom_parameter] = value;
    }


    //COLLS
    void setInputRMovParameter(std::string nom_parameter, std::string type_parameter, relMovementPol_GL value_parameter){
        parameterRMovPolType pIRData(nom_parameter, type_parameter, value_parameter);
        std::pair<std::string, parameterRMovPolType> elem(nom_parameter, pIRData);
        iRMovPolParam.insert(elem);
    }

    //MAPS
    void setInputMapParameter(std::string nom_parameter, std::string type_parameter, mapLevel value_parameter){
        parameterMapEntityType pIRData(nom_parameter, type_parameter, value_parameter);
        std::pair<std::string, parameterMapEntityType> elem(nom_parameter, pIRData);
        this->iMapParam.insert(elem);
    };

    //INPUT DATA
    void setInputEntityParameter(std::string nom_parameter, std::string type_parameter, idInputEntityElement value_parameter){
        parameterInputEntityType pIRData(nom_parameter, type_parameter, value_parameter);
        std::pair<std::string, parameterInputEntityType> elem(nom_parameter, pIRData);
        iIEntParam.insert(elem);
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //OUTPUT
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setOutputParameter(std::string nom_parameter, std::string type_parameter, std::string value_parameter){
        parameterDataType pOData(nom_parameter, type_parameter, value_parameter);
        std::pair<std::string, parameterDataType> elem(nom_parameter, pOData);
        oParams.insert(elem);
    };


    void setOutputEntityParameter(std::string nom_parameter, std::string type_parameter, idOutputEntityElement value_parameter){
        parameterOutputEntityType pIRData(nom_parameter, type_parameter, value_parameter);
        std::pair<std::string, parameterOutputEntityType> elem(nom_parameter, pIRData);
        this->oOEntParamm.insert(elem);
    };


    void updateOutputParameter(std::string nom_parameter, std::tuple<std::string, std::string, std::string> value){
        oParams[nom_parameter] = value;
    };

    void updateOutputEntityParameter(std::string nom_parameter, std::tuple<std::string, std::string, idOutputEntityElement> value){
        oOEntParamm[nom_parameter] = value;
    };
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    std::tuple<std::string, std::string, std::string> getInputParameterDef(std::string key){
        parameterType::iterator it;
        parameterDataType pIDLE("", "", "");

        it = iParams.find(key);

        if (it!=iParams.end()){
            return it->second;
        }else{
            return pIDLE;
        }
    };

    std::tuple<std::string, std::string, relMovementPol_GL> getInputParameterRelMovDef(std::string key){

        parameterRMovType::iterator it;

        relMovementPol_GL rMPol;
        parameterRMovPolType pIDLE("", "", rMPol);

        it = iRMovPolParam.find(key);

        if (it!=iRMovPolParam.end()){
            return it->second;
        }else{
            return pIDLE;
        }
    };


    std::tuple<std::string, std::string, mapLevel> getInputParameterMapDef(std::string key){

        parameterMapType::iterator it;

        mapLevel rMPol;
        parameterMapEntityType pIDLE("", "", rMPol);

        it = iMapParam.find(key);

        if (it!=iMapParam.end()){
            return it->second;
        }else{
            return pIDLE;
        }
    };


    std::tuple<std::string, std::string, idInputEntityElement> getInputParameterEntityDef(std::string key){

        parameterIEntType::iterator it;

        idInputEntityElement rMPol;
        parameterInputEntityType pIDLE("", "", rMPol);

        it = iIEntParam.find(key);

        if (it!=iIEntParam.end()){
            return it->second;
        }else{
            return pIDLE;
        }
    };



    std::tuple<std::string, std::string, std::string> getOutputParameterDef(std::string key){
        parameterType::iterator it;
        parameterDataType pIDLE("", "", "");

        it = oParams.find(key);

        if (it!=oParams.end()){
            return it->second;
        }else{
            return pIDLE;
        }
    };

    std::tuple<std::string, std::string, idOutputEntityElement> getOutputParameterEntityDef(std::string key){

        parameterOEntType ::iterator it;

        idOutputEntityElement rMPol;
        parameterOutputEntityType pIDLE("", "", rMPol);

        it = oOEntParamm.find(key);

        if (it!=oOEntParamm.end()){
            return it->second;
        }else{
            return pIDLE;
        }
    };


    //////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::string> getInputParameter(){
        return ilParams;
    };

    std::vector<std::string> getInputRMParameter(){
        return ilRMParams;
    };

    std::vector<std::string> getInputEntitiesParameter(){
        return ilIEntParams;
    };

    std::vector<std::string> getInputMapParameter(){
        return ilMapParams;
    };
    //////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::string> getOutputParameter(){
        return olParams;
    };

    std::vector<std::string> getOutputEntitiesParameter(){
        return olOEntParams;
    }
    //////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////
    void inputParameterToList(std::string nom_parameter){
        ilParams.push_back(nom_parameter);
    };

    void inputParameterToRMList(std::string nom_parameter){
        ilRMParams.push_back(nom_parameter);
    };

    void inputParameterToIEntList(std::string nom_parameter){
        ilIEntParams.push_back(nom_parameter);
    };

    void inputParameterToMapList(std::string nom_parameter){
        ilMapParams.push_back(nom_parameter);
    };

    void outputParameterToList(std::string nom_parameter){
        olParams.push_back(nom_parameter);
    };

    void outputParameterToOEntList(std::string nom_parameter){
        olOEntParams.push_back(nom_parameter);
    };

    //////////////////////////////////////////////////////////////////////////////////////

private:

    lua_State *L;


    char *name_file;
    char *name_function;

    typedef std::tuple<std::string, std::string, std::string> parameterDataType;
    typedef std::tuple<std::string, std::string, relMovementPol_GL> parameterRMovPolType;

    typedef std::tuple<std::string, std::string, idInputEntityElement > parameterInputEntityType;
    typedef std::tuple<std::string, std::string, mapLevel > parameterMapEntityType;
    typedef std::tuple<std::string, std::string, idOutputEntityElement> parameterOutputEntityType;



    typedef std::map<std::string, parameterDataType> parameterType;             //input_parameter[nom_parameter] --> <nom_parameter,type_parameter,value_parameter>
    typedef std::map<std::string, parameterRMovPolType> parameterRMovType;

    typedef std::map<std::string, parameterInputEntityType> parameterIEntType;
    typedef std::map<std::string, parameterMapEntityType> parameterMapType;
    typedef std::map<std::string, parameterOutputEntityType> parameterOEntType;


    typedef std::vector<std::string> listIParamType;
    typedef std::vector<std::string> listOParamType;

    parameterType iParams;
    parameterRMovType iRMovPolParam;
    parameterIEntType iIEntParam;
    parameterMapType iMapParam;

    parameterType oParams;
    parameterOEntType oOEntParamm;

    listIParamType ilParams;
    listIParamType ilRMParams;
    listIParamType ilIEntParams;
    listIParamType ilMapParams;

    listOParamType olParams;
    listOParamType olOEntParams;
};



#endif // GLLUASCRIPT_H_INCLUDED
