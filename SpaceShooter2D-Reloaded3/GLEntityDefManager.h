/*
20151005 JALCARAZ SPACESHOOTER2D-RELOADED2

GLEntityDefManager.h

Version 1.0 -> Gestión desatendida de definiciones de entidades. A partir de un indentificador, devuelve toda la identificación de un objeto.

20151018 JALCARAZ SPACESHOOTER2D-RELOADED3

Parseo y volcado del documento components2D.ini

num_elements=3                  //numero de elementos

element_1_ID = 1                //identificador del primer elemento

element_1_IMG_ARRAY = 1         //numero de imagenes
element_1_IMG_1 = MAP_1         //identificador de la primera imagen
element_1_IMG_1_ARRAY = 1       //numero de elementos del array de imagenes.
element_1_IMG_1_1 =             //coordenadas float (par X,Y) de la imagen

element_1_REF_ARRAY = 1         //numero de elementos asociados
element_1_REF_1 = 0             //elemento_id_referencia.

element_1_OTHER_ARRAY = 1       //numero de atributos auxiliares.

(Ejemplo de otros elementos, en este caso, de un elemento enemigo. Se definirá un GLEnemy que extienda de GLEntity, que parsee estos campos por separado)

////////////////////////////////////////////////////////////////////////////
element_1_LIVE = 100            //puntos de vida
element_1_SHIELD = 100          //puntos de escudo
element_1_FIRE = 100            //puntos de fuego

element_1_IA = ...              //rutina lua del comportamiento del enemigo (habrá rutinas de comportamiento de enemigos cuando actuan por separado y cuando actuan de forma conjunta)
////////////////////////////////////////////////////////////////////////////


*/

#ifndef GLENTITYDEFMANAGER_H_INCLUDED
#define GLENTITYDEFMANAGER_H_INCLUDED


#include "Stdafx.h"
#include "GLEntityDefinition.h"
#include "ConfigFile.h"
#include "GLImageDef.h"

#define DELIMITER_COORD " "
#define ID_IMAGE_NOTFOUND -1
#define ID_IMAGE_DEFAULT "IDLE"

class GLEntityDefManager{

public:

GLEntityDefManager(){};

GLEntityDefManager(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    ENTITY_DATA = _ENTITY_DATA;
    gLogEngine = _log;
};

~GLEntityDefManager(){};

void processEntityDefinitionFile(char *gamezipfile);

private:

//descripcion entidades.
char *getEntityDescription(int typeEntity);

//procesa las imagenes asociadas por cada elemento
void processArrayImages(){};

//procesa los tiles del elemento asociado por cada elemento
void processTilesArrayForImages(std::string coord, GLuint idImage, int j, int z, GLEntityDefinition *data);

//procesa los elementos dinamicos asociados por cada elemento
void processDynamicParams(){};

GlobalNew *gNew;
MemManagerNew *ENTITY_DATA;
LogEngine *gLogEngine;

};


#endif // GLENTITYDEFMANAGER_H_INCLUDED
