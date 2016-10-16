#include "GLCameraNew.h"

/**********************************************************************************/
/*
GLCameraNew()

Inicializacion de la camara, valores por defecto
*/
/**********************************************************************************/

/** */
GLCameraNew::GLCameraNew(){

//posicion del jugador
pos_x_player = 0;
pos_y_player = 0;

//tamaño del mundo
size_world_x = 1024;
size_world_y = 768;

//tamaño de la ventana
size_screen_x = 640;
size_screen_y = 480;

//tamaño de tile (estático)
size_tile_x = 64;
size_tile_y = 64;

//numero totales tiles del mundo
tile_max_world_x = 10;
tile_max_world_y = 8;

//numero totales tiles de la pantalla
tile_tot_scr_x = 16;
tile_tot_scr_y = 12;

//tiles que se muestran en el mapa
tile_min_screen_x = 0;
tile_max_screen_x = 9;

tile_min_screen_y = 0;
tile_max_screen_y = 8;

reference_size_screen_x = 0;
reference_size_screen_y = 0;

gLogEngine = NULL;

}

/**********************************************************************************/


/**********************************************************************************/
/*
GLCameraNew()

Inicializacion de la camara, valores por defecto
*/
/**********************************************************************************/

/** */
GLCameraNew::GLCameraNew(LogEngine *_log){

//posicion del jugador
pos_x_player = 0;
pos_y_player = 0;

//tamaño del mundo
size_world_x = 1024;
size_world_y = 768;

//tamaño de la ventana
size_screen_x = 640;
size_screen_y = 480;

//tamaño de tile (estático)
size_tile_x = 64;
size_tile_y = 64;

//numero totales tiles del mundo
tile_max_world_x = 10;
tile_max_world_y = 8;

//numero totales tiles de la pantalla
tile_tot_scr_x = 16;
tile_tot_scr_y = 12;

//tiles que se muestran en el mapa
tile_min_screen_x = 0;
tile_max_screen_x = 9;

tile_min_screen_y = 0;
tile_max_screen_y = 8;

deff_x_0 = 0;
deff_y_0 = 0;

reference_size_screen_x = 0;
reference_size_screen_y = 0;


gLogEngine = _log;

}

/**********************************************************************************/

/**********************************************************************************/
/*
~GLCameraNew()

Eliminacion de variables
*/
/**********************************************************************************/

/** */
GLCameraNew::~GLCameraNew(){

//poaicion del jugador
pos_x_player = 0;
pos_y_player = 0;

//tamaño del mundo
size_world_x = 0;
size_world_y = 0;

//tamaño de la ventana
size_screen_x = 0;
size_screen_y = 0;

//tamaño de tile (estático)
size_tile_x = 0;
size_tile_y = 0;

//numero totales tiles del mundo
tile_max_world_x = 0;
tile_max_world_y = 0;

//numero totales tiles de la pantalla
tile_tot_scr_x = 0;
tile_tot_scr_y = 0;

//tiles que se muestran en el mapa
tile_min_screen_x = 0;
tile_max_screen_x = 0;

tile_min_screen_y = 0;
tile_max_screen_y = 0;

reference_size_screen_x = 0;
reference_size_screen_y = 0;

deff_x_0 = 0;
deff_y_0 = 0;

}

/**********************************************************************************/
/*
screenSize init(float _pos_x_player, float _pos_y_player, int _size_world_x, int _size_world_y, int _size_screen_x,  int _size_screen_y, int _size_tile_x, int _size_tile_y){

Inicializa los parámetros de la camara. Posiciona la camara en su posicion inicial

pos_x_player, pos_y_player := posicion inicial del jugador
size_world_x, size_world_y := tamaño del mundo
size_screen_x, size_screen_y := tamaño de la ventana a mostrar
size_tile_x, size_tile_y := tamaño de los tiles que conforman la parte "estática" del mundo (por defecto 64x64)

tile_max_world_x, tile_max_world_y := tamaño del mundo en tiles
tile_tot_scr_x, tile_tot_scr_y := tamaño de la ventana en tiles

tile_min_screen_x, tile_max_screen_x, tile_min_screen_y, tile_max_screen_y := tamaño de la ventana a mostrar

*/
/**********************************************************************************/

