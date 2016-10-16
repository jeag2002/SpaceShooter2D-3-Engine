#include "GLEntityDefManager.h"


//2015-10-31 JALCARAZ. Reflexionar que es mejor. Guardar la BD de elementos de un videojuego antes?... o cargarla en el momento de generar el mapa
//(accediendo a las definiciones conforme las vayamos necesitando)

char *GLEntityDefManager::getEntityDescription(int typeEntity){

    if (typeEntity == ENTITY_TYPE_TILE){
        return "TILE_ENTITY";
    }else if (typeEntity ==  ENTITY_TYPE_ACTOR){
        return "ACTOR_ENTITY";
    }else if (typeEntity ==  ENTITY_TYPE_LIGHT){
        return "LIGHT_ENTITY";
    }else if (typeEntity ==  ENTITY_TYPE_PART){
        return "PARTICLE_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_SWITCH_ACT){
        return "SWITCH_ACT_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_SWITCH_PAS){
        return "SWITCH_PAS_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_PORTAL_UP){
        return "SWITCH_PORTAL_UP_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_PORTAL_DOWN){
        return "SWITCH_PORTAL_DOWN_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_PORTAL_UPDOWN){
        return "PORTAL_UPDOWN_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_EXIT){
        return "EXIT_ENTITY";
    }else if (typeEntity == ENTITY_TYPE_EXIT_STOP){
        return "EXIT_STOP";
    }else if (typeEntity == ENTITY_TYPE_ITEM){
        return "ITEM";
    }else if (typeEntity == ENTITY_TYPE_BLOCK){
        return "BLOCK";
    }else if (typeEntity == ENTITY_TYPE_GENERATOR){
        return "GENERATOR";
    }else{
        return "DEFAULT";
    }
}

