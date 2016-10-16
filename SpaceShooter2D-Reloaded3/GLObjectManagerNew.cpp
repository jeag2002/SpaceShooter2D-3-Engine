#include "GLObjectManagerNew.h"


void GLObjectManagerNew::processTileDef(int idEntityDef, float x, float y, float level){

       if (idEntityDef != 0){
           data = gMem->getEntityDefinition(idEntityDef);

           if(data != NULL){
                _tile = tileParser->processTileDef(data, x, y, level);
                //DEBUGLOGPFOUR("GLObjectManagerNew::processTileDef -> TILE (%04.2f,%04.2f,%04.2f) == %02d",level,x,y,_tile->getTypeIdTile());
                gMem->setStaticTileLevel(level, x, y, *_tile);
           }else{
                WARNLOGPONE("GLObjectManagerNew::processTileDef --> TILE DEF NO ENCONTRADO ID::(%04d)",idEntityDef);
           }
       }else{
           //insertar tile -null.
           _tile = new GLTile();
           gMem->setStaticTileLevel(level, x, y, *_tile);
       }
}


void GLObjectManagerNew::processDynamicDef(int idEntityDef, float x, float y, float level){

    if (idEntityDef != 0){
        data = gMem->getEntityDefinition(idEntityDef);

        if (data != NULL){

                if (data->getEntityType() == ENTITY_TYPE_ACTOR){
                    _entity = enemyParser->processElementDef(data, x, y, level);
                    //DEBUGLOGPFOUR("GLObjectManagerNew::processDynamicDef -> ENEMY_ENTITY (%04.2f,%04.2f,%04.2f) == %02d",level,x,y,data->getEntityType());
                    //gMem->setDinamicElementLevel(level, x, y, *_entity, ENTITY_TYPE_ENEM);
                }
        }else{
            WARNLOGPONE("GLObjectManagerNew::processTileDef --> ENTITY DEF NO ENCONTRADO ID::(%04d)",idEntityDef);
        }
    }
}

void GLObjectManagerNew::processPlayerDef(int idEntityDef, int numPlayer, float x, float y, int level, int orientation){

    if (idEntityDef != 0){
        data = gMem->getEntityDefinition(idEntityDef);
        if (data != NULL){
            DEBUGLOGPFIVE("GLObjectManagerNew::processPlayerDef --> PLAYER %d [ID %d] x:%f y:%f level:%f",numPlayer,idEntityDef,x,y,level);
            _entity = playerParser->processElementDef(data,x,y,level,orientation);
            gMem->setPlayer(numPlayer,_entity);
        }else{
            WARNLOGPONE("GLObjectManagerNew::processPlayerDef --> PLAYER DEF NO ENCONTRADO ID::(%04d)",idEntityDef);
        }
    }
}



