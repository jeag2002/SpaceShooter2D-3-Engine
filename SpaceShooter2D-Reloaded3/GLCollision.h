#ifndef GLCOLLISION_H_INCLUDED
#define GLCOLLISION_H_INCLUDED

#include "GlobalNew.h"

class GLCollision{

public:

GLCollision(){};
GLCollision(relMovementPol _rMP){rMP = setRelMovementPol(rMP,_rMP);};
~GLCollision(){};

void setRelMovementPol(relMovementPol _rMP){rMP = setRelMovementPol(rMP,_rMP);}
relMovementPol getRelMovementPol(){return rMP;}

private:

relMovementPol rMP;

relMovementPol setRelMovementPol(relMovementPol dst, const relMovementPol src){

        dst.num_nodes = src.num_nodes;
        dst.coll = src.coll;

        for (int i=0; i<dst.num_nodes; i++){
            dst.nodes[i].rel_pos_x = src.nodes[i].rel_pos_x;
            dst.nodes[i].rel_pos_y = src.nodes[i].rel_pos_y;
        }

        return dst;
};


};


#endif // GLCOLLISION_H_INCLUDED
