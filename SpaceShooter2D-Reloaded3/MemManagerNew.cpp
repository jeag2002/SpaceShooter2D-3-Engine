#include "MemManagerNew.h"

void MemManagerNew::createLevels(int x, int y, int levels){



    if (levels == 1){

        this->level_1_static = new GLTile *[y];
        for (int i = 0; i< y; i++){
            this->level_1_static[i] = new GLTile[x];
        }

        /*
        //Dynamic Elements
        this->level_1_dinamic = new GLTile*[y];
        for (int i = 0; i< y; i++){
            this->level_1_dinamic[i] = new GLTile[x];
        }*/
    }

    if (levels <= 2){

        this->level_2_static = new GLTile *[y];
        for (int i = 0; i< y; i++){
            this->level_2_static[i] = new GLTile[x];
        }

        /*
        //Dynamic Elements
        this->level_2_dinamic = new GLTile*[y];
        for (int i = 0; i< y; i++){
            this->level_2_dinamic[i] = new GLTile[x];
        }*/
    }

    if (levels <= 3){

        this->level_3_static = new GLTile *[y];
        for (int i = 0; i< y; i++){
            this->level_3_static[i] = new GLTile[x];
        }

        /*
        //Dynamic Elements
        this->level_3_dinamic = new GLTile*[y];
        for (int i = 0; i< y; i++){
            this->level_3_dinamic[i] = new GLTile[x];
        }*/
    }

    if (levels <= SIZEOFLEVELS){

        this->level_4_static = new GLTile *[y];
        for (int i = 0; i< y; i++){
            this->level_4_static[i] = new GLTile[x];
        }

        /*
        //Dynamic Elements
        this->level_4_dinamic = new GLTile*[y];
        for (int i = 0; i< y; i++){
            this->level_4_dinamic[i] = new GLTile[x];
        }*/
    }
}


void MemManagerNew::setStaticTileLevel(int level, int x, int y, GLTile data){

    if (level == 0){
        this->level_1_static[x][y] = data;
    }else if (level == 1){
        this->level_2_static[x][y] = data;
    }else if (level == 2){
        this->level_3_static[x][y] = data;
    }else if (level == 3){
        this->level_4_static[x][y] = data;
    }
}


GLTile MemManagerNew::getStaticTileLevel(int level, int x, int y){
    if (level == 0){
        return this->level_1_static[x][y];
    }else if (level == 1){
        return this->level_2_static[x][y];
    }else if (level == 2){
        return this->level_3_static[x][y];
    }else if (level == 3){
        return this->level_4_static[x][y];
    }else{
        GLTile *tile = new GLTile();
        return  tile;
    }
}


std::vector<GLCollision *> MemManagerNew::getCollisionStaticMap(int level, int orientation){

     if (level == 0){

        if (orientation == MEM_UP){
            return this->coll_1_Up;
        }else if (orientation == MEM_DOWN){
            return this->coll_1_Down;
        }else if (orientation == MEM_LEFT){
            return this->coll_1_Left;
        }else if (orientation == MEM_RIGHT){
            return this->coll_1_Right;
        }

    }else if (level == 1){

        if (orientation == MEM_UP){
            return this->coll_2_Up;
        }else if (orientation == MEM_DOWN){
            return this->coll_2_Down;
        }else if (orientation == MEM_LEFT){
            return this->coll_2_Left;
        }else if (orientation == MEM_RIGHT){
            return this->coll_2_Right;
        }

    }else if (level == 2){

        if (orientation == MEM_UP){
            return this->coll_3_Up;
        }else if (orientation == MEM_DOWN){
            return this->coll_3_Down;
        }else if (orientation == MEM_LEFT){
            return this->coll_3_Left;
        }else if (orientation == MEM_RIGHT){
            return this->coll_3_Right;
        }

    }else if (level == 3){

        if (orientation == MEM_UP){
            return this->coll_4_Up;
        }else if (orientation == MEM_DOWN){
            return this->coll_4_Down;
        }else if (orientation == MEM_LEFT){
            return this->coll_4_Left;
        }else if (orientation == MEM_RIGHT){
            return this->coll_4_Right;
        }
    }
}


