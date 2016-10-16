#ifndef GLSTATE_H_INCLUDED
#define GLSTATE_H_INCLUDED

#include "Stdafx.h"
#include "EventMsg.h"

/*

20151015.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2

Definicion de un estado del juego. Representa a una pantalla diferente según el momento (una splashpage, un menu, un nivel de juego etc.)

Definido de momento como un fichero .ini. Tiene este aspecto:

INDEX_STATE TYPE_STATE STATE_ID PATH_TO_DEFINITION_LEVEL INDEX_FORWARD INDEX_STOP INDEX_FINISH INDEX_ERROR

Siendo:

INDEX_STATE => Estado a procesar
TYPE_STATE  => (Splash, Menu, Level, Exit) => (Todos son estados, pero se procesan de forma distinta)
STATE_ID    => (Estado del "ESTADO"... CREATE, START, UPDATE, CLOSE, DELETE)
PATH_TO_DEFINITION_LEVEL => (fichero ini configuración del estado)

INDEX_CALLBACK => Estado origen cuando se ha hecho una pausa en la ejecucion del nivel (p.j de un nivel a un menu)
INDEX_FORWARD => Estado al que va, cuando todo ha ido bien
INDEX_STOP => Estado al que va cuando hay una pausa
INDEX_FINISH => EXIT
INDEX_ERROR => EXIT (IGUAL DE FINISH, pero en este caso, se cierra todo el programa y se guarda toda la info del error disponible)


Ejemplo:

0 0 0 ./data/level1/level1.ini 1 1 1 1
1 3 0 ./data/exit/exit.ini  0 0 0 0

*/


class GLState{

public:

GLState(){
    path = "";
    stateid = 0;
    type = 0;

    forwardId = 0;
    stopId = 0;
    finishId = 0;
    errorId = 0;
    callbackId = IDLE_STATE;
};

GLState(char *path_to_identificator, int _ini_state_id, int _ini_type){
    path = path_to_identificator;
    type = _ini_type;
    stateid = _ini_state_id;

    forwardId = 0;
    stopId = 0;
    finishId = 0;
    errorId = 0;
    callbackId = IDLE_STATE;
};

~GLState(){
    path = "";
    stateid = 0;
    type = 0;

    forwardId = 0;
    stopId = 0;
    finishId = 0;
    errorId = 0;

    callbackId = IDLE_STATE;
};

//GET-SETS
////////////////////////////////////////////////////
char *getIdentificator(){return path;};

void setState(int _stateid){stateid = _stateid;};
int getState(){return stateid;};

void setType(int _type){type = _type;};
int getType(){return type;};

//Gets-sets diferentes estados.
void setIndexForwardId(int _forwardId){forwardId = _forwardId;};
int getIndexForwardId(){return forwardId;};

void setIndexStopId(int _stopId){stopId = _stopId;};
int getIndexStopId(){return stopId;};

void setIndexFinishId(int _finishId){finishId = finishId;};
int getIndexFinishId(){return finishId;};

void setIndexErrorId(int _errorId){errorId = _errorId;};
int getIndexErrorId(){return errorId;};

void setCallbackId(int _callbackId){callbackId = _callbackId;};
int getCallbackId(){return callbackId;}

////////////////////////////////////////////////////

virtual void Start(){};
virtual void Stop(){};
virtual void Update(EventMsg *msgEvent){};
virtual void Run(){};

private:

char *path;
int stateid; //CREATION, START, UPDATE, STOP, RUN, DELETE
int type;    //SPLASH, MENU, LEVEL, EXIT

int forwardId;
int stopId;
int finishId;
int errorId;
int callbackId;

};

#endif // GLSTATE_H_INCLUDED
