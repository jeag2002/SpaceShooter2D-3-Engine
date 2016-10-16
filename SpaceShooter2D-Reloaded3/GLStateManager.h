/*

20151015.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2

GLStateManager.h

Version 1.0 -> Gestión desatendida de estados de un proyecto.

Encargado de:

2-Seleccionar el estado actual.
3-Hacer funcionar el estado actual.
4-Capturar eventos externos (teclado/raton)
4-Deinir transicion entre estados.
5-Salir del bucle.
*/

#ifndef GLSTATEMANAGER_H_INCLUDED
#define GLSTATEMANAGER_H_INCLUDED

#include "Stdafx.h"
#include "GameNew.h"

class GLStateManager{

public:
    GLStateManager(){};
    GLStateManager(GlobalNew *_gNew, MemManagerNew *_DATA_TYPE, LogEngine *_log){
        gNew = _gNew;
        DATA_TYPE = _DATA_TYPE;
        gLogEngine = _log;
    };

    void startStateManager();                             //inicializa el primer de la lista de estados
    void updateStateManager();                            //actualiza el estado con los eventos capturados
    void runStateManager();                               //ejecuta el estado actual
    void stopStateManager(){};                            //para el proceso de gestion de estados.

    ~GLStateManager(){
        INFOLOG("GLStateManager::~GLStateManager --> FINISHED");
    };

private:

    GlobalNew *gNew;
    MemManagerNew *DATA_TYPE;
    LogEngine *gLogEngine;
    GLState *glState;

    GameNew *gGNew;

    void getEventFromGL11();                                  //captura eventos los procesa y los reenvia al estado actual
    void sendEventToGL11(EventMsg *msgEventRtrn);             //genera eventos del StateManager y lo reenvia al principal.
    void changeStateFromStateManager(int typeMsg);                       //cambiamos el flag del estado.

    void processUpdateStateManager();


};


#endif // GLSTATEMANAGER_H_INCLUDED
