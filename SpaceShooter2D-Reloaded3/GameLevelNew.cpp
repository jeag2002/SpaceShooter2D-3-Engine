#include "GameLevelNew.h"

/*

size_mundo_x size_mundo_y size_tile_x size_tile_y

ID_GLOBAL_IA ID_GLOBAL_COLL

num_levels

#level_0

xx -> imagen background

#level_1

#componente estático level_1
1.....
.
.
.

#Collisions level_1

#componente dinámico level_1
x.....
.
.
.


#level_2

#componente estático level_2
1.....
.
.
.


#Collisions level_2 (colisiones)

#componente dinámico level_2
x.....
.
.
.

Roles (element_1 level_1 type_1 pos_1(x,y) element_2 level_2 type_2 pos_2(x,y) rul12) (reglas objetos dinámicos: switches, teletransportadores, etc)
Roles (element_1 level_1 type_1 pos_1(x,y) element_2 level_2 type_2 pos_2(x,y) rul12) (reglas objetos dinámicos: switches, teletransportadores, etc)

*/



void GameLevelNew::processGameLevelDef(char *gamezipfile){

    DEBUGLOG("GameLevelNew::processGameLevelDef --> INI");

    std::string line;
    std::ifstream myfile (gamezipfile);

    if (myfile.is_open())
    {
      std::getline (myfile,line);
      if (line.c_str() != NULL) {globalParams(line);}                       //parametros globales
      std::getline (myfile,line);
      if (line.c_str() != NULL) {setGlobalScripts(line);}                   //parametros script globales.
      std::getline (myfile,line);
      if (line.c_str() != NULL) {createLevels(line);}                       //pisos del nivel
      std::getline (myfile,line);
      if (line.c_str() != NULL) {
            setBackgroundImg(line);                                         //imagen background
            processLevel(myfile);                                           //datos del nivel
      }
      std::getline(myfile,line);
      if (line.c_str() != NULL) {
            processNumRoles(line);
            processRoles(myfile);
      }                                                                     //roles generales entre elementos dinamicos del nivel
      std::getline(myfile,line);
      if (line.c_str() != NULL) {
            processNumPlayer(line);
            processPlayers(myfile);
      }
      //numero de players
      //player
      myfile.close();
      INFOLOGPONE("GameLevelNew::processGameLevelDef LEVEL %s PROCESSED!",gamezipfile);
    }else{
      WARNLOGPONE("GameLevelNew::processGameLevelDef LEVEL %s NOT FOUND",gamezipfile);
    }


    DEBUGLOG("GameLevelNew::processGameLevelDef --> FIN");

}

//size_mundo_x size_mundo_y size_tile_x size_tile_y
void GameLevelNew::globalParams(std::string line){

    int sizeMundoX = 0;
    int sizeMundoY = 0;
    int sizeTileX = 0;
    int sizeTileY = 0;
    int mundoTileX = 0;
    int mundoTileY = 0;

    char *data_1 = strtok((char *)line.c_str(), DELIMITER);
    if (data_1 != NULL){ sizeMundoX = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){sizeMundoY = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){sizeTileX = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){sizeTileY = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){mundoTileX = atoi(data_1);}

    data_1 = strtok(0, DELIMITER);
    if (data_1 != NULL){mundoTileY = atoi(data_1);}

    this->size_world_x = sizeMundoX;
    this->size_world_y = sizeMundoY;
    this->tile_x = sizeTileX;
    this->tile_y = sizeTileY;
    this->world_tile_x = mundoTileX;
    this->world_tile_y = mundoTileY;

    //DEBUGLOGPSIX("GameLevelNew::globalParams --> GLOBAL PARAMS: (%d x %d) - (%d x %d) - (%d x %d)",this->size_world_x,this->size_world_y, this->tile_x, this->tile_y, this->world_tile_x, this->world_tile_y);
}

