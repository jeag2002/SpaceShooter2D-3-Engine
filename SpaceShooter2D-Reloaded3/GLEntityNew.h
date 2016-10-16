/*

20150827.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2

Definición de una entidad mínima del juego. Puede ser un tile; un player; un enemy; un elemento estático u dinámico del juego.
Se definen en principio de forma cuadrada.

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Definicion de los parametros x_entity; y_entity. Punto de referencia de la entidad.

*/


#ifndef GLENTITYNEW_H_INCLUDED
#define GLENTITYNEW_H_INCLUDED

#include "GlobalNew.h"
#include "GLTile.h"
//#include "GLEntityDefinition.h"

#define ENTITY_SIZE 4 //coordenadas del entity (colisiones)
#define SIZE_TILES 8
#define ENTITY_CHILDREN 4 //num máximo de hijos

class GLEntityNew{

public:

GLEntityNew(){

x_entity = 0.0f;
y_entity = 0.0f;
id_level = 0;

num_tiles = SIZE_TILES;
num_vertices = SIZE_TILES;

tiles = new GLTile *[num_tiles];
child = NULL;

uniqueID = 0;
parentUniqueID = 0;

};

GLEntityNew(int _id_level, float _x_entity, float _y_entity){

x_entity = _x_entity;
y_entity = _y_entity;
id_level = _id_level;

num_tiles = SIZE_TILES;
num_vertices = SIZE_TILES;

tiles = new GLTile *[num_tiles];
child = NULL;

uniqueID = 0;
parentUniqueID = 0;

};

GLEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles){

x_entity = _x_entity;
y_entity = _y_entity;
id_level = _id_level;

num_tiles = _num_tiles;
num_vertices = _num_vertices;

tiles = new GLTile *[num_tiles];
child = NULL;

uniqueID = 0;
parentUniqueID = 0;

child = new GLEntityNew();

};

GLEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, relMovementPol _shape, GLTile *_tiles[]){
num_tiles = _num_tiles;
num_vertices = _num_vertices;

x_entity = _x_entity;
y_entity = _y_entity;
id_level = _id_level;

Vertices = _vertices;
VerticesCpy = _vertices;
VerticesShw = _shape;

tiles = _tiles;
child = NULL;

uniqueID = 0;
parentUniqueID = 0;

child = new GLEntityNew();
};

GLEntityNew(int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, relMovementPol _shape, GLTile *_tiles[], GLEntityNew *_entity){
num_tiles = _num_tiles;
num_vertices = _num_vertices;

x_entity = _x_entity;
y_entity = _y_entity;
id_level = _id_level;

Vertices = _vertices;
VerticesCpy = _vertices;
VerticesShw = _shape;

tiles = _tiles;

uniqueID = 0;
parentUniqueID = 0;

child = _entity;
};


~GLEntityNew(){
};

float getEntityXPos(){return x_entity;}
void setEntityXPos(float _x_entity){x_entity = _x_entity;}

float getEntityYPos(){return y_entity;}
void setEntityYPos(float _y_entity){y_entity = _y_entity;}

int getIdLevel(){return id_level;}
void setIdLevel(int _id_level){id_level = _id_level;}

long getUniqueID(){return uniqueID;}
void setUniqueID(float _uniqueID){uniqueID = _uniqueID;}

long getParentUniqueID(){return parentUniqueID;}
void setParentUniqueID(float _parentUniqueID){parentUniqueID = _parentUniqueID;}

GLTile **getTiles(){return tiles;}
void setTiles(GLTile **tiles_1){tiles = tiles_1;}

int getVerticesSize(){return num_vertices;}
void setVerticesSize(int _num_vertices){num_vertices = _num_vertices;}

int getTileSize(){return num_tiles;}
void setTileSize(int _num_tiles){num_tiles = _num_tiles;}

void setChildEntity(GLEntityNew *children){childs.push_back(children);}
int getChildSize(){return childs.size();}

GLEntityNew *getChildEntity(int index){return childs[index];}

//coordenadas relativas del Entity
void setLimits(relMovementPol _rMPol){Vertices = setRelMovementPol(Vertices,_rMPol);}
relMovementPol getLimits(){return Vertices;}

//coordenados absolutas del Entity
void setCoordShape(relMovementPol _rMPol){VerticesCpy = setRelMovementPol(VerticesCpy,_rMPol);}
relMovementPol getCoordShape(){return VerticesCpy;}

//coordenadas sombreado del Entity
void setShadowShape(relMovementPol _rMPol){VerticesShw = setRelMovementPol(VerticesShw,_rMPol);}
relMovementPol getShadowShape(){return VerticesShw;}

virtual void copyEntity(GLEntityNew *origin){};

protected:

float x_entity;
float y_entity;

int num_tiles;                           //num tiles;
int num_vertices;                        //num vertices;
int id_level;                            //identificador level;

long uniqueID;                           //identificador unico entidad
long parentUniqueID;                     //identificador entidad padre.

GLTile **tiles;                          //define los tiles que están asociados a la imagen

relMovementPol Vertices;                 //definicion de los vertices de un componente. (determina el desplazamiento de un componente)
relMovementPol VerticesCpy;              //limite del elemento
relMovementPol VerticesShw;              //Shadow de un componente

GLEntityNew *child;                      //definición de un hijo de un entity (entities compuestos)
std::vector<GLEntityNew *>childs;

private:

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


#endif // GLENTITYNEW_H_INCLUDED