void MemManagerNew::setCollisionStaticMapData(int level, int orientation, int index, GLCollision *coll){
    if (level == 0){
        if (orientation == MEM_UP){
            this->coll_1_Up[index] = coll;
        }else if (orientation == MEM_DOWN){
            this->coll_1_Down[index] = coll;
        }else if (orientation == MEM_LEFT){
            this->coll_1_Left[index]= coll;
        }else if (orientation == MEM_RIGHT){
            this->coll_1_Right[index] = coll;
        }
    }else if (level == 1){
        if (orientation == MEM_UP){
            this->coll_2_Up[index] = coll;
        }else if (orientation == MEM_DOWN){
            this->coll_2_Down[index] = coll;
        }else if (orientation == MEM_LEFT){
            this->coll_2_Left[index] = coll;
        }else if (orientation == MEM_RIGHT){
            this->coll_2_Right[index] = coll;
        }
    }else if (level == 2){

        if (orientation == MEM_UP){
            this->coll_3_Up[index] = coll;
        }else if (orientation == MEM_DOWN){
            this->coll_3_Down[index] = coll;
        }else if (orientation == MEM_LEFT){
            this->coll_3_Left[index] = coll;
        }else if (orientation == MEM_RIGHT){
            this->coll_3_Right[index] = coll;
        }
    }else if (level == 3){

        if (orientation == MEM_UP){
            this->coll_4_Up[index] = coll;
        }else if (orientation == MEM_DOWN){
            this->coll_4_Down[index] = coll;
        }else if (orientation == MEM_LEFT){
            this->coll_4_Left[index] = coll;
        }else if (orientation == MEM_RIGHT){
            this->coll_4_Right[index] = coll;
        }
    }
}


void MemManagerNew::setCollisionStaticMap(int level, int orientation, GLCollision *coll){
    if (level == 0){
        if (orientation == MEM_UP){
            this->coll_1_Up.push_back(coll);
        }else if (orientation == MEM_DOWN){
            this->coll_1_Down.push_back(coll);
        }else if (orientation == MEM_LEFT){
            this->coll_1_Left.push_back(coll);
        }else if (orientation == MEM_RIGHT){
            this->coll_1_Right.push_back(coll);
        }
    }else if (level == 1){
        if (orientation == MEM_UP){
            this->coll_2_Up.push_back(coll);
        }else if (orientation == MEM_DOWN){
            this->coll_2_Down.push_back(coll);
        }else if (orientation == MEM_LEFT){
            this->coll_2_Left.push_back(coll);
        }else if (orientation == MEM_RIGHT){
            this->coll_2_Right.push_back(coll);
        }
    }else if (level == 2){

        if (orientation == MEM_UP){
            this->coll_3_Up.push_back(coll);
        }else if (orientation == MEM_DOWN){
            this->coll_3_Down.push_back(coll);
        }else if (orientation == MEM_LEFT){
            this->coll_3_Left.push_back(coll);
        }else if (orientation == MEM_RIGHT){
            this->coll_3_Right.push_back(coll);
        }
    }else if (level == 3){

        if (orientation == MEM_UP){
            this->coll_4_Up.push_back(coll);
        }else if (orientation == MEM_DOWN){
            this->coll_4_Down.push_back(coll);
        }else if (orientation == MEM_LEFT){
            this->coll_4_Left.push_back(coll);
        }else if (orientation == MEM_RIGHT){
            this->coll_4_Right.push_back(coll);
        }
    }
}



