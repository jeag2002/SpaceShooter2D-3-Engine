#ifndef GLOBJECTMANAGERPLAYER_H_INCLUDED
#define GLOBJECTMANAGERPLAYER_H_INCLUDED

#include "Stdafx.h"
#include "GLEntityDefinition.h"
#include "GLDynamicEntityNew.h"

#define LIVE "LIVE"
#define SHIELD "SHIELD"
#define FIRE "FIRE"
#define INC "INC"
#define LIMITS "LIMITS"
#define SHAPE "SHAPE"
#define ORIENTATION "ORIENTATION"

#define IA_SCRIPT "IA_SCRIPT"
#define COLL_SCRIPT "COLL_SCRIPT"
#define ANIM_SCRIPT "ANIM_SCRIPT"

#define DELIMITER_COORD_GP " "

class GLObjectManagerPlayer{

public:

GLObjectManagerPlayer(){};

GLObjectManagerPlayer(LogEngine *_gLogEngine, GlobalNew *_gNew, MemManagerNew *_gMem){
    gLogEngine = _gLogEngine;
    gNew = _gNew;
    gMem = _gMem;
};

GLEntityNew *processElementDef(GLEntityDefinition *dataTile, float x, float y, float level, int orientation);
~GLObjectManagerPlayer(){};

private:

GLTile **processTilesDef(GLEntityDefinition *dataTile, float x, float y, float level);
relMovementPol processLimits(std::string limits);

LogEngine *gLogEngine;
GlobalNew *gNew;
MemManagerNew *gMem;

};




#endif // GLOBJECTMANAGERPLAYER_H_INCLUDED
