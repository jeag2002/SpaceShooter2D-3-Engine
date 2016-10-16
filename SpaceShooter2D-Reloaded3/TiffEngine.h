#ifndef TIFFENGINE_H_INCLUDED
#define TIFFENGINE_H_INCLUDED

#include "GlobalNew.h"
#include <SDL.h>
#include <SDL_ttf.h>

class TiffEngine{

public:

    TiffEngine(){
        pathtotiff = "";
        sizetiff = 0;
    }

    TiffEngine(char *_pathtotiff, int _sizetiff, SDL_Color _color){
        pathtotiff = _pathtotiff;
        sizetiff = _sizetiff;
        color = _color;
    }

    ~TiffEngine(){
    };

    SDL_Surface *processInputText(const char *text);


private:

char *pathtotiff;
int sizetiff;
SDL_Color color;
TTF_Font *font;

};

#endif // TIFFENGINE_H_INCLUDED
