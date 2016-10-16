#ifndef GLANIMPARTICLEDEFMANAGER_H_INCLUDED
#define GLANIMPARTICLEDEFMANAGER_H_INCLUDED


#define ID_IMAGE_PARTICLE_NOTFOUND -1
#define ID_IMAGE_IDLE_DEFAULT "IDLE"
#define DELIMITER_COORD_PARTICLE ","

#include "Stdafx.h"
#include "ConfigFile.h"

class GLAnimParticleDefManager{

public:

GLAnimParticleDefManager(){};

GLAnimParticleDefManager(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;
}

SDL_Color processColor(char *color_path);

void processAnimParticleDefManager(char *gamezipfile);

~GLAnimParticleDefManager(){};

private:

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;
GLParticleDesc *gParticleDesc;

};




#endif // GLANIMPARTICLEDEFMANAGER_H_INCLUDED
