#include "GLGameLogic.h"


void GLGameLogic::Update(EventMsg *msgEvent){

    processActiveEvents(msgEvent);
    processReactiveEvents();
    //dummyScript();
    //EventMsg *msg = new EventMsg();
    //return msg;
}

void GLGameLogic::processActiveEvents(EventMsg *msgInputEvent){

    EventMsg *msgOutputEvent;

    if (msgInputEvent->getTypeMsg() != NO_MSG){
        processActiveCommands(msgInputEvent);
    }
}

void GLGameLogic::processActiveCommands(EventMsg *msgEvents){


    float xPos = 0.0f;
    float yPos = 0.0f;
    int position = IDLE_DIRECTION;
    relMovementPol polPlayer;

    polPlayer = Player->getLimits();
    polPlayer = CAMERA_DATA->getRelativePositionInc(polPlayer, Player->getEntityXPos(), Player->getEntityYPos());

    if ((msgEvents->getTypeMsg() !=  SHOOT) && (msgEvents->getTypeMsg() != CHGWEAPON) && (msgEvents->getTypeMsg() != TOGGLE) && (msgEvents->getTypeMsg() != TOGGLE_COLL)){



        //evaluamos las colisiones + desplazamientos de forma estatica WSAD. (Mas adelante WSAD + Raton)
        if (gNew->getFLAGMOUSE() == MOUSE_OFF){

             if (msgEvents->getTypeMsg() == UP){
                //DEBUGLOG("GLGameLogic::processActiveCommands --> KEYUP DETECTED");

                xPos = Player->getEntityXPos();
                yPos = Player->getEntityYPos() - (float)Player->getInc();
                position = UP;

            }else if (msgEvents->getTypeMsg() ==  DOWN){

                //DEBUGLOG("GLGameLogic::processActiveCommands --> KEYDOWN DETECTED");

                xPos = Player->getEntityXPos();
                yPos = Player->getEntityYPos() + (float)Player->getInc();
                position = DOWN;

            }else if (msgEvents->getTypeMsg() ==  LEFT){

                //DEBUGLOG("GLGameLogic::processActiveCommands --> KEYLEFT DETECTED");

                xPos = Player->getEntityXPos() - (float)Player->getInc();
                yPos = Player->getEntityYPos();
                position = LEFT;

            }else if (msgEvents->getTypeMsg() ==  RIGHT){

                //DEBUGLOG("GLGameLogic::processActiveCommands --> KEYRIGHT DETECTED");

                xPos = Player->getEntityXPos() + (float)Player->getInc();
                yPos = Player->getEntityYPos();
                position = RIGHT;

            }

            if (!processActiveCollisions(polPlayer, xPos, yPos, position)){
                Player->setEntityXPos(xPos);
                Player->setEntityYPos(yPos);
                Player->setOrientation(position);

                EventMsg *msg = new EventMsg(position);
                ENTITY_DATA->setEventMsgStateManagerToRender(msg);
            }



        }else{

            int position_1 = IDLE_DIRECTION;
            int position_2 = IDLE_DIRECTION;

            //MOUSE + KEYBOARD
            if (msgEvents->getTypeMsg() == DIFFMOUSE){

                float x_cursor = msgEvents->getValue();
                float y_cursor = msgEvents->getDiff();
                ENTITY_DATA->setEventMsgStateManagerToRender(msgEvents);

                double angle = Utils::defineAngle(x_cursor, y_cursor, Player->getEntityXPos(), Player->getEntityYPos());
                if (angle < 0.00){angle = 360.00 + angle;}

                if ((angle >= 0.00) && (angle < 30.0)){          //RIGHT
                    position = RIGHT;
                }else if ((angle >= 30.0) && (angle < 60.0)){    //UPRIGHT
                    position = UPRIGTH;
                }else if ((angle >= 60.0) && (angle < 90.0)){    //UP
                    position = UP;
                }else if ((angle >= 90.0) && (angle < 120.0)){   //UP
                    position = UP;
               }else if ((angle >= 120.0) && (angle < 150.0)){  //UPLEFT
                    position = UPLEFT;
               }else if ((angle >= 150.0) && (angle < 180.0)){  //LEFT
                    position = LEFT;
               }else if ((angle >= 180.0) && (angle < 210.0)){  //LEFT
                    position = LEFT;
               }else if ((angle >= 210.0) && (angle < 240.0)){  //DOWNLEFT
                    position = DOWNLEFT;
               }else if ((angle >= 240.0) && (angle < 270.0)){  //DOWN
                   position = DOWN;
               }else if ((angle >= 270.0) && (angle < 300.0)){  //DOWN
                   position = DOWN;
               }else if ((angle >= 300.0) && (angle < 330.0)){  //DOWNRIGHT
                   position = DOWNRIGTH;
               }else if ((angle >= 330.0) && (angle < 360.0)){  //RIGHT
                   position = RIGHT;
               }else{
                 WARNLOG("GLGameLogic::processActiveCommands --> ANGULO DE REFERENCIA NO RECONOCIDO!");
               }

               DEBUGLOGPFOUR("GLGameLogic::processActiveCommands -- [%s] <x:%f,y:%f> angle [%f]",
                             Utils::getTypeMSG(msgEvents->getTypeMsg()),
                             msgEvents->getValue(),
                             msgEvents->getDiff(),
                             angle);

               Player->setOrientationCursor(position);

            }else if (msgEvents->getTypeMsg() == UP){ //tecla ARRIBA Sigue la misma direccion y sentido del vector

                if (Player->getOrientationCursor() == UP){                      //vector ARRIBA

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position_1 = UP;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == UPLEFT){            //vector ARRIBA IZQUIERDA

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position_1 = UP;
                    position_2 = LEFT;


                }else if (Player->getOrientationCursor() == LEFT){              //vector IZQUIERDA

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position_1 = LEFT;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == DOWNLEFT){          //vector ABAJO IZQUIERDA

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position_1 = DOWN;
                    position_2 = LEFT;


                }else if (Player->getOrientationCursor() == DOWN){              //vector ABAJO

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position_1 = DOWN;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == DOWNRIGTH){        //vector ABAJO DERECHA

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position_1 = DOWN;
                    position_2 = RIGHT;

                }else if (Player->getOrientationCursor() == RIGHT){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position_1 = RIGHT;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == UPRIGTH){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position_1 = UP;
                    position_2 = RIGHT;

                }

            }/*else if (msgEvents->getTypeMsg() == DOWN){ //tecla ABAJO Sigue la direccion del vector en direccion contraria

                if (Player->getOrientationCursor() == UP){

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position_1 = DOWN;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == UPLEFT){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position_1 = DOWN;
                    position_2 = RIGHT;

                }else if (Player->getOrientationCursor() == LEFT){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position_1 = LEFT;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == DOWNLEFT){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position_1 = UP;
                    position_2 = RIGHT;


                }else if (Player->getOrientationCursor() == DOWN){

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position_1 = UP;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == DOWNRIGTH){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position_1 = UP;
                    position_2 = LEFT;

                }else if (Player->getOrientationCursor() == RIGHT){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position_1 = RIGHT;
                    position_2 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == UPRIGTH){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position_1 = DOWN;
                    position_2 = LEFT;

                }

            }else if (msgEvents->getTypeMsg() == LEFT){ //tecla izquierda. Sigue la dirección perpendicular al vector

                if (Player->getOrientationCursor() == UP){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = LEFT;
                    position_1 = IDLE_DIRECTION;



                }else if (Player->getOrientationCursor() == UPLEFT){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = DOWN;
                    position_1 = LEFT;


                }else if (Player->getOrientationCursor() == LEFT){

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;
                    position_1 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == DOWNLEFT){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = DOWN;
                    position_1 = RIGHT;


                }else if (Player->getOrientationCursor() == DOWN){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = RIGHT;
                    position_1 = IDLE_DIRECTION;


                }else if (Player->getOrientationCursor() == DOWNRIGTH){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = DOWN;
                    position_1 = LEFT;


                }else if (Player->getOrientationCursor() == RIGHT){

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = DOWN;
                    position_1 = IDLE_DIRECTION;


                }else if (Player->getOrientationCursor() == UPRIGTH){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;
                    position_1 = LEFT;


                }

            }else if (msgEvents->getTypeMsg() == RIGHT){ //tecla derecha, sigue la dirección perpendicular, sentido contrario al vector

                if (Player->getOrientationCursor() == UP){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = RIGHT;
                    position_1 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == UPLEFT){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;
                    position_1 = RIGHT;

                }else if (Player->getOrientationCursor() == LEFT){

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = DOWN;
                    position_1 = IDLE_DIRECTION;

                }else if (Player->getOrientationCursor() == DOWNLEFT){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;
                    position_1 = LEFT;


                }else if (Player->getOrientationCursor() == DOWN){

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = LEFT;
                    position_1 = IDLE_DIRECTION;


                }else if (Player->getOrientationCursor() == DOWNRIGTH){


                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;
                    position_1 = RIGHT;


                }else if (Player->getOrientationCursor() == RIGHT){

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;
                    position_1 = IDLE_DIRECTION;


                }else if (Player->getOrientationCursor() == UPRIGTH){

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = DOWN;
                    position_1 = RIGHT;

                }

            }*/else{
                WARNLOG("GLGameLogic::processActiveCommands --> TECLA NO RECONOCIDA!");
            }

            DEBUGLOGPFIVE("GLGameLogic::processActiveCommands --> posPlayer [%s - %s] posCursor [%s] ::= <%f,%f>",Utils::getTypeMSG(position_1),Utils::getTypeMSG(position_2),Utils::getTypeMSG(Player->getOrientationCursor()),xPos,yPos);

            if (position_1 != IDLE_DIRECTION){
                if (!processActiveCollisions(polPlayer, xPos, yPos, position_1)){
                    if (position_2 != IDLE_DIRECTION){
                        if (!processActiveCollisions(polPlayer, xPos, yPos, position_2)){
                                Player->setEntityXPos(xPos);
                                Player->setEntityYPos(yPos);
                                Player->setOrientation(position);
                                EventMsg *msg = new EventMsg(position);
                                ENTITY_DATA->setEventMsgStateManagerToRender(msg);
                        }
                    }else{
                        Player->setEntityXPos(xPos);
                        Player->setEntityYPos(yPos);
                        Player->setOrientation(position);

                        EventMsg *msg = new EventMsg(position);
                        ENTITY_DATA->setEventMsgStateManagerToRender(msg);
                    }
                }
            }



            //MOUSE
            /*
               int position_1 = IDLE_DIRECTION;

               DEBUGLOGPTHREE("GLGameLogic::processActiveCommands -- [%s] <x:%f,y:%f>",Utils::getTypeMSG(msgEvents->getTypeMsg()),msgEvents->getValue(),msgEvents->getDiff());

               float x_cursor = msgEvents->getValue();
               float y_cursor = msgEvents->getDiff();
               ENTITY_DATA->setEventMsgStateManagerToRender(msgEvents);

               double angle = Utils::defineAngle(x_cursor, y_cursor, Player->getEntityXPos(), Player->getEntityYPos());
               if (angle < 0.00){angle = 360.00 + angle;}


               if ((angle >= 0.00) && (angle < 30.0)){          //RIGHT

                    xPos = Player->getEntityXPos() + (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = RIGHT;


               }else if ((angle >= 30.0) && (angle < 60.0)){    //UPRIGHT

                   xPos = Player->getEntityXPos() + (float)Player->getInc();
                   yPos = Player->getEntityYPos() - (float)Player->getInc();
                   position = RIGHT;
                   position_1 = UP;

               }else if ((angle >= 60.0) && (angle < 90.0)){    //UP

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;

               }else if ((angle >= 90.0) && (angle < 120.0)){   //UP

                    xPos = Player->getEntityXPos();
                    yPos = Player->getEntityYPos() - (float)Player->getInc();
                    position = UP;

               }else if ((angle >= 120.0) && (angle < 150.0)){  //UPLEFT

                   xPos = Player->getEntityXPos() - (float)Player->getInc();
                   yPos = Player->getEntityYPos() - (float)Player->getInc();
                   position = LEFT;
                   position_1 = UP;


               }else if ((angle >= 150.0) && (angle < 180.0)){  //LEFT

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = LEFT;


               }else if ((angle >= 180.0) && (angle < 210.0)){  //LEFT

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos();
                    position = LEFT;

               }else if ((angle >= 210.0) && (angle < 240.0)){  //DOWNLEFT

                    xPos = Player->getEntityXPos() - (float)Player->getInc();
                    yPos = Player->getEntityYPos() + (float)Player->getInc();
                    position = LEFT;
                    position_1 = DOWN;

               }else if ((angle >= 240.0) && (angle < 270.0)){  //DOWN

                   xPos = Player->getEntityXPos();
                   yPos = Player->getEntityYPos() + (float)Player->getInc();
                   position = DOWN;

               }else if ((angle >= 270.0) && (angle < 300.0)){  //DOWN

                   xPos = Player->getEntityXPos();
                   yPos = Player->getEntityYPos() + (float)Player->getInc();
                   position = DOWN;

               }else if ((angle >= 300.0) && (angle < 330.0)){  //DOWNRIGHT

                   xPos = Player->getEntityXPos() + (float)Player->getInc();
                   yPos = Player->getEntityYPos() + (float)Player->getInc();
                   position = RIGHT;
                   position_1 = DOWN;


               }else if ((angle >= 330.0) && (angle < 360.0)){  //RIGHT

                   xPos = Player->getEntityXPos() + (float)Player->getInc();
                   yPos = Player->getEntityYPos();
                   position = RIGHT;


               }else{
                 WARNLOG("GLGameLogic::processActiveCommands --> ANGULO DE REFERENCIA NO RECONOCIDO!");
               }



               if (!processActiveCollisions(polPlayer, xPos, yPos, position)){
                    if (position_1 != IDLE_DIRECTION){
                        if (!processActiveCollisions(polPlayer, xPos, yPos, position_1)){
                            Player->setEntityXPos(xPos);
                            Player->setEntityYPos(yPos);
                            Player->setOrientation(position);

                            EventMsg *msg = new EventMsg(position);
                            ENTITY_DATA->setEventMsgStateManagerToRender(msg);
                        }
                    }else{
                        Player->setEntityXPos(xPos);
                        Player->setEntityYPos(yPos);
                        Player->setOrientation(position);

                        EventMsg *msg = new EventMsg(position);
                        ENTITY_DATA->setEventMsgStateManagerToRender(msg);
                    }
               }
            */

            }//DIFFMOUSE


    }else{
        if (msgEvents->getTypeMsg() ==  SHOOT){
            DEBUGLOG("GLGameLogic::processActiveCommands --> KEYSHOOT DETECTED");

        }else if (msgEvents->getTypeMsg() == CHGWEAPON){
            DEBUGLOG("GLGameLogic::processActiveCommands --> KEYCHGWEAPON DETECTED");


        }else if ((gNew->getTogglePlayer() == KEY_ON) || (gNew->getToggleColl() == KEY_ON)){

            if (msgEvents->getTypeMsg() == TOGGLE){

                int idPlayer = 0;
                int idPlayerOld = gNew->getActPlayer();
                int numPlayers = ENTITY_DATA->getNumPlayers();

                if ((numPlayers > 1) && (numPlayers <= MAX_NUM_PLAYERS)){
                    idPlayer = idPlayerOld+1;
                    if (idPlayer > numPlayers){
                        idPlayer = 1;
                    }
                    gNew->setActPlayer(idPlayer);
                    Player = ENTITY_DATA->getPlayer(idPlayer-1);
                }
                DEBUGLOGPTWO("GLGameLogic::processActiveCommands --> CHANGE PLAYER ID:[%d] TO ID:[%d]",idPlayerOld,idPlayer);

            }else if (msgEvents->getTypeMsg() == TOGGLE_COLL){
                int toggleColl = gNew->getToggleColl();
                toggleColl++;
                if (toggleColl > KEY_ON_COLL_LIGHT){toggleColl = KEY_ON_COLL;}
                gNew->setToggleColl(toggleColl);
                DEBUGLOGPONE("GLGameLogic::processActiveCommands --> TOGGLE COLLITION MAP [%d] ", gNew->getToggleColl());
            }

        }else{
            DEBUGLOG("GLGameLogic::processActiveCommands --> KEY NOT DETECTED");
        }
    }
}

