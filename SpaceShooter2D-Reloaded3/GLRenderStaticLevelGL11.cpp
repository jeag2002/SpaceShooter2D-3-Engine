#include "GLRenderStaticLevelGL11.h"


void GLRenderStaticLevelGL11::renderStaticLevel(int level, screenSize scrSize){

    glPushMatrix();

    float vtxcoords[8];
    float texcoords[8];

    float sizeX = 0.0f;
    float sizeY = 0.0f;

    glTranslatef(CAM_MANAGER->getDeffY0(),CAM_MANAGER->getDeffX0(),0.0f);

    for(int x = scrSize.y_inf; x<= scrSize.y_sup; x++){
        for(int y = scrSize.x_inf; y<= scrSize.x_sup; y++){

            GLTile tileVal = MEM_MANAGER->getStaticTileLevel(level,x,y);

             sizeX += tileVal.getWidthX();
             sizeY = tileVal.getWidthY();

             if (tileVal.getTypeIdTile() != IDLE_TILE){

                    glBindTexture(GL_TEXTURE_2D, (GLuint)tileVal.getGLIDImage());
                    relMovementPol rMP = tileVal.getTextures(tileVal.TexturesSize()-1);

                    vtxcoords[0] = 0.0f;
                    vtxcoords[1] = 0.0f;

                    vtxcoords[2] = 0.0f;
                    vtxcoords[3] = tileVal.getWidthY();

                    vtxcoords[4] = tileVal.getWidthX();
                    vtxcoords[5] = tileVal.getWidthY();

                    vtxcoords[6] = tileVal.getWidthX();
                    vtxcoords[7] = 0.0f;

                    texcoords[0]  = rMP.nodes[0].rel_pos_x;
                    texcoords[1]  = rMP.nodes[0].rel_pos_y;
                    texcoords[2]  = rMP.nodes[1].rel_pos_x;
                    texcoords[3]  = rMP.nodes[1].rel_pos_y;
                    texcoords[4]  = rMP.nodes[2].rel_pos_x;
                    texcoords[5]  = rMP.nodes[2].rel_pos_y;
                    texcoords[6]  = rMP.nodes[3].rel_pos_x;
                    texcoords[7]  = rMP.nodes[3].rel_pos_y;

                    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
                    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
             }
             glTranslatef(tileVal.getWidthX(),0.0f,0.0f);
        }

        glTranslatef((-1.0f)*sizeX ,0.0f,0.0f);
        glTranslatef(0.0f, sizeY,0.0f);
        sizeX = 0.0f;
        sizeY = 0.0f;
    }
    glPopMatrix();
}

