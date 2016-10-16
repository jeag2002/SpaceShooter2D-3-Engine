#ifndef GLOBJECTMANAGERENEMY_H_INCLUDED
#define GLOBJECTMANAGERENEMY_H_INCLUDED

#include "Stdafx.h"

class GLObjectManagerEnemy{

public:

GLObjectManagerEnemy(){};

GLObjectManagerEnemy(LogEngine *_gLogEngine, GlobalNew *_gNew, MemManagerNew *_gMem){
    gLogEngine = _gLogEngine;
    gNew = _gNew;
    gMem = _gMem;
};

GLEntityNew *processElementDef(GLEntityDefinition *dataTile, float x, float y, float level){
    GLEntityNew *glEN = new GLEntityNew();
    return glEN;
};

~GLObjectManagerEnemy(){};

private:

LogEngine *gLogEngine;
GlobalNew *gNew;
MemManagerNew *gMem;

};




#endif // GLOBJECTMANAGERENEMY_H_INCLUDED
