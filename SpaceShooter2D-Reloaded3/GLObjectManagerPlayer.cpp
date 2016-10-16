#include "GLObjectManagerPlayer.h"

/*

#define LIVE "LIVE"
#define SHIELD "SHIELD"
#define FIRE "FIRE"
#define INC "INC"
#define LIMITS "LIMITS"

#define IA_SCRIPT "IA_SCRIPT"
#define COLL_SCRIPT "COLL_SCRIPT"
#define ANIM_SCRIPT "ANIM_SCRIPT"

*/


GLEntityNew *GLObjectManagerPlayer::processElementDef(GLEntityDefinition *dataTile, float x, float y, float level, int orientation){

    GLDynamicEntityNew *glPlayer;
    GLDynamicEntityNew *entity;

    GLTile **tiles = processTilesDef(dataTile,x,y,level);
    DEBUGLOGPONE("[ENTITY-PLAYER] GLObjectManagerPlayer::processElementDef --> %s",dataTile->getEntityDesc());
    DEBUGLOGPONE("[ENTITY-PLAYER] GLObjectManagerPlayer::processElementDef --> (LIMITS)[%s]",dataTile->getOtherParam("LIMITS"));
    DEBUGLOGPONE("[ENTITY-PLAYER] GLObjectManagerPlayer::processElementDef --> (SHAPE)[%s]",dataTile->getOtherParam("SHAPE"));
    DEBUGLOGPONE("[ENTITY-PLAYER] GLObjectManagerPlayer::processElementDef --> x:%f",dataTile->getSizeTileX());
    DEBUGLOGPONE("[ENTITY-PLAYER] GLObjectManagerPlayer::processElementDef --> y:%f",dataTile->getSizeTileY());

    relMovementPol limits = processLimits(dataTile->getOtherParam(LIMITS));
    relMovementPol shape = processLimits(dataTile->getOtherParam(SHAPE));


    std::string live_str = dataTile->getOtherParam(LIVE);
    int live_int = atoi(live_str.c_str());

    std::string shield_str = dataTile->getOtherParam(SHIELD);
    int shield_int = atoi(shield_str.c_str());

    std::string fire_str = dataTile->getOtherParam(FIRE);
    int fire_int = atoi(fire_str.c_str());

    std::string inc_str = dataTile->getOtherParam(INC);
    int inc_int = atoi(inc_str.c_str());

    std::string orientation_str = dataTile->getOtherParam(ORIENTATION);
    int orientation_int = orientation;

    std::string ai_script_id = dataTile->getOtherParam(IA_SCRIPT);
    std::string coll_script_id = dataTile->getOtherParam(COLL_SCRIPT);
    std::string anim_script_id = dataTile->getOtherParam(ANIM_SCRIPT);

    //int _id_level, float _x_entity, float _y_entity, int _num_vertices, int _num_tiles, relMovementPol _vertices, GLTile *_tiles[]

    glPlayer = new GLDynamicEntityNew((int)level, x, y, limits.num_nodes, dataTile->getNumImages(), limits, shape ,tiles);

    if (dataTile->getSizeNodes() == 0){
        entity = new GLDynamicEntityNew();
    }else if (dataTile->getSizeNodes() > 0){

        for(int i=0; i<dataTile->getSizeNodes(); i++){

            EntityRef eRef = dataTile->getNodes(i);
            GLEntityDefinition *nodeData = gMem->getEntityDefinition(eRef.idEntity);

            if (nodeData != NULL){
                entity = processElementDef(nodeData,eRef.x_diff_pos+x, eRef.y_diff_pos+y, level,orientation_int);
                glPlayer->setChildEntity(entity);
            }else{
                WARNLOGPONE("GLObjectManagerPlayer::processElementDef --> REFERENCIA ENTIDAD (%04d) NO ENCONTRADA",eRef.idEntity);
            }
        }
    }




    glPlayer->setLive(live_int);
    glPlayer->setShield(shield_int);
    glPlayer->setFire(fire_int);
    glPlayer->setInc(inc_int);
    glPlayer->setOrientation(orientation);
    glPlayer->setUniqueID(Utils::generateUIDDSinistar(0));
    glPlayer->setParentUniqueID(Utils::generateUIDDSinistar(0));

    glPlayer->setANIM_SCRIPT(ai_script_id.c_str());
    glPlayer->setCOLL_SCRIPT(coll_script_id.c_str());
    glPlayer->setANIM_SCRIPT(anim_script_id.c_str());

    return glPlayer;
}

relMovementPol GLObjectManagerPlayer::processLimits(std::string limits){

    relMovementPol coordTexXY;
    coordTexXY.num_nodes = 0;
    coordTexXY.coll = 0;

    relMovement texXY;

    char *ptr = NULL;

    ptr = strtok(limits.c_str(),DELIMITER_COORD_GP);

    int contador = 0;

    while(ptr != NULL){
        if (contador==0){
           texXY.rel_pos_x = atof(ptr);
           contador += 1;
        }else if (contador==1){
           texXY.rel_pos_y = atof(ptr);
           coordTexXY.nodes[coordTexXY.num_nodes] = texXY;
           coordTexXY.num_nodes += 1;
           contador = 0;
        }
         ptr = strtok(NULL,DELIMITER_COORD_GP);

    }

    return coordTexXY;
}

GLTile **GLObjectManagerPlayer::processTilesDef(GLEntityDefinition *dataTile, float x, float y, float level){

  float xAbsPos = x * dataTile->getSizeTileX();
  float yAbsPos = y * dataTile->getSizeTileY();

  GLuint gIDImage = 0;
  GLuint gIDImageLM = 0;
  GLuint gIDImageBM = 0;
  GLuint gIDImageMK = 0;

  relMovementPol textures;
  textures.num_nodes = 0;

  int numImages = dataTile->getNumImages();
  GLTile **tiles = new GLTile *[numImages];

  for(int i=0; i<numImages; i++){

      gIDImage = dataTile->getImage(i);
      gIDImageLM = dataTile->getImageLightmap(i);
      gIDImageBM = dataTile->getImageBumpmap(i);
      gIDImageMK = dataTile->getImageMask(i);

      relMovement rM = dataTile->getCoordTileParameter(i);

      tiles[i] = new GLTile(x+rM.rel_pos_x,y+rM.rel_pos_y,dataTile->getSizeTileX(),dataTile->getSizeTileY(),dataTile->getId(),gIDImage,gIDImageLM,gIDImageBM,gIDImageMK);

      int num_coordinades = dataTile->getCoordTextureSize(gIDImage);

      for(int j=0; j<num_coordinades; j++){
          tiles[i]->setTextures(dataTile->getCoordTexture(gIDImage,j));
      }
  }

  return tiles;
}
