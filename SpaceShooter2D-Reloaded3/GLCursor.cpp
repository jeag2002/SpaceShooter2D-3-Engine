#include "GLCursor.h"


void GLCursor::processCursor(){

        glPushMatrix();

        GLImageDef *dataImage = gMem->getImageDef("CURSOR_1");

        //DEBUGLOGPFIVE("GLCursor::processCursor -- image id [%d] pos(x:%f y:%f) <width:%d,height:%d>",dataImage->getImageID(),x_pos_cursor,y_pos_cursor,dataImage->getWidth(),dataImage->getHeight());

        glBindTexture(GL_TEXTURE_2D, dataImage->getImageID());

        float vtxcoords[8];
        float texcoords[8];


        vtxcoords[0] = x_pos_cursor;
        vtxcoords[1] = y_pos_cursor;

        vtxcoords[2] = x_pos_cursor + float(dataImage->getWidth());
        vtxcoords[3] = y_pos_cursor;

        vtxcoords[4] = x_pos_cursor;
        vtxcoords[5] = y_pos_cursor + float(dataImage->getHeight());

        vtxcoords[6] = x_pos_cursor + float(dataImage->getWidth());
        vtxcoords[7] = y_pos_cursor + float(dataImage->getHeight());


        texcoords[0] = 0.0f;
        texcoords[1] = 0.0f;

        texcoords[2] = 1.0f;
        texcoords[3] = 0.0f;

        texcoords[4] = 0.0f;
        texcoords[5] = 1.0f;

        texcoords[6] = 1.0f;
        texcoords[7] = 1.0f;


        glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glPopMatrix();
}
