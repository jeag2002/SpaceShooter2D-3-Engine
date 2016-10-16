/**
GESTION CENTRALIZADA DE ENTRADA/SALIDA

Definicion de diferentes appends para derivar el flujo de entrada desde diferentes streams; el flujo de salida hacia diferentes streams
(Files, Cout, Network, Memory)

IDEA: generar diferentes streams segun necesidad. que puedan derivarse a diferentes entradas/salidas

Como extender streams:

http://www.mr-edd.co.uk/blog/beginners_guide_streambuf

**/

#ifndef GLIO_H_INCLUDED
#define GLIO_H_INCLUDED

#include "Stdafx.h"

class GLIO{

public:

    GLIO(GlobalNew *_gNew){
        gNew = _gNew;
        #ifdef _WIN32

            iScriptFile.open (gNew->getScriptDefinitionPath(), std::ifstream::in);
            iSoundFile.open (gNew->getSoundDefinitionPath(), std::ifstream::in);
            iStateFile.open (gNew->getStateDefinitionPath(), std::ifstream::in);
            iImageFile.open (gNew->getImageDefinitionPath(), std::ifstream::in);
            iComponentsFile.open (gNew->getEntityDefinitionPath(), std::ifstream::in);
            iTiffFile.open (gNew->getTypewriteDefinitionPath(), std::ifstream::in);
            iGlobalFile.open (gNew->getGlobalPath(), std::ifstream::in);

            iAnimationFile.open(gNew->getAnimationPath(),std::ifstream::in);
            iAnimationScriptFile.open(gNew->getAnimationParticlesPath(),std::ifstream::in);
            iLightsFile.open(gNew->getLigthDefinitionPath(),std::ifstream::in);

            oLogFile.open (gNew->getLogPath(), std::ifstream::out);
            oProfileFile.open (gNew->getProfilePath(), std::ifstream::out);
        #endif
    };

    std::istream &getScriptFile(){
        #ifdef _WIN32
            return iScriptFile;
        #endif
    }

    std::istream &getSoundFile(){
        #ifdef _WIN32
            return iSoundFile;
        #endif
    }

    std::istream &getStateFile(){
        #ifdef _WIN32
            return iStateFile;
        #endif
    }

    std::istream &getImageFile(){
        #ifdef _WIN32
            return iImageFile;
        #endif
    }

    std::istream &getComponentsFile(){
        #ifdef _WIN32
            return iComponentsFile;
        #endif
    }

    std::istream &getTiffFile(){
        #ifdef _WIN32
            return iTiffFile;
        #endif
    }

    std::istream &getGlobalFile(){
        #ifdef _WIN32
            return iGlobalFile;
        #endif
    }

    std::istream &getAnimationScript(){
        #ifdef _WIN32
            return iAnimationFile;
        #endif
    }

    std::istream &getAnimationParticleScript(){
        #ifdef _WIN32
            return iAnimationScriptFile;
        #endif
    }

    std::istream &getLightDefFile(){
        #ifdef _WIN32
            return iLightsFile;
        #endif
    }


    std::istream &getLogFile(){
        #ifdef _WIN32
            return oLogFile;
        #endif
    }

    std::istream &getProfileFile(){
        #ifdef _WIN32
            return oProfileFile;
        #endif
    }

    std::istream &getAsciiFileStream(const char *gameLevelStr){

        #ifdef _WIN32
            iAsciiFile.open(gameLevelStr,std::ifstream::in);
            return iAsciiFile;
        #endif
    }

    std::istream &getBinaryFileStream(const char *imageStr){

        #ifdef _WIN32
            iBinaryFile.open(imageStr,  ios::in|ios::binary|ios::ate);
            return iBinaryFile;
        #endif
    }

    void clearAsciiFileStream(){
        #ifdef _WIN32
            iAsciiFile.close();
        #endif
    }

    void clearBinaryFileStream(){
        #ifdef _WIN32
            iBinaryFile.close();
        #endif
    }

    ~GLIO(){
        #ifdef _WIN32

            iScriptFile.close();
            iSoundFile.close();
            iStateFile.close();
            iImageFile.close();
            iComponentsFile.close();
            iTiffFile.close();
            iGlobalFile.close();

            iAnimationFile.close();
            iAnimationScriptFile.close();
            iLightsFile.close();

            oLogFile.close();
            oProfileFile.close();


        #endif

    };


private:

GlobalNew *gNew;

#ifdef _WIN32

std::ifstream iScriptFile;
std::ifstream iSoundFile;
std::ifstream iStateFile;
std::ifstream iImageFile;
std::ifstream iComponentsFile;
std::ifstream iTiffFile;
std::ifstream iGlobalFile;

std::ifstream iAnimationFile;
std::ifstream iAnimationScriptFile;
std::ifstream iLightsFile;

std::ifstream oLogFile;
std::ifstream oProfileFile;

std::ifstream iAsciiFile; //--> ficheros ASCII (definicion de niveles, scripts de lua, shaders)
std::ifstream iBinaryFile; //--> ficheros Binarios (imagenes, audios)

#endif


};

#endif //GLIO INCLUDED
