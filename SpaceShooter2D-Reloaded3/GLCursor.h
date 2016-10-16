#ifndef GLCURSOR_H_INCLUDED
#define GLCURSOR_H_INCLUDED

#include "Stdafx.h"

class GLCursor{

public:

GLCursor(){};

GLCursor(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
    gNew = _gNew;
    gMem = _ENTITY_DATA;
    gLogEngine = _log;
    x_pos_cursor = 0.0f;
    y_pos_cursor = 0.0f;
};

void setXPosCursor(float _x_pos_cursor){x_pos_cursor = _x_pos_cursor;}
float getXPosCursor(){return x_pos_cursor;}

void setYPosCursor(float _y_pos_cursor){y_pos_cursor = _y_pos_cursor;}
float getYPosCursor(){return y_pos_cursor;}

~GLCursor(){};

void processCursor();

private:

GlobalNew *gNew;
MemManagerNew *gMem;
LogEngine *gLogEngine;

float x_pos_cursor;
float y_pos_cursor;

};

#endif // GLCURSOR_H_INCLUDED
