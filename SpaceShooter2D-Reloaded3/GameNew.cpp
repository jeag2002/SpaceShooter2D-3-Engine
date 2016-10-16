
/*
v20150823.0.001.0 JALCARAZ
SpaceShooter2D-2. GameNew.

1) Se encarga de la orquestación de todos los elementos de un nivel.
(GameLevel, GLObjectManager, GLRenderer, GLCamera)

//previamente debe haber cargado el gestor de elementos del juego y el gestor de imágenes

v20151011.0.0001.0 JALCARAZ
SpaceShooter2D-Reloaded2

1) Se añaden nuevos componentes:

MemManager -> Gestión espacio de memoria de los elementos del juego
EntityDefManager -> Carga

*/
#include "GameNew.h"

GameNew::GameNew() : GLState(){
    gNew = NULL;
    gMem = NULL;
    gLogEngine = NULL;
}


GameNew::GameNew(GlobalNew *_gNew, MemManagerNew *_gMem, LogEngine *_log): GLState(){

gNew = _gNew;
gMem = _gMem;
gLogEngine = _log;

}

GameNew::GameNew(GlobalNew *_gNew, MemManagerNew *_gMem, LogEngine *_log,  char *gamezipfile) : GLState(gamezipfile,VALUE_STATE_CREATION,TYPE_STATE_LEVEL)
{

gNew = _gNew;
gMem = _gMem;
gLogEngine = _log;

gamepath = gamezipfile;

INFOLOG("GameNew::GameNew --> LEVEL CREATED");
}

//Arranque del nivel (Funcionamiento del clock)
void GameNew::Start(){

DEBUGLOGPFIVE("GameNew::Start --> Cargando nivel Type(%d): %s State(%d): %s Load data from: %s", this->getType(), Utils::getTypeState(this->getType()), this->getState(), Utils::getState(this->getState()), this->getIdentificator());

gLevelNew = new GameLevelNew(gNew, gMem, gLogEngine);
gLevelNew->processGameLevelDef(gamepath);
gCameraNew = new GLCameraNew(gLogEngine);

gPlayer = (GLDynamicEntityNew *)gMem->getPlayer(gNew->getActPlayer()-1);

gCameraNew->init(gPlayer->getEntityXPos(),
                 gPlayer->getEntityYPos(),
                 gLevelNew->getSizeWorldX(),
                 gLevelNew->getSizeWorldY(),
                 gNew->getWidthScr(),
                 gNew->getHeightScr(),
                 gLevelNew->getTileX(),
                 gLevelNew->getTileY()
                 );


gGameLogic = new GLGameLogic(gNew, gMem, gLogEngine, gCameraNew);
gRenderNew = new GLRenderNew(gNew, gLogEngine, gMem, gCameraNew);

clock = new ClockEngine();
clock->start();
DEBUGLOG("GameNew::Start --> clock::start");

}

//Procesado del nivel.
void GameNew::Run(){

    gRenderNew->runRender();
    clock->evaluateFramerrate();
    //DEBUGLOGPONE("GameNew::Run --> clock::running FRAMERRATE (%d) ",clock->getFrammerrate());

    //Captura de eventos
    //GameLogic => Colisiones. IA, Final del Estado (+InputEvent) (+gObjectManagerNew)
    //GameRenderer => Presentación por pantalla(+InputEvent)(+gObjectManagerNew)(+gCameraNew)
    //Clock
}

//bloqueo del nivel.
void GameNew::Stop(){
    clock->stop();
    DEBUGLOG("GameNew::Stop --> clock::stop");
}

void GameNew::Update(EventMsg *msgEvent){

    clock->pause();
    //DEBUGLOG("GameNew::Update --> clock::pause");
    gGameLogic->Update(msgEvent);
    gRenderNew->updateRender();
    clock->unpause();
    //DEBUGLOG("GameNew::Update --> clock::unpause");
}

GameNew::~GameNew(){

    //delete gNew;
    //delete gMem;
    //delete gLogEngine;
    delete gPlayer;
    delete gLevelNew;
    delete gGameLogic;
    delete gRenderNew;
    delete gCameraNew;
}