/** */
void GLCameraNew::init(float _pos_x_player, float _pos_y_player, int _size_world_x, int _size_world_y, int _size_screen_x,  int _size_screen_y, int _size_tile_x, int _size_tile_y){

//posicion del jugador inicial
pos_x_player = _pos_x_player;
pos_y_player = _pos_y_player;

//tamaño del mundo
size_world_x = _size_world_x;
size_world_y = _size_world_y;

//tamaño de la ventana
size_screen_x = _size_screen_x;
size_screen_y = _size_screen_y;

//tamaño de tile (estático)
size_tile_x = _size_tile_x;
size_tile_y = _size_tile_y;

//numero totales tiles del mundo
tile_max_world_x = 0;
tile_max_world_y = 0;

//numero totales tiles de la pantalla
tile_tot_scr_x = 0;
tile_tot_scr_y = 0;

//tiles que se muestran en el mapa
tile_min_screen_x = 0;
tile_max_screen_x = 0;

tile_min_screen_y = 0;
tile_max_screen_y = 0;

reference_size_screen_x = 0;
reference_size_screen_y = 0;

 calculateIniPos();

}


/**********************************************************************************/
/*
GLCameraNew::calculateIniPos()

Se encarga de definir los tiles que se presentaran por pantalla al principio del nivel, teniendo en cuenta
la posicion del jugador.

Las coordenadas del jugador se determinan por el margen superior izquierda.

(x,                     (x+size_tile_player_x,
 y)                      y)
-----------------------
|                      |
|                      |
|                      |
-----------------------
(x,                    (x+size_tile_player_x,
 y+size_tile_player_y)  y+size_tile_player_y)



las coordenadas del mundo a mostrar por pantalla son las siguientes:

(tile_min_screen_x   (tile_max_screen_x,
tile_min_screen_y)    tile_min_screen_y)
----------------------
|                    |
|                    |
|                    |
|                    |
----------------------
(tile_min_screen_x   (tile_max_screen_x
tile_max_screen_y)    tile_max_screen_y)

*/
/**********************************************************************************/

