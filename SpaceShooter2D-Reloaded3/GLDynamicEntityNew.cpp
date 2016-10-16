#include "GLDynamicEntityNew.h"

GLDynamicEntityNew::GLDynamicEntityNew(): GLEntityNew(){
}

GLDynamicEntityNew::GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity):
    GLEntityNew(_id_level, _x_entity, _y_entity){

    live = 0;
    score = 0;
    shield = 0;
    fire = 0;
    inc = 0;

    orientation = -1;
    orientationCursor = -1;

    IA_SCRIPT = "";
    COLL_SCRIPT = "";
    ANIM_SCRIPT = "";


}

GLDynamicEntityNew::GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles):
    GLEntityNew(_id_level, _x_entity, _y_entity, _num_vertices, _num_tiles){

    live = 0;
    score = 0;
    shield = 0;
    fire = 0;
    inc = 0;

    orientation = -1;
    orientationCursor = -1;

    IA_SCRIPT = "";
    COLL_SCRIPT = "";
    ANIM_SCRIPT = "";
}



GLDynamicEntityNew::GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, relMovementPol _shape, GLTile *_tiles[]):
    GLEntityNew(_id_level, _x_entity, _y_entity, _num_vertices, _num_tiles, _vertices, _shape, _tiles){

    live = 0;
    score = 0;
    shield = 0;
    fire = 0;
    inc = 0;

    orientation = -1;
    orientationCursor = -1;

    IA_SCRIPT = "";
    COLL_SCRIPT = "";
    ANIM_SCRIPT = "";

}

GLDynamicEntityNew::GLDynamicEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, relMovementPol _shape, GLTile *_tiles[], GLEntityNew *_entity):
    GLEntityNew(_id_level, _x_entity, _y_entity, _num_vertices, _num_tiles, _vertices, _shape,_tiles, _entity){

    live = 0;
    score = 0;
    shield = 0;
    fire = 0;
    inc = 0;

    orientation = -1;
    orientationCursor = -1;

    IA_SCRIPT = "";
    COLL_SCRIPT = "";
    ANIM_SCRIPT = "";
}

void GLDynamicEntityNew::copyEntity(GLEntityNew *origin){

    GLDynamicEntityNew *originDyn = (GLDynamicEntityNew *)origin;

    this->setANIM_SCRIPT(originDyn->getANIM_SCRIPT());
    this->setCOLL_SCRIPT(originDyn->getCOLL_SCRIPT());
    this->setIA_SCRIPT(originDyn->getIA_SCRIPT());
    this->setCoordShape(originDyn->getCoordShape());
    this->setShadowShape(originDyn->getShadowShape());
    this->setLimits(originDyn->getLimits());
    this->setEntityXPos(originDyn->getEntityXPos());
    this->setEntityYPos(originDyn->getEntityYPos());
    this->setFire(originDyn->getFire());
    this->setOrientation(originDyn->getOrientation());
    this->setOrientationCursor(originDyn->getOrientationCursor());
    this->setInc(originDyn->getInc());
    this->setUniqueID(originDyn->getUniqueID());
    this->setParentUniqueID(originDyn->getParentUniqueID());
    //this->setChildEntity(originDyn->getChildEntity());
    this->setTiles(originDyn->getTiles());
    this->setVerticesSize(originDyn->getVerticesSize());
    this->setTileSize(originDyn->getTileSize());


}
