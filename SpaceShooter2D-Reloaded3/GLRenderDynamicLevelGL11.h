#ifndef GLRENDERDYNAMICLEVELGL11_H_INCLUDED
#define GLRENDERDYNAMICLEVELGL11_H_INCLUDED

#include "Stdafx.h"
#include "GLCameraNew.h"
#include "GLDynamicEntityNew.h"

class GLRenderDynamicLevelGL11{

public:

GLRenderDynamicLevelGL11(){
};

GLRenderDynamicLevelGL11(GlobalNew *_GLOBAL_DATA, LogEngine *_LOG, MemManagerNew *_MEM_MANAGER, GLCameraNew *_CAM_MANAGER){
    GLOBAL_DATA = _GLOBAL_DATA;
    gLogEngine = _LOG;
    MEM_MANAGER = _MEM_MANAGER;
    CAM_MANAGER = _CAM_MANAGER;
};

~GLRenderDynamicLevelGL11(){
};

void renderDynamicLevel(int level,screenSize scrSize){
};

void renderPlayerLevel(int level, screenSize scrSize, GLDynamicEntityNew *player);

private:

LogEngine *gLogEngine;
GlobalNew *GLOBAL_DATA;
MemManagerNew *MEM_MANAGER;
GLCameraNew *CAM_MANAGER;


};




#endif // GLRENDERDYNAMICLEVELGL11_H_INCLUDED
