/*

20151011.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2

GLGameLogic.h

Version 1.0 -> Gestión lógica del juego. (Collisiones, IA, Fin del nivel)

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Reflexionar sobre la idoniedad de utilizar scripts LUA para comportamientos globales, grupales, de colisiones, fisicas e IA

Pasos:

Procesado de eventos de teclado/raton sobre el elemento jugador.
Evaluacion de colisiones y mecanicas del juego activados por el jugador. (colision con otros elementos y triggers disparados por el jugador)
Evaluacion de animaciones del jugador.
Movimiento de la camara.

Procesado de IA de los otros elementos dinámicos (enemigos) por separado
Procesado de IA global de los otros elementos de forma conjunta (enemigos)
Evaluacion de colisiones y mecanicas del juego activado por los elementos dinámicos que no son el jugador
Evaluacion de animaciones de los enemigos

*/

#ifndef GLGAMELOGIC_H_INCLUDED
#define GLGAMELOGIC_H_INCLUDED

#include "Stdafx.h"
#include "GLCameraNew.h"
#include "GLLuaScript.h"
#include "GLDynamicEntityNew.h"
#include "GLCollision.h"

#include "GLCollisionScript.h"
#include "GLIAScript.h"
#include "GLAnimationScript.h"
#include "GLGamePlayScript.h"

