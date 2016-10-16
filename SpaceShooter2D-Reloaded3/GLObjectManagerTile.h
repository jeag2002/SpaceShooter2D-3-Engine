#ifndef GLOBJECTMANAGERTILE_H_INCLUDED
#define GLOBJECTMANAGERTILE_H_INCLUDED

#include "Stdafx.h"
#include "GLEntityDefinition.h"
#include "GLTile.h"

#define TILE_LIGHTMAP "LIGHTMAP"
#define TILE_BUMPMAP "BUMPMAP"
#define TILE_IDLE "IDLE"
#define TILE_EMPTY " "

class GLObjectManagerTile{

public:

GLObjectManagerTile(){};

GLObjectManagerTile(LogEngine *_gLogEngine, GlobalNew *_gNew, MemManagerNew *_gMem){
    gLogEngine = _gLogEngine;
    gNew = _gNew;
    gMem = _gMem;
};

GLTile *processTileDef(GLEntityDefinition *dataTile, float x, float y, float level);

~GLObjectManagerTile(){};

private:

LogEngine *gLogEngine;
GlobalNew *gNew;
MemManagerNew *gMem;

GLTile *_tile;
};


#endif // GLOBJECTMANAGERTILE_H_INCLUDED
