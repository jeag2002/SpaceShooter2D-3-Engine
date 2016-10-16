/*
23-08-2015 JALCARAZ
SPACESHOOTER2D-RELOADED2
Gestión del scrolling del nivel.

A partir de la posición  del jugador, definirá la ventana en el que se mueve el jugador,
Establecerá la referencia.
Hará que el resto de elementos aparezcan posicionados según esta referencia.

1- Definir el tamaño del mundo.
2- Dividir el mundo en recuadros del tamanyo de la ventana.
3- Evaluar en que ventana está el jugador
4- Tomar como referencia esa posición y pintar la ventana. Tomar un punto de referencia relativo.
5- Coger todos los elementos estáticos y dinámicos y tomarlos como esta referencia.
6- A medida que el jugador se mueva, solo se moverá la ventana si supera el limite horizontal/vertical de la ventana.

(NOTA:El tamaño del mundo; asi como de los tiles y de la ventana a mostrar han de ser proporcionales.)

1.1-
Ampliar la gestion para cualquier tamanyo del mundo, tamanyo de los tiles y tamanyo de la ventana.

Cálculo de:

1-Posición inicial del jugador.
2-Referencia del mapa (pos_glob<->pos_rel; getScreen_tile_set)

La gestion de colisiones, etc; se hacen en coordenadas absolutas. GLCamera solo se encarga de transformar las coordenadas
absolutas en relativas.


*/

#ifndef GLCAMERANEW_H_INCLUDED
#define GLCAMERANEW_H_INCLUDED

#include "Stdafx.h"

class GLCameraNew{

public:

GLCameraNew();

GLCameraNew(LogEngine *_log);

~GLCameraNew();

void setScrSize(screenSize _scrSize){scrSize = _scrSize;}
screenSize getScrSize(){return scrSize;}

float getDeffX0(){return deff_x_0;}
float getDeffY0(){return deff_y_0;}

void init(float _pos_x_player, float _pos_y_player, int _size_world_x, int _size_world_y, int _size_screen_x,  int _size_screen_y, int _size_tile_x, int _size_tile_y);

//1era version => definimos 8 posiciones. (teclas)
screenSize moveCamera(float _pos_x_player, float _pos_y_player, int _size_tile_x, int _size_tile_y, int _direction, int inc);

//definimos nueva funcionalidad desplazando la camara del jugador en funcion de su contorno. (calculado en el proceso de gamelogic)--> cinematica con raton
screenSize moveCameraInc(relMovementPol absCoordPol);

//conversion de coordenadas reales a coordenadas relativas de una entidad (sprite cuadrado)
relMovement getRelativePosition(float _pos_x_entity, float _pos_y_entity, int _size_tile_x, int _size_tile_y);

//conversion de coordenadas reales a coordenadas relativas de una entidad en forma de poligono-
relMovementPol getRelativePositionInc(relMovementPol absCoordPol, float _pos_x_entity, float _pos_y_entity);

//encuadre de la imagen de detras.
relMovementPol getBackgroundImageDimensions();

//encuadre parallax imagen de detras
relMovementPol textCoordinatesParallax(float imgSizeXParallax, float imgSizeYParallax, float _pos_x_player, float _pos_y_player, float inc, int _direction);

//encuadre parallax imagen de detras a coordenadas relativas de una entidad en forma de poligono
relMovementPol textCoordinatesParallaxInc(relMovementPol absCoordPol);

private:

LogEngine *gLogEngine;

screenSize scrSize;

//ATRIBUTES
//-> posicion del jugador (real)
float pos_x_player;
float pos_y_player;

//-> size del mundo a printar
int size_world_x;
int size_world_y;

//-> tamanyo de la ventana a mostrar
int size_screen_x;
int size_screen_y;

//-> tamanyo de los tiles
int size_tile_x;
int size_tile_y;

float ref_x_0; //referencia 0_x
float ref_y_0; //referencia 0_y

float deff_x_0;
float deff_y_0;

int reference_size_screen_x;
int reference_size_screen_y;

int tile_tot_scr_x;
int tile_tot_scr_y;

int tile_max_world_x;
int tile_max_world_y;

int tile_min_screen_x;
int tile_max_screen_x;

int tile_min_screen_y;
int tile_max_screen_y;

int num_tiles_x_scr;
int num_tiles_y_scr;

int tit_inf_x_begin;
int tit_sup_x_begin;
int tit_inf_y_begin;
int tit_sup_y_begin;

//FUNCTIONS

//posicionamiento inicial de la camara
screenSize calculateIniPos();





};

#endif // GLCAMERANEW_H_INCLUDED
