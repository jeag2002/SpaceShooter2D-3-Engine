#ifndef GLPLAYER_H_INCLUDED
#define GLPLAYER_H_INCLUDED

#include "Stdafx.h"
#include "GLEntityNew.h"

/*
20151208.SPACESHOOTER2D-RELOADED2.1.000.001 -> Definicion del elemento del juego Jugador
*/

class GLPlayer: public GLEntityNew{

public:
    GLPlayer();
    GLPlayer(int _num_vertices, int _num_tiles, int _id_level, relMovementPol _vertices, GLTile *_tiles[], GLEntityNew *_entity);
    ~GLPlayer();
private:
};


#endif // GLPLAYER_H_INCLUDED
