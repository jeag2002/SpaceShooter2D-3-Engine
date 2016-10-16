/*
20151213.SPACESHOOTER2D-RELOADED3.0.001.001
Presentación de datos por pantalla.
1-Primero version debug. Printado del framerrate, y del desplazamiento del jugador por pantalla.
2-Versión gráfica

//http://www.willusher.io/sdl2%20tutorials/2013/12/18/lesson-6-true-type-fonts-with-sdl_ttf/
*/


#ifndef GLHUD_H_INCLUDED
#define GLHUD_H_INCLUDED

#include "Stdafx.h"
#include "GLDynamicEntityNew.h"
#include "GLImageDef.h"

#define DEBUG_LEVEL 1
#define INFO_LEVEL 2

class GLHud{

public:

GLHud(){};

GLHud(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    gMem = _ENTITY_DATA;
    gLogEngine = _log;
    initHud();
}

void initHud();
void initDebugHud();
void processHud();
void processDebugHud();

~GLHud(){};

private:

TTF_Font *font;
GlobalNew *gNew;
MemManagerNew *gMem;
LogEngine *gLogEngine;
TTF_Font *gFont;
int numFrames;
int presentFrames;
int currentTime;
int lastTime;

};

#endif // GLHUD_H_INCLUDED
