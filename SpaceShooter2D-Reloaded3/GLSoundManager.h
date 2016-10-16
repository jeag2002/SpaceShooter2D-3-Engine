#ifndef GLSOUNDMANAGER_H_INCLUDED
#define GLSOUNDMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "GLSoundFile.h"
#include "ConfigFile.h"

class GLSoundManager{

public:

    GLSoundManager(){};

    GLSoundManager(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
        ENTITY_DATA = _ENTITY_DATA;
        gLogEngine = _log;
        gNew = _gNew;
    };

    void processSoundManagerFile(char *gamezipfile);
    ~GLSoundManager(){};

private:

    GlobalNew *gNew;
    MemManagerNew *ENTITY_DATA;
    LogEngine *gLogEngine;

};



#endif // GLSOUNDMANAGER_H_INCLUDED
