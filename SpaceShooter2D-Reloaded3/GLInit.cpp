#include "GLInit.h"


void GLInit::processGlobalFileInit(){

    ConfigFile config(gNew->getGlobalPath());

    gNew->setLog(config.read<int>("log"));
    gNew->setTypeLog(config.read<int>("logType"));
    gNew->setProfType(config.read<int>("profType"));
    gNew->setTasType(config.read<int>("tasType"));
    gNew->setToggleColl(config.read<int>("toggleColl"));
    gNew->setTogglePlayer(config.read<int>("togglePlayer"));


    gNew->setWidthScr(config.read<int>("screen_w"));
    gNew->setHeightScr(config.read<int>("screen_h"));
    gNew->setDepthScr(config.read<int>("screen_d"));

    gNew->setRedRGB(config.read<int>("red_rgb"));
    gNew->setGreenRGB(config.read<int>("green_rgb"));
    gNew->setBlueRGB(config.read<int>("blue_rgb"));
    gNew->setDDBuffer(config.read<int>("ddbuffer"));

    gNew->setSoundFrec(config.read<int>("sound_frecuency"));
    gNew->setSoundFormat(config.read<int>("sound_format"));
    gNew->setSoundChannel(config.read<int>("sound_channel"));
    gNew->setSoundSampleSize(config.read<int>("sound_sample"));

    //set keys first player
    gNew->setKEYUP_1(config.read<int>("up_1"));
    gNew->setKEYDOWN_1(config.read<int>("down_1"));
    gNew->setKEYLEFT_1(config.read<int>("left_1"));
    gNew->setKEYRIGHT_1(config.read<int>("right_1"));
    gNew->setKEYSHOOT_1(config.read<int>("fire_1"));
    gNew->setKEYCHGWEAPON_1(config.read<int>("changeweapon_1"));
    gNew->setKEYRETURN_1(config.read<int>("return_1"));
    gNew->setKEYESC_1(config.read<int>("esc_1"));
    gNew->setKEYEXIT_1(config.read<int>("exit_1"));

    //set keys second player
    gNew->setKEYUP_2(config.read<int>("up_2"));
    gNew->setKEYDOWN_2(config.read<int>("down_2"));
    gNew->setKEYLEFT_2(config.read<int>("left_2"));
    gNew->setKEYRIGHT_2(config.read<int>("right_2"));
    gNew->setKEYSHOOT_2(config.read<int>("fire_2"));
    gNew->setKEYCHGWEAPON_2(config.read<int>("changeweapon_2"));
    gNew->setKEYRETURN_2(config.read<int>("return_2"));
    gNew->setKEYESC_2(config.read<int>("esc_2"));
    gNew->setKEYEXIT_2(config.read<int>("exit_2"));

    //set keys third player
    gNew->setKEYUP_3(config.read<int>("up_3"));
    gNew->setKEYDOWN_3(config.read<int>("down_3"));
    gNew->setKEYLEFT_3(config.read<int>("left_3"));
    gNew->setKEYRIGHT_3(config.read<int>("right_3"));
    gNew->setKEYSHOOT_3(config.read<int>("fire_3"));
    gNew->setKEYCHGWEAPON_3(config.read<int>("changeweapon_3"));
    gNew->setKEYRETURN_3(config.read<int>("return_3"));
    gNew->setKEYESC_3(config.read<int>("esc_3"));
    gNew->setKEYEXIT_3(config.read<int>("exit_3"));

    //set keys fourth player
    gNew->setKEYUP_4(config.read<int>("up_4"));
    gNew->setKEYDOWN_4(config.read<int>("down_4"));
    gNew->setKEYLEFT_4(config.read<int>("left_4"));
    gNew->setKEYRIGHT_4(config.read<int>("right_4"));
    gNew->setKEYSHOOT_4(config.read<int>("fire_4"));
    gNew->setKEYCHGWEAPON_4(config.read<int>("changeweapon_4"));
    gNew->setKEYRETURN_4(config.read<int>("return_4"));
    gNew->setKEYESC_4(config.read<int>("esc_4"));
    gNew->setKEYEXIT_4(config.read<int>("exit_4"));

    gNew->setFLAGMOUSE(config.read<int>("flagmouse"));

    //2015-10-31 JALCARAZ OJO! Debo hacer copias de los objetos std::string antes de asignarlos para evitar comportamientos "mutables"

    const std::string datatitle = (const std::string)config.read<std::string>("titleEng");
    char* c_datatitle_cpy = new char[datatitle.length()+1];
    strcpy(c_datatitle_cpy, datatitle.c_str());
    //memcpy(c_datatitle_cpy, datatitle.c_str(), datatitle.length()+1);
    gNew->setTitle(c_datatitle_cpy);

    gNew->setFramerrate(config.read<int>("framerrate"));

    gNew->setInitialState(config.read<int>("initialState"));
    gNew->setActPlayer(config.read<int>("initialPlayer"));

    gNew->setDelayBWShoot(config.read<int>("delaybwshoot"));
    gNew->setDelayBWEnem(config.read<int>("delaybwenem"));

    INFOLOG("GLInit::processGlobalFileInit --> GLOBAL PARAMETERS LOADED");


}

