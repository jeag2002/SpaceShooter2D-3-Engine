#include "GLRenderNewGL11.h"


void GLRenderNewGL11::initRender2D(){

    float vtxcoords[8];
    float texcoords[8];

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    /*
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    */


    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}



void GLRenderNewGL11::endRender2D(){


    glDisable(GL_BLEND);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glFlush();

}

void GLRenderNewGL11::updateRender(){

    while (!MEM_MANAGER->isEmptyQueueMsgStateManagerToRender()){

        EventMsg *msg = MEM_MANAGER->getEventMsgStateManagerToRender();



        //DEBUGLOGPONE("GLRenderNewGL11::updateRender --> RENDER MSG [%d]",msg->getTypeMsg());
        //if (GLOBAL_DATA->getFLAGMOUSE() == MOUSE_OFF){
        //if (msg->getTypeMsg() != DIFFMOUSE){
        screenSize scrSize = CAM_MANAGER->moveCamera(player->getEntityXPos(),player->getEntityYPos(),sizeXPlayer,  sizeYPlayer, msg->getTypeMsg(), player->getInc());
        CAM_MANAGER->setScrSize(scrSize);
        //}else{
        if (msg->getTypeMsg() == DIFFMOUSE){
            DEBUGLOGPTHREE("GLRenderNewGL11::updateRender -- [%s] <x:%f,y:%f>",Utils::getTypeMSG(msg->getTypeMsg()),msg->getValue(),msg->getDiff());
            gGLCursor->setXPosCursor(msg->getValue());
            gGLCursor->setYPosCursor(msg->getDiff());
        }
        //}
        //}
    }

    if (idBackgroundImage->isParallax()){
            relMovementPol pol;

            //if (GLOBAL_DATA->getFLAGMOUSE() == MOUSE_OFF){
            DEBUGLOGPSIX("GLRenderNewGL11::updateRender --> PROCESS PARALLAX image_width %d image_height %d player_xpos %f player_ypos %f, player_inc %f player orientation %i",idBackgroundImage->getWidth(), idBackgroundImage->getHeight(), player->getEntityXPos(), player->getEntityYPos(), float(player->getInc()), player->getOrientation());
            pol = CAM_MANAGER->textCoordinatesParallax(idBackgroundImage->getWidth(), idBackgroundImage->getHeight(), player->getEntityXPos(), player->getEntityYPos(), float(player->getInc()), player->getOrientation());
            //}

            if (!Utils::equalsRelMovementPol(pol,polParallax)){
                idBackgroundImageParallax = parallaxProcessor->processParallaxImageToGL((const char *)idBackgroundImage->getPathToImage(),pol);
                idBackgroundImage->copyImage(idBackgroundImageParallax);
                delete idBackgroundImageParallax;
                polParallax = pol;
            }
    }


}




