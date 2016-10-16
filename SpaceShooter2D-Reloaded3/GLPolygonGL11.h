#ifndef GLPOLYGONGL11_H_INCLUDED
#define GLPOLYGONGL11_H_INCLUDED

#include "Stdafx.h"
#include "GLCameraNew.h"

class GLPolygonGL11{

public:

GLPolygonGL11(GlobalNew *_GLOBAL_DATA, LogEngine *_LOG, MemManagerNew *_MEM_MANAGER, GLCameraNew *_CAM_MANAGER){
    GLOBAL_DATA = _GLOBAL_DATA;
    gLogEngine = _LOG;
    MEM_MANAGER = _MEM_MANAGER;
    CAM_MANAGER = _CAM_MANAGER;
};

void drawPolygonGL11(float ref_x, float ref_y, float radio, int num_vertex, bool isfilled);
void drawRMPPolygonGL11(relMovementPol rMP, bool isfilled){}
void drawRMPPolygonCollGL11(relMovementPol rMP, float red, float green, float blue, bool isfilled);

private:

LogEngine *gLogEngine;
GlobalNew *GLOBAL_DATA;
MemManagerNew *MEM_MANAGER;
GLCameraNew *CAM_MANAGER;


};

#endif // GLPOLYGONGL11_H_INCLUDED
