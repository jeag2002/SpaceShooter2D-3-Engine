#ifndef GLRENDERSTATICLEVELGL11_H_INCLUDED
#define GLRENDERSTATICLEVELGL11_H_INCLUDED

#include "Stdafx.h"
#include "GLCameraNew.h"
#include "GLTile.h"

#define IDLE_TILE 0

class GLRenderStaticLevelGL11{

public:

GLRenderStaticLevelGL11(){
};

GLRenderStaticLevelGL11(GlobalNew *_GLOBAL_DATA, LogEngine *_LOG, MemManagerNew *_MEM_MANAGER, GLCameraNew *_CAM_MANAGER){
    GLOBAL_DATA = _GLOBAL_DATA;
    gLogEngine = _LOG;
    MEM_MANAGER = _MEM_MANAGER;
    CAM_MANAGER = _CAM_MANAGER;
};

~GLRenderStaticLevelGL11(){
};

void renderStaticLevel(int level,screenSize scrSize);

private:

LogEngine *gLogEngine;
GlobalNew *GLOBAL_DATA;
MemManagerNew *MEM_MANAGER;
GLCameraNew *CAM_MANAGER;
};


#endif // GLRENDERSTATICLEVELGL11_H_INCLUDED
