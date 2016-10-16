/*

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Carga de los elementos de imagen, sonido, script, etc.

Carga de datos globales de la aplicación

GLEntityDefManager      => Carga de definicion de elementos estáticos/dinámicos del juego
GLImageFactoryManager   => Carga de imagenes del juego
GLLuaScriptManager      => Carga de scripts en lua.
GLStateDefManager       => Carga definicion de estados.
GLSoundManager          => Carga sonidos/musica
*/

#ifndef GLINIT_H_INCLUDED
#define GLINIT_H_INCLUDED

#include "Stdafx.h"

#include "ConfigFile.h"
#include "GLEntityDefManager.h"
#include "GLImageFactoryManager.h"
#include "GLLuaScriptManager.h"
#include "GLStateDefManager.h"
#include "GLSoundManager.h"
#include "TiffDefManager.h"
#include "GLAnimEntityDefManager.h"
#include "GLAnimParticleDefManager.h"

class GLInit{

public:

    GLInit(){

        gNew = NULL;
        memW = NULL;
        gLogEngine = NULL;

        gEDM = NULL;
        gIFM = NULL;
        gLSM = NULL;
        gLSDM = NULL;
        gLSGM = NULL;
        tDM = NULL;
        gLAEDM = NULL;
        gLAPDM = NULL;

    };

    GLInit(GlobalNew *_gNew,
           MemManagerNew *_memW,
           LogEngine *_log){

        gNew = _gNew;
        memW = _memW;
        gLogEngine = _log;

        gEDM = new GLEntityDefManager(gNew, memW, gLogEngine);
        gIFM = new GLImageFactoryManager(memW, gLogEngine);
        gLSM = new GLLuaScriptManager(gNew, memW, gLogEngine);
        gLSDM = new GLStateDefManager(gNew, memW, gLogEngine);
        gLSGM = new GLSoundManager(gNew,memW,gLogEngine);
        tDM = new TiffDefManager(gNew,memW,gLogEngine);
        gLAEDM = new GLAnimationEntityDefManager(gNew,memW,gLogEngine);
        gLAPDM = new GLAnimParticleDefManager(gNew,memW,gLogEngine);
    };

    //cargamos los diferentes atributos: Definicion_De_Entidades, Imagenes, Script_Lua,Definicion_De_Estados,Sonidos/Musicas
    void processResourcesFilesInit(){
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS IMAGE DEFINITION");
        gIFM->processImageDefFile(gNew->getImageDefinitionPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS LUA SCRIPT DEFINITION");
        gLSM->processLuaDefFile(gNew->getScriptDefinitionPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS STATE DESCRIPTION DEFINITION");
        gLSDM->processStateDefFile(gNew->getStateDefinitionPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS SOUND DEFINITION");
        gLSGM->processSoundManagerFile(gNew->getSoundDefinitionPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS TIFF DEFINITION");
        tDM->processTiffDefFile(gNew->getTypewriteDefinitionPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS ANIM ENTITY DEFINITION");
        gLAEDM->processAnimEntityDefManager(gNew->getEntityDefinitionPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS ANIM PARTICLE DEFINITION");
        gLAPDM->processAnimParticleDefManager(gNew->getAnimationParticlesPath());
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS ENTITY DEFINITION");
        gEDM->processEntityDefinitionFile(gNew->getEntityDefinitionPath());
    };

    void processImageFilesInit(){
        DEBUGLOG("GLInit::processResourcesFilesInit --> PROCESS IMAGE DEFINITION");
        gIFM->processImageDefFile(gNew->getImageDefinitionPath());
    };

    //oricesar variables globales
    void processGlobalFileInit();

    //printado variables globales.
    void printGlobalFileParams();

    //20151031 JALCARAZ SPACESHOOTER2D-RELOADED3.0.001.01 salvar variables globales, estadísticas, etc.
    void saveActDataToFile(){};

    //20151031 JALCARAZ SPACESHOOTER2D-RELOADED3.0.001.01 recuperar variables globales, estadisticas, etc.
    void loadActDataToFile(){};

    ~GLInit(){
        delete gEDM;
        delete gIFM;
        delete gLSM;
        delete gLSDM;
        delete gLSGM;
        delete tDM;
        delete gLAEDM;
        delete gLAPDM;
    };


private:

    LogEngine *gLogEngine;
    GlobalNew *gNew;
    MemManagerNew *memW;

    GLEntityDefManager *gEDM;
    GLImageFactoryManager *gIFM;
    GLLuaScriptManager *gLSM;
    GLStateDefManager *gLSDM;
    GLSoundManager *gLSGM;
    TiffDefManager *tDM;

    GLAnimationEntityDefManager *gLAEDM;
    GLAnimParticleDefManager *gLAPDM;



};

#endif // GLINIT_H_INCLUDED
