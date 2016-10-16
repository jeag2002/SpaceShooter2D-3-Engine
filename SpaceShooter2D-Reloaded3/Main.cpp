#include "Main.h"


Main::Main(int argc, char *argv[]){

    globalN = new GlobalNew();                         //generacion variables globales
    gLogEngine = new LogEngine();                      //motor de logs
    gLogEngine->deleteLogFile();                       //borra traza anterior ejecucion
    gLogEngine->printLogFlag();

    memM = new MemManagerNew();                        //gestor de memoria


    iOEngine = new GLIO(globalN);                      //engine gestion IO

    init = new GLInit(globalN, memM, gLogEngine);      //inicializa gestor de datos del juego.

    //carga datos del videojuego en formato ini en memoria (datos globales, estados, imagenes, scripts de lua).
    init->processGlobalFileInit();

    //gestion de parametros de entrada.
    gInitParamEngine = new GLInitParamEngine(argc,argv,gLogEngine,globalN);
    gInitParamEngine->startUp();

    gLogEngine->startUp(globalN->getLog(),globalN->getTypeLog());

    //carga de inicializacion
    //GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log
    gLSystems = new GLLaunchSystems(globalN,memM,gLogEngine);

    //inicializa el sistema. (cliente)
    gLSystems->initOpenGLESSystems(0,0);

    //setea nivel de logs.
    init->processResourcesFilesInit();
    //print da Global.
    init->printGlobalFileParams();

    //carga del primer nivel del juego
    gStateManager = new GLStateManager(globalN,memM,gLogEngine);


    INFOLOG("############################################");
    INFOLOG("SINISTAR 2.00.001.1  BEGIN                  ");
    INFOLOG("############################################");
}

Main::~Main(){

    INFOLOG("############################################");
    INFOLOG("SINISTAR 2.00.001.1  END                    ");
    INFOLOG("############################################");

    delete gStateManager;
    delete gLSystems;
    delete gInitParamEngine;
    delete init;
    delete iOEngine;
    delete memM;
    delete gLogEngine;
    delete globalN;

}

void Main::Start(){

    //inicializa la ventana OpenGL
    gLSystems->initOpenGLESWindow();

    //inicializa el gestor de estados (servidor)
    gStateManager->startStateManager();
}

void Main::Run(){

    //renderizado de prueba.
    //gLSystems->renderOpenGLES11Dummy(); //prueba de renderizado.
    //gLSystems->swapSDLOpenGLESBuffer();
    //SDL_Delay(2000);

    while (!gLSystems->processInputEvents()){
        gStateManager->updateStateManager();
        gStateManager->runStateManager();
        gLSystems->swapSDLOpenGLESBuffer();
        //SDL_Delay(2000);
    }


    /*
    Proceso de funcionamiento
    while(gLSystems->processInputEvents()){     //captura eventos de teclado/raton de los dispositivos de entrada (cliente)

        gStateManager->updateStateManager();    //evalua si continua el estado actual o se ha de cambiar (servidor)

        gLSystems->swapPerspectiveOpenGLES();   //prepara la pàantalla gráfica. dispositivo de salida (cliente)

        gStateManager->runStateManager();       //resuelve la logica de negocio del estado actual (cliente)

        gLSystems->swapSDLOpenGLESBuffer();     //activa el doblebuffer del sistema. (cliente)
    }
    */
}

void Main::Stop(){
    gStateManager->stopStateManager();          //para el gestor de estados (servidor)
    gLSystems->terminateSDLOpenGLES();          //para el gestor de dispositivos de entrada/salida (cliente)
}

void sinistarEnvirontment(int argc, char *argv[]){
    Main *sinistarEngine = new Main(argc, argv);
    sinistarEngine->Start();
    sinistarEngine->Run();
    sinistarEngine->Stop();
    delete sinistarEngine;
}


int main (int argc, char *argv[])
{
   sinistarEnvirontment(argc,argv);
   return 0;

}