void GameLevelNew::setGlobalScripts(std::string line){

    char *data_1 = strtok((char *)line.c_str(), DELIMITER);
    this->globalGameScript = data_1;
    ENTITY_DATA->setGamePlayScript(this->globalGameScript);

    data_1 = strtok(0, DELIMITER);
    this->globalCollScript = data_1;
    ENTITY_DATA->setGameCollScript(this->globalCollScript);

    data_1 = strtok(0, DELIMITER);
    this->globalIAScript = data_1;
    ENTITY_DATA->setGameIAScript(this->globalIAScript);

    data_1 = strtok(0, DELIMITER);
    this->globalMusic = data_1;

    data_1 = strtok(0, DELIMITER);
    this->globalLighting = data_1;

    //DEBUGLOGPFOUR("GameLevelNew::setGlobalScripts --> GLOBAL COLL SCRIPT: (%s) - GLOBAL IA SCRIPT: (%s) - GLOBAL MUSIC: (%s) - GLOBAL LIGTH: (%s)",this->globalCollScript.c_str(),this->globalIAScript.c_str(), this->globalMusic.c_str(), this->globalLighting.c_str());

}


void GameLevelNew::createLevels(std::string line){

    int levels = 0;
    levels = atoi(line.c_str());

    this->num_levels = levels;

    ENTITY_DATA->setNumLevels(this->num_levels);
    ENTITY_DATA->setNumColls(this->world_tile_x);
    ENTITY_DATA->setNumRows(this->world_tile_y);

    if (this->num_levels > SIZEOFLEVELS){
        this->num_levels = SIZEOFLEVELS;
    }

    ENTITY_DATA->createLevels(this->world_tile_x, this->world_tile_y, this->num_levels);

    //DEBUGLOGPONE("GameLevelNew::globalParams --> LEVEL NUMBERS %d",this->num_levels);
}


void GameLevelNew::setBackgroundImg(std::string line){
    this->backgroundImage = line;
    GLIDef = ENTITY_DATA->getImageDef(line);
    ENTITY_DATA->setBackgroudImage(GLIDef);
}


void GameLevelNew::processLevel(std::ifstream &myfile){

    std::string line;

    for (int i=0; i<this->num_levels; i++){
         //procesando elementos pasivos
         for(int j=0; j<this->world_tile_y; j++){
            std::getline (myfile,line);
            processLevelStaticRow(line, i, j);
         }
         DEBUGLOGPONE("GameLevelNew::processLevelStaticEntities --> Processed Static Entities Level %d",i);


         std::getline(myfile,line);
         this->num_collition_by_level = atoi(line.c_str());

         //DEBUGLOGPTWO("GameLevelNew::processLevel --> Nº COLLISION LEVEL[%d] %d",i,num_collition_by_level);

         for (int j=0; j<num_collition_by_level; j++){
            std::getline(myfile,line);
            processLevelCollitionRow(line, i, j, COLL_PROCESS);
         }

         std::getline(myfile,line);
         this->num_light_by_level = atoi(line.c_str());

         //DEBUGLOGPTWO("GameLevelNew::processLevel --> Nº LIGHT LEVEL[%d] %d",i,num_light_by_level);

         for (int j=0; j<num_light_by_level; j++){
            std::getline(myfile,line);
            processLevelCollitionRow(line, i, j, LIGHT_PROCESS);
         }

         //procesando elementos activos
         for(int j=0; j<this->world_tile_y; j++){
            std::getline (myfile,line);
            processLevelDinamicRow(line, i, j);
         }
         DEBUGLOGPONE("GameLevelNew::processLevelDynamicEntities --> Processed Dynamic Entities Level %d",i);
    }
}