//**//
screenSize GLCameraNew::calculateIniPos(){

    DEBUGLOG("GLCameraNew::calculateIniPos --> POSICIONAMIENTO INICIAL DE LA CAMARA - INI");

    //numero de tiles que dispone el mundo a renderizar
    int num_tiles_x_total = size_world_x / size_tile_x;
    if (size_world_x % size_tile_x > 0){num_tiles_x_total += 1;}
    int num_tiles_y_total = size_world_y / size_tile_y;
    if (size_world_y % size_tile_y > 0){num_tiles_y_total += 1;}

    DEBUGLOGPFOUR("GLCameraNew::calculateIniPos --> size world (%d, %d); tiles scr (%d, %d)",size_world_x, size_world_y, num_tiles_x_total, num_tiles_y_total);

    tile_max_world_x = num_tiles_x_total;
    tile_max_world_y = num_tiles_y_total;

    //limitacion en caso de que la pantalla sea mayor que el mundo a renderizar.


    if (size_screen_x <= size_world_x){reference_size_screen_x = size_screen_x;} else {reference_size_screen_x = size_world_x;}
    if (size_screen_y <= size_world_y){reference_size_screen_y = size_screen_y;} else {reference_size_screen_y = size_world_y;}

    //numero de tiles que dispone la pantalla a renderizar
    num_tiles_x_scr = reference_size_screen_x / size_tile_x;
    if (reference_size_screen_x % size_tile_x > 0){num_tiles_x_scr += 1;}
    num_tiles_y_scr = reference_size_screen_y / size_tile_y;
    if (reference_size_screen_y % size_tile_y > 0){num_tiles_y_scr += 1;}

    INFOLOGPFOUR("GLCameraNew::calculateIniPos --> size screen (%d, %d) tiles scr (%d, %d)",reference_size_screen_x, reference_size_screen_y, num_tiles_x_scr, num_tiles_y_scr);

    int tit_inf_x = 0;
    int tit_sup_x = num_tiles_x_scr-1;
    int tit_inf_y = 0;
    int tit_sup_y = num_tiles_y_scr-1;

    //definimos la cuadricula donde situamos la posicion inicial del jugador
    bool encontrado = false;
    while ((tit_sup_x < num_tiles_x_total) && (!encontrado)){

       encontrado = (((tit_inf_x * size_tile_x) <= pos_x_player) && ((tit_sup_x * size_tile_x) >= pos_x_player));

       if (!encontrado){
            tit_sup_x += 1;
            tit_inf_x = tit_sup_x - (num_tiles_x_scr-1);
       }

    }


    //22-03-2016 (posicionado inicial en caso de descuadre)
    //////////////////// FILTER IF TILE SCREEN ARE OUT OF LIMITS /////////////////////////////////////
    if ((tile_max_world_x - tit_sup_x ) <= 3){
         encontrado = false;
         tit_sup_x = tile_max_world_x - 1;
         tit_inf_x = tit_sup_x - (num_tiles_x_scr-1);
         while((tit_inf_x > 0) && (!encontrado)){
            encontrado = (((tit_inf_x * size_tile_x) <= pos_x_player) && ((tit_sup_x * size_tile_x) >= pos_x_player));
            if (!encontrado){
                tit_sup_x -= 1;
                tit_inf_x = tit_sup_x - (num_tiles_x_scr-1);
            }
         }
    }
    //////////////////// FILTER IF TILE SCREEN ARE OUT OF LIMITS /////////////////////////////////////

    encontrado = false;

    while ((tit_sup_y < num_tiles_y_total) && (!encontrado)){

       encontrado = (((tit_inf_y * size_tile_y) <= pos_y_player) && ((tit_sup_y * size_tile_y) >= pos_y_player));

       if (!encontrado){
            tit_sup_y += 1;
            tit_inf_y = tit_sup_y - (num_tiles_y_scr-1);
       }

    }


    //22-03-2016 (posicionado en caso de descuadre)
    //////////////////// FILTER IF TILE SCREEN ARE OUT OF LIMITS /////////////////////////////////////
    if ((tile_max_world_y - tit_sup_y ) <= 3){
         encontrado = false;
         tit_sup_y = tile_max_world_y - 1;
         tit_inf_y = tit_sup_y - (num_tiles_y_scr-1);
         while((tit_inf_y > 0) && (!encontrado)){
            encontrado = (((tit_inf_y * size_tile_y) <= pos_y_player) && ((tit_sup_y * size_tile_y) >= pos_y_player));
            if (!encontrado){
                tit_sup_y -= 1;
                tit_inf_y = tit_sup_y - (num_tiles_y_scr-1);
            }
         }
    }
    //////////////////// FILTER IF TILE SCREEN ARE OUT OF LIMITS /////////////////////////////////////

    /*
    tit_inf_x_begin = tit_inf_x;
    tit_sup_x_begin = tit_sup_x;
    tit_inf_y_begin = tit_inf_y;
    tit_sup_y_begin = tit_sup_y;
    */

    tit_inf_x_begin = 0;
    tit_sup_x_begin = (num_tiles_x_scr-1);
    tit_inf_y_begin = 0;
    tit_sup_y_begin = (num_tiles_y_scr-1);




    scrSize.x_inf = tit_inf_x;
    scrSize.x_sup = tit_sup_x;
    scrSize.y_inf = tit_inf_y;
    scrSize.y_sup = tit_sup_y;

    //definimos la posición relativa (lo que en el screen, será el punto (0,0))
    ref_x_0 = (float)(tit_inf_x * size_tile_x);
    ref_y_0 = (float)(tit_inf_y * size_tile_y);

    INFOLOGPEIGHT("GLCameraNew::calculateIniPos --> Pos Ini player Player (%f, %f) - Ventana de muestra (%d, %d) x (%d, %d) ref (%f, %f)", pos_x_player , pos_y_player, tit_inf_x, tit_inf_y, tit_sup_x, tit_sup_y, ref_x_0, ref_y_0);

    //size_world_x, size_world_y
    //size_screen_x, size_screen_y

    if (size_screen_x > size_world_x){
        deff_x_0 = ((float)size_screen_x / 2.0) - ((float)size_world_x / 2.0);
    }else{
        deff_x_0 = 0.0f;
    }

    if (size_screen_y > size_world_y){
        deff_y_0 = ((float)size_screen_y / 2.0) - ((float)size_world_y / 2.0);
    }else{
        deff_y_0 = 0.0f;
    }

    INFOLOGPSIX("GLCameraNew::calculateIniPos --> size_screen (%d, %d) - size_world (%d, %d)  =  deff (%f, %f)",size_screen_x,size_screen_y,size_world_x,size_world_y,deff_x_0,deff_y_0);

    return scrSize;

}

