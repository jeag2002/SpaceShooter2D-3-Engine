#include "TiffEngine.h"

SDL_Surface *TiffEngine::processInputText(const char *text){

    SDL_Surface *outputSurface = NULL;
    font = TTF_OpenFont(pathtotiff, sizetiff);
    if (font != NULL){
        outputSurface = TTF_RenderUTF8_Blended(const_cast<TTF_Font*>(font),text,color);
    }
    return outputSurface;
}