class GLGameLogic{

public:

GLGameLogic(){};
//GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log
GLGameLogic(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log, GLCameraNew *_CAMERA_DATA){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    CAMERA_DATA = _CAMERA_DATA;
    gLogEngine = _log;
    Player = ENTITY_DATA->getPlayer(gNew->getActPlayer()-1);

    glCollisionScript = new GLCollisionScript(gNew,ENTITY_DATA,gLogEngine);
    glIAScript = new GLIAScript(gNew,ENTITY_DATA,gLogEngine);
    glAnimationScript = new GLAnimationScript(gNew,ENTITY_DATA,gLogEngine);
    glGamePlayScript = new GLGamePlayScript(gNew,ENTITY_DATA,gLogEngine);

    DEBUGLOGPFOUR("GLGameLogic::Init --> INIT PLAYER ID [%d] GLOBAL SCRIPTS GAMEPLAY ID:(%s) COLLITION ID:(%s) IA ID:(%s)",gNew->getActPlayer(),ENTITY_DATA->getGamePlayScript().c_str(),ENTITY_DATA->getGameCollScript().c_str(),ENTITY_DATA->getGameIAScript().c_str());
};

void Update(EventMsg *msgEvent);

~GLGameLogic(){
     delete glCollisionScript;
     delete glIAScript;
     delete glAnimationScript;
     delete glGamePlayScript;
};

private:

void dummyScript();

//GAME LOGIC JUGADOR
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void processActiveEvents(EventMsg *msgEvent);                                                                 //-> detecta eventos activos
void processActiveCommands(EventMsg *msgEvents);                                                              //-> detecta eventos activos que son comandos de entrada
bool processActiveCollisions(relMovementPol playerLimits, float x_pos, float y_pos, int position);            //-> procesa script colisiones jugador/otros elementos del nivel
void processActiveAnimations(GLDynamicEntityNew *player){};                                                   //-> procesa script animaciones del jugador

void gameLogicPlayerVsEnemy(GLDynamicEntityNew *player, GLDynamicEntityNew *enemy){                           //-> procesa script gameplay jugador-enemigo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicPlayerActiveEntity(GLDynamicEntityNew *player, GLDynamicEntityNew *actEntity){                   //-> procesa script gameplay jugador-elemento activo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicPlayerPasiveEntity(GLDynamicEntityNew *player, GLDynamicEntityNew *pasEntity){                    //-> procesa script gameplay jugador-elemento pasivo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicPlayerRolActive(GLDynamicEntityNew *player, GLRole *pasEntity){                                   //-> procesa script gameplay jugador-elemento activo trigger
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicPlayerRolPasive(GLDynamicEntityNew *player, GLDynamicEntityNew *pasEntity){                       //-> procesa script gameplay jugador-elemento pasivo trigger
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//GAME LOGIC ACTIVE ELEMENTS CONTROLLED BY ID
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void processReactiveEvents();
GLDynamicEntityNew *processReactiveIA(GLDynamicEntityNew *enemy){return enemy;}
void processReactiveAnimations(GLDynamicEntityNew *enemy){};
void processGlobalReactiveIA(){};
void processReactiveCollision(){};

/***********************************************************************************************************************************************/
void gameLogicEnemyVsPlayer(GLDynamicEntityNew *enemy, GLDynamicEntityNew *player){               //-> procesa script gameplay enemigo-jugador
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicEnemyVsEnemy(GLDynamicEntityNew *enemyI, GLDynamicEntityNew *enemyO){                 //-> procesa script gameplay enemigo-enemigo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicEnemyActiveEntity(GLDynamicEntityNew *enemy, GLDynamicEntityNew *actEntity){        //-> procesa script gameplay enemigo-elemento activo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicEnemyPasiveEntity(GLDynamicEntityNew *enemy, GLDynamicEntityNew *pasEntity){        //-> procesa script gameplay enemigo-elemento pasivo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicEnemyRolActive(GLDynamicEntityNew *enemy, GLRole *pasEntity){                       //-> procesa script gameplay enemigo-elemento activo trigger
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicEnemyRolPasive(GLDynamicEntityNew *enemy, GLDynamicEntityNew *pasEntity){           //-> procesa script gameplay enemigo-elemento pasivo trigger
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};
/***********************************************************************************************************************************************/

/***********************************************************************************************************************************************/
void gameLogicActiveElemVsPlayer(GLDynamicEntityNew *activeElem, GLDynamicEntityNew *player){             //-> procesa script gameplay activeElem-jugador
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicActiveElemVsEnemy(GLDynamicEntityNew *activeElem, GLDynamicEntityNew *enemy){               //-> procesa script gameplay activeElem-enemigo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicActiveElemActiveEntity(GLDynamicEntityNew *activeElem, GLDynamicEntityNew *actEntity){      //-> procesa script gameplay activeElem-elemento activo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicActiveElemPasiveEntity(GLDynamicEntityNew *activeElem, GLDynamicEntityNew *pasEntity){      //-> procesa script gameplay activeElem-elemento pasivo
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicActiveElemRolActive(GLDynamicEntityNew *activeElem, GLRole *pasEntity){                      //-> procesa script gameplay activeElem-elemento activo trigger
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};

void gameLogicActiveElemRolPasive(GLDynamicEntityNew *activeElem, GLDynamicEntityNew *pasEntity){          //-> procesa script gameplay activeElem-elemento pasivo trigger
    EventMsg *msgReturn = new EventMsg();
    ENTITY_DATA->setEventMsgRenderToStateManager(msgReturn);
};
/***********************************************************************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//UTILITIES
////////////////////////////////////////////////////////////////////////////////////////////
relMovementPol transformRelMovement(relMovementPol playerLimits, float x_pos, float y_pos); //-> reposiciona los limites con el 0,0 de referencia
bool isCollition(relMovementPol source1, relMovementPol source2,int orientation);           //-> evalua si hay colisiones o no.
bool isCollition(relMovementPol source1, relMovementPol source2);
bool isCollition(relMovementPol source1, int orientation, int level);



GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
GLCameraNew *CAMERA_DATA;
LogEngine *gLogEngine;
GLLuaScript *script;
GLDynamicEntityNew *Player;

GLCollisionScript *glCollisionScript;
GLIAScript *glIAScript;
GLAnimationScript *glAnimationScript;
GLGamePlayScript *glGamePlayScript;

};


#endif // GLGAMELOGIC_H_INCLUDED