//ELEMENTOS ESTATICOS x NIVEL
void GameLevelNew::processLevelStaticRow(std::string line, int level, int row){

    //DEBUGLOGPTHREE("GameLevelNew::processLevelStaticRow --> LEVEL[%04d]ROW[%04d] %s",level,row,line.c_str());

    for(int z=0; z<this->world_tile_x; z++){
        char *data_1;
        if (z==0){
            data_1 = strtok((char *)line.c_str(), DELIMITER);
        }else{
            data_1 = strtok(0, DELIMITER);
        }

        int idStaticRow = atoi(data_1);

        GLOMN->processTileDef(idStaticRow,row,z,level);

        //procesando tiles.
        //GLTile *glTile = new GLTile();
        //ENTITY_DATA->setStaticTileLevel(level,row,z,*glTile);
    }
    //DEBUGLOGPONE("GameLevelNew::processLevelDinamicRow --> Processed Static Entities Level %d",level);
}

//ELEMENTOS DINAMICOS x NIVEL
void GameLevelNew::processLevelDinamicRow(std::string line, int level, int row){

    //DEBUGLOGPTHREE("GameLevelNew::processLevelDinamicRow --> LEVEL[%04d]ROW[%04d] %s",level,row,line.c_str());

    for(int z=0; z<this->world_tile_x; z++){
        char *data_1;
        if (z==0){
            data_1 = strtok((char *)line.c_str(), DELIMITER);
        }else{
            data_1 = strtok(0, DELIMITER);
        }

        int idEntityDef = atoi(data_1);

        //procesando tiles.
        GLOMN->processDynamicDef(idEntityDef,row,z,level);
    }

    //DEBUGLOGPONE("GameLevelNew::processLevelDinamicRow --> Processed Dinamic Entities Level %d",level);
}


//COLISIONES x NIVEL
void GameLevelNew::processLevelCollitionRow(std::string line, int level, int row, int flag){

    int z = 0;
    float x = 0;
    float y = 0;
    char *data_1;

    GLCollision *glColl = new GLCollision();

    relMovementPol rPol;
    rPol.num_nodes = 0;
    relMovement rM;

    DEBUGLOGPONE("GameLevelNew::processLevelCollitionRow statical coll array --> [%s]", line.c_str());

    do{

        if (z==0){
            data_1 = strtok((char *)line.c_str(), DELIMITER_1);
        }else{
            data_1 = strtok(0, DELIMITER_1);
        }

        if (data_1 != NULL){

            if (z%2 == 0){
                x = atof(data_1);
                z+=1;
                rM.rel_pos_x = x;
            }else{
                y = atof(data_1);
                z+=1;

                rM.rel_pos_y = y;
                rPol.nodes[rPol.num_nodes] = rM;
                rPol.num_nodes++;

                rM.rel_pos_x = 0;
                rM.rel_pos_y = 0;
            }

        }

    }while(data_1 != NULL);

    rPol.coll = 0;
    glColl->setRelMovementPol(rPol);

    if (flag == COLL_PROCESS){

        ENTITY_DATA->setDataCollitionLevel(level,glColl);
        processLevelOrientationCollRow(level,glColl);

        DEBUGLOGPONE("GameLevelNew::processLevelCollitionRow --> Processed Static Collitions Level %d",level);
    }else{
        ENTITY_DATA->setDataLightLevel(level,glColl);
        DEBUGLOGPONE("GameLevelNew::processLevelCollitionRow --> Processed Static Lightmaps Level %d",level);
    }
}


