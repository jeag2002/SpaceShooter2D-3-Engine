#ifndef GLIASCRIPT_H_INCLUDED
#define GLIASCRIPT_H_INCLUDED

#include "Stdafx.h"

class GLIAScript{

public:

GLIAScript(){};

GLIAScript(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;
}

~GLIAScript(){};


private:

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;

};


#endif // GLIASCRIPT_H_INCLUDED