/**********************************************************************************/
/*
screenSize GLCameraNew::moveCamera(float _pos_x_player, float _pos_y_player, int _direction)

Mueve la camara conforme se desplaza el jugador.

Toma como referencia la coordenada (x,y) del jugador.
(De momento se descarta _size_tile_x; _size_tile_y)

De momento, se deja con logs... si se embarrulla mucho, estos logs se "desconectarán"

*/
/**********************************************************************************/

/*
https://forums.tigsource.com/index.php?topic=30011.0
*/

screenSize GLCameraNew::moveCamera(float _pos_x_player, float _pos_y_player, int _size_tile_x, int _size_tile_y, int direction, int inc){

    float incX = 0.0f;
    float incY = 0.0f;


    ref_x_0 = (_pos_x_player) - floor(float(reference_size_screen_x)*0.5f);
    if (ref_x_0 < 0.0f){ref_x_0 = 0.0f;}
    else if ((int(ref_x_0)+reference_size_screen_x)>size_world_x){ref_x_0 = float(size_world_x-reference_size_screen_x);}
    else{ref_x_0 = ref_x_0;}

    ref_y_0 = (_pos_y_player) - floor(float(reference_size_screen_y)*0.5f);
    if (ref_y_0 < 0.0f){ref_y_0 = 0.0f;}
    else if ((int(ref_y_0)+reference_size_screen_y)>size_world_y){ref_y_0 = float(size_world_y-reference_size_screen_y);}
    else{ref_y_0 = ref_y_0;}

    int tit_inf_x = int(floor((float(ref_x_0))/float(size_tile_x)));
    int tit_inf_y = int(floor((float(ref_y_0))/float(size_tile_y)));
    int tit_sup_x = int(floor((float(ref_x_0))/float(size_tile_x)));
    int tit_sup_y = int(floor((float(ref_y_0))/float(size_tile_y)));


    tit_inf_x = tit_inf_x + tit_inf_x_begin;
    tit_inf_y = tit_inf_y + tit_inf_y_begin;
    tit_sup_x = tit_sup_x + tit_sup_x_begin;
    tit_sup_y = tit_sup_y + tit_sup_y_begin;


    /*
    DEBUGLOGPEIGHT("GLCameraNew::moveCamera --> (%d,%d) x (%d,%d) ref (%f,%f) player (%f,%f) ",
                  tit_inf_x,
                  tit_inf_y,
                  tit_sup_x,
                  tit_sup_y,
                  ref_x_0,
                  ref_y_0,
                  _pos_x_player,
                  _pos_y_player);
    */

    scrSize.x_inf = tit_inf_x;
    scrSize.x_sup = tit_sup_x;
    scrSize.y_inf = tit_inf_y;
    scrSize.y_sup = tit_sup_y;



    return this->scrSize;
}


/**********************************************************************************/
/*
relMovementPol GLCameraNew::textCoordinatesParallax

Mueve la parte de la imagen Parallax a mostrar en funcion de la posición del jugador y del tamaño de la ventana a mostrar.

*/
/**********************************************************************************/

relMovementPol GLCameraNew::textCoordinatesParallax(float imgSizeXParallax, float imgSizeYParallax, float _pos_x_player, float _pos_y_player, float inc, int direction){

    relMovementPol pol;
    pol.num_nodes = 2;

    float limitXParallax = 0.0f;
    float limitYParallax = 0.0f;

    if (imgSizeXParallax >= reference_size_screen_x) {limitXParallax = reference_size_screen_x; } else{ limitXParallax = imgSizeXParallax;}
    if (imgSizeYParallax >= reference_size_screen_y) {limitYParallax = reference_size_screen_y; } else{ limitYParallax = imgSizeYParallax;}

    pol.nodes[0].rel_pos_x = (ref_x_0*2.0f);
    pol.nodes[0].rel_pos_y = (ref_y_0*2.0f);

    pol.nodes[1].rel_pos_x = limitXParallax+(ref_x_0*2.0f);
    pol.nodes[1].rel_pos_y = limitYParallax+(ref_y_0*2.0f);

    if (imgSizeXParallax <= pol.nodes[1].rel_pos_x){pol.nodes[1].rel_pos_x = imgSizeXParallax; pol.nodes[0].rel_pos_x = imgSizeXParallax-limitXParallax;}
    if (imgSizeYParallax <= pol.nodes[1].rel_pos_y){pol.nodes[1].rel_pos_y = imgSizeYParallax; pol.nodes[0].rel_pos_y = imgSizeYParallax-limitYParallax;}

    //DEBUGLOGPFOUR("GLCameraNew::moveParallax--> (%f,%f) x (%f,%f)",pol.nodes[0].rel_pos_x,pol.nodes[0].rel_pos_y,pol.nodes[1].rel_pos_x,pol.nodes[1].rel_pos_y);

    return pol;
}


