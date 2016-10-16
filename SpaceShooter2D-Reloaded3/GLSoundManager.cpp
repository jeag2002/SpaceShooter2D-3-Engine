#include "GLSoundManager.h"

void GLSoundManager::processSoundManagerFile(char *gamezipfile){

char buff[100];
ConfigFile config(gamezipfile);

int num_sounds = 0;


num_sounds = config.read<int>("num_sounds");

std::string path_to_sound = "";
std::string extension = "";
std::string type = "";
std::string id = "";

for(int i=1; i<=num_sounds; i++){

    GLSoundFile *glSoundFile = new GLSoundFile(gNew,gLogEngine);

    sprintf(buff, "%d_sound_file", i);
    path_to_sound = buff;
    path_to_sound = config.read<std::string>(path_to_sound);

    glSoundFile->setFilePath(path_to_sound);

    sprintf(buff, "%d_sound_ext",i);
    extension = buff;
    extension = config.read<std::string>(extension);

    glSoundFile->setExtension(extension);

    sprintf(buff, "%d_sound_type",i);
    type = buff;
    type = config.read<std::string>(type);

    glSoundFile->setTypeSound(type);

    sprintf(buff, "%d_sound_id",i);
    id = buff;
    id = config.read<std::string>(id);

    ENTITY_DATA->setSoundFile(id,glSoundFile);
    DEBUGLOGPFOUR("GLSoundManager::processSoundManagerFile --> [%d] sound id (%s) extension (%s) path (%s)", i, id.c_str(), extension.c_str(), path_to_sound.c_str());
}

config.close();
INFOLOGPONE("GLSoundManager::processSoundManagerFile --> SONIDOS PROCESADOS (%d)",num_sounds);





}
