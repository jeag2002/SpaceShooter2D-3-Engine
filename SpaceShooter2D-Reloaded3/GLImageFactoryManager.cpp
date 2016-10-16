#include "GLImageFactoryManager.h"

//procesamos el fichero de imagenes
 void GLImageFactoryManager::processImageDefFile(char *gamezipfile){

      char buff[100];
      ConfigFile config(gamezipfile);

      int num_image = config.read<int>("num_images");

      std::string path_to_image = "";
      std::string path_to_imageKey = "";
      std::string extension = "";
      std::string extension_res = "";
      std::string width_key = "";
      std::string height_key = "";
      std::string parallax = "";
      std::string flag = "";

      int width = 0;
      int height = 0;

      int flag_bgr_cnv = 0;
      int flag_clamp = 0;
      int flag_lin_near = 0;
      int flag_mipmap = 0;
      int flag_power2 = 0;
      int flag_trans = 0;

      for(int i=1; i<=num_image; i++){

        sprintf(buff, "image_%d", i);
        path_to_image = buff;
        path_to_image = config.read<std::string>(path_to_image);

        char *path_to_image_cpy = new char[path_to_image.length()+1];
        for(int i=0; i<(path_to_image.length()+1); i++){path_to_image_cpy[i] = path_to_image.c_str()[i];}
        //memcpy(path_to_image_cpy,path_to_image.c_str(),path_to_image.length()+1);
        //std::string path_to_image_cpy_str(path_to_image);

        sprintf(buff, "image_%d_ticked",i);
        path_to_imageKey = buff;
        path_to_imageKey = config.read<std::string>(path_to_imageKey);
        char *image_key_cpy = new char[path_to_imageKey.length()+1];
        for(int i=0; i<(path_to_imageKey.length()+1); i++){image_key_cpy[i] = path_to_imageKey.c_str()[i];}
        //memcpy(image_key_cpy,path_to_imageKey.c_str(),path_to_imageKey.length()+1);
        std::string image_key_cpy_str(image_key_cpy);

        sprintf(buff, "image_%d_ext",i);
        extension = buff;
        extension_res = config.read<std::string>(extension);

        char* extension_res_cpy = new char[extension_res.length()+1];
        for(int i=0; i<(extension_res.length()+1); i++){extension_res_cpy[i] = extension_res.c_str()[i];}

        //memcpy(extension_res_cpy, extension_res.c_str(), extension_res.length()+1);
        //std::string extension_res_cpy_str(extension_res_cpy);

        sprintf(buff,"image_%d_width",i);
        width_key = buff;
        width = config.read<int>(width_key);

        sprintf(buff,"image_%d_height",i);
        height_key = buff;
        height = config.read<int>(height_key);

        sprintf(buff, "image_%d_parallax",i);
        parallax = buff;
        parallax = config.read<std::string>(parallax);

        //flags.
        sprintf(buff, "image_%d_bgr_conv",i);
        flag = buff;
        flag_bgr_cnv = config.read<int>(flag);

        sprintf(buff, "image_%d_lin_near",i);
        flag = buff;
        flag_lin_near = config.read<int>(flag);

        sprintf(buff, "image_%d_clamp",i);
        flag = buff;
        flag_clamp = config.read<int>(flag);

        sprintf(buff, "image_%d_mipmap",i);
        flag = buff;
        flag_mipmap = config.read<int>(flag);

        sprintf(buff, "image_%d_power2",i);
        flag = buff;
        flag_power2 = config.read<int>(flag);

        sprintf(buff, "image_%d_transparent",i);
        flag = buff;
        flag_trans = config.read<int>(flag);


        int flags[6] = {0,0,0,0,0,0};

        flags[0] = flag_bgr_cnv;
        flags[1] = flag_lin_near;
        flags[2] = flag_clamp;
        flags[3] = flag_mipmap;
        flags[4] = flag_power2;
        flags[5] = flag_trans;

        GLImageDef *imageDef = image->processImage(path_to_image_cpy, extension_res_cpy, flags);


        if (strncmp(parallax.c_str(),PARALLAX_ENABLED,strlen(PARALLAX_ENABLED)) == 0){
            imageDef->setParallax(true);
        }else{
            imageDef->setParallax(false);
        }

        //int idOpenGL = i;
        DATA_TYPE->setImageDefinition(image_key_cpy_str,imageDef);
        DEBUGLOGPFIVE("GLImageFactoryManager::processImageDefFile --> [%d]-[%s] TYPE [%s] PATH [%s] OPENGL-ID (%d)",
                     i,
                     image_key_cpy,
                     extension_res_cpy,
                     path_to_image_cpy,
                     imageDef->getImageID());


        delete path_to_image_cpy;
        delete image_key_cpy;
        delete extension_res_cpy;

      }

      config.close();
      INFOLOGPONE("GLImageFactoryManager::processImageDefFile --> IMAGENES PROCESADAS (%d)",num_image);
 };
