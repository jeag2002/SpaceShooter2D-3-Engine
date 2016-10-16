#ifndef GLGAMEPLAYSCRIPT_H_INCLUDED
#define GLGAMEPLAYSCRIPT_H_INCLUDED

#include "Stdafx.h"

class GLGamePlayScript{

public:

GLGamePlayScript(){};

GLGamePlayScript(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;
}

~GLGamePlayScript(){};


private:

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;

};



#endif // GLGAMEPLAYSCRIPT_H_INCLUDED
