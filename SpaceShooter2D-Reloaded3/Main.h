/*

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Primera version del main.

1) Carga Motor de Logs
2) Carga GLLaunchSystems
3) Carga GLInitParam (gestor de parámetros de entrada)
4) Carga GLInit (Carga en memoria, definicion de objetos, estados, imagenes)
5) Carga primer estado del GLStateManager
    5.1)START
    5.2)RUN
    5.2)Hay eventos SDL?
    5.2.1)Si no ESC, FIN => pasa al proceso interno del State
    5.2.2)ESC = STOP. Pasa al estado ESC. (+ Estado padre) --> 5.1
    5.2.3)FIN = DELETE --> FINAL
*/

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "Stdafx.h"
#include "GLIO.h"
#include "GLInit.h"
#include "GLStateManager.h"
#include "GLLaunchSystems.h"
#include "GLInitParamEngine.h"

class Main{

public:

    Main(int argc, char *argv[]);
    ~Main();
    void Start();
    void Run();
    void Stop();

private:

    GLLaunchSystems *gLSystems;
    MemManagerNew *memM;
    GLInitParamEngine *gInitParamEngine;
    GLStateManager *gStateManager;
    GlobalNew *globalN;
    LogEngine *gLogEngine;
    GLInit *init;
    GLIO *iOEngine;
};


#endif // MAIN_H_INCLUDED
