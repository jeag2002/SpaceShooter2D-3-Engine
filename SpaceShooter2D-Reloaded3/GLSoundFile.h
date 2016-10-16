#ifndef GLSOUNDFILE_H_INCLUDED
#define GLSOUNDFILE_H_INCLUDED

#include "Stdafx.h"


class GLSoundFile{

private:

LogEngine *gLogEngine;
GlobalNew *gNew;

std::string identSound;
std::string filePath;
std::string extension;
std::string typeSound;


public:

GLSoundFile(){
        identSound = "";
        filePath = "";
        extension = "";
        typeSound = "";
};

GLSoundFile(GlobalNew *_gNew, LogEngine *_log){
        gLogEngine = _log;
        gNew = _gNew;

        identSound = "";
        filePath = "";
        extension = "";
        typeSound = "";
};

std::string getIdentSound(){return identSound;};
void setIdentSound(std::string _idSound){identSound = _idSound;};

std::string getFilePath(){return filePath;};
void setFilePath(std::string _filePath){filePath = _filePath;};

std::string getExtension(){return extension;};
void setExtension(std::string _extension){extension = _extension;};

std::string getTypeSound(){return typeSound;};
void setTypeSound(std::string _typeSound){typeSound = _typeSound;};


~GLSoundFile(){};



};


#endif // GLSOUNDFILE_H_INCLUDED