bool GLGameLogic::processActiveCollisions(relMovementPol playerLimits, float x_pos, float y_pos, int position){
     bool res = false;

     relMovementPol relMovementPlayer = transformRelMovement(playerLimits, x_pos,y_pos);
     int level = Player->getIdLevel();
     //->evalua colision con elementos activos
     std::vector<GLEntityNew *>active_elements = ENTITY_DATA->getDynamicEntitiesByLevel(level);
     for(int i=0; i<active_elements.size(); i++){
        GLEntityNew *activeElement = active_elements[i];
        if (isCollition(relMovementPlayer,transformRelMovement(activeElement->getLimits(), activeElement->getEntityXPos(), activeElement->getEntityYPos()))){
            DEBUGLOG("GLGameLogic::processActiveCollisions --> Coll Player vs Dynamic entity detected");
            //activa gameplay
            res = res || true;
        }
     }


     //->evalua colision con enemigos
     std::vector<GLEntityNew *>enemies = ENTITY_DATA->getEnemiesByLevel(level);
     for(int i=0; i<enemies.size(); i++){
        GLEntityNew *enemy = enemies[i];
        if (isCollition(relMovementPlayer,transformRelMovement(enemy->getLimits(),enemy->getEntityXPos(),enemy->getEntityYPos()))){
            DEBUGLOG("GLGameLogic::processActiveCollisions --> Coll Player vs Enemy entity detected");
            //activa gameplay
            res = res || true;
        }
     }



     //->evalua colision con elementos pasivos (Exit?, Slopes?, )
     std::vector<GLEntityNew *>pasive_elements = ENTITY_DATA->getStaticEntitiesByLevel(level);
     for(int i=0; i<pasive_elements.size(); i++){
        GLEntityNew *pasiveElement = pasive_elements[i];
        if (isCollition(relMovementPlayer,transformRelMovement(pasiveElement->getLimits(),pasiveElement->getEntityXPos(),pasiveElement->getEntityYPos()))){
            DEBUGLOG("GLGameLogic::processActiveCollisions --> Coll Player vs Static entities detected");
            //activa gameplay
            res = res || true;
        }
     }

    if (isCollition(relMovementPlayer,position,level)){
        DEBUGLOG("GLGameLogic::processActiveCollisions --> Coll Player vs Map detected");
        res = res || true;
    }

     std::vector<GLRole *>roles = ENTITY_DATA->getRoles();

     for(int i=0; i<roles.size(); i++){
        GLRole *rol = roles[i];
        GLEntityNew *active = rol->getActiveElement();
        GLEntityNew *pasive = rol->getPassiveElement();

        if ((active->getIdLevel() == Player->getIdLevel()) && (isCollition(relMovementPlayer,transformRelMovement(active->getLimits(),active->getEntityXPos(),active->getEntityYPos())))){
            DEBUGLOG("GLGameLogic::processActiveCollisions --> Coll Player vs static part of switch detected");
            res = res || true;
        }

        if ((pasive->getIdLevel() == Player->getIdLevel()) && (isCollition(relMovementPlayer,transformRelMovement(pasive->getLimits(),pasive->getEntityXPos(),pasive->getEntityYPos())))){
            DEBUGLOG("GLGameLogic::processActiveCollisions --> Coll Player vs dynamic part of switch detected");
            res = res || true;
        }
     }

     if (ENTITY_DATA->getNumPlayers() > 1){

        int act_player = gNew->getActPlayer() - 1;
        for(int other_player_id=0; other_player_id<ENTITY_DATA->getNumPlayers(); other_player_id++){
            if(other_player_id != act_player){
               GLDynamicEntityNew *other_player = ENTITY_DATA->getPlayer(other_player_id);
               if (Player->getIdLevel() == other_player->getIdLevel()){
                    relMovementPol rMPOther = CAMERA_DATA->getRelativePositionInc(other_player->getLimits(),other_player->getEntityXPos(),other_player->getEntityYPos());
                    rMPOther.coll = 0;
                    if (this->isCollition(relMovementPlayer,rMPOther,position)){
                        DEBUGLOG("GLGameLogic::processActiveCollision --> Coll Player vs Other player detected");
                        res = res || true;
                    }
               }
            }
        }
     }

     return res;
}




