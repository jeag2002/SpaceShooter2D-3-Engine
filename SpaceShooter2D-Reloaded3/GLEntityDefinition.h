/*

20151013.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED2

Clase que carga las definiciones de todos los componentes del juego.

Identificación de todos los elementos del juego:

id:                 Identificador de la entidad
entityDesc:         descripcion de la entidad
idImage:            Identificador de la imagen asociada.


typedef std::vector<relMovementPol> textureCoordType;
textureCoordType tCType;                                numero de elementos (texturas) que componen la entidad
map<id,value>:                                          valores a parte (cambian segun el tipo de entidad)

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Se definen cuatro estructuras definitivas:

typedef std::vector<int> NodeType;                                                          //identificador de nodos adjacentes a un nodo (Estructura esqueletal)
typedef std::vector<std::string> ImgType;                                                   //almacen de gestion de imagenes
typedef std::map<std::string, std::pair<std::string,relMovementPol>> TextureCoordType;      //gestion de coordenadas de imagenes (<IDIMAGE,<IDTEXTURA,TEXTCOORDTYPE>>)
                                                                                            //si hay mas de uno, representa animacion.
typedef std::map<std::string, std::string> OtherParametersType;                             //almacen de otros parámetros.
*/

#ifndef GLENTITYDEFINITION_H_INCLUDED
#define GLENTITYDEFINITION_H_INCLUDED

#include "Stdafx.h"

