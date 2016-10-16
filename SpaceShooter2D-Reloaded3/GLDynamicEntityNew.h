#ifndef GLDYNAMICENTITYNEW_H_INCLUDED
#define GLDYNAMICENTITYNEW_H_INCLUDED

#include "GLEntityNew.h"

class GLDynamicEntityNew: public GLEntityNew{

public:

GLDynamicEntityNew();
GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity);
GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles);
GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, relMovementPol _shape, GLTile *_tiles[]);
GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, relMovementPol _shape, GLTile *_tiles[], GLEntityNew *_entity);

int getLive(){return live;}
void setLive(int _live){live = _live;}

int getScore(){return score;}
void setScore(int _score){score = _score;}

int getShield(){return shield;}
void setShield(int _shield){shield = _shield;}

int getFire(){return fire;}
void setFire(int _fire){fire = _fire;}

int getInc(){return inc;}
void setInc(int _inc){inc = _inc;}

int getOrientation(){return orientation;}
void setOrientation(int _orientation){orientation = _orientation;}

int getOrientationCursor(){return orientationCursor;}
void setOrientationCursor(int _orientationCursor){orientationCursor = _orientationCursor;}

virtual void copyEntity(GLEntityNew *origin);

char *getIA_SCRIPT(){return IA_SCRIPT;}
void setIA_SCRIPT(char *_IA_SCRIPT){IA_SCRIPT = _IA_SCRIPT;}

char *getCOLL_SCRIPT(){return COLL_SCRIPT;}
void setCOLL_SCRIPT(char *_COLL_SCRIPT){COLL_SCRIPT = _COLL_SCRIPT;}

char *getANIM_SCRIPT(){return ANIM_SCRIPT;}
void setANIM_SCRIPT(char *_ANIM_SCRIPT){ANIM_SCRIPT = _ANIM_SCRIPT;}

private:

int live;
int score;
int shield;
int fire;
int inc;
int orientation;
int orientationCursor;

char *IA_SCRIPT;
char *COLL_SCRIPT;
char *ANIM_SCRIPT;
};

#endif // GLDYNAMICENTITYNEW_H_INCLUDED
