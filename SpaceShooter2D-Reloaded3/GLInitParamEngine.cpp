#include "GLInitParamEngine.h"

/*

-log 1/2/3/4 (1=Debug,2=Info,3=Warn,4=Error)
-typeLev 0/1 (0=Level,1=Random)
-framerrate (60=framerrate,30=framerrate)
*/

GLInitParamEngine::GLInitParamEngine(int _argc, char **_argv, LogEngine *_gLogEngine, GlobalNew *_global){

    logLevel = false;
    logChannel = false;
    typeLev = false;
    Lev = false;
    frame = false;
    glengine = false;
    state = false;

    argc = _argc;
    argv = _argv;

    gLogEngine = _gLogEngine;
    globalN = _global;
}


void GLInitParamEngine::startUp(){

    INFOLOGPONE("GLInitParamEngine::InitParamEngine --> STARTUP  ARGS (%d) ",argc);

    if (argc > 1){

        for (int i =1; i<argc; i++){

            std::string data = std::string(argv[i]);

            if (strncmp(data.c_str(),HELPTAG,5)){
                outParameter();
                exit(0);

            }else if (strncmp(data.c_str(),LOGTAG,4)){
                logLevel = true;
            }else if (strncmp(data.c_str(),LOGCHANNEL,11)){
                logChannel = true;
            }else if (strncmp(data.c_str(),TYPELEVTAG,8)){
                typeLev = true;
            }else if (strncmp(data.c_str(),LEVELTAG,6)){
                Lev = true;
            }else if (strncmp(data.c_str(),FRAMETAG,6)){
                frame = true;
            }else if (strncmp(data.c_str(),GLTAG,6)){
                glengine = true;
            }else if (strncmp(data.c_str(),STATETAG,6)){
                state = true;
            }else if (logLevel || typeLev || frame || glengine || logChannel) {

                int value = atoi(data.c_str());
                if (value >= 0 && value <= 4){
                    if (logLevel==true){
                        globalN->setLog(value);
                        logLevel=false;
                    }
                    if (logChannel == true){
                        globalN->setTypeLog(value);
                        logChannel=false;
                    }
                    if (typeLev==true){
                        typeLev=false;
                    }
                    if (glengine==true){
                        glengine=false;
                    }
                }else if (value > 4){
                     if (frame==true){
                        globalN->setFramerrate(value);
                        frame=false;
                     }
                }else{
                    DEBUGLOG("GLInitParamEngine::InitParamEngine --> PARAMETRO NO RECONOCIDO");
                    break;
                }
            }else if (Lev || state){

                if (Lev==true){Lev=false;}
                if (state==true){
                    int value = atoi(data.c_str());
                    globalN->setInitialState(value);
                    state=false;
                }

            }else{
                WARNLOG("GLInitParamEngine::InitParamEngine --> PARAMETRO NO RECONOCIDO");
                break;
            }
        }
    }else{
        WARNLOG("GLInitParamEngine::InitParamEngine --> NO HAY PARAMETROS DE ENTRADA");
    }

}


GLInitParamEngine::~GLInitParamEngine(){

}


void GLInitParamEngine::outParameter(){

    std::cout << "Parametros reconocidos: \r\n";                                            //muestra ayuda
    std::cout << "-help              : Muestra esta ayuda \r\n";                            //print esta ayuda por pantalla
    std::cout << "-frame [framerrate]: Set framerrate del juego (por defecto 60) \r\n";     //framerrate del juego
    std::cout << "-log [1/2/3/4]     : Nivel de logs \r\n";                                 //nivel de logs
    std::cout << "-logchannel [0/1]  : Channel (0 = file; 1=file+Cout) \r\n";               //logchannel 0,1
    std::cout << "-gltag [0/1]       : Motor GL11(0), GL30(1) \r\n";                        //GL11(0)/GL30(1)
    std::cout << "-typeLev [0/1]     : Tipo de nivel (0=Random;1=Carpeta) \r\n";            //generacion del nivel (0 = BPS; 1 = Predefinido)
    std::cout << "-level [nom_level] : Nivel \r\n";                                         //en caso de que typeLev =1; carpeta nom_level
    std::cout << "-state [0-X]       : State \r\n";                                         //state
}
