#include "TiffDefManager.h"

SDL_Color TiffDefManager::processColor(char *color_path){
    SDL_Color color_def;

    char *ptr = NULL;

    ptr = strtok(color_path,DELIMITER_COORD);
    if (ptr != NULL){color_def.r = atoi(ptr);}

    ptr = strtok(NULL,DELIMITER_COORD);
    if (ptr != NULL){color_def.g = atoi(ptr);}

    ptr = strtok(NULL,DELIMITER_COORD);
    if (ptr != NULL){color_def.b = atoi(ptr);}

    ptr = strtok(NULL,DELIMITER_COORD);
    if (ptr != NULL){color_def.a = atoi(ptr);}

    return color_def;
}


void TiffDefManager::processTiffDefFile(char *gamezipfile){

     char buff[100];
     ConfigFile config(gamezipfile);

     int num_tiff = config.read<int>("num_tiff");

     std::string path_to_id = "";
     std::string path_to_tiff = "";
     int sizeTiff = 0;
     SDL_Color color;

     for(int i=1; i<=num_tiff; i++){

        sprintf(buff, "tiff_%d_id", i);
        path_to_id = buff;
        path_to_id = config.read<std::string>(path_to_id);

        char* c_path_to_id_cpy = new char[path_to_id.length()+1];
        memcpy(c_path_to_id_cpy, path_to_id.c_str(), path_to_id.length()+1);

        std::string path_to_id_cpy_str(c_path_to_id_cpy);

        sprintf(buff, "tiff_%d_path", i);
        path_to_tiff = buff;
        path_to_tiff = config.read<std::string>(path_to_tiff);

        char* c_path_to_tiff_cpy = new char[path_to_tiff.length()+1];
        memcpy(c_path_to_tiff_cpy, path_to_tiff.c_str(), path_to_tiff.length()+1);

        sprintf(buff, "tiff_%d_size", i);
        path_to_tiff = buff;
        sizeTiff = config.read<int>(path_to_tiff);

        sprintf(buff, "tiff_%d_color", i);
        path_to_tiff = buff;
        path_to_tiff = config.read<std::string>(path_to_tiff);
        char* c_path_to_color_cpy = new char[path_to_tiff.length()+1];
        memcpy(c_path_to_color_cpy, path_to_tiff.c_str(), path_to_tiff.length()+1);
        color = processColor(c_path_to_color_cpy);

        TiffEngine *tEngine = new TiffEngine(c_path_to_tiff_cpy,sizeTiff,color);
        DATA_TYPE->setTiffEngine(path_to_id_cpy_str,tEngine);

        DEBUGLOGPSEVEN("TiffDefManager::processTiffDefFile --> [%d] id [%s] ::= path [%s] size [%d] color [%d,%d,%d]",i,c_path_to_id_cpy,c_path_to_tiff_cpy,sizeTiff,color.r,color.g,color.b);

     }

     config.close();

     INFOLOGPONE("TiffDefManager::processTiffDefFile --> FUENTES TRUETYPE PROCESADAS (%d)",num_tiff);
}