void GameLevelNew::processLevelOrientationCollRow(int level, GLCollision *data){

    relMovementPol rMP = data->getRelMovementPol();
    int limit = rMP.num_nodes;
    relMovement m1;
    relMovement m2;
    relMovement normal;

    for(int i=0; i<limit; i++){

        if (i <(limit-1)){
            m1 = rMP.nodes[i];
            m2 = rMP.nodes[i+1];
        }else if (i == (limit-1)){
            m1 = rMP.nodes[i];
            m2 = rMP.nodes[0];
        }

        normal = Utils::getNormal(m1,m2);

        relMovementPol rMP;
        rMP.num_nodes = 2;
        rMP.coll = 0;


        if (((normal.rel_pos_y > 0) && (normal.rel_pos_x > 0))){      //DOWN & LEFT
            rMP.nodes[0] = m2;
            rMP.nodes[1] = m1;
        }else if ((normal.rel_pos_y < 0) && (normal.rel_pos_x > 0)){  //UP & LEFT
            rMP.nodes[0] = m2;
            rMP.nodes[1] = m1;
        }else if ((normal.rel_pos_y > 0) && (normal.rel_pos_x < 0)){  //DOWN  & RIGHT
            rMP.nodes[0] = m1;
            rMP.nodes[1] = m2;
        }else if (normal.rel_pos_y > 0){
            rMP.nodes[0] = m2;
            rMP.nodes[1] = m1;
        }else if (normal.rel_pos_x > 0){
            rMP.nodes[0] = m2;
            rMP.nodes[1] = m1;
        }else{
            rMP.nodes[0] = m1;
            rMP.nodes[1] = m2;
        }


        GLCollision *plane = new GLCollision(rMP);

        if (normal.rel_pos_y < 0){ //UP
            DEBUGLOGPSIX("GameLevelNew::processLevelOrientationCollRow --> m2 [%f,%f] m1 [%f,%f] normal [%f,%f] UP", m2.rel_pos_x, m2.rel_pos_y, m1.rel_pos_x, m1.rel_pos_y, normal.rel_pos_x, normal.rel_pos_y);
            ENTITY_DATA->setCollisionStaticMap(level, UP, plane);
        }

        if (normal.rel_pos_y > 0){ //DOWN
            DEBUGLOGPSIX("GameLevelNew::processLevelOrientationCollRow --> m2 [%f,%f] m1 [%f,%f] normal [%f,%f] DOWN", m2.rel_pos_x, m2.rel_pos_y, m1.rel_pos_x, m1.rel_pos_y, normal.rel_pos_x, normal.rel_pos_y);
            ENTITY_DATA->setCollisionStaticMap(level, DOWN, plane);
        }

        if (normal.rel_pos_x < 0){ //RIGHT
            DEBUGLOGPSIX("GameLevelNew::processLevelOrientationCollRow --> m2 [%f,%f] m1 [%f,%f] normal [%f,%f] RIGHT", m2.rel_pos_x, m2.rel_pos_y, m1.rel_pos_x, m1.rel_pos_y, normal.rel_pos_x, normal.rel_pos_y);
            ENTITY_DATA->setCollisionStaticMap(level, RIGHT, plane);
        }

        if (normal.rel_pos_x > 0){ //LEFT
            DEBUGLOGPSIX("GameLevelNew::processLevelOrientationCollRow --> m2 [%f,%f] m1 [%f,%f] normal [%f,%f] LEFT", m2.rel_pos_x, m2.rel_pos_y, m1.rel_pos_x, m1.rel_pos_y, normal.rel_pos_x, normal.rel_pos_y);
            ENTITY_DATA->setCollisionStaticMap(level, LEFT, plane);
        }
    }


}




//NUMROLES
void GameLevelNew::processNumRoles(std::string line){
    this->num_roles = atoi(line.c_str());
    //DEBUGLOGPONE("GameLevelNew::processNumRoles --> NUM_ROLES [%d]",num_roles);
}

//ROLES
void GameLevelNew::processRoles(std::ifstream &myfile){
    std::string line;
    for(int i=0; i<this->num_roles; i++){
        std::getline(myfile,line);
        processRole(i, line);
    }
    DEBUGLOG("GameLevelNew::processRoles --> Processed Roles");

}

//ROLE
void GameLevelNew::processRole(int indexRole, std::string line){
    //DEBUGLOGPTWO("GameLevelNew::processNumRoles --> ROLE [%d] - [%s]",indexRole, line.c_str());
    GLRole *rol = new GLRole();
    ENTITY_DATA->setDataRoleMap(rol);
}