class GLEntityDefinition{

public:

GLEntityDefinition(){
    id = 0;
    entityType = 0;
    entityDesc = "";
    size_tile_x = 0.0;                  //size_tile_x
    size_tile_y = 0.0;                  //size_tile_y

    num_images = 0;
    num_images_ligthmap = 0;
    num_images_bumpmap = 0;

    num_images_str = 0;
    num_images_ligthmap_str = 0;
    num_images_bumpmap_str = 0;

    num_images_ligthmap_str_cmb = 0;
    num_images_bumpmap_str_cmb = 0;
    num_images_mask_str_cmb = 0;

    num_others = 0;
};

GLEntityDefinition(int _id, int _entityType, std::string _entityDesc){
    id = _id;
    entityType = _entityType;
    entityDesc = _entityDesc;
    size_tile_x = 0.0;                  //size_tile_x
    size_tile_y = 0.0;                  //size_tile_y

    num_images = 0;
    num_images_ligthmap = 0;
    num_images_bumpmap = 0;

    num_images_str = 0;
    num_images_ligthmap_str = 0;
    num_images_bumpmap_str = 0;

    num_images_ligthmap_str_cmb = 0;
    num_images_bumpmap_str_cmb = 0;
    num_images_mask_str_cmb = 0;

    num_others = 0;
};

GLEntityDefinition(int _id, int _entityType, float _size_tile_x, float _size_tile_y, std::string _entityDesc){
    id = _id;
    entityType = _entityType;
    entityDesc = _entityDesc;
    size_tile_x = _size_tile_x;                  //size_tile_x
    size_tile_y = _size_tile_y;                  //size_tile_y

    num_images = 0;
    num_images_ligthmap = 0;
    num_images_bumpmap = 0;

    num_images_str = 0;
    num_images_ligthmap_str = 0;
    num_images_bumpmap_str = 0;

    num_images_ligthmap_str_cmb = 0;
    num_images_bumpmap_str_cmb = 0;
    num_images_mask_str_cmb = 0;


    num_others = 0;
};



~GLEntityDefinition(){
    id = 0;
    entityType = 0;
    entityDesc = "";
    size_tile_x = 0.0;                  //size_tile_x
    size_tile_y = 0.0;                  //size_tile_y

    num_images = 0;
    num_images_ligthmap = 0;
    num_images_bumpmap = 0;

    num_images_str = 0;
    num_images_ligthmap_str = 0;
    num_images_bumpmap_str = 0;

    num_images_ligthmap_str_cmb = 0;
    num_images_bumpmap_str_cmb = 0;
    num_images_mask_str_cmb = 0;

    num_others = 0;
};


void setId(int _id){id = _id;}
int getId(){return id;}

void setEntityType(int _entityType){entityType = _entityType;}
int getEntityType(){return entityType;}

void sizeTileX(float _size_tile_x){size_tile_x = _size_tile_x;}
float getSizeTileX(){return size_tile_x;}

void sizeTileY(float _size_tile_y){size_tile_y = _size_tile_y;}
float getSizeTileY(){return size_tile_y;}

void setEntityDesc(std::string _entityDesc){entityDesc = _entityDesc;}
char *getEntityDesc(){return entityDesc.c_str();}

void setNodes(EntityRef _refNodeId){nParameter.push_back(_refNodeId);}
int getSizeNodes(){return nParameter.size();}
EntityRef getNodes(int index){return nParameter[index];}

/////////////////////////////////-IMAGES
void setImage(GLuint _refImageId){
    iParameter.push_back(_refImageId);
    num_images++;
}

GLuint getImage(int idImage){
    return iParameter[idImage];
}

void setImageStr(std::string _refImageIdStr){
    iParameterStr.push_back(_refImageIdStr);
    num_images_str++;
}

std::string getImageStr(int idImage){
    return iParameterStr[idImage];
}
/////////////////////////////////////////

/////////////////////////////////////////-IMAGES LIGTHMAP
void setImageLightmap(GLuint _refImageId){
    ilParameter.push_back(_refImageId);
    num_images_ligthmap++;
}

GLuint getImageLightmap(int idImage){
    return ilParameter[idImage];
}

void setImageLightmapStr(std::string _refImageIdStr){
    ilParameterStr.push_back(_refImageIdStr);
    num_images_ligthmap_str++;
}

std::string getImageLightmapStr(int idImage){
    return ilParameterStr[idImage];
}

void setImageLightmapCmb(std::string _refImageIdCmb){
    ilParameterStrCmb.push_back(_refImageIdCmb);
    num_images_ligthmap_str_cmb++;
}

std::string getImageLightmapCmb(int idImage){
    return ilParameterStrCmb[idImage];
}
/////////////////////////////////////////

/////////////////////////////////////////-IMAGES BUMPMAP
void setImageBumpmap(GLuint _refImageId){
    ibParameter.push_back(_refImageId);
    num_images_bumpmap++;
}

GLuint getImageBumpmap(int idImage){
    return ibParameter[idImage];
}

void setImageBumpmapStr(std::string _refImageIdStr){
    ibParameterStr.push_back(_refImageIdStr);
    num_images_bumpmap_str++;
}

std::string getImageBumpmapStr(int idImage){
    return ibParameterStr[idImage];
}

void setImageBumpmapCmb(std::string _refImageIdCmb){
    ibParameterStrCmb.push_back(_refImageIdCmb);
    num_images_bumpmap_str_cmb++;
}

std::string getImageBumpmapCmb(int idImage){
    return ibParameterStrCmb[idImage];
}

/////////////////////////////////////////

/////////////////////////////////////////-IMAGES MASK
void setImageMask(GLuint _refImageId){
    imParameter.push_back(_refImageId);
    num_images_mask++;
}

GLuint getImageMask(int idImage){
    return imParameter[idImage];
}

void setImageMaskStr(std::string _refImageIdStr){
    imParameterStr.push_back(_refImageIdStr);
    num_images_mask_str++;
}

std::string getImageMaskStr(int idImage){
    return imParameterStr[idImage];
}

void setImageMaskCmb(std::string _refImageIdCmb){
    imParameterStrCmb.push_back(_refImageIdCmb);
    num_images_mask_str_cmb++;
}

std::string getImageMaskCmb(int idImage){
    return imParameterStrCmb[idImage];
}

/////////////////////////////////////////




void setOtherParams(std::string key, const char *value){
    std::pair<std::string, const char *> node(key, value);
    oParameter.insert(node);
    num_others++;
};

const char *getOtherParam(std::string key){
    OtherParametersType::iterator it;
    it = oParameter.find(key);
    const char *value = " ";

    if (it != oParameter.end()){
        return it->second;
    }else{
        return value;
    }

}

void setCoordTextures(GLuint key, relMovementPol rPol){

   TextureCoordType::iterator it;
   textCoordVectType tCoordVectType;
   it = tParameter.find(key);

   if (it!=tParameter.end()){
       tCoordVectType = it->second;
       tCoordVectType.push_back(rPol);
       tParameter[key] = tCoordVectType;
   }else{
       tCoordVectType.push_back(rPol);
       std::pair<GLuint, textCoordVectType> coordData(key,tCoordVectType);
       tParameter.insert(coordData);
   }


   //std::pair<GLuint, textCoordVectType> coordData(key,tCoordVectType);
   //tParameter.insert(coordData);


}

int getCoordTextureSize(GLuint key){

    TextureCoordType::iterator it;
    it = tParameter.find(key);

    if (it!=tParameter.end()){
        return it->second.size();
    }else{
        return -1;
    }
};


relMovementPol getCoordTexture(GLuint key, int index){

    TextureCoordType::iterator it;
    relMovementPol data0;
    data0.num_nodes = 0;
    textCoordVectType tCoordVectType;
    it = tParameter.find(key);
    if (it!=tParameter.end()){
        tCoordVectType = it->second;
        if (index < tCoordVectType.size()){
            return tCoordVectType[index];
        }else{
            return data0;
        }
    }else{
        return data0;
    }
}

//posCoordTileParameter

void setCoordTileParameter(relMovement rM){
    posCoordTileParameter.push_back(rM);
}

int getCoordTileParameterSize(){
    return posCoordTileParameter.size();
}

relMovement getCoordTileParameter(int index){
    return posCoordTileParameter[index];
}

int getNumImages(){return num_images;};
int getNumOthers(){return num_others;};


private:

int id;                             //id del entity
int entityType;                     //tipo de entidad. PAS->PASIVO, PLAY->PLAYER, ENEM->ENEMY, PORT->PORTAL
std::string entityDesc;             //descripcion de la entidad.

float size_tile_x;                  //size_tile_x
float size_tile_y;                  //size_tile_y


typedef std::vector<EntityRef> NodeType;                                                    //identificador de nodos adjacentes a un nodo (Estructura esqueletal)
typedef std::vector<GLuint> ImgType;                                                        //almacen de gestion de imagenes
typedef std::vector<std::string> ImgStrType;                                                //almacen de gestion etiquetas de imagenes.
typedef std::vector<relMovementPol> textCoordVectType;                                      //vectores de textures.
typedef std::map<GLuint, textCoordVectType> TextureCoordType;                               //gestion de coordenadas de imagenes (<IDIMAGE,<IDTEXTURA,TEXTCOORDTYPE>>)
                                                                                            //si hay mas de uno, representa animacion.
typedef std::map<std::string, const char *> OtherParametersType;                             //almacen de otros parámetros.

typedef std::vector<relMovement> TextPosTileType;                                           //posiciones relativas de los tiles dentro de la entidad.


int num_images;
int num_images_ligthmap;
int num_images_bumpmap;
int num_images_mask;

int num_images_str;
int num_images_ligthmap_str;
int num_images_bumpmap_str;
int num_images_mask_str;

int num_images_ligthmap_str_cmb;
int num_images_bumpmap_str_cmb;
int num_images_mask_str_cmb;

int num_others;

NodeType nParameter;
OtherParametersType oParameter;
TextureCoordType tParameter;
TextPosTileType posCoordTileParameter;

ImgType iParameter;
ImgType ilParameter;
ImgType ibParameter;
ImgType imParameter;

ImgStrType iParameterStr;
ImgStrType ilParameterStr;
ImgStrType ibParameterStr;
ImgStrType imParameterStr;

ImgStrType ilParameterStrCmb;
ImgStrType ibParameterStrCmb;
ImgStrType imParameterStrCmb;

};

#endif // GLENTITYDEFINITION_H_INCLUDED
