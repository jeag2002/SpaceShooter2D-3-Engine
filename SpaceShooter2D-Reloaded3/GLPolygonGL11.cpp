#include "GLPolygonGL11.h"


void GLPolygonGL11::drawPolygonGL11(float ref_x, float ref_y, float radio, int num_vertex, bool isfilled){

    /*
    static const GLfloat squareVertices[] = {
        0.0f, 100.0f,
        0.0f, 200.0f,
        100.0f, 200.0f,
        100.0f, 100.0f
    };

    glPushMatrix();
    glLineWidth(3.0);
    glColor4f(0.0, 0.0, 1.0, 1.0); // blue
    glTranslatef(5.0, 0.0, 0.0);
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glTranslatef(100.0, 0.0, 0.0);
    glColor4f(1.0, 0.0, 0.0, 1.0);  // Red
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glTranslatef(100.0, 0.0, 0.0);
    glColor4f(1.0, 1.0, 0.0, 1.0);  // Yellow
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glFlush();
    */

    static const GLfloat squareVertices[] = {
        64.0f, 64.0f,
        640.0f, 64.0f,
        640.0f, 480.0f,
        64.0f, 480.0f
    };

    glPushMatrix();
    glLineWidth(3.0);
    glColor4f(1.0, 0.0, 0.0, 0.0); // red
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glFlush();


}



void GLPolygonGL11::drawRMPPolygonCollGL11(relMovementPol rMP, float red, float green, float blue, bool isfilled){

    float *squareVertices = new float[rMP.num_nodes*2];

    int j=0;
    for (int i=2; i<=rMP.num_nodes*2; i=i+2){

         relMovement rM = rMP.nodes[j];
         relMovement rMAux = CAM_MANAGER->getRelativePosition(rM.rel_pos_x,rM.rel_pos_y,0,0);

         if (rMAux.rel_pos_x < 0){rMAux.rel_pos_x = 0;}
         else if (rMAux.rel_pos_x > float(GLOBAL_DATA->getWidthScr())){rMAux.rel_pos_x = float(GLOBAL_DATA->getWidthScr());}

         if (rMAux.rel_pos_y < 0){rMAux.rel_pos_y = 0;}
         else if (rMAux.rel_pos_y > float(GLOBAL_DATA->getHeightScr())){rMAux.rel_pos_y = float(GLOBAL_DATA->getHeightScr());}

         squareVertices[i-2] = rMAux.rel_pos_x;
         squareVertices[i-1] = rMAux.rel_pos_y;

         j++;
    }


    glPushMatrix();
    glLineWidth(3.0);

    if (rMP.coll == 0){
        glColor4f(red, green, blue, 0.0); // red
    }else{
        glColor4f(255.0,0.0,255.0, 0.0); //purple
    }

    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);

    if (!isfilled){
        glDrawArrays(GL_LINE_LOOP, 0, rMP.num_nodes);
    }else{
        glDrawArrays(GL_TRIANGLE_FAN, 0, rMP.num_nodes);
    }

    glColor4f(1.0, 1.0, 1.0, 1.0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
    glFlush();


}
