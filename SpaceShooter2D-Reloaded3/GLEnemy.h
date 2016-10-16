#ifndef GLENEMY_H_INCLUDED
#define GLENEMY_H_INCLUDED

#include "Stdafx.h"
#include "GLEntityNew.h"

/*
20151208.SPACESHOOTER2D-RELOADED2.1.000.001 -> Definicion del elemento del juego Enemigos
*/

class GLEnemy: public GLEntityNew{

public:
    GLEnemy(int _num_vertices, int _num_tiles, int _id_level, relMovement _vertices[], GLTile _tiles[], GLEntityNew *_entity, std::string _luaIAId);
    ~GLEnemy();
private:
    std::string luaIAId;
};

#endif // GLENEMY_H_INCLUDED