//primera version con GTILES. Version Definitiva con GLEntityNew; GLDynamicEntityNew
void MemManagerNew::setDinamicElementLevel(int level, int x, int y, GLEntityNew data, int typeEntity){

    if (level == 0){
            if (typeEntity == ENTITY_TYPE_ACTOR){
                level_1_enemies.push_back(&data);
            }else if ((typeEntity == ENTITY_TYPE_LIGHT) || (typeEntity == ENTITY_TYPE_PART)){
                level_1_dinamic.push_back(&data);
            }else{
                level_1_EStatic.push_back(&data);
            }
    }else if (level == 1){
            if (typeEntity == ENTITY_TYPE_ACTOR){
                level_2_enemies.push_back(&data);
            }else if ((typeEntity == ENTITY_TYPE_LIGHT) || (typeEntity == ENTITY_TYPE_PART)){
                level_2_dinamic.push_back(&data);
            }else{
                level_2_EStatic.push_back(&data);
            }
    }else if (level == 2){
            if (typeEntity == ENTITY_TYPE_ACTOR){
                level_3_enemies.push_back(&data);
            }else if ((typeEntity == ENTITY_TYPE_LIGHT) || (typeEntity == ENTITY_TYPE_PART)){
                level_3_dinamic.push_back(&data);
            }else{
                level_3_EStatic.push_back(&data);
            }

    }else if (level == 3){
            if (typeEntity == ENTITY_TYPE_ACTOR){
                level_4_enemies.push_back(&data);
            }else if ((typeEntity == ENTITY_TYPE_LIGHT) || (typeEntity == ENTITY_TYPE_PART)){
                level_4_dinamic.push_back(&data);
            }else{
                level_4_EStatic.push_back(&data);
            }
    }else{}


    /*
    if (level == 0){
        this->level_1_dinamic[x][y] = data;
    }else if (level == 1){
        this->level_2_dinamic[x][y] = data;
    }else if (level == 2){
        this->level_3_dinamic[x][y] = data;
    }else if (level == 3){
        this->level_4_dinamic[x][y] = data;
    }
    */
}





void MemManagerNew::setDataCollitionLevel(int level, GLCollision *data){
    if (level == 0){
        this->coll_1.push_back(data);
    }else if (level == 1){
        this->coll_2.push_back(data);
    }else if (level == 2){
        this->coll_3.push_back(data);
    }else if (level == 3){
        this->coll_4.push_back(data);
    }
}

void MemManagerNew::setDataLightLevel(int level, GLCollision *data){
    if (level == 0){
        this->light_1.push_back(data);
    }else if (level == 1){
        this->light_2.push_back(data);
    }else if (level == 2){
        this->light_3.push_back(data);
    }else if (level == 3){
        this->light_4.push_back(data);
    }
}


std::vector<GLEntityNew *>MemManagerNew::getEnemiesByLevel(int level){
    if (level == 0){
        return  level_1_enemies;
    }else if (level == 1){
        return  level_2_enemies;
    }else if (level == 2){
        return  level_3_enemies;
    }else if (level == 3){
        return  level_4_enemies;
    }
}
std::vector<GLEntityNew *>MemManagerNew::getDynamicEntitiesByLevel(int level){
    if (level == 0){
        return  level_1_dinamic;
    }else if (level == 1){
        return  level_2_dinamic;
    }else if (level == 2){
        return  level_3_dinamic;
    }else if (level == 3){
        return  level_4_dinamic;
    }
}
std::vector<GLEntityNew *>MemManagerNew::getStaticEntitiesByLevel(int level){
    if (level == 0){
        return level_1_EStatic;
    }else if (level == 1){
        return level_2_EStatic;
    }else if (level == 2){
        return level_3_EStatic;
    }else if (level == 3){
        return level_4_EStatic;
    }

}

std::vector<GLCollision *>MemManagerNew::getCollisionByLevel(int level){
    if (level == 0){
        return coll_1;
    }else if (level == 1){
        return coll_2;
    }else if (level == 2){
        return coll_3;
    }else if (level == 3){
        return coll_4;
    }
}


