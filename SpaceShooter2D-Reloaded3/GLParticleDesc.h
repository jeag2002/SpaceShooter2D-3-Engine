#ifndef GLPARTICLEDESC_H_INCLUDED
#define GLPARTICLEDESC_H_INCLUDED

#include <SDL.h>

class GLParticleDesc{

public:

GLParticleDesc(){
    idimage = 0.0f;
    x_1 = 0.0f;
    y_1 = 0.0f;
    scale = 0.0f;
    maxparticles = 0.0f;
    alpha_inf = 0.0f;
    alpha_sup = 0.0f;
    velocity = 0.0f;
    direction = 0.0f;
    spread = 0.0f;
    length = 0.0f;
};

~GLParticleDesc(){
    idimage = 0.0f;
    x_1 = 0.0f;
    y_1 = 0.0f;
    scale = 0.0f;
    maxparticles = 0.0f;
    alpha_inf = 0.0f;
    alpha_sup = 0.0f;
    velocity = 0.0f;
    direction = 0.0f;
    spread = 0.0f;
    length = 0.0f;
};

unsigned int getImageId(){return idimage;}
void setImageId(unsigned int _idimage){idimage = _idimage;}

float getX(){return x_1;}
void setX(float _x_1){x_1 = _x_1;}

float getY(){return y_1;}
void setY(float _y_1){y_1 = _y_1;}

float getScale(){return scale;}
void setScale(float _scale){scale = _scale;}

float getMaxParticles(){return maxparticles;}
void setMaxParticles(float _maxparticles){maxparticles = _maxparticles;}

float getAlphaInf(){return alpha_inf;}
void setAlphaInf(float _alpha_inf){alpha_inf = _alpha_inf;}

float getAlphaSup(){return alpha_sup;}
void setAlphaSup(float _alpha_sup){alpha_sup = _alpha_sup;}

float getVelocity(){return velocity;}
void setVelocity(float _velocity){velocity = _velocity;}

float getDirection(){return direction;}
void setDirection(float _direction){direction = _direction;}

float getSpread(){return spread;}
void setSpread(float _spread){spread = _spread;}

float getLength(){return length;}
void setLength(float _length){length = _length;}

SDL_Color getColorInf(){return color_inf;}
void setColorInf(SDL_Color _color_inf){color_inf = _color_inf;}

SDL_Color getColorSup(){return color_sup;}
void setColorSup(SDL_Color _color_sup){color_sup = _color_sup;}

void renderParticle(){};

private:

unsigned int idimage;
float x_1;
float y_1;
float scale;
float maxparticles;
float alpha_inf;
float alpha_sup;
float velocity;
float direction;
float spread;
float length;

SDL_Color color_inf;
SDL_Color color_sup;


};


#endif // GLPARTICLEDESC_H_INCLUDED
