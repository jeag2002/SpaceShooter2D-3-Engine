#include "GLStateManager.h"

void GLStateManager::startStateManager(){
    glState = DATA_TYPE->getState(gNew->getInitialState());
    DEBUGLOGPONE("GLStateManager::startStateManager --> CARGANDO ESTADO [%d]",gNew->getInitialState());
    glState->setState(VALUE_STATE_START);
    glState->Start();
}


void GLStateManager::updateStateManager(){

    glState->setState(VALUE_STATE_UPDATE);
    //PROCESS ACTIVE MSG FROM GL11
    getEventFromGL11();
    //ACTIVE STATE LOGIC
    processUpdateStateManager();
}


void GLStateManager::processUpdateStateManager(){

    if (glState->getState() == VALUE_STATE_DELETE){
        //NEXT LEVEL
        DEBUGLOGPONE("GLStateManager::processUpdateStateManager --> NEXT LEVEL [%d]",glState->getIndexForwardId());

        //DELETE ACT DATA
        DATA_TYPE->deleteLevels(0,DATA_TYPE->getNumRows(),DATA_TYPE->getNumLevels());
        //GET NEXT STATE
        glState = DATA_TYPE->getState(glState->getIndexForwardId());
        glState->setState(VALUE_STATE_START);
        //INIT NEXT STATE
        glState->Start();
        glState->setState(VALUE_STATE_UPDATE);
        //FIRST UPDATE NEXT STATE
        EventMsg *dummyEventMsg = new EventMsg();
        glState->Update(dummyEventMsg);



    }else if (glState->getState() == VALUE_STATE_STOP){
        //CHANGE TO MENU
        DEBUGLOGPTWO("GLStateManager::processUpdateStateManager --> FREEZE TO MENU [%d] FROM [%d]", glState->getIndexStopId(), DATA_TYPE->getActState());

        unsigned int callbackId = DATA_TYPE->getActState();
        glState = DATA_TYPE->getState(glState->getIndexStopId());
        glState->setCallbackId(callbackId);
        glState->setState(VALUE_STATE_START);
        //INIT NEXT STATE MENU
        glState->Start();
        glState->setState(VALUE_STATE_UPDATE);
        //FIRST UPDATE MENU
        EventMsg *dummyEventMsg = new EventMsg();
        glState->Update(dummyEventMsg);


    }else if (glState->getState() == VALUE_STATE_RUN){

        DEBUGLOGPTWO("GLStateManager::processUpdateStateManager --> RETURN TO GAME [%d] FROM MENU [%d]", glState->getCallbackId(), DATA_TYPE->getActState());

        if (glState->getCallbackId() != IDLE_STATE)
        {
            glState = DATA_TYPE->getState(glState->getCallbackId());
            glState->setState(VALUE_STATE_UPDATE);
            EventMsg *dummyEventMsg = new EventMsg();
            glState->Update(dummyEventMsg);
        }

    }else if (glState->getState() == VALUE_STATE_FINAL){

        DEBUGLOGPONE("GLStateManager::processUpdateStateManager --> END GAME [%d]", glState->getIndexFinishId());
        EventMsg *msg = new EventMsg(QUIT,0);
        sendEventToGL11(msg);

    }else{
        EventMsg *dummyEventMsg = new EventMsg();
        glState->Update(dummyEventMsg);
    }
}



void GLStateManager::runStateManager(){

    glState->setState(VALUE_STATE_RUN);
    glState->Run();
}


//--> GLLAUNCH TO STATEMANAGER
void GLStateManager::getEventFromGL11(){

    EventMsg *msgEventRtrn = new EventMsg();

    //MESSAGES FROM GLLaunchSystemsGL11
    while(!DATA_TYPE->isEmptyQueueMsgFromStateManager())
    {

        EventMsg *msgEvent = DATA_TYPE->getEventMsgFromStateManager();
        //DEBUGLOGPSIX("GLStateManager::getEvent MSG: [%s] ON: [%d] PLAYER_ID: [%d] data::<pos:[%f] inc:[%f] ini:[%f]>",Utils::getTypeMSG(msgEvent->getTypeMsg()),msgEvent->getOn(),gNew->getActPlayer(),msgEvent->getValue(),msgEvent->getDiff(),msgEvent->getInit());

        if (msgEvent->getOn() == KEY_ON){
            if (msgEvent->getTypeMsg() == ESC){
                DEBUGLOG("GLStateManager::getEvent --> GET ESC FROM SDL ENGINE (SALIR DEL NIVEL A LA PANTALLA PRINCIPAL)");
                changeStateFromStateManager(msgEvent->getTypeMsg());
            }else if (msgEvent->getTypeMsg() == RESUME){
                DEBUGLOG("GLStateManager::getEvent --> GET RESUME FROM SDL ENGINE (RETORNAR AL NIVEL DESDE LA PANTALLA PRINCIPAL)");
                changeStateFromStateManager(msgEvent->getTypeMsg());
                //retormar el estado iniciar.
            }else if (msgEvent->getTypeMsg() == QUIT){
                DEBUGLOG("GLStateManager::getEvent --> GET QUIT FROM SDL ENGINE (FIN DEL PROCESO)");
                changeStateFromStateManager(msgEvent->getTypeMsg());
                //eliminacion de los datos
                msgEventRtrn = msgEvent;
                sendEventToGL11(msgEventRtrn);
            }else{
                //envio de eventos de consola al proceso de estado
                glState->Update(msgEvent);
            }
        }
    }

    //MESSAGES FROM GLGameLogic
    while(!DATA_TYPE->isEmptyQueueMsgRenderToStateManager())
    {
        EventMsg *msgEvent = DATA_TYPE->getEventMsgRenderToStateManager();

        if (msgEvent->getTypeMsg() == NEXT){
                DEBUGLOG("GLStateManager::getEvent --> GET NEXT FROM STATE (SIGUIENTE NIVEL)");
                changeStateFromStateManager(msgEvent->getTypeMsg());
        }else if ((msgEvent->getTypeMsg() == END) || (msgEvent->getTypeMsg() == ERR_MSG)){
                DEBUGLOG("GLStateManager::getEvent --> FIN DE LA APLICACION!");
                changeStateFromStateManager(msgEvent->getTypeMsg());
        }
    }

}

//--> STATE MANAGER TO GLLAUNCH
void GLStateManager::sendEventToGL11(EventMsg *msgEventRtrn){
    DATA_TYPE->setEventMsgToGLLaunch(msgEventRtrn);
}


void GLStateManager::changeStateFromStateManager(int typeMsg){

    if (typeMsg == ESC){
        INFOLOG("GLStateManager::changeStateFromStateManager --> STATE FREEZED");
        glState->setState(VALUE_STATE_STOP);
    }else if (typeMsg == RESUME){
        INFOLOG("GLStateManager::changeStateFromStateManager --> STATE RESUME");
        glState->setState(VALUE_STATE_RUN);
    }else if (typeMsg == NEXT){
        INFOLOG("GLStateManager::changeStateFromStateManager --> STATE NEXT");
        glState->setState(VALUE_STATE_DELETE);
    }else if ((typeMsg == END) || (typeMsg == QUIT)){
        INFOLOG("GLStateManager::changeStateFromStateManager --> STATE END");
        glState->setState(VALUE_STATE_FINAL);
    }else if (typeMsg == ERROR){
        INFOLOG("GLStateManager::changeStateFromStateManager --> STATE ERROR");
        glState->setState(VALUE_STATE_FINAL);
    }

}
