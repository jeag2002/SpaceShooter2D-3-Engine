#ifndef GLANIMENTITYDEFMANAGER_H_INCLUDED
#define GLANIMENTITYDEFMANAGER_H_INCLUDED

#define ID_IMAGE_ANIM_NOTFOUND -1

#include "Stdafx.h"

class GLAnimationEntityDefManager{

public:

GLAnimationEntityDefManager(){};

GLAnimationEntityDefManager(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;
}

void processAnimEntityDefManager(char *gamezipfile);

~GLAnimationEntityDefManager(){};

private:

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;

};



#endif // GLANIMENTITYDEFMANAGER_H_INCLUDED