//de momento, se hará un procesado del mismo antes de cargar los niveles.
void GLEntityDefManager::processEntityDefinitionFile(char *gamezipfile){

      char buff[100];
      ConfigFile config(gamezipfile);

      int num_elements = config.read<int>("num_elements");

      int id = 0;                   //identificador del elemento
      int type_id = 0;              //identificador del tipo de elementos.
      int image_id = 0;             //identificador GLUINT image;
      int node_id = 0;              //identificador node adj.

      int num_images = 0;           //numero de imagenes
      int num_arrays_by_images = 0; //numeros de elementos de la imagen
      int num_adj_nodes = 0;        //numero de nodos adjacentes
      int num_others_elems = 0;     //numero otros elementos.

      std::string path = "";        //string => etiqueta general
      std::string descEntity = "";  //string => descripcion de la entidad
      std::string id_image = "";    //string => identificador de la imagen
      std::string coord_image = ""; //string => coordenadas de la imagen

      std::string var_name = "";      //nombre de la variable
      std::string var_value = "";     //valor de la variable

      EntityRef data;

      for(int i=1; i<=num_elements; i++){

        GLEntityDefinition *gEDefinition = new GLEntityDefinition();

        //identificador ID
        sprintf(buff, "element_%i_ID", i);
        path = buff;
        id = config.read<int>(path);
        gEDefinition->setId(id);

        //identificador TYPE
        sprintf(buff, "element_%i_TYPE", i);
        path = buff;
        type_id = config.read<int>(path);
        gEDefinition->setEntityType(type_id);

        //identificador SIZEX
        sprintf(buff, "element_%i_SIZETILEX", i);
        path = buff;
        float sizeTileX = config.read<float>(path);
        gEDefinition->sizeTileX(sizeTileX);

        //identificador SIZEY
        sprintf(buff, "element_%i_SIZETILEY", i);
        path = buff;
        float sizeTileY = config.read<float>(path);
        gEDefinition->sizeTileY(sizeTileY);


        //identificador descripcion tipo de elemento.
        descEntity = getEntityDescription(type_id);
        gEDefinition->setEntityDesc(descEntity);

        //numero de imagenes
        sprintf(buff, "element_%i_IMG_ARRAY", i);
        path = buff;
        num_images = config.read<int>(path);

        //recorrido de todas las imagenes definidas en el elemento a printar
        //////////////////////////////////////////////////////////////////////////////
        for(int j=1; j<=num_images; j++){

            //obtiene el codigo del elemento de la imagen recuperado
            sprintf(buff,"element_%i_IMG_%i",i,j);
            path = buff;

            //inserta el codigo OpenGL de la imagen.
            id_image = config.read<std::string>(path);
            char* c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy(c_id_image_cpy);

            GLImageDef *dataImage = ENTITY_DATA->getImageDef(id_image_cpy);
            image_id = dataImage->getImageID();

            //image_id = ENTITY_DATA->getImageDef(id_image_cpy);

            if (image_id != ID_IMAGE_NOTFOUND){
                gEDefinition->setImage(image_id);
                DEBUGLOGPFIVE("GLEntityDefManager::processEntityDefinitionFile --> [%i] ELEMENTO %i (%s) INSERTADO IMAGE [%s] ::= %d", i, id, descEntity.c_str(),id_image_cpy.c_str(),image_id);

                //obtiene el numero de arrays por imagen
                sprintf(buff,"element_%i_IMG_%i_ARRAY", i, j);
                path = buff;

                num_arrays_by_images = config.read<int>(path);

                for (int z=1; z<=num_arrays_by_images; z++){
                    sprintf(buff,"element_%i_IMG_%i_%i",i,j,z);
                    path = buff;

                    coord_image = config.read<std::string>(path);
                    char* c_coord_image_cpy = new char[coord_image.length()+1];
                    memcpy(c_coord_image_cpy, coord_image.c_str(), coord_image.length()+1);
                    const std::string coord_image_cpy(c_coord_image_cpy);

                    //std::string coord_image_cpy(coord_image.c_str());
                    processTilesArrayForImages(coord_image_cpy, image_id, j, (z-1), gEDefinition);

                }
            }else{

                image_id = ENTITY_DATA->getImageDef(ID_IMAGE_DEFAULT);
                gEDefinition->setImage(image_id);
                DEBUGLOGPFIVE("GLEntityDefManager::processEntityDefinitionFile --> [%i] ELEMENTO %i (%s) INSERTADO IMAGE IDLE [%s] ::= %d", i, id, descEntity.c_str(),id_image_cpy.c_str(),image_id);
                std::string coord_image_cpy = "0.0 0.0 1.0 0.0 0.0 1.0 1.0 1.0";
                processTilesArrayForImages(coord_image_cpy, image_id, j, 1, gEDefinition);

            }


            //obtiene el codigo del elemento de la imagen recuperado LIGHTMAP
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            sprintf(buff,"element_%i_IMG_%i_LIGHTMAP",i,j);
            path = buff;

            //inserta el codigo OpenGL de la imagen.
            id_image = config.read<std::string>(path);
            c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy_lm(c_id_image_cpy);

            dataImage = ENTITY_DATA->getImageDef(id_image_cpy_lm);
            image_id = dataImage->getImageID();
            gEDefinition->setImageLightmap(image_id);

            sprintf(buff,"element_%i_IMG_%i_LIGHTMAP_CMB",i,j);
            path = buff;
            id_image = config.read<std::string>(path);
            c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy_lm_cmb(c_id_image_cpy);
            gEDefinition->setImageLightmapCmb(id_image_cpy_lm_cmb);

            ////////////////////////////////////////////////////////////////////////////////////////////////////

            //obtiene el codigo del elemento de la imagen recuperada BUMPMAP
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            sprintf(buff,"element_%i_IMG_%i_BUMPMAP",i,j);
            path = buff;

            //inserta el codigo OpenGL de la imagen.
            id_image = config.read<std::string>(path);
            c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy_bm(c_id_image_cpy);

            dataImage = ENTITY_DATA->getImageDef(id_image_cpy_bm);
            image_id = dataImage->getImageID();
            gEDefinition->setImageBumpmap(image_id);

            sprintf(buff,"element_%i_IMG_%i_BUMPMAP_CMB",i,j);
            path = buff;
            id_image = config.read<std::string>(path);
            c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy_bmp_cmb(c_id_image_cpy);
            gEDefinition->setImageBumpmapCmb(id_image_cpy_bmp_cmb);



            ////////////////////////////////////////////////////////////////////////////////////////////////////

             //obtiene el codigo del elemento de la imagen recuperada BUMPMAP
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            sprintf(buff,"element_%i_IMG_%i_MASK",i,j);
            path = buff;

            //inserta el codigo OpenGL de la imagen.
            id_image = config.read<std::string>(path);
            c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy_mk(c_id_image_cpy);

            dataImage = ENTITY_DATA->getImageDef(id_image_cpy_mk);
            image_id = dataImage->getImageID();
            gEDefinition->setImageMask(image_id);


            sprintf(buff,"element_%i_IMG_%i_MASK_CMB",i,j);
            path = buff;
            id_image = config.read<std::string>(path);
            c_id_image_cpy = new char[id_image.length()+1];
            memcpy(c_id_image_cpy, id_image.c_str(), id_image.length()+1);
            const std::string id_image_cpy_mk_cmb(c_id_image_cpy);
            gEDefinition->setImageMaskStr(id_image_cpy_mk_cmb);

            ////////////////////////////////////////////////////////////////////////////////////////////////////





            //posiciones diferenciales de los tiles que forman la entidad
            ////////////////////////////////////////////////////////////////////////////////////////////////////

            sprintf(buff,"element_%i_IMG_%i_DIFF_X",i,j);
            path = buff;
            float diff_x_image = config.read<float>(path);

            sprintf(buff,"element_%i_IMG_%i_DIFF_Y",i,j);
            path = buff;
            float diff_y_image = config.read<float>(path);

            relMovement rM;
            rM.rel_pos_x = diff_x_image;
            rM.rel_pos_y = diff_y_image;

            gEDefinition->setCoordTileParameter(rM);
            ////////////////////////////////////////////////////////////////////////////////////////////////////


            delete c_id_image_cpy;
        }
        //////////////////////////////////////////////////////////////////////////////

        //elementos variables asociados;
        //////////////////////////////////////////////////////////////////////////////
        sprintf(buff,"element_%i_OTHER_ARRAY",i);
        path = buff;
        num_others_elems = config.read<int>(path);

        for (int j=1; j<=num_others_elems; j++){
            sprintf(buff, "element_%i_OTHER_%i_NAME",i,j);
            path = buff;

            var_name = config.read<std::string>(path);
            char* c_var_name_cpy = new char[var_name.length()+1];
            memcpy(c_var_name_cpy, var_name.c_str(), var_name.length()+1);
            std::string var_name_cpy(c_var_name_cpy);

            sprintf(buff, "element_%i_OTHER_%i_VALUE",i,j);
            path = buff;

            var_value = config.read<std::string>(path);
            char* c_var_value_cpy = new char[var_value.length()+1];
            memcpy(c_var_value_cpy, var_value.c_str(), var_value.length()+1);
            std::string var_value_cpy(c_var_value_cpy);

            gEDefinition->setOtherParams(var_name_cpy,c_var_value_cpy);

        }

        //DEBUGLOGPTHREE("GLEntityDefManager::processEntityDefinitionFile --> [%i] ELEMENTO %i (%s) INSERTADO", i, id, descEntity.c_str());
        //////////////////////////////////////////////////////////////////////////////

         //nodos asociados
        //////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "element_%i_REF_ARRAY", i);
        path = buff;
        num_adj_nodes = config.read<int>(path);

        for(int j=1; j<=num_adj_nodes; j++){


           sprintf(buff, "element_%i_REF_%i_ID",i,j);
           path = buff;
           data.idEntity = config.read<int>(path);

           sprintf(buff, "element_%i_REF_%i_DIFFX",i,j);
           path = buff;
           data.x_diff_pos = config.read<float>(path);

           sprintf(buff, "element_%i_REF_%i_DIFFY",i,j);
           path = buff;
           data.y_diff_pos = config.read<float>(path);

           sprintf(buff, "element_%i_REF_%i_ROT",i,j);
           path = buff;
           data.rotate_pos = config.read<float>(path);

           gEDefinition->setNodes(data);
        }
        //////////////////////////////////////////////////////////////////////////////

        ENTITY_DATA->setEntityDefinition(id,gEDefinition);


      }//final del proceso

      INFOLOGPONE("GLEntityDefManager::processEntityDefinitionFile --> NUM ELEMENTOS INSERTADOS (%i)",num_elements);
      config.close();
}



//Parseo de coordenadas de texturas.
void GLEntityDefManager::processTilesArrayForImages(std::string coord, GLuint idImage, int j, int z, GLEntityDefinition *data){

    relMovementPol coordTexXY;
    coordTexXY.num_nodes = 0;

    relMovement texXY;

    char *ptr = NULL;

    ptr = strtok(coord.c_str(),DELIMITER_COORD);

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
         ptr = strtok(NULL,DELIMITER_COORD);

    }

    data->setCoordTextures(idImage,coordTexXY);
}

