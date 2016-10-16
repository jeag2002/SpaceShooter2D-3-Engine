/*

20150803.0.0001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Primer paso: rehacer SpaceShooter2D-2; mejorando su lógica interna.

1) Nueva clase encargada de la carga de un nivel.

1.1) Carga de los diferentes niveles almacenados como ficheros de configuración como en el SpaceShooter2D-2.
1.2) Desacoplar renderizado de lógica de muestreo (redefinir renderizado en una nueva clase. Primero como OpenGL ES 1.1/ Luego como OpenGL ES 3.0/3.1)
1.3) Cambio motor a carga SpaceShooter2D-Reloaded2 (Simplifica los 4 ficheros en 1. Mejora las colisiones definiendo los bordes como póligonos en vez de como
                                                    frames)


5 Niveles:

1-Background (Imagen)

2-Elementos estaticos primer nivel
3-Colisiones primer nivel

4-Elementos dinámicos primer nivel
5-Reglas comportamiento elementos dinamicos primer nivel

6-Elementos estaticos segundo nivel
7-Colisiones segundo nivel

8-Elementos dinámicos segundo nivel
9-Reglas comportamiento elementos dinamicos segundo nivel

10-Colisiones mapa
11-IA mapa

(los elementos de 32x32, se recogen en un tile de 64 y se tratan de forma particular. los elementos de 128x128 se dividen en 4 partes)

Estructura del mapa

size_mundo_x size_mundo_y size_tile_x size_tile_y

level_0

xx -> imagen background

level_1

#componente estático level_1
1.....
.
.
.

Collisions level_1

#componente dinámico level_1
x.....
.
.
.


level_2

#componente estático level_2
1.....
.
.
.


Collisions level_2 (colisiones)

#componente dinámico level_2
x.....
.
.
.

Roles (element_1 level_1 type_1 pos_1(x,y) element_2 level_2 type_2 pos_2(x,y) rul12) (reglas objetos dinámicos: switches, teletransportadores, etc)
Roles (element_1 level_1 type_1 pos_1(x,y) element_2 level_2 type_2 pos_2(x,y) rul12) (reglas objetos dinámicos: switches, teletransportadores, etc)


*/

#ifndef GAMELEVELNEW_H_INCLUDED
#define GAMELEVELNEW_H_INCLUDED

#include "Stdafx.h"
#include "GLTile.h"
#include "GLEntityNew.h"
#include "GLCollision.h"
#include "GLRole.h"
#include "GLImageDef.h"

#include "GLObjectManagerNew.h"


#define DELIMITER " "
#define DELIMITER_1 ","

//Generar funcionamiento automatizado del nivel.
#define PROCEDURAL_LEVEL "PROCEDURAL"

#define COLL_PROCESS 1
#define LIGHT_PROCESS 2