void GLInit::printGlobalFileParams(){

    DEBUGLOG("GLInit::printGlobalFileParams -->  PRINT GLOBAL INI");

    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  TITLE:           (%s)",gNew->getTitle());

    DEBUGLOG("GLInit::printGlobalFileParams --> PROFILE PARAMS:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  LOG LEVEL:       (%d)",gNew->getLog());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  LOG CHANNEL:     (%d)",gNew->getTypeLog());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  PROFILE SWITCH:  (%d)",gNew->getProfType());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  TAS SWITCH:      (%d)",gNew->getTasType());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  TOGGLE COLL:     (%d)",gNew->getToggleColl());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  TOGGLE PLAYER:   (%d)",gNew->getTogglePlayer());

    DEBUGLOG("GLInit::printGlobalFileParams --> SCREEN PARAMS:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SCREEN W:        (%d)",gNew->getWidthScr());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SCREEN H:        (%d)",gNew->getHeightScr());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  RED__RGB:        (%d)",gNew->getRedRGB());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  GREENRGB:        (%d)",gNew->getGreenRGB());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  BLUE_RGB:        (%d)",gNew->getBlueRGB());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  D.D.BSCR:        (%d)",gNew->getDDBuffer());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SCREEN D:        (%d)",gNew->getDepthScr());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  FRAMERRATE:      (%d)",gNew->getFramerrate());

    DEBUGLOG("GLInit::printGlobalFileParams --> SOUND PARAMS:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  S.FREC:          (%d)",gNew->getSoundFrec());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  S.FORM:          (%d)",gNew->getSoundFormat());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  S.CHAN:          (%d)",gNew->getSoundChannel());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  S.SAMPLE:        (%d)",gNew->getSoundSampleSize());

    //hay un maximo de cuatro jugadores por nodo.
    DEBUGLOG("GLInit::printGlobalFileParams --> KEYS FIRST PLAYER:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY UP     :     (%d)",gNew->getKEYUP_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY DOWN   :     (%d)",gNew->getKEYDOWN_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY LEFT   :     (%d)",gNew->getKEYLEFT_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RIGHT  :     (%d)",gNew->getKEYRIGHT_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SHOOT      :     (%d)",gNew->getKEYSHOOT_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  CHGWEAPON  :     (%d)",gNew->getKEYCHGWEAPON_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY EXIT   :     (%d)",gNew->getKEYEXIT_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY ESC    :     (%d)",gNew->getKEYESC_1());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RETURN :     (%d)",gNew->getKEYRETURN_1());

    DEBUGLOG("GLInit::printGlobalFileParams --> KEYS SECOND PLAYER:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY UP     :     (%d)",gNew->getKEYUP_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY DOWN   :     (%d)",gNew->getKEYDOWN_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY LEFT   :     (%d)",gNew->getKEYLEFT_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RIGHT  :     (%d)",gNew->getKEYRIGHT_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SHOOT      :     (%d)",gNew->getKEYSHOOT_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  CHGWEAPON  :     (%d)",gNew->getKEYCHGWEAPON_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY EXIT   :     (%d)",gNew->getKEYEXIT_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY ESC    :     (%d)",gNew->getKEYESC_2());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RETURN :     (%d)",gNew->getKEYRETURN_2());

    DEBUGLOG("GLInit::printGlobalFileParams --> KEYS THIRD PLAYER:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY UP     :     (%d)",gNew->getKEYUP_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY DOWN   :     (%d)",gNew->getKEYDOWN_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY LEFT   :     (%d)",gNew->getKEYLEFT_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RIGHT  :     (%d)",gNew->getKEYRIGHT_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SHOOT      :     (%d)",gNew->getKEYSHOOT_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  CHGWEAPON  :     (%d)",gNew->getKEYCHGWEAPON_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY EXIT   :     (%d)",gNew->getKEYEXIT_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY ESC    :     (%d)",gNew->getKEYESC_3());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RETURN :     (%d)",gNew->getKEYRETURN_3());

    DEBUGLOG("GLInit::printGlobalFileParams --> KEYS FOURTH PLAYER:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY UP     :     (%d)",gNew->getKEYUP_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY DOWN   :     (%d)",gNew->getKEYDOWN_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY LEFT   :     (%d)",gNew->getKEYLEFT_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RIGHT  :     (%d)",gNew->getKEYRIGHT_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  SHOOT      :     (%d)",gNew->getKEYSHOOT_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  CHGWEAPON  :     (%d)",gNew->getKEYCHGWEAPON_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY EXIT   :     (%d)",gNew->getKEYEXIT_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY ESC    :     (%d)",gNew->getKEYESC_4());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  KEY RETURN :     (%d)",gNew->getKEYRETURN_4());

    DEBUGLOG("GLInit::printGlobalFileParams --> ADVANCED INPUT CONTROL (KEY+MOUSE):");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  FLAGMOUSE (ON/OFF) :     (%d)",gNew->getFLAGMOUSE());

    DEBUGLOG("GLInit::printGlobalFileParams --> VAR GENERAL GAME BEHAVIOUR:");
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  INIT STATE :     (%d)",gNew->getInitialState());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  ACT PLAYER :     (%d)",gNew->getActPlayer());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  DELAYSHOOT :     (%d) frames",gNew->getDelayBWShoot());
    DEBUGLOGPONE("GLInit::printGlobalFileParams -->  DELAYENEMY :     (%d) frames",gNew->getDelayBWEnem());


    DEBUGLOG("GLInit::printGlobalFileParams -->  PRINT GLOBAL FIN");


}