//de momento solo se activan los elementos del "piso del juego"
void GLGameLogic::processReactiveEvents(){
    EventMsg *msgOutputEvent = new EventMsg();

    int level = Player->getIdLevel();

    std::vector<GLEntityNew *>active_elements = ENTITY_DATA->getDynamicEntitiesByLevel(level);
    std::vector<GLEntityNew *>pasive_elements = ENTITY_DATA->getStaticEntitiesByLevel(level);
    std::vector<GLEntityNew *>enemies = ENTITY_DATA->getEnemiesByLevel(level);
    std::vector<GLCollision *>coll_map = ENTITY_DATA->getCollisionByLevel(level);
    std::vector<GLRole *>roles = ENTITY_DATA->getRoles();


    for(int i=0; i<enemies.size(); i++){

            //GET ACTUAL ENEMY
            GLDynamicEntityNew *enemy = (GLDynamicEntityNew *)enemies[i];

            //PROCESS INDIVIDUAL IA OF ENEMY
            GLDynamicEntityNew *actEnemy = processReactiveIA(enemy);


            //ENEMY VS ENEMY
            for (int w=0; w<enemies.size(); w++){
                    GLEntityNew *enemy = enemies[w];
                    if (actEnemy->getUniqueID() != enemy->getUniqueID()){
                        if (isCollition(transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos()),
                                        transformRelMovement(enemy->getLimits(),enemy->getEntityXPos(),enemy->getEntityYPos()))){
                                  //ENEMY VS ENEMY --> SIBLINGS
                                  if (actEnemy->getParentUniqueID() == enemy->getParentUniqueID()){
                                  //GAMEPLAY OF ENEMY
                                  }else{
                                  //GAMEPLAY OF ENEMY
                                  }
                        }
                    }
            }

            //ENEMY VS ACTIVE ELEMENT
            for (int j=0; j<active_elements.size(); j++){
                    GLEntityNew *actElement = active_elements[j];

                    //ACTIVE ELEMENT IS SON OF ENEMY?
                    if (actEnemy->getUniqueID() != actElement->getParentUniqueID()){
                        if (isCollition(transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos()),
                                        transformRelMovement(actElement->getLimits(), actElement->getEntityXPos(), actElement->getEntityYPos()))){
                        //GAMEPLAY OF ENEMY
                        }
                    }
            }

            //ENEMY VS PASIVE ELEMENT
            for (int z=0; z<pasive_elements.size(); z++){
                GLEntityNew *pasElement = pasive_elements[z];

                //PASIVE ELEMENT IS FATHER OF ENEMY?
                if (actEnemy->getParentUniqueID() != pasElement->getUniqueID()){
                     if (isCollition(transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos()),
                                     transformRelMovement(pasElement->getLimits(), pasElement->getEntityXPos(), pasElement->getEntityYPos()))){
                       //GAMEPLAY OF ENEMY
                     }
                 }
            }

            //ENEMY VS STATIC MAP
            for(int x=0; x<coll_map.size(); x++){

                GLCollision *collData = coll_map[i];

                if (isCollition(collData->getRelMovementPol(),
                                transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos()))){
                    //GAMEPLAY OF ENEMY
                }
            }

            //ENEMY VS TRIGGERS
            for (int y=0; y<roles.size(); y++){
                GLRole *rol = roles[i];
                GLEntityNew *active = rol->getActiveElement();
                GLEntityNew *pasive = rol->getPassiveElement();

                if ((active->getIdLevel() == actEnemy->getIdLevel()) && (isCollition(transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos())
                                                                                   ,transformRelMovement(active->getLimits(),active->getEntityXPos(),active->getEntityYPos())))){
                }

                if ((pasive->getIdLevel() == actEnemy->getIdLevel()) && (isCollition(transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos())
                                                                                   ,transformRelMovement(pasive->getLimits(),pasive->getEntityXPos(),pasive->getEntityYPos())))){
                }


            }

            //ENEMY VS PLAYER
            if (isCollition( transformRelMovement(Player->getLimits(),Player->getEntityXPos(),Player->getEntityYPos()),
                 transformRelMovement(actEnemy->getLimits(),actEnemy->getEntityXPos(),actEnemy->getEntityYPos()))){

            }

            //PROCESS ANIMATION OF ENEMY
            processReactiveAnimations(enemy);

    }

    //IA GLOBAL OF ALL ENEMIES
    processGlobalReactiveIA();




    for(int j=0; j<active_elements.size(); j++){

            GLDynamicEntityNew *actelement = (GLDynamicEntityNew *)active_elements[j];
            GLDynamicEntityNew *activeElement = processReactiveIA(actelement);


            //enemy elements
            for (int w=0; w<enemies.size(); w++){
                GLEntityNew *enemy = enemies[w];
                if (activeElement->getParentUniqueID() != enemy->getUniqueID()){
                        if (isCollition(transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos()),
                                        transformRelMovement(enemy->getLimits(),enemy->getEntityXPos(),enemy->getEntityYPos()))){
                        }
                }

            }

            //ACTIVE ELEMENT VS ACTIVE ELEMENT
            for (int j=0; j<active_elements.size(); j++){
                 GLEntityNew *actElement = active_elements[j];

                //ACTIVE ELEMENT IS THE SAME ELEMENT OF ACTIVE ELEMENT
                if (activeElement->getUniqueID() != actElement->getUniqueID()){
                        if (isCollition(transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos()),
                                        transformRelMovement(actElement->getLimits(), actElement->getEntityXPos(), actElement->getEntityYPos()))){
                                  //GAMEPLAY OF ACTIVE ELEMENT
                                  //ACTIVELEMENT VS ACTIVELEMENT --> SIBLINGS
                                  if (activeElement->getParentUniqueID() == actElement->getParentUniqueID()){
                                  //GAMEPLAY OF ENEMY
                                  }else{
                                  //GAMEPLAY OF ENEMY
                                  }

                        }
                }

            }

            //ACTIVE ELEMENT VS PASIVE ELEMENT
            for (int z=0; z<pasive_elements.size(); z++){
                GLEntityNew *pasElement = pasive_elements[z];

                //PASIVE ELEMENT IS FATHER OF ACTIVE ELEMENT?
                if (activeElement->getParentUniqueID() != pasElement->getUniqueID()){
                     if (isCollition(transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos()),
                                     transformRelMovement(pasElement->getLimits(), pasElement->getEntityXPos(), pasElement->getEntityYPos()))){
                       //GAMEPLAY OF ACTIVE ELEMENT
                     }
                 }


            }

            //ACTIVE ELEMENT VS MAP
            for(int x=0; x<coll_map.size(); x++){
                 GLCollision *collData = coll_map[x];

                if (isCollition(collData->getRelMovementPol(),
                                transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos()))){
                    //GAMEPLAY OF ACTIVE ELEMENT
                }

            }

            //ACTIVE ELEMENT VS ROL-TRIGGER
            for (int y=0; y<roles.size(); y++){

                GLRole *rol = roles[y];
                GLEntityNew *active = rol->getActiveElement();
                GLEntityNew *pasive = rol->getPassiveElement();

                if ((active->getIdLevel() == activeElement->getIdLevel()) && (isCollition(transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos())
                                                                                   ,transformRelMovement(active->getLimits(),active->getEntityXPos(),active->getEntityYPos())))){
                }

                if ((pasive->getIdLevel() == activeElement->getIdLevel()) && (isCollition(transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos())
                                                                                   ,transformRelMovement(pasive->getLimits(),pasive->getEntityXPos(),pasive->getEntityYPos())))){
                }


            }

            //ACTIVE ELEMENT VS PLAYER
            if (isCollition( transformRelMovement(Player->getLimits(),Player->getEntityXPos(),Player->getEntityYPos()),
                 transformRelMovement(activeElement->getLimits(),activeElement->getEntityXPos(),activeElement->getEntityYPos()))){
                     if (Player->getUniqueID() != activeElement->getParentUniqueID()){

                     }
            }


            processReactiveAnimations(activeElement);
    }




    return msgOutputEvent;
}


