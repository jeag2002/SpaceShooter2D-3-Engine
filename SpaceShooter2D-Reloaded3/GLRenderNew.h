/*

23-08-2015 JALCARAZ

SPACESHOOTER2D-RELOADED2

Renderizado de varios niveles + parallax + iluminación (OpenGL ES 1.1/3.0)

1-Projection
2-General lighting
3-Tiles
4-Elements
5-Lights
6-Shadows.
*/

#ifndef GLRENDERNEW_H_INCLUDED
#define GLRENDERNEW_H_INCLUDED

#include "Stdafx.h"
#include "GLCameraNew.h"
#include "GLRenderNewGL11.h"

class GLRenderNew{

public:

 GLRenderNew(){
    #ifdef GL11
        gRenderNewGL11 = new GLRenderNewGL11();
    #endif
};

GLRenderNew(GlobalNew *_GLOBAL_DATA, LogEngine *_LOG, MemManagerNew *_MEM_MANAGER, GLCameraNew *_CAM_MANAGER){
    #ifdef GL11
        gRenderNewGL11 = new GLRenderNewGL11(_GLOBAL_DATA, _LOG, _MEM_MANAGER, _CAM_MANAGER);
    #endif
};

~GLRenderNew(){
    #ifdef GL11
        delete gRenderNewGL11;
    #endif
};

void initRender(){
    #ifdef GL11
        gRenderNewGL11->initRender();
    #endif
};
void updateRender(){
    #ifdef GL11
        gRenderNewGL11->updateRender();
    #endif
};
void runRender(){
    #ifdef GL11
        gRenderNewGL11->runRender();
    #endif
};
void terminateRender(){
    #ifdef GL11
        gRenderNewGL11->terminateRender();
    #endif
};

private:

LogEngine *LOG;
GlobalNew *GLOBAL_DATA;
MemManagerNew *MEM_MANAGER;
GLCameraNew *CAM_MANAGER;

GLRenderNewGL11 *gRenderNewGL11;

//recupera informacion de renderizado del juego.
//void getRenderElement(){}
//void sendEventMsg(){}

};

#endif // GLRENDERNEW_H_INCLUDED
