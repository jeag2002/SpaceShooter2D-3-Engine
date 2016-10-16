#ifndef GLANIMATIONSCRIPT_H_INCLUDED
#define GLANIMATIONSCRIPT_H_INCLUDED

#include "Stdafx.h"

class GLAnimationScript{

public:

GLAnimationScript(){};

GLAnimationScript(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;
}

~GLAnimationScript(){};


private:

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;

};
#endif // GLANIMATIONSCRIPT_H_INCLUDED