//NUM PLAYERS. ACTUAL PLAYER.
void GameLevelNew::processNumPlayer(std::string line){

    char *data_1 = NULL;

    data_1 = strtok((char *)line.c_str(), DELIMITER);
    this->num_players = atoi(data_1);
    ENTITY_DATA->setNumPlayers(this->num_players);
    DEBUGLOGPONE("GameLevelNew::processNumPlayer --> Num Players [%d]",num_players);

    data_1 = strtok(0, DELIMITER);
    this->act_player = atoi(data_1);
    gNew->setActPlayer(this->act_player);
    DEBUGLOGPONE("GameLevelNew::processNumPlayer --> Act Player [%d]",act_player);

}

void GameLevelNew::processPlayers(std::ifstream &myfile){

    std::string line;
    for(int i=0; i<this->num_players; i++){
        std::getline(myfile,line);
        processPlayer(line,i);
    }
    DEBUGLOG("GameLevelNew::processPlayers --> Processed Player");


}


//PLAYER
void GameLevelNew::processPlayer(std::string line, int id_player){
    //DEBUGLOGPONE("GameLevelNew::processPlayer --> PLAYERS COORD [%s]",line.c_str());

    char *data_1 = NULL;
    int idplayer = 0;
    int level  = 0;
    int orientation = 0;
    int x_pos = 0;
    int y_pos = 0;

    data_1 = strtok((char *)line.c_str(), DELIMITER_1);
    idplayer = atoi(data_1);
    data_1 = strtok(0, DELIMITER_1);
    level = atoi(data_1);
    data_1 = strtok(0, DELIMITER_1);
    orientation = atoi(data_1);
    data_1 = strtok(0, DELIMITER_1);
    x_pos = atoi(data_1);
    data_1 = strtok(0, DELIMITER_1);
    y_pos = atoi(data_1);
    GLOMN->processPlayerDef(idplayer,id_player,float(x_pos),float(y_pos),level,orientation);


    /*
    int idplayer = 0;
    int level  = 0;
    int x_pos = 0;
    int y_pos = 0;
    int z=0;
    int y=0;
    char *data_1 = NULL;

    int inc_players = 0;
    bool end_players = false;

    do{
        if (inc_players < this->num_players){

            if (z==0){
                data_1 = strtok((char *)line.c_str(), DELIMITER_1);
            }else{
                data_1 = strtok(0, DELIMITER_1);
            }

            if (data_1 != NULL){
                if (z%4 == 0){
                    idplayer = atoi(data_1);
                    z+=1;
                }else if (z%4 == 1){
                    level = atoi(data_1);
                    z+=1;
                }else if (z%4 == 2){
                    x_pos = atoi(data_1);
                    z+=1;
                }else if (z%4 == 3){
                    y_pos = atoi(data_1);
                    if (z==3){
                        this->pos_x_player_1 = float(x_pos);
                        this->pos_y_player_1 = float(y_pos);
                        this->level_player_1 = level;
                        GLOMN->processPlayerDef(idplayer,inc_players,float(x_pos),float(y_pos),level);
                        inc_players=inc_players+1;
                    }else if (z==7){
                        this->pos_x_player_2 = float(x_pos);
                        this->pos_y_player_2 = float(y_pos);
                        this->level_player_2 = level;
                        GLOMN->processPlayerDef(idplayer,inc_players,float(x_pos),float(y_pos),level);
                        inc_players=inc_players+1;
                    }else if (z==11){
                        this->pos_x_player_3 = float(x_pos);
                        this->pos_y_player_3 = float(y_pos);
                        this->level_player_3 = level;
                        GLOMN->processPlayerDef(idplayer,inc_players,float(x_pos),float(y_pos),level);
                        inc_players=inc_players+1;
                    }else if (z==15){
                        this->pos_x_player_4 = float(x_pos);
                        this->pos_y_player_4 = float(y_pos);
                        this->level_player_4 = level;
                        GLOMN->processPlayerDef(idplayer,inc_players,float(x_pos),float(y_pos),level);
                        inc_players=inc_players+1;
                    }
                    z+=1;
                }

            }
        }else{
           end_players = true;
        }
    }while((data_1 != NULL) && !end_players);
    */


}


