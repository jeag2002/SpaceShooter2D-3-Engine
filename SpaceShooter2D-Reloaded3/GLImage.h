#ifndef GLIMAGE_H_INCLUDED
#define GLIMAGE_H_INCLUDED

#include "Stdafx.h"
#include "GLImageDef.h"

#define BMP "BMP"
#define JPG "JPEG"
#define PNG "PNG"
#define TGA "TGA"
#define ETC1 "ETC1"         //para imagenes comprimidas

#define BGR_RGB_FLAG 1
#define LINEAL 0
#define NEAREST 1
#define REPEAT 0
#define CLAMP 1
#define MIPMAP 1
#define POWER2 1

#define BMP_TRANSPARENT 1

class GLImage{

public:

    GLImage(){
        DATA_TYPE = NULL;
        gLogEngine = NULL;
    };

    GLImage(MemManagerNew *_ENTITY_DATA, LogEngine *_log){
        DATA_TYPE = _ENTITY_DATA;
        gLogEngine = _log;
    };

    ~GLImage(){
    };

    //params 0 ->BGR a RGB
    //params 1 ->LINEAL (0); NEAREST(1)
    //params 2 ->CLAMP (0/1)
    //params 3 ->MIPMAP
    //params 4 ->POWER 2

    GLImageDef *processImageToGL(const char *path_to_img, const char *extension, int params[]);
    GLImageDef *processParallaxImageToGL(const char *file, relMovementPol windows);

private:

    struct TextureImage {
        enum Format {
            RGB = 0,
            RGBA = 1
        };
    };

    typedef struct image{
        void *data;
        GLenum format;
        GLint width;
        GLint height;
    };

    GLImageDef *processBMPOld(const char *path_to_img, int params[]);
    GLImageDef *processBMP(const char *path_to_img, int params[]);
    GLImageDef *processJPGPNG(const char *path_to_img, int params[], enum TextureImage::Format format);
    GLImageDef *processTGA(const char *path_to_img);

    int power_of_two(int input);

    SDL_Surface *ConvertToRGBA(SDL_Surface *frame);
    SDL_Surface *ConvertToPower2(SDL_Surface *frame, std::string extension);
    GLubyte *ConvertToTransparent(SDL_Surface *frame);

    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;
    image img_1;

};

#endif // GLIMAGE_H_INCLUDED
