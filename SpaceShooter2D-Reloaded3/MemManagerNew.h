/*

20150827.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2

Clase gestora de espacios de memoria. Intenta mejorar eficiencia de estructuras dinámicas implementadas en STL
(Puede ser útil en entornos críticos)

20151011.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2.

Collections (de momento definido como STLl)

1- Collection de estados => HashMap <id, GLState *>
2- Collection de imágenes => HashMap <id, GLuint> (almacena las imágenes)
3- Collection de Objetos dinámicos del mapa => Vector<Entities>
4- Collection de Definiciones de objetos => HashMap<id, entityDef>
5- Collection levels del mapa => Array[TILE_X x TILE_Y]

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

estudio consumo espacio entornos memoria: http://info.prelert.com/blog/stl-container-memory-usage

Creacion de nuevos elementos.
1)Jugadores
2)Enemigos
3)Otros.

3.1) Portales.
3.2) Salida.
3.3) Switches.

*/


#ifndef MEMMANAGERNEW_H_INCLUDED
#define MEMMANAGERNEW_H_INCLUDED

#include <vector>
#include <map>
#include <queue>

#include "GLTile.h"                    //ladrillos
#include "GLDynamicEntityNew.h"        //entidades dinamicas
#include "GLCollision.h"               //colisiones
#include "GLRole.h"                    //roles
#include "GLImageDef.h"

#include "GLState.h"                   //estados
#include "GLEntityDefinition.h"        //definiciones de estados
#include "EventMsg.h"                  //mensajes de eventos
#include "GLLuaScript.h"               //scripts
#include "GLSoundFile.h"               //efectos de música y sonido
#include "TiffEngine.h"                //fuentes de texto
#include "GLAnimationDesc.h"           //animation desc
#include "GLParticleDesc.h"            //particle desc

#include "LogEngine.h"

#include "SDLTextureContainer.h"        //contenedor especial texturas SDL

#define SIZEOFSTATES 20 //20 estado max
#define SIZEOFDYNELEM 50 //50 elementos activos en el mapa
#define SIZEOFIMAGES 100 //100 imagenes
#define SIZEOFELEM 200 //200 tipos de elementos
#define SIZEOFLEVELS 4 //4 niveles

#define ENTITY_TYPE_ENEM_MEM 2

#define MEM_UP 0
#define MEM_DOWN 1
#define MEM_LEFT 2
#define MEM_RIGHT 3

