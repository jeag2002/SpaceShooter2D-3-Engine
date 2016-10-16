#ifndef GLCOLLISIONSCRIPT_H_INCLUDED
#define GLCOLLISIONSCRIPT_H_INCLUDED

#include "Stdafx.h"
#include "GLLuaScript.h"

#define SIZE_X 64
#define SIZE_Y 64

class GLCollisionScript{

public:

GLCollisionScript(){};

GLCollisionScript(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;

    SIZE_BLOCK_X = SIZE_X;
    SIZE_BLOCK_Y = SIZE_Y;
}

bool processCollisionDynToDyn(relMovementPol rM1, relMovementPol rM2, std::string nomScriptCollision);
bool processCollisionDynToStatic(relMovementPol rM1, relMovementPol rM2, std::string nomScriptCollision){return false;};
bool processCollisionStaticToStatic(relMovementPol rM1, relMovementPol rM2, std::string nomScriptCollision){return false;};

bool AABBCollision(relMovementPol rM1, relMovementPol rM2, int orientation);
bool AABBCollisionToPlane(relMovementPol rM1, relMovementPol plane, int orientation);
bool AABBCollisionToMap(relMovementPol rM1, int orientation, int level);
bool evaluateIfSameBlockMap(relMovementPol rM1, relMovementPol rM2, int orientation);

bool SphericalCollision(relMovementPol rM1, relMovementPol rM2);

~GLCollisionScript(){};

private:

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;

int SIZE_BLOCK_X;
int SIZE_BLOCK_Y;

};

#endif // GLCOLLISIONSCRIPT_H_INCLUDED
