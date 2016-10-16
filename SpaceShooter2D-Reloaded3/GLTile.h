#ifndef GLTILE_H_INCLUDED
#define GLTILE_H_INCLUDED

#include "GlobalNew.h"
#include <string>
#include <vector>

#define SIZE_TILE 4

class GLTile{

public:

    GLTile(){
        x = 0.0f;
        y = 0.0f;
        width_x = 64.0f;
        width_y = 64.0f;
        typeIdTile = 0;
        GLIDImage = 0;
        GLIDImageLightMap = 0;
        GLIDImageBumpMap = 0;
        GLIDImageMK = 0;

        TexturesCoord.clear();
        VerticesCoord.clear();

    };

    GLTile(float _x, float _y, float _width_x, float _width_y, int _typeIdTile, unsigned int _GLIDImage,
           unsigned int _GLIDImageLightMap,
           unsigned int _GLIDImageBumpMap,
           unsigned int _GLIDImageMask){
        x = _x;
        y = _y;
        width_x = _width_x;
        width_y = _width_y;
        typeIdTile = _typeIdTile;
        GLIDImage = _GLIDImage;
        GLIDImageLightMap = _GLIDImageLightMap;
        GLIDImageBumpMap = _GLIDImageBumpMap;
        GLIDImageMK = _GLIDImageMask;

        TexturesCoord.clear();
        VerticesCoord.clear();

    };

    GLTile(GLTile *data){
        x= data->getX();
        y= data->getY();
        width_x = data->getWidthX();
        width_y = data->getWidthY();
        typeIdTile = data->getTypeIdTile();
        GLIDImage = data->getGLIDImage();
        GLIDImageLightMap = data->getGLIDImageLight();
        GLIDImageBumpMap = data->getGLIDImageBumpMap();
        GLIDImageMK = data->getGLIDImageMK();
        TexturesCoord = data->getTextureArray();
        VerticesCoord = data->getVerticesArray();

    };

    float getX(){return x;}
    float getY(){return y;}
    float getWidthX(){return width_x;}
    float getWidthY(){return width_y;}
    int getTypeIdTile(){return typeIdTile;}
    unsigned int getGLIDImage(){return GLIDImage;}
    unsigned int getGLIDImageLight(){return GLIDImageLightMap;}
    unsigned int getGLIDImageBumpMap(){return GLIDImageBumpMap;}
    unsigned int getGLIDImageMK(){return GLIDImageMK;}

    void copyGLTile(GLTile *data){

        x= data->getX();
        y= data->getY();
        width_x = data->getWidthX();
        width_y = data->getWidthY();
        typeIdTile = data->getTypeIdTile();
        GLIDImage = data->getGLIDImage();
        GLIDImageLightMap = data->getGLIDImageLight();
        GLIDImageBumpMap = data->getGLIDImageBumpMap();
        GLIDImageMK = data->getGLIDImageMK();
        TexturesCoord = data->getTextureArray();
        VerticesCoord = data->getVerticesArray();

    }


    ~GLTile(){
        x = 0.0f;
        y = 0.0f;
        width_x = 64.0f;
        width_y = 64.0f;
        typeIdTile = 0;
        GLIDImage = 0;
        GLIDImageLightMap = 0;
        GLIDImageBumpMap = 0;

        TexturesCoord.clear();
        VerticesCoord.clear();
    }


    void setTextures(relMovementPol _Textures){TexturesCoord.push_back(_Textures);}
    int TexturesSize(){return TexturesCoord.size();}
    relMovementPol getTextures(int index){return TexturesCoord[index];}
    std::vector<relMovementPol> getTextureArray(){return TexturesCoord;}

    void setVertices(relMovementPol _Vertices){VerticesCoord.push_back(_Vertices);}
    int VerticesSize(){return VerticesCoord.size();}
    relMovementPol getVertices(int index){return VerticesCoord[index];}
    std::vector<relMovementPol> getVerticesArray(){return VerticesCoord;}

private:

    float x;                            //Posicion  absoluta tile X
    float y;                            //Posicion  absoluta tile Y

    float width_x;                      //Tamanyo X de un tile
    float width_y;                      //tamanyo Y de un tile

    int typeIdTile;                     //Identificador del tipo de tile
    std::string GLIDImageStr;           //Identificador de la imagen

    int GLIDImage;                      //identificador de la imagen asociada al tile
    int GLIDImageLightMap;              //identificador del ligth map de la tile
    int GLIDImageBumpMap;               //identificador del bump map de la tile
    int GLIDImageMK;                    //identificador del mask de la tile

    std::vector<relMovementPol> TexturesCoord;
    std::vector<relMovementPol> VerticesCoord;

    //relMovement Vertices[SIZE_TILE];    //identificador de los vertices asociados a un tile.
    //relMovement Texturas[SIZE_TILE];    //identificador de las coordenadas de texturas asociadas a un tile.


};

#endif // GLTILE_H_INCLUDED