class GameLevelNew{
public:

GameLevelNew::GameLevelNew(){

    gLogEngine = NULL;
    gNew = NULL;
    ENTITY_DATA = NULL;

    size_world_x = 1024;
    size_world_y = 768;

    tile_x = 64;
    tile_y = 64;

    world_tile_x = 16;
    world_tile_y = 12;

    pos_x_player_1 = 0;
    pos_y_player_1 = 0;
    level_player_1 = 0;

    pos_x_player_2 = 0;
    pos_y_player_2 = 0;
    level_player_2 = 0;

    pos_x_player_3 = 0;
    pos_y_player_3 = 0;
    level_player_3 = 0;

    pos_x_player_4 = 0;
    pos_y_player_4 = 0;
    level_player_4 = 0;

    backgroundImage = "";

    globalGameScript = "";
    globalIAScript = "";
    globalCollScript = "";
    globalMusic = "";
    globalLighting = "";

    num_collition_by_level = 0;
    num_light_by_level = 0;
    num_roles = 0;
    num_players = 0;
    act_player = 0;
}



GameLevelNew(GlobalNew *_gNew, MemManagerNew *_gMemManagerNew, LogEngine *_gLogEngine){

    gLogEngine = _gLogEngine;
    gNew = _gNew;
    ENTITY_DATA = _gMemManagerNew;

    size_world_x = 1024;
    size_world_y = 768;

    tile_x = 64;
    tile_y = 64;

    world_tile_x = 16;
    world_tile_y = 12;

    pos_x_player_1 = 0;
    pos_y_player_1 = 0;
    level_player_1 = 0;

    pos_x_player_2 = 0;
    pos_y_player_2 = 0;
    level_player_2 = 0;

    pos_x_player_3 = 0;
    pos_y_player_3 = 0;
    level_player_3 = 0;

    pos_x_player_4 = 0;
    pos_y_player_4 = 0;
    level_player_4 = 0;

    backgroundImage = "";

    globalGameScript = "";
    globalIAScript = "";
    globalCollScript = "";
    globalMusic = "";
    globalLighting = "";

    num_collition_by_level = 0;
    num_light_by_level = 0;
    num_roles = 0;
    num_players = 0;
    act_player = 0;

    //LogEngine *_gLogEngine, GlobalNew *_gNew, MemManagerNew *_gMem
    GLOMN = new GLObjectManagerNew(_gLogEngine,_gNew,_gMemManagerNew);

};

~GameLevelNew(){

    size_world_x = 0;
    size_world_y = 0;

    tile_x = 0;
    tile_y = 0;

    world_tile_x = 0;
    world_tile_y = 0;

    pos_x_player_1 = 0;
    pos_y_player_1 = 0;
    level_player_1 = 0;

    pos_x_player_2 = 0;
    pos_y_player_2 = 0;
    level_player_2 = 0;

    pos_x_player_3 = 0;
    pos_y_player_3 = 0;
    level_player_3 = 0;

    pos_x_player_4 = 0;
    pos_y_player_4 = 0;
    level_player_4 = 0;

    backgroundImage = "";

    globalGameScript = "";
    globalIAScript = "";
    globalCollScript = "";
    globalMusic = "";
    globalLighting = "";

    num_collition_by_level = 0;
    num_light_by_level = 0;
    num_roles = 0;
    num_players = 0;
    act_player = 0;
};

//Atributes
////////////////////////////////////////////////
int getNumLevels(){return num_levels;}

int getSizeWorldX(){return size_world_x;}
int getSizeWorldY(){return size_world_y;}

int getTileX(){return tile_x;}
int getTileY(){return tile_y;}

float getPosPlayer1X(){return pos_x_player_1;}
float getPosPlayer1Y(){return pos_y_player_1;}
int getLevelPlayer1(){return level_player_1;}

float getPosPlayer2X(){return pos_x_player_2;}
float getPosPlayer2Y(){return pos_y_player_2;}
int getLevelPlayer2(){return level_player_2;}

float getPosPlayer3X(){return pos_x_player_3;}
float getPosPlayer3Y(){return pos_y_player_3;}
int getLevelPlayer3(){return level_player_3;}

float getPosPlayer4X(){return pos_x_player_4;}
float getPosPlayer4Y(){return pos_y_player_4;}
int getLevelPlayer4(){return level_player_4;}

float getActPosPlayerX(){return pos_x_player_1;}
float getActPosPlayerY(){return pos_y_player_1;}
int getLevelPlayerAct(){return level_player_1;}

int getPlayers(){return num_players;}
int getActPlayer(){return act_player;}

char *getScriptGamePlay(){return this->globalGameScript.c_str();}
char *getScriptCollPlay(){return this->globalCollScript.c_str();}
char *getScriptIAPlay(){return this->globalIAScript.c_str();}
char *getScriptLigth(){return this->globalLighting.c_str();}
char *getScriptMusic(){return this->globalMusic.c_str();}

////////////////////////////////////////////////


void processGameLevelDef(char *gamezipfile);

private:

LogEngine *gLogEngine;
GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
GLObjectManagerNew *GLOMN;
GLImageDef *GLIDef;

std::string backgroundImage;

std::string globalGameScript;
std::string globalIAScript;
std::string globalCollScript;
std::string globalMusic;
std::string globalLighting;

//tamanyo del mapa a renderizar
int size_world_x;
int size_world_y;

//tamanyo de los tiles a renderizar
int tile_x;
int tile_y;

//tamanyo de tiles
int world_tile_x;
int world_tile_y;

//numero de niveles
int num_levels;

//numero de colisiones por nivel
int num_collition_by_level;
int num_light_by_level;

//numero de roles
int num_roles;

int num_players;
int act_player;

//pos player_1
float pos_x_player_1;
float pos_y_player_1;
int level_player_1;
//pos player_2
float pos_x_player_2;
float pos_y_player_2;
int level_player_2;

//pos player_3
float pos_x_player_3;
float pos_y_player_3;
int level_player_3;

//pos player_4
float pos_x_player_4;
float pos_y_player_4;
int level_player_4;

void globalParams(std::string line);
void createLevels(std::string line);
void setBackgroundImg(std::string line);
void setGlobalScripts(std::string line);
void processLevel(std::ifstream &myfile);
void processLevelStaticRow(std::string line, int level, int row);
void processLevelDinamicRow(std::string line, int level, int row);
void processLevelCollitionRow(std::string line, int level, int row, int flag);

void processLevelOrientationCollRow(int level, GLCollision *data);
void processLevelOrientationCollBlockMapRow(int level, GLCollision *data);

void processNumRoles(std::string line);
void processRoles(std::ifstream &myfile);
void processRole(int indexRole, std::string line);
void processNumPlayer(std::string line);
void processPlayers(std::ifstream &myfile);
void processPlayer(std::string line, int player);

};

#endif // GAMELEVELNEW_H_INCLUDED
