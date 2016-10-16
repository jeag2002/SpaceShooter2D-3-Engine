#include "GLHud.h"


void GLHud::initHud(){
    if (gNew->getLog() <= INFO_LEVEL){
        initDebugHud();
    }
}

void GLHud::initDebugHud(){
    font = TTF_OpenFont("./data/asserts/ttf/lazy.ttf", 28);
    if (font == NULL){
        WARNLOG("GLHud::initDebugHud --> UNCAPABLE TO LOAD LAZY.TTF");
    }else{
        numFrames = 0;
        presentFrames = 0;
        currentTime = SDL_GetTicks();
        lastTime = 0;
    }
}



void GLHud::processHud(){
    if (gNew->getLog() < INFO_LEVEL){
        processDebugHud();
    }
}

void GLHud::processDebugHud(){

    unsigned Texture = 0;
    char buff[100];
    GLDynamicEntityNew *player = (GLDynamicEntityNew *)gMem->getPlayer(gNew->getActPlayer()-1);

    numFrames=numFrames + 1;
    currentTime = SDL_GetTicks();

    if (currentTime > lastTime + 1000){
        presentFrames = numFrames;
        numFrames = 0;
        lastTime = currentTime;
    }


    sprintf(buff, "x:%4.2f y:%4.2f frames/scnd %d",player->getEntityXPos(),player->getEntityYPos(),presentFrames);

    SDL_Color white = {0xff, 0xff, 0xff, 0xff};
    SDL_Surface *Message = TTF_RenderUTF8_Blended(const_cast<TTF_Font*>(font),buff,white);

    //DEBUGLOGPONE("GLHud::processDebugHud --> PRINT HUD (%s)",buff);


    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Message->pixels);

    float texcoords[8];
    float vtxcoords[8];

    glBindTexture(GL_TEXTURE_2D, Texture);

    vtxcoords[0] = 0.0f;
    vtxcoords[1] = 0.0f;

    vtxcoords[2] = (float)gNew->getWidthScr()/2.0f;
    vtxcoords[3] = 0.0f;

    vtxcoords[4] = 0.0f;
    vtxcoords[5] = 32.0f;

    vtxcoords[6] = (float)gNew->getWidthScr()/2.0f;
    vtxcoords[7] = 32.0f;

    texcoords[0] = 0.0f;
    texcoords[1] = 0.0f;

    texcoords[2] = 1.0f;
    texcoords[3] = 0.0f;

    texcoords[4] = 0.0f;
    texcoords[5] = 1.0f;

    texcoords[6] = 1.0f;
    texcoords[7] = 1.0f;

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDeleteTextures(1, &Texture);
	SDL_FreeSurface(Message);
}

