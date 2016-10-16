#include "GLStateDefManager.h"


void GLStateDefManager::createState(int indexState, int typeState, int stateState, char *pathDef, int iForward, int iStop, int iFinish, int iError){

    if (typeState == TYPE_STATE_LEVEL){

        char* pathDef_cpy = new char[strlen(pathDef)+1];

        for(int i=0; i<strlen(pathDef); i++){pathDef_cpy[i]= pathDef[i];}
        pathDef_cpy[strlen(pathDef)] = '\0';

        //memcpy(pathDef_cpy, (const char *)pathDef, strlen(pathDef));
        //char* pathDef_cpy = new char[(sizeof(pathDef)*sizeof(char))+1];
        //strcpy(pathDef_cpy, pathDef);

        GameNew *gameNew = new GameNew(gNew, DATA_TYPE , gLogEngine, pathDef_cpy);
        gameNew->setIndexForwardId(iForward);
        gameNew->setIndexErrorId(iError);
        gameNew->setIndexFinishId(iFinish);
        gameNew->setIndexStopId(iStop);


        DATA_TYPE->setState(indexState,gameNew);
        DEBUGLOGPTWO("GLStateDefManager::createState --> STATE INDEX (%d) TYPE GAMELEVEL PATH(%s)",indexState,pathDef);

    }else if (typeState == TYPE_STATE_EXIT){

        GLState *glNew = new GLState(pathDef,TYPE_STATE_EXIT,TO_START);
        glNew->setIndexForwardId(iForward);
        glNew->setIndexErrorId(iError);
        glNew->setIndexFinishId(iFinish);
        glNew->setIndexStopId(iStop);
        DATA_TYPE->setState(indexState,glNew);

        DEBUGLOGPTWO("GLStateDefManager::createState --> STATE INDEX (%d) TYPE EXIT PATH(%s)",indexState,pathDef);

    }

}


/*

INDEX_STATE                 => Estado a procesar
TYPE_STATE                  => (Splash, Menu, Level, Exit) => (Todos son estados, pero se procesan de forma distinta)
STATE_ID                    => (Estado del "ESTADO"... CREATE, START, UPDATE, CLOSE, DELETE)
PATH_TO_DEFINITION_LEVEL    => (fichero ini configuración del estado)

INDEX_FORWARD               => Estado al que va, cuando todo ha ido bien
INDEX_STOP                  => Estado al que va cuando hay una pausa
INDEX_FINISH                => EXIT
INDEX_ERROR                 => EXIT (IGUAL DE FINISH, pero en este caso, se cierra todo el programa y se guarda toda la info del error disponible)

*/

void GLStateDefManager::processState(std::string line){

    int indexState = 0;
    int typeState = 0;
    int stateState = 0;
    char *pathDefinitionLevel = "";

    int indexForward = 0;
    int indexStop = 0;
    int indexFinish = 0;
    int indexError = 0;


    char *data_1 = strtok((char *)line.c_str(), DELIMITER);
    if (data_1 != NULL){ indexState = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){typeState = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){stateState = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){pathDefinitionLevel = data_1;}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){indexForward = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){indexStop = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){indexFinish = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){indexError = atoi(data_1);}

    createState(indexState, typeState, stateState, pathDefinitionLevel, indexForward, indexStop, indexFinish, indexError);
};


void GLStateDefManager::processStateDefFile(char *gamezipfile){

    std::string line;
    ifstream myfile (gamezipfile);

    int numero_estados = 0;


    if (myfile.is_open())
    {
        while ( std::getline (myfile,line)){
            processState(line);
            numero_estados += 1;
        }
        myfile.close();
    }

     INFOLOGPONE("GLStateDefManager::processStateDefFile --> ESTADOS PROCESADOS (%d)",numero_estados);
};