void GLRenderNewGL11::runRender(){
    int level = MEM_MANAGER->getNumLevels();
    int numPlayers = MEM_MANAGER->getNumPlayers();
    int actPlayer = GLOBAL_DATA->getActPlayer();

    screenSize scrSize;
    scrSize = CAM_MANAGER->getScrSize();

    int levelPlayer = player->getIdLevel();
    //levelPlayer -= 1;

    if (GLOBAL_DATA->getTogglePlayer() == KEY_ON){
        player = MEM_MANAGER->getPlayer(actPlayer-1);
    }

    initRender2D();
    renderBackgroundImage();

    glRenderStatic->renderStaticLevel(levelPlayer,scrSize);
    glRenderDyn->renderDynamicLevel(levelPlayer,scrSize);
    glRenderDyn->renderPlayerLevel(levelPlayer,scrSize, player);

    for(int otherPlayer=0; otherPlayer<numPlayers; otherPlayer++){
        if ((otherPlayer) != (actPlayer-1)){
            GLDynamicEntityNew *otherDynPlayer = MEM_MANAGER->getPlayer(otherPlayer);
            int levelOtherPlayer = otherDynPlayer->getIdLevel();
            if (levelPlayer == levelOtherPlayer){
                glRenderDyn->renderPlayerLevel(levelPlayer,scrSize,otherDynPlayer);
            }
        }
    }

    if (GLOBAL_DATA->getFLAGMOUSE() == KEY_ON){
        gGLCursor->processCursor();
    }

    gHudNew->processHud();
    endRender2D();


    //Dibuja las lineas de colision
    if ((GLOBAL_DATA->getToggleColl() == KEY_ON_COLL) || (GLOBAL_DATA->getToggleColl() == KEY_ON_COLL_LIGHT)){
        //glPolygon->drawPolygonGL11(0.0f,0.0f,2,4,true);

        std::vector<GLCollision *> vecCollUp = MEM_MANAGER->getCollisionStaticMap(levelPlayer, UP);

        for(int i=0; i<vecCollUp.size(); i++){
            GLCollision *glColl = vecCollUp[i];
            relMovementPol rMP = glColl->getRelMovementPol();
            glPolygon->drawRMPPolygonCollGL11(rMP,255.0f,0.0f,0.0f,false);
        }


        std::vector<GLCollision *> vecCollDown = MEM_MANAGER->getCollisionStaticMap(levelPlayer, DOWN);

        for(int i=0; i<vecCollDown.size(); i++){
            GLCollision *glColl = vecCollDown[i];
            relMovementPol rMP = glColl->getRelMovementPol();
            glPolygon->drawRMPPolygonCollGL11(rMP,0.0f,255.0f,0.0f,false);
        }


        std::vector<GLCollision *> vecCollLeft = MEM_MANAGER->getCollisionStaticMap(levelPlayer, LEFT);

        for(int i=0; i<vecCollLeft.size(); i++){
            GLCollision *glColl = vecCollLeft[i];
            relMovementPol rMP = glColl->getRelMovementPol();
            glPolygon->drawRMPPolygonCollGL11(rMP,0.0f,0.0f,255.0f,false);
        }


        std::vector<GLCollision *> vecCollRight = MEM_MANAGER->getCollisionStaticMap(levelPlayer, RIGHT);

         for(int i=0; i<vecCollRight.size(); i++){
            GLCollision *glColl = vecCollRight[i];
            relMovementPol rMP = glColl->getRelMovementPol();
            glPolygon->drawRMPPolygonCollGL11(rMP,255.0f,255.0f,0.0f,false);
        }

        //DRAW COLLITION MAP ENEMIES

        //DRAW COLLITION MAP ACTIVE ELEMENTS

        //DRAW COLLITION MAP PLAYERS
        relMovementPol rMPRel = CAM_MANAGER->getRelativePositionInc(player->getLimits(), player->getEntityXPos(), player->getEntityYPos());
        rMPRel.coll = 0;
        glPolygon->drawRMPPolygonCollGL11(rMPRel,255.0f,128.0f,255.0f,false);

        for(int otherPlayer=0; otherPlayer<numPlayers; otherPlayer++){
            if ((otherPlayer) != (actPlayer-1)){
                GLDynamicEntityNew *otherDynPlayer = MEM_MANAGER->getPlayer(otherPlayer);
                int levelOtherPlayer = otherDynPlayer->getIdLevel();
                if (levelPlayer == levelOtherPlayer){

                    relMovementPol rMOther_Lim = otherDynPlayer->getLimits();
                    relMovementPol rMPRel_Old = CAM_MANAGER->getRelativePositionInc(rMOther_Lim, otherDynPlayer->getEntityXPos(), otherDynPlayer->getEntityYPos());
                    rMPRel_Old.coll = 0;
                    glPolygon->drawRMPPolygonCollGL11(rMPRel_Old,0.0f,255.0f,255.0f,false);
                }
            }
        }
    }

}


/*
void GLRenderNewGL11::renderCollLimits(int actLevel){

     std::vector<GLCollision *>collLevels = MEM_MANAGER->getCollisionByLevel(actLevel);

     glPushMatrix();

     glColor4f(255.0f, 0.0f, 0.0f, 0.0f);

     float params[] = {0.0f, 0.0f, 0.0f, 640.0f, 480.0f, 640.0f, 480.0f, 0.0f};

     glVertexPointer(2, GL_FLOAT, 0, params);
     glDrawArrays(GL_LINE_LOOP, 0, 4);

     glPopMatrix();
}
*/


void GLRenderNewGL11::renderBackgroundImage(){


    glBindTexture(GL_TEXTURE_2D, (GLuint)idBackgroundImage->getImageID());
    relMovementPol sizeScreen = CAM_MANAGER->getBackgroundImageDimensions();

    float vtxcoords[8];
    GLfloat texcoords[8];

    vtxcoords[0] = sizeScreen.nodes[0].rel_pos_x;
    vtxcoords[1] = sizeScreen.nodes[0].rel_pos_y;
    vtxcoords[2] = sizeScreen.nodes[1].rel_pos_x;
    vtxcoords[3] = sizeScreen.nodes[0].rel_pos_y;
    vtxcoords[4] = sizeScreen.nodes[0].rel_pos_x;
    vtxcoords[5] = sizeScreen.nodes[1].rel_pos_y;
    vtxcoords[6] = sizeScreen.nodes[1].rel_pos_x;
    vtxcoords[7] = sizeScreen.nodes[1].rel_pos_y;

    /*
    DEBUGLOGPEIGHT("GLRenderNewGL11::renderBackgroundImage --> RENDER BACKGROUND IMAGE [%f %f %f %f %f %f %f %f]",
    vtxcoords[0],
    vtxcoords[1],
    vtxcoords[2],
    vtxcoords[3],
    vtxcoords[4],
    vtxcoords[5],
    vtxcoords[6],
    vtxcoords[7]
    );
    */


    texcoords[0] = 0.0f;
    texcoords[1] = 0.0f;
    texcoords[2] = 1.0f;
    texcoords[3] = 0.0f;
    texcoords[4] = 0.0f;
    texcoords[5] = 1.0f;
    texcoords[6] = 1.0f;
    texcoords[7] = 1.0f;

    /*
    DEBUGLOGPEIGHT("GLRenderNewGL11::renderBackgroundImage --> RENDER TEXTCOORDS IMAGE [%f %f %f %f %f %f %f %f]",
    texcoords[0],
    texcoords[1],
    texcoords[2],
    texcoords[3],
    texcoords[4],
    texcoords[5],
    texcoords[6],
    texcoords[7]
    );
    */

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


}




