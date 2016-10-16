#include "GLRenderDynamicLevelGL11.h"



void GLRenderDynamicLevelGL11::renderPlayerLevel(int level,screenSize scrSize, GLDynamicEntityNew *player){

    int NTiles = player->getTileSize();
    GLTile **tiles = player->getTiles();

    for(int i=0; i<NTiles; i++){
        GLTile *tile = tiles[i];

        relMovement rM = CAM_MANAGER->getRelativePosition(player->getEntityXPos(),player->getEntityYPos(),tile->getWidthX(),tile->getWidthY());
        //relMovementPol rMP = CAM_MANAGER->getRelativePosition(player->getCoordShape());

        relMovementPol polTextures = tile->getTextures(player->getOrientation()-1);

        glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, tile->getGLIDImage());

        float vtxcoords[8];
        float texcoords[8];


        vtxcoords[0] = rM.rel_pos_x;
        vtxcoords[1] = rM.rel_pos_y;

        vtxcoords[2] = rM.rel_pos_x + tile->getWidthX();
        vtxcoords[3] = rM.rel_pos_y;

        vtxcoords[4] = rM.rel_pos_x;
        vtxcoords[5] = rM.rel_pos_y + tile->getWidthY();

        vtxcoords[6] = rM.rel_pos_x + tile->getWidthX();
        vtxcoords[7] = rM.rel_pos_y + tile->getWidthY();



        texcoords[0] = polTextures.nodes[0].rel_pos_x;
        texcoords[1] = polTextures.nodes[0].rel_pos_y;

        texcoords[2] = polTextures.nodes[1].rel_pos_x;
        texcoords[3] = polTextures.nodes[1].rel_pos_y;

        texcoords[4] = polTextures.nodes[2].rel_pos_x;
        texcoords[5] = polTextures.nodes[2].rel_pos_y;

        texcoords[6] = polTextures.nodes[3].rel_pos_x;
        texcoords[7] = polTextures.nodes[3].rel_pos_y;


        /*
        DEBUGLOGPNINE("GLRenderDynamicLevelGL11::renderPlayerLevel [%d] --> [%f,%f,%f,%f,%f,%f,%f,%f]",
        player->getOrientation(),
        texcoords[0],
        texcoords[1],
        texcoords[2],
        texcoords[3],
        texcoords[4],
        texcoords[5],
        texcoords[6],
        texcoords[7]
        );*/

        glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        //glDisable(GL_BLEND);
        glPopMatrix();
    }

}
