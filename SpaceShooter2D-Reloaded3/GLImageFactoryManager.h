/*
11-10-2015 JALCARAZ
SPACESHOOTER2D-RELOADED2

GLImageFactoryManager.h

Version 1.0 -> Gestión desatendida de imágenes. Devuelve el identificador OpenGL de la imagen. Si no lo encuentra, lo carga.

*/


#ifndef GLIMAGEFACTORYMANAGER_H_INCLUDED
#define GLIMAGEFACTORYMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "ConfigFile.h"
#include "Image.h"
#include "GLImageDef.h"

#define PARALLAX_ENABLED "SI"

class GLImageFactoryManager{

public:
    GLImageFactoryManager(){

        DATA_TYPE = NULL;
        gLogEngine = NULL;

        image = new Image();

    };

    GLImageFactoryManager(MemManagerNew *_ENTITY_DATA, LogEngine *_log){

        DATA_TYPE = _ENTITY_DATA;
        gLogEngine = _log;


        int flags = IMG_INIT_JPG | IMG_INIT_PNG;

        int result = IMG_Init(flags);
        if (result != flags) {
            WARNLOGPONE("GLImageFactoryManager ERROR %s", IMG_GetError());
            exit(-1);
        }

        image = new Image(DATA_TYPE, gLogEngine);
    };

    void processImageDefFile(char *gamezipfile);

    ~GLImageFactoryManager(){};

private:

    Image *image;
    GLImageDef *imageDef;
    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;

};

#endif // GLIMAGEFACTORYMANAGER_H_INCLUDED
