#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include "Stdafx.h"
#include "SDLImagen.h"
#include "GLImage.h"

#include "Stdafx.h"

class Image{

public:

    Image(){
        DATA_TYPE = NULL;
        gLogEngine = NULL;

        glImage = new GLImage();
        sdlImage = new SDLImagen();


    };

    Image(MemManagerNew *_ENTITY_DATA, LogEngine *_log){
        DATA_TYPE = _ENTITY_DATA;
        gLogEngine = _log;

        glImage = new GLImage(DATA_TYPE,gLogEngine);
        sdlImage = new SDLImagen(DATA_TYPE,gLogEngine);

    };

    ~Image(){
    };

    GLImageDef *processImage(const char *path_to_img, const char *extension, int params[]){
        #ifdef GL11
            return glImage->processImageToGL(path_to_img,extension,params);
        #endif

        #ifdef SDL20_IMAGE
            return sdlImage->processImageToSDL(path_to_img,extension,params);
        #endif
    }

    GLImageDef *processParallaxImageToGL(const char *file, relMovementPol windows){
        #ifdef GL11
            return glImage->processParallaxImageToGL(file, windows);
        #endif
    }

private:

    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;

    GLImage *glImage;
    SDLImagen *sdlImage;

};

#endif // IMAGE_H_INCLUDED
