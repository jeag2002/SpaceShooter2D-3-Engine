#ifndef GLROLE_H_INCLUDED
#define GLROLE_H_INCLUDED

#include "Stdafx.h"
#include "GLEntityNew.h"

class GLRole{

private:

GLEntityNew *pasiv;
GLEntityNew *activ;

std::string roleID;

public:

GLRole(){
    pasiv = new GLEntityNew();
    activ = new GLEntityNew();
    roleID = "";
};

~GLRole(){
    delete pasiv;
    delete activ;
};

GLEntityNew *getActiveElement(){return activ;}
GLEntityNew *getPassiveElement(){return pasiv;}

};

#endif // GLROLE_H_INCLUDED
