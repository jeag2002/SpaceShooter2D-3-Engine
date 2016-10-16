#include "GLAnimParticleDefManager.h"


SDL_Color GLAnimParticleDefManager::processColor(char *color_path){
    SDL_Color color_def;

    char *ptr = NULL;

    ptr = strtok(color_path,DELIMITER_COORD_PARTICLE);
    if (ptr != NULL){color_def.r = atoi(ptr);}

    ptr = strtok(NULL,DELIMITER_COORD_PARTICLE);
    if (ptr != NULL){color_def.g = atoi(ptr);}

    ptr = strtok(NULL,DELIMITER_COORD_PARTICLE);
    if (ptr != NULL){color_def.b = atoi(ptr);}

    ptr = strtok(NULL,DELIMITER_COORD_PARTICLE);
    if (ptr != NULL){color_def.a = atoi(ptr);}

    return color_def;
}



void GLAnimParticleDefManager::processAnimParticleDefManager(char *gamezipfile){

    char buff[100];

    std::string path_to_data = "";
    std::string idImageStr = "";
    std::string colorStr = "";
    SDL_Color color;

    unsigned int imageid = 0;
    float x_1 = 0.0f;
    float y_1 = 0.0f;
    float scale = 0.0f;
    float max_1 = 0.0f;
    float alpha_inf = 0.0f;
    float alpha_sup = 0.0f;
    float velocity = 0.0f;
    float direction = 0.0f;
    float spread = 0.0f;
    float length = 0.0f;

    ConfigFile config(gamezipfile);

    int num_particles = config.read<int>("num_particles");


    for(int i=1; i<=num_particles; i++){

        gParticleDesc = new GLParticleDesc();

        //KEY
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_id_%i", i);
        path_to_data = buff;
        path_to_data = config.read<std::string>(path_to_data);

        char *particle_key_char = new char[path_to_data.length()+1];
        for(int i=0; i<(path_to_data.length()+1); i++){particle_key_char[i] = path_to_data.c_str()[i];}
        std::string particleKey(particle_key_char);
        /////////////////////////////////////////////////////////////////////////////////////////////////

        //IMAGE
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff,"particle_idmage_%i",i);
        path_to_data = buff;
        idImageStr = config.read<std::string>(path_to_data);

        char *id_image_key_char = new char[idImageStr.length()+1];
        for(int i=0; i<(idImageStr.length()+1); i++){id_image_key_char[i] = idImageStr.c_str()[i];}
        std::string imageKeyClone(id_image_key_char);

        GLImageDef *imageDef = ENTITY_DATA->getImageDef(imageKeyClone);
        if (imageDef->getImageID() != ID_IMAGE_PARTICLE_NOTFOUND){
            gParticleDesc->setImageId(imageDef->getImageID());
            DEBUGLOGPTWO("GLAnimParticleDefManager::processAnimParticleDefManager IMAGE [%s] ::= %d",imageKeyClone.c_str(),imageDef->getImageID());
        }else{
            WARNLOGPONE("GLAnimParticleDefManager::processAnimParticleDefManager IMAGE [%s] NOT FOUND",imageKeyClone.c_str());
            GLImageDef *imageDefIDLE = ENTITY_DATA->getImageDef(ID_IMAGE_IDLE_DEFAULT);
            gParticleDesc->setImageId(imageDefIDLE->getImageID());
            INFOLOGPTWO("GLAnimParticleDefManager::processAnimParticleDefManager IMAGE [%s] ::= %d",ID_IMAGE_IDLE_DEFAULT,imageDefIDLE->getImageID());
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////


        //X_1
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_x_%i",i);
        path_to_data = buff;
        gParticleDesc->setX(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //Y_1
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_y_%i",i);
        path_to_data = buff;
        gParticleDesc->setY(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //SCALE
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_scale_%i",i);
        path_to_data = buff;
        gParticleDesc->setScale(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //MAX
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_max_%i",i);
        path_to_data = buff;
        gParticleDesc->setMaxParticles(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //ALPHA_INF
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_alpha_inf_%i",i);
        path_to_data = buff;
        gParticleDesc->setAlphaInf(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //ALPHA_SUP
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_alpha_sup_%i",i);
        path_to_data = buff;
        gParticleDesc->setAlphaSup(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //COLOR_INF
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_color_inf_%i", i);
        path_to_data = buff;
        colorStr = config.read<std::string>(path_to_data);
        char* color_str_inf_cpy = new char[colorStr.length()+1];
        for(int i=0; i<(colorStr.length()+1); i++){color_str_inf_cpy[i] = colorStr.c_str()[i];}
        color = processColor(color_str_inf_cpy);
        gParticleDesc->setColorInf(color);
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //COLOR_SUP
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_color_sup_%i", i);
        path_to_data = buff;
        colorStr = config.read<std::string>(path_to_data);
        char* color_str_sup_cpy = new char[colorStr.length()+1];
        for(int i=0; i<(colorStr.length()+1); i++){color_str_sup_cpy[i] = colorStr.c_str()[i];}
        color = processColor(color_str_sup_cpy);
        gParticleDesc->setColorSup(color);
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //VELOCITY
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_velocity_%i",i);
        path_to_data = buff;
        gParticleDesc->setVelocity(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //DIRECTION
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_direction_%i",i);
        path_to_data = buff;
        gParticleDesc->setDirection(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //SPREAD
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_spread_%i",i);
        path_to_data = buff;
        gParticleDesc->setSpread(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////
        //LENGTH
        /////////////////////////////////////////////////////////////////////////////////////////////////
        sprintf(buff, "particle_length_%i",i);
        path_to_data = buff;
        gParticleDesc->setLength(config.read<float>(path_to_data));
        /////////////////////////////////////////////////////////////////////////////////////////////////

        DEBUGLOGPTWO("GLAnimParticleDefManager::processAnimParticleDefManager -->[%d] INSERTED PARTICLE [%s]",i,particleKey.c_str());
        ENTITY_DATA->setParticleDesc(particleKey,gParticleDesc);
    }

    config.close();
    INFOLOGPONE("GLAnimParticleDefManager::processAnimParticleDefManager --> PARTICULAS PROCESADAS (%d)",num_particles);

};
