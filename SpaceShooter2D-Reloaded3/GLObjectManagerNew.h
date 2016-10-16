/*

23-08-2015 JALCARAZ

SPACESHOOTER2D-RELOADED2

Gestión de los elementos que conforman un nivel. Movimiento, Collision, IA, etc...
Parseo de GLEntityDefinition en objetos GLTiles, GLPlayers, GLEnemies.... etc...


20151206.SPACESHOOTER2D-RELOADED3.1.001.001. Motor de parseo

*/

#ifndef GLOBJECTMANAGERNEW_H_INCLUDED
#define GLOBJECTMANAGERNEW_H_INCLUDED

#include "Stdafx.h"
#include "GLObjectManagerTile.h"
#include "GLObjectManagerPlayer.h"
#include "GLObjectManagerEnemy.h"


class GLObjectManagerNew{

public:

GLObjectManagerNew(){};

GLObjectManagerNew(LogEngine *_gLogEngine, GlobalNew *_gNew, MemManagerNew *_gMem){
    gLogEngine = _gLogEngine;
    gNew = _gNew;
    gMem = _gMem;

    tileParser = new GLObjectManagerTile(gLogEngine,gNew,gMem);
    playerParser = new GLObjectManagerPlayer(gLogEngine,gNew,gMem);
    enemyParser = new GLObjectManagerEnemy(gLogEngine,gNew,gMem);
};

~GLObjectManagerNew(){};

//procesado elementos estaticos
void processTileDef(int idEntityDef, float x, float y, float level);
//procesado elementos dinamicos
void processDynamicDef(int idEntityDef, float x, float y, float level);
//procesado elementos
void processPlayerDef(int idEntityDef, int numPlayer, float x, float y, int level, int orientation);


private:

LogEngine *gLogEngine;
GlobalNew *gNew;
MemManagerNew *gMem;

GLObjectManagerTile *tileParser;
GLObjectManagerPlayer *playerParser;
GLObjectManagerEnemy *enemyParser;

GLEntityDefinition *data;
GLTile *_tile;
GLDynamicEntityNew *_entity;





};

#endif // GLOBJECTMANAGERNEW_H_INCLUDED
