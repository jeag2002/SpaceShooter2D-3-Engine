#ifndef SDLIMAGEN_H_INCLUDED
#define SDLIMAGEN_H_INCLUDED

#include "Stdafx.h"
#include "GLImageDef.h"

class SDLImagen{

public:

    SDLImagen(){
        DATA_TYPE = NULL;
        gLogEngine = NULL;
    };

    SDLImagen(MemManagerNew *_ENTITY_DATA, LogEngine *_log){
        DATA_TYPE = _ENTITY_DATA;
        gLogEngine = _log;
    };

    ~SDLImagen(){
    };

    GLImageDef *processImageToSDL(const char *path_to_img, const char *extension, int params[]){
        GLImageDef *img = new GLImageDef();
        return img;
    }

private:

    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;

};
#endif // SDLIMAGEN_H_INCLUDED