class MemManagerNew{

private:

LogEngine *gLog;

///////////////////////////////////////////////////// DEFINICION DE UN ELEMENTO DEL JUEGO //////////////////////////////////////
int numLevels;

int numRows;
int numColls;

GLImageDef *idBackgroundImage;

typedef std::vector<GLCollision *> CollitionType;
typedef std::vector<GLEntityNew *> DinElementsType;
typedef std::vector<GLRole *> RoleType;

//componentes del mapa
GLTile **level_1_static;
//GLTile **level_1_dinamic;

DinElementsType level_1_EStatic;
DinElementsType level_1_dinamic;
DinElementsType level_1_enemies;

CollitionType coll_1;

//GESTION DE MAPA DE COLISIONES GESTIONADO POR NORMALES
CollitionType coll_1_Up;
CollitionType coll_1_Down;
CollitionType coll_1_Left;
CollitionType coll_1_Right;

CollitionType light_1;

GLTile **level_2_static;
//GLTile **level_2_dinamic;

DinElementsType level_2_EStatic;
DinElementsType level_2_dinamic;
DinElementsType level_2_enemies;
CollitionType coll_2;

//GESTION DE MAPA DE COLISIONES GESTIONADO POR NORMALES
CollitionType coll_2_Up;
CollitionType coll_2_Down;
CollitionType coll_2_Left;
CollitionType coll_2_Right;


CollitionType light_2;

GLTile **level_3_static;
//GLTile **level_3_dinamic;

DinElementsType level_3_EStatic;
DinElementsType level_3_dinamic;
DinElementsType level_3_enemies;
CollitionType coll_3;

CollitionType coll_3_Up;
CollitionType coll_3_Down;
CollitionType coll_3_Left;
CollitionType coll_3_Right;

CollitionType light_3;

GLTile **level_4_static;
//GLTile **level_4_dinamic;

DinElementsType level_4_EStatic;
DinElementsType level_4_dinamic;
DinElementsType level_4_enemies;
CollitionType coll_4;

CollitionType coll_4_Up;
CollitionType coll_4_Down;
CollitionType coll_4_Left;
CollitionType coll_4_Right;


CollitionType light_4;

RoleType rol_1;

//elementos dinámicos del mapa:
unsigned int numEntities;                             //elementos dinámicos.

int num_players;                                      //numero de jugadores

int act_player_id;
int act_player_level;
float act_player_X;
float act_player_Y;

GLDynamicEntityNew *player_1;                                //elementos dinamicos especiales => Jugadores
GLDynamicEntityNew *player_2;
GLDynamicEntityNew *player_3;
GLDynamicEntityNew *player_4;

std::string GamePlayScript;
std::string GameIAScript;
std::string GameCollScript;

///////////////////////////////////////////////////// DEFINICION DE UN ELEMENTO DEL JUEGO //////////////////////////////////////

typedef std::map<int, GLState *> StateType;         //vector de estados
unsigned int actState;                              //estados actuales.


typedef std::map<int, GLEntityDefinition *> StaticElementsType;
typedef std::map<std::string, GLLuaScript *> LuaScriptType;
typedef std::map<std::string, GLImageDef *> IdImagesType;
typedef std::map<std::string, GLSoundFile *> SoundElementsType;
typedef std::map<std::string, TiffEngine *> TiffElementsType;
typedef std::map<std::string, GLAnimationDesc *> GLAnimType;
typedef std::map<std::string, GLParticleDesc *> GLParticleType;

StateType s;
DinElementsType dElements;
StaticElementsType sElements;
SoundElementsType sonElements;
IdImagesType iImages;
LuaScriptType lSElements;
TiffElementsType tElements;
GLAnimType gAnimElements;
GLParticleType gParticleElements;

//Container de imagenes SI SOLO ENGINE SDL20
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SDL20_IMAGE
    SDLTextureContainer imageSDLContainer;
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Transmision de eventos entre el gestor de los dispositivos de entrada, dispositivo gráfico de salida y
//el "cerebro" del juego (gestor de estados, gestor del juego)

typedef std::queue<EventMsg *> qMsgEventType;       //GLLaunchSystems -> GLStateManager
typedef std::queue<GLTile *> qMsgRenderType;        //GLStateManager -> GLRenderNew
//typedef std::queue<LevelMap *> qMsgMapLevelType;    //-> futuro almacen remoto de datos

qMsgEventType qMsgGLLS_GLSM;    //cola de mensajes de GLLaunchSystems a GLStateManager;
qMsgEventType qMsgGLSM_GLLS;    //cola de mensajes de GLStateManager a GLLaunchSystems;

qMsgEventType qMsgGLSM_GLRNT;   //cola de render entre GLStateManager y GLRenderNew;
qMsgEventType qMsgGLRNT_GLSM;    //cola de eventos entre GLRenderMew y GLStateManager;


public:

MemManagerNew(){
    numEntities = 0;
    actState = -1;
    gLog = new LogEngine();
    idBackgroundImage = new GLImageDef();
    player_1 = NULL;
    player_2 = NULL;
    player_3 = NULL;
    player_4 = NULL;

};

~MemManagerNew(){
    numEntities = 0;
    actState = -1;

    //borrar todas las estructuras de memoria que gestiona el juego:

    //(nota: los contenedores de información de nivel se eliminan en cada traspaso de estado)
    s.clear();
    dElements.clear();
    sElements.clear();
    sonElements.clear();
    iImages.clear();
    lSElements.clear();
    gAnimElements.clear();
    gParticleElements.clear();

    //almacenes de recursos del juegos
    gLog->info("MemManager::~MemManagerNew() --> MEMORY MANAGEMENT FINISHED! ");
};

//GET-SET RECURSOS DE LA APLICACION
/***********************************************************************/
//Gestion de elementos dinámicos (en GameNew)
////////////////////////////////////////////////////////////////
unsigned int getDinElementsLength(){
    return numEntities;
};

GLEntityNew *getDinElement(unsigned int index){
    return dElements[index];
};

void setDinElement(unsigned int index, GLEntityNew *data){
    dElements[index] = data;
};
////////////////////////////////////////////////////////////////

//Gestion de elementos
////////////////////////////////////////////////////////////////
GLEntityDefinition *getEntityDefinition(int key){
    StaticElementsType::iterator it;

    it = sElements.find(key);

    if (it!=sElements.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setEntityDefinition(int key, GLEntityDefinition *data){
    std::pair<int, GLEntityDefinition *> node(key, data);
    sElements.insert(node);
};
////////////////////////////////////////////////////////////////

//Gestion de imagenes.
/////////////////////////////////////////////////////////////////
GLImageDef *getImageDef(std::string key){

    IdImagesType::iterator it;
    ImageData iData;

    GLImageDef *dummyImageDef = new GLImageDef();

    it = iImages.find(key);

    if (it!=iImages.end()){
        return it->second;
    }else{
        return dummyImageDef;
    }
};

void setImageDefinition(std::string key, GLImageDef *data){
    std::pair<std::string, GLImageDef *> node(key, data);
    iImages.insert(node);
};
/////////////////////////////////////////////////////////////////

//Gestion de estados
/////////////////////////////////////////////////////////////////
GLState *getState(int key){
    StateType::iterator it;
    it = s.find(key);
    if (it!=s.end()){
        actState = key;
        return it->second;
    }else{
        actState = -1;
        return NULL;
    }
};

unsigned int getActState(){return actState;}

void setState(int key, GLState *data){
     std::pair<int, GLState *> node(key, data);
     s.insert(node);
};
/////////////////////////////////////////////////////////////////

//Gestion LUA
/////////////////////////////////////////////////////////////////
GLLuaScript *getLuaScript(std::string key){

    LuaScriptType::iterator it;
    it = lSElements.find(key);
    if (it!=lSElements.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setLuaScript(std::string key, GLLuaScript *data){
    std::pair<std::string, GLLuaScript *> node(key, data);
    lSElements.insert(node);
};

/////////////////////////////////////////////////////////////////

//Gestion TIFF
/////////////////////////////////////////////////////////////////

TiffEngine *getTiffEngine(std::string key){

    TiffElementsType::iterator it;
    it = tElements.find(key);
    if (it!=tElements.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setTiffEngine(std::string key, TiffEngine *data){
    std::pair<std::string, TiffEngine *> node(key, data);
    tElements.insert(node);
};

/////////////////////////////////////////////////////////////////

//Gestion Sounds
/////////////////////////////////////////////////////////////////
GLSoundFile *getSoundFile(std::string key){

    SoundElementsType::iterator it;
    it = sonElements.find(key);
    if (it!=sonElements.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setSoundFile(std::string key, GLSoundFile *data){
    std::pair<std::string, GLSoundFile *> node(key, data);
    sonElements.insert(node);
};
//////////////////////////////////////////////////////////////////////

//Gestion de animacion esqueletal
//////////////////////////////////////////////////////////////////////
GLAnimationDesc *getAnimationDesc(std::string key){

    GLAnimType::iterator it;
    it = gAnimElements.find(key);
    if (it!=gAnimElements.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setAnimationDesc(std::string key, GLAnimationDesc *data){
    std::pair<std::string, GLAnimationDesc *> node(key, data);
    gAnimElements.insert(node);
};
//////////////////////////////////////////////////////////////////////

//Gestion de animacion de particulas
//////////////////////////////////////////////////////////////////////
GLParticleDesc *getParticleDesc(std::string key){

    GLParticleType::iterator it;
    it = gParticleElements.find(key);
    if (it!=gParticleElements.end()){
        return it->second;
    }else{
        return NULL;
    }
};

void setParticleDesc(std::string key, GLParticleDesc *data){
    std::pair<std::string, GLParticleDesc *> node(key, data);
    gParticleElements.insert(node);
};

//////////////////////////////////////////////////////////////////////

/***********************************************************************/

//GET-SET MENSAJES DE LA APLICACION
/***********************************************************************/

//--> SEND MSG MQ STATE MANAGER TO RENDER
void setEventMsgStateManagerToRender(EventMsg *msg){
    qMsgGLSM_GLRNT.push(msg);
};

//--> GET MSG MQ RENDER STATE MANAGER TO RENDER
EventMsg *getEventMsgStateManagerToRender(){
     if (!qMsgGLSM_GLRNT.empty()){
        EventMsg *msg = qMsgGLSM_GLRNT.front();
        qMsgGLSM_GLRNT.pop();
        return msg;
    }else{
        EventMsg *data = new EventMsg();
        return data;
    }
};

//--> QUEUE RENDER STATE MANAGER TO RENDER
bool isEmptyQueueMsgStateManagerToRender(){
    return qMsgGLSM_GLRNT.empty();
};



//--> SEND MSG MQ RENDER TO STATE MANAGER
void setEventMsgRenderToStateManager(EventMsg *msg){
    qMsgGLRNT_GLSM.push(msg);
};

//--> GET MSG MQ RENDER TO STATE MANAGER
EventMsg *getEventMsgRenderToStateManager(){
    if (!qMsgGLRNT_GLSM.empty()){
        EventMsg *msg = qMsgGLRNT_GLSM.front();
        qMsgGLRNT_GLSM.pop();
        return msg;
    }else{
        EventMsg *data = new EventMsg();
        return data;
    }
}

//--> QUEUE RENDER TO STATE MANAGER
bool isEmptyQueueMsgRenderToStateManager(){
    return qMsgGLRNT_GLSM.empty();
};


//-->SEND MSG MQ GLLAUNCH TO STATE MANAGER
void setEventMsgToStateManager(EventMsg *msg){
    qMsgGLLS_GLSM.push(msg);
};
//-->GET MSG MQ GLLAUNCH TO STATE MANAGER
EventMsg *getEventMsgFromStateManager(){
    if (!qMsgGLLS_GLSM.empty()){
        EventMsg *msg = qMsgGLLS_GLSM.front();
        qMsgGLLS_GLSM.pop();
        return msg;
    }else{
        EventMsg *data = new EventMsg();
        return data;
    }
};
//--> EMPTY MSG MQ GLLAUNCH TO STATE MANAGER
bool isEmptyQueueMsgFromStateManager(){
    return qMsgGLLS_GLSM.empty();
};
//--> SEND MSG MQ STATE MANAGER TO GLLAUNCH
void setEventMsgToGLLaunch(EventMsg *msg){
    qMsgGLSM_GLLS.push(msg);
};
//--> GET MSG MQ STATE MANAGER TO GLLAUNCH
EventMsg *getEventMsgFromToGLLaunch(){
    if (!qMsgGLSM_GLLS.empty()){
        EventMsg *msg = qMsgGLSM_GLLS.front();
        qMsgGLSM_GLLS.pop();
        return msg;
    }else{
        EventMsg *data = new EventMsg();
        return data;
    }
};
//--> EMPTY MSG MQ STATE MANAGER TO GLLAUNCH
bool isEmptyQueueMsgFromToGLLaunch(){
    return qMsgGLSM_GLLS.empty();
};

/***********************************************************************/


//GET-SET ELEMENTOS DEL NIVEL
/***********************************************************************/
//num levels
int getNumLevels(){return numLevels;}
void setNumLevels(int _numLevels){numLevels = _numLevels;}

//num rows
int getNumRows(){return numRows;}
void setNumRows(int _numRows){numRows = _numRows;}

//num colls
int getNumColls(){return numColls;}
void setNumColls(int _numColls){numColls = _numColls;}


//idBackgroundImage
GLImageDef *getBackgroundImage(){return idBackgroundImage;}
void setBackgroudImage(GLImageDef *_idBackgroundImage){idBackgroundImage->copyImage(_idBackgroundImage);}

void createLevels(int x, int y, int levels);
void deleteLevels(int x, int y, int levels);

void setStaticTileLevel(int level, int x, int y, GLTile data);
GLTile getStaticTileLevel(int level, int x, int y);

void setDinamicElementLevel(int level, int x, int y, GLEntityNew data, int typeEntity);
void setDataCollitionLevel(int level, GLCollision *data);

void setCollisionStaticMap(int level, int orientation, GLCollision *coll);
void setCollisionStaticMapData(int level, int orientation, int index, GLCollision *coll);

std::vector<GLCollision *>getCollisionStaticMap(int level, int orientation);


void setDataLightLevel(int level, GLCollision *data);

void setDataRoleMap(GLRole *data){
    rol_1.push_back(data);
}

int getNumPlayers(){return this->num_players;}
void setNumPlayers(int _num_players){this->num_players = _num_players;}

void setActPlayer(int _act_player_id, int _act_player_level, float _act_player_X, float _act_player_Y){
    act_player_id = _act_player_id;
    act_player_level = _act_player_level;
    act_player_X = _act_player_X;
    act_player_Y = _act_player_Y;
}

int getPlayerId(){return act_player_id;}
int getPlayerLevel(){return act_player_level;}
float getPlayerX(){return act_player_X;}
float getPlayerY(){return act_player_Y;}

void setPlayer(int level, GLDynamicEntityNew *player);
GLDynamicEntityNew *getPlayer(int level);
void deletePlayers();

void setGamePlayScript(std::string _GamePlay){GamePlayScript = _GamePlay;}
std::string getGamePlayScript(){return GamePlayScript;}

void setGameIAScript(std::string _GameIA){GameIAScript = _GameIA;}
std::string getGameIAScript(){return GameIAScript;}

void setGameCollScript(std::string _GameColl){GameCollScript = _GameColl;}
std::string getGameCollScript(){return GameCollScript;}

std::vector<GLEntityNew *>getEnemiesByLevel(int level);
std::vector<GLEntityNew *>getDynamicEntitiesByLevel(int level);
std::vector<GLEntityNew *>getStaticEntitiesByLevel(int level);
std::vector<GLCollision *>getCollisionByLevel(int level);
std::vector<GLRole *>getRoles(){return rol_1;}

/***********************************************************************/
};

#endif // MEMMANAGERNEW_H_INCLUDED