relMovementPol GLGameLogic::transformRelMovement(relMovementPol playerLimits, float x_pos, float y_pos){
    return playerLimits;
}

bool GLGameLogic::isCollition(relMovementPol source1, relMovementPol source2){
    return false;
}

bool GLGameLogic::isCollition(relMovementPol source1, relMovementPol source2, int orientation){
    bool res = false;
    //res = glCollisionScript->processCollision(source1, source2, ENTITY_DATA->getGameCollScript());
    res = glCollisionScript->AABBCollision(source1,source2, orientation);
    return res;
}

bool GLGameLogic::isCollition(relMovementPol source1, int orientation, int level){
    bool res = false;
    res = glCollisionScript->AABBCollisionToMap(source1,orientation,level);
    return res;
}




void GLGameLogic::dummyScript(){

    script = ENTITY_DATA->getLuaScript("script_1");

    DEBUGLOGPTWO("GLGameLogic::Update --> FILE %s FUNCTION %s",script->getFileName(),script->getFunction());

    std::vector<std::string> inputParameterVector = script->getInputParameter();

    DEBUGLOGPONE("GLGameLogic::Update --> INPUT PARAMETERS %d", inputParameterVector.size());

    for(int i=0; i<inputParameterVector.size(); i++){
        std::tuple<std::string, std::string, std::string> iParam = script->getInputParameterDef(inputParameterVector[i]);
        std::get<2>(iParam) = "4.0";
        script->updateInputParameter(inputParameterVector[i],iParam);
    }

    script->executeLuaScript();

    std::vector<std::string> outputParameterVector = script->getOutputParameter();

    DEBUGLOGPONE("GLGameLogic::Update --> OUTPUT PARAMETERS %d", outputParameterVector.size());

    for(int j=0; j<outputParameterVector.size(); j++){
        std::tuple<std::string, std::string, std::string> oParam = script->getOutputParameterDef(outputParameterVector[j]);
        std::string param_value = std::get<2>(oParam);
        DEBUGLOGPONE("GLGameLogic::Update --> OUTPUT PARAM RESULT: (%s)",param_value.c_str());
    }
}


