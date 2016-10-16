/*

23-08-2015 JALCARAZ

SPACESHOOTER2D-RELOADED2

Primer paso: rehacer SpaceShooter2D-2; mejorando su lógica interna.

1)Game como State. Orquestiza los siguientes elementos por cada iteración.

1.1-GameLevel => Carga de los elementos de un nivel. (Parseo de los objetos de configuración). Genera un objeto GLObjectManager que almacena estos resultados como
objetos independientes en un vector + un objeto GLPlayer.

a)Mejora: Las colisiones con los objetos estáticos del mapa, pasan de ser a nivel de frame a ser poligonos. Se almacenará cada obstaculo como un objeto independiente tb.

b)Definir una clase Tile que almacene bordes.

1.2-GLObjectManager => Gestiona los movimientos de los elementos, IA, Colisiones. Devuelve una coleccion de vectores que luego el GLRendererNew; se encargará de printar
en la pantalla.

Colisiones primero como AABB; (evaluar colision perpixel)

1.3-GLCameraNew => Gestiona el scrolling del nivel. Define la ventana de visualización. Define la referencia, que será útil para posicionar (o no pintar) los elementos
que hay por pantalla.

1.4-GLRendererNew => Vuelca el contenido de GLObjectManager (como vectores de objetos) en pantalla, utilizando OpenGL Es 1.1/OpenGL ES 3.0-3.1

11-10-2015

Nuevos motores:

GLEntityDefManager.h => Carga de definicion de entidades
GLImageFactoryManager.h => Gestor de imagenes.
GLGameLogic => Gestor de la lógica del juego.

*/

#ifndef GAMENEW_H_INCLUDED
#define GAMENEW_H_INCLUDED

#include "Stdafx.h"

//nuevas definiciones
#include "GLGameLogic.h"
#include "GLObjectManagerNew.h"
#include "GameLevelNew.h"
#include "GLRenderNew.h"
#include "GLCameraNew.h"
#include "ClockEngine.h"
#include "GLState.h"
#include "GLHud.h"

class GameNew : public GLState{

private:


GlobalNew *gNew;
MemManagerNew *gMem;
LogEngine *gLogEngine;
char *gamepath;

GameLevelNew *gLevelNew;
GLGameLogic *gGameLogic;
GLRenderNew *gRenderNew;
GLCameraNew *gCameraNew;
GLHud *gHudNew;
ClockEngine *clock;
GLDynamicEntityNew *gPlayer;

screenSize sSize;

public:

GameNew();
GameNew(GlobalNew *_gNew, MemManagerNew *_gMem, LogEngine *_log);
GameNew(GlobalNew *_gNew, MemManagerNew *_gMem, LogEngine *_log, char *gamezipfile);

void Start();                           //=> arranca el nivel
void Update(EventMsg *msgEvent);        //=> Replantear si recolocar aquí logica de negocio; en vez de hacerlo todo en RUN
void Run();                             //=> Volcado de todo el nivel en framebuffer
void Stop();                            //=> Parado del nivel.

~GameNew();

};

#endif // GAMENEW_H_INCLUDED
