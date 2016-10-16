/*
20151019.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Motor parseo datos del fichero de estados del SpaceShooter. Transforma un fichero de estados en una colección de objetos GLStates que pueda ser gestionado desde
GLStateManager

*/

#ifndef GLSTATEDEFMANAGER_H_INCLUDED
#define GLSTATEDEFMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "ConfigFile.h"
#include "GLStateManager.h"

#include "GameNew.h"

#define DELIMITER " "
#define DELIMITER_1 ","
#define DELIMITER_2 "_"


class GLStateDefManager{

public:

    GLStateDefManager(){
        gNew = NULL;
        DATA_TYPE = NULL;
        gLogEngine = NULL;
    }

    GLStateDefManager(GlobalNew *_gNew, MemManagerNew *_DATA_TYPE, LogEngine *_log){
        gNew = _gNew;
        DATA_TYPE = _DATA_TYPE;
        gLogEngine = _log;
    }

    /*
    int indexState = 0;
    int typeState = 0;
    int stateState = 0;
    char *pathDefinitionLevel = "";

    int indexForward = 0;
    int indexStop = 0;
    int indexFinish = 0;
    int indexError = 0;
    */


     void createState(int indexState, int typeState, int stateState, char *pathDef, int iForward, int iStop, int iFinish, int iError);
     void processState(std::string line);
     void processStateDefFile(char *gamezipfile);



    ~GLStateDefManager(){};

private:

    GlobalNew *gNew;
    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;

};

#endif // GLSTATEDEFMANAGER_H_INCLUDED
