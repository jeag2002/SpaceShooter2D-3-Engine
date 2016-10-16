/*
INITPARAMENGINE_H: Procesa los parámetros de entrada del juego
*/

#ifndef INITPARAMENGINE_H_INCLUDED
#define INITPARAMENGINE_H_INCLUDED

#include "Stdafx.h"

#define HELPTAG "-help"
#define LOGTAG "-log"
#define LOGCHANNEL "-logchannel"
#define TYPELEVTAG "-typeLev"
#define LEVELTAG "-level"
#define FRAMETAG "-frame"
#define GLTAG "-gltag"
#define STATETAG "-state"

class GLInitParamEngine{

    public:

        GLInitParamEngine(int _argc, char **_argv, LogEngine *_gLogEngine, GlobalNew *_globalN);
        void startUp();
        ~GLInitParamEngine();

    private:

        LogEngine *gLogEngine;
        GlobalNew *globalN;

        int argc;
        char **argv;

        bool logLevel;
        bool logChannel;
        bool typeLev;
        bool Lev;
        bool frame;
        bool glengine;
        bool state;

        void outParameter();


};


#endif // INITPARAMENGINE_H_INCLUDED