/**********************************************************************************/
/*
relMovementPol GLCameraNew:getBackgroundImageDimensions

Posiciona/centra la imagen de abajo en la pantalla del juego
*/
/**********************************************************************************/

relMovementPol GLCameraNew::getBackgroundImageDimensions(){

    relMovementPol screenSz;
    screenSz.num_nodes = 2;

    screenSz.nodes[0].rel_pos_x = deff_y_0;
    screenSz.nodes[0].rel_pos_y = deff_x_0;

    screenSz.nodes[1].rel_pos_x = (float)(reference_size_screen_x) +  deff_y_0;
    screenSz.nodes[1].rel_pos_y = (float)(reference_size_screen_y) +  deff_x_0;

    return screenSz;
}


/**********************************************************************************/
/*
relMovement getRelativePosition(float _pos_x_entity, float _pos_y_entity, int _size_tile_x, int _size_tile_y)

Calcula la posicion relativa de una entidad, a partir de las coordenadas globales del mismo.

Si no está en el recuadro. devuelve un (-1,-1)

*/
/**********************************************************************************/
relMovement GLCameraNew::getRelativePosition(float _pos_x_entity, float _pos_y_entity, int _size_tile_x, int _size_tile_y){

    relMovement rM;
    rM.rel_pos_x = (_pos_x_entity - ref_x_0) + deff_y_0;
    rM.rel_pos_y = (_pos_y_entity - ref_y_0) + deff_x_0;

    return rM;
}

relMovementPol GLCameraNew::getRelativePositionInc(relMovementPol input,float _pos_x_entity, float _pos_y_entity){

    relMovementPol output;
    output.num_nodes = input.num_nodes;

    for(int i=0; i<input.num_nodes; i++){
        output.nodes[i].rel_pos_x = input.nodes[i].rel_pos_x + _pos_x_entity;
        output.nodes[i].rel_pos_y = input.nodes[i].rel_pos_y + _pos_y_entity;
    }

    return output;
}

/*
if (direction == UP){incY = -1.0f;}
else if (direction == DOWN){incY = 1.0f;}
else if (direction == LEFT){incX = -1.0f;}
else if (direction == RIGHT){incX = 1.0f;}
*/

/*
actPlayer.dX = actPlayer.x - Math.floor(0.5 * 320);
if (actPlayer.dX < 0){actPlayer.dX = 0;}
if ((actPlayer.dX+320)>384){actPlayer.dX = (384-320);}

actPlayer.dY = actPlayer.y - Math.floor(0.5 * 320);
if (actPlayer.dY < 0){actPlayer.dY = 0;}
if ((actPlayer.dY+320)>384){actPlayer.dY = (384-320);}
*/

/*
DEBUGLOGPSIX("GLCameraNew::moveCamera --> pos absoluta (%f,%f) rel0-0 (%f,%f) pos relativa (%f,%f)", _pos_x_entity, _pos_y_entity, ref_x_0, ref_y_0, rM.rel_pos_x, rM.rel_pos_y);
}else{
    rM.rel_pos_x = -1.0f;
    rM.rel_pos_y = -1.0f;
}

DEBUGLOG("GLCameraNew::moveCamera --> POSICIONAMIENTO RELATIVO DE UNA ENTIDAD SPRITE CUADRADO - FIN");
*/

/*
DEBUGLOG("GLCameraNew::moveCamera --> POSICIONAMIENTO RELATIVO DE UNA ENTIDAD SPRITE CUADRADO - INI");

float lim_x_inf = (float)(tile_min_screen_x * size_tile_x);
float lim_x_sup = (float)(tile_max_screen_x * size_tile_x);

float lim_y_inf = (float)(tile_min_screen_y * size_tile_y);
float lim_y_sup = (float)(tile_max_screen_y * size_tile_y);

relMovement rM;

if (
    (lim_x_inf <= _pos_x_entity) &&
    (lim_x_sup >= (_pos_x_entity + (float)_size_tile_x)) &&
    (lim_y_inf <= _pos_y_entity) &&
    (lim_y_sup >= (_pos_y_entity + (float)_size_tile_y))
){
*/
