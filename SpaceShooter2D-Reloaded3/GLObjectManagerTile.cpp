#include "GLObjectManagerTile.h"

//Proceso de un elemento estático TILE.
GLTile *GLObjectManagerTile::processTileDef(GLEntityDefinition *dataTile, float x, float y, float level){

  float xAbsPos = x * dataTile->getSizeTileX();
  float yAbsPos = y * dataTile->getSizeTileY();

  int sizeCoordText = 0;
  GLuint gIDImage = 0;
  GLuint gIDImageLM = 0;
  GLuint gIDImageBM = 0;
  GLuint gIDImageMK = 0;

  relMovementPol textures;
  textures.num_nodes = 0;
  relMovement rM;

  rM.rel_pos_x = 0.0f;
  rM.rel_pos_y = 0.0f;

  //numero de imagenes de tiles.
  if (dataTile->getNumImages() > 0){
    int index = dataTile->getNumImages()-1;
    gIDImage = dataTile->getImage(index);
    gIDImageLM = dataTile->getImageLightmap(index);
    gIDImageBM = dataTile->getImageBumpmap(index);
    gIDImageMK = dataTile->getImageMask(index);

    sizeCoordText = dataTile->getCoordTextureSize(gIDImage);
    rM = dataTile->getCoordTileParameter(index);

    if (sizeCoordText > 0){
        textures = dataTile->getCoordTexture(gIDImage,sizeCoordText-1);
    }
  }

  _tile = new GLTile(
        xAbsPos + rM.rel_pos_x,
        yAbsPos + rM.rel_pos_y,
        dataTile->getSizeTileX(),
        dataTile->getSizeTileY(),
        dataTile->getId(),
        gIDImage,
        gIDImageLM,
        gIDImageBM,
        gIDImageMK);
  _tile->setTextures(textures);
  return _tile;
}