void MemManagerNew::deleteLevels(int x, int y, int levels){

    if (levels == 1){

        for (int i = 0; i < y; ++i){
            delete [] level_1_static[i];
        }
        delete [] level_1_static;

        level_1_EStatic.clear();
        level_1_dinamic.clear();
        level_1_enemies.clear();

        /*
        for (int i = 0; i < y; ++i){
            delete [] level_1_dinamic[i];
        }
        delete [] level_1_dinamic;
        */

    }

    if (levels <= 2){

        for (int i = 0; i < y; ++i){
            delete [] level_2_static[i];
        }
        delete [] level_2_static;

        level_2_EStatic.clear();
        level_2_dinamic.clear();
        level_2_enemies.clear();

        /*
        for (int i = 0; i < y; ++i){
            delete [] level_2_dinamic[i];
        }
        delete [] level_2_dinamic;
        */
    }

    if (levels <= 3){

        for (int i = 0; i < y; ++i){
            delete [] level_3_static[i];
        }
        delete [] level_3_static;

        level_3_EStatic.clear();
        level_3_dinamic.clear();
        level_3_enemies.clear();

        /*
        for (int i = 0; i < y; ++i){
            delete [] level_3_dinamic[i];
        }
        delete [] level_3_dinamic;
        */
    }

    if (levels <= SIZEOFLEVELS){

        for (int i = 0; i < y; ++i){
            delete [] level_4_static[i];
        }
        delete [] level_4_static;

        level_4_EStatic.clear();
        level_4_dinamic.clear();
        level_4_enemies.clear();

        /*
        for (int i = 0; i < y; ++i){
            delete [] level_4_dinamic[i];
        }
        delete [] level_4_dinamic;
        */
    }

    coll_1.clear();
    coll_1_Up.clear();
    coll_1_Down.clear();
    coll_1_Left.clear();
    coll_1_Right.clear();
    light_1.clear();

    coll_2.clear();
    coll_2_Up.clear();
    coll_2_Down.clear();
    coll_2_Left.clear();
    coll_2_Right.clear();
    light_2.clear();

    coll_3.clear();
    coll_3_Up.clear();
    coll_3_Down.clear();
    coll_3_Left.clear();
    coll_3_Right.clear();
    light_3.clear();

    coll_4.clear();
    coll_4_Up.clear();
    coll_4_Down.clear();
    coll_4_Left.clear();
    coll_4_Right.clear();
    light_4.clear();

    rol_1.clear();

    gLog->info("MemManagerNew::deleteLevels --> LEVEL DATA DELETED");
}

void MemManagerNew::setPlayer(int level, GLDynamicEntityNew *player){

    if (level == 0){
        if (this->player_1 == NULL){
            this->player_1 = new GLDynamicEntityNew();
        }
        this->player_1->copyEntity(player);
        gLog->info("MemManagerNew::setPlayer --> player 1");
    }else if (level == 1){
        if (this->player_2 == NULL){
                this->player_2 = new GLDynamicEntityNew();
        }
        this->player_2->copyEntity(player);
        gLog->info("MemManagerNew::setPlayer --> player 2");
    }else if (level == 2){
        if (this->player_3 == NULL){
                this->player_3 = new GLDynamicEntityNew();
        }
        this->player_3->copyEntity(player);
        gLog->info("MemManagerNew::setPlayer --> player 3");
    }else if (level == 3){
        if (this->player_4 == NULL){
                this->player_4 = new GLDynamicEntityNew();
        }
        this->player_4->copyEntity(player);
        gLog->info("MemManagerNew::setPlayer --> player 4");
    }
}

void MemManagerNew::deletePlayers(){
    if (this->player_1 != NULL){delete this->player_1;}
    if (this->player_2 != NULL){delete this->player_2;}
    if (this->player_3 != NULL){delete this->player_3;}
    if (this->player_4 != NULL){delete this->player_4;}

    gLog->info("MemManagerNew::deletePlayers --> PLAYERS DELETED");
}

GLDynamicEntityNew *MemManagerNew::getPlayer(int level){

    if (level == 0){
        return this->player_1;
    }else if (level == 1){
        return this->player_2;
    }else if (level == 2){
        return this->player_3;
    }else if (level == 3){
        return this->player_4;
    }
}
