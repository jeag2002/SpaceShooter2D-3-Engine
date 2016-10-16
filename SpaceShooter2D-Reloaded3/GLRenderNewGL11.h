#ifndef GLRENDERNEWGL11_H_INCLUDED
#define GLRENDERNEWGL11_H_INCLUDED

#include "Stdafx.h"
#include "GLCameraNew.h"
#include "GLTile.h"
#include "GLHud.h"
#include "Image.h"

#include "GLCollision.h"

#include "GLRenderStaticLevelGL11.h"
#include "GLRenderDynamicLevelGL11.h"
#include "GLPolygonGL11.h"
#include "GLCursor.h"

#define IDLE_TILE 0

class GLRenderNewGL11{

private:

LogEngine *gLogEngine;
GlobalNew *GLOBAL_DATA;
MemManagerNew *MEM_MANAGER;
GLCameraNew *CAM_MANAGER;
GLHud *gHudNew;
GLCursor *gGLCursor;

GLDynamicEntityNew *player;

int sizeXPlayer;
int sizeYPlayer;

Image *parallaxProcessor;
relMovementPol pol;
relMovementPol polParallax;

relMovement cursor_pos;

GLRenderDynamicLevelGL11 *glRenderDyn;
GLRenderStaticLevelGL11 *glRenderStatic;
GLPolygonGL11 *glPolygon;

GLImageDef *idBackgroundImage;
GLImageDef *idBackgroundImageParallax;


void renderBackgroundImage();
void initRender2D();
void endRender2D();



public:

GLRenderNewGL11(){
};

GLRenderNewGL11(GlobalNew *_GLOBAL_DATA, LogEngine *_LOG, MemManagerNew *_MEM_MANAGER, GLCameraNew *_CAM_MANAGER){
    GLOBAL_DATA = _GLOBAL_DATA;
    gLogEngine = _LOG;
    MEM_MANAGER = _MEM_MANAGER;
    CAM_MANAGER = _CAM_MANAGER;

    player = MEM_MANAGER->getPlayer(GLOBAL_DATA->getActPlayer()-1);

    relMovementPol rMP = player->getLimits();
    sizeXPlayer = int(rMP.nodes[1].rel_pos_x - rMP.nodes[0].rel_pos_x);
    sizeYPlayer = int(rMP.nodes[1].rel_pos_y - rMP.nodes[0].rel_pos_y);

    glRenderDyn = new GLRenderDynamicLevelGL11(GLOBAL_DATA,gLogEngine,MEM_MANAGER,CAM_MANAGER);
    glRenderStatic = new GLRenderStaticLevelGL11(GLOBAL_DATA,gLogEngine,MEM_MANAGER,CAM_MANAGER);
    glPolygon = new GLPolygonGL11(GLOBAL_DATA,gLogEngine,MEM_MANAGER,CAM_MANAGER);

    gHudNew = new GLHud(GLOBAL_DATA,MEM_MANAGER,gLogEngine);
    gGLCursor = new GLCursor(GLOBAL_DATA,MEM_MANAGER,gLogEngine);

    parallaxProcessor = new Image(MEM_MANAGER, gLogEngine);

    idBackgroundImage = MEM_MANAGER->getBackgroundImage();
    idBackgroundImageParallax = new GLImageDef();
};

~GLRenderNewGL11(){
    delete idBackgroundImage;
    delete idBackgroundImageParallax;
};

void renderCollLimits(int actLevel);

void initRender(){};
void updateRender();
void runRender();
void terminateRender(){};



/*
void renderStaticLevel(int level,screenSize scrSize);
void renderDynamicLevel(int level,screenSize scrSize);
*/
//recupera informacion de renderizado del juego.
//void getRenderElement(){}
//void sendEventMsg(){}

};

#endif // GLRENDERNEWGL11_H_INCLUDED
