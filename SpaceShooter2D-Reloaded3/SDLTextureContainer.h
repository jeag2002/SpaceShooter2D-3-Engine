#ifndef SDLTEXTURECONTAINER_H_INCLUDED
#define SDLTEXTURECONTAINER_H_INCLUDED


#ifdef SDL20
#include <SDL.h>
#include <SDL_image.h>
#endif // SDL20

#define DEFAULT_SIZE 20

class SDLTextureContainer{

public:

SDL_Texture **createContainer(int initialSize){
    buffer = new SDL_Texture *[initialSize];
    sizeTextureBuffer = initialSize;
    sizeActTextBuffer = 0;
    return buffer;
};

SDL_Texture **createDefaultContainer(){
    buffer = new SDL_Texture *[DEFAULT_SIZE];
    sizeTextureBuffer = DEFAULT_SIZE;
    sizeActTextBuffer = 0;
    return buffer;
};

int getSizeTextureBuffer(){return sizeTextureBuffer;}
int getSizeActTextBuffer(){return sizeActTextBuffer;}

int addTexture(SDL_Texture *text){
    if (sizeActTextBuffer < sizeTextureBuffer){
        sizeActTextBuffer++;
        return sizeActTextBuffer;
    }else{
        return -1;
    }
};

SDL_Texture *getTexture(int indexTexture){
    if ((indexTexture >=0) && (indexTexture <= sizeActTextBuffer)){
        return buffer[indexTexture];
    }else{
        return NULL;
    }
};

private:

SDL_Texture **buffer;
int sizeTextureBuffer;
int sizeActTextBuffer;

};

#endif // SDLTEXTURECONTAINER_H_INCLUDED
