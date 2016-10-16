#ifndef TIFFDEFMANAGER_H_INCLUDED
#define TIFFDEFMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "TiffEngine.h"
#include "ConfigFile.h"
#define DELIMITER_COORD ","

class TiffDefManager{

public:

    TiffDefManager(){
        GLOBAL_TYPE = NULL;
        DATA_TYPE = NULL;
        gLogEngine = NULL;
    };

    TiffDefManager(GlobalNew *_GLOBAL_TYPE, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
         GLOBAL_TYPE = _GLOBAL_TYPE;
         DATA_TYPE = _ENTITY_DATA;
         gLogEngine = _log;
     };

     void processTiffDefFile(char *gamezipfile);
     SDL_Color processColor(char *color_path);

     ~TiffDefManager(){
     };


private:

    GlobalNew *GLOBAL_TYPE;
    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;


};

#endif // TIFFDEFMANAGER_H_INCLUDED
