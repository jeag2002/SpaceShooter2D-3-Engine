/*
20151014.0.001.0 JALCARAZ

GlobalNew
Redefinicion del gestor de variables globales.

*/


#ifndef GLOBALNEW_H_INCLUDED
#define GLOBALNEW_H_INCLUDED

//DECLARATIONS
//DECLARATION OF STATES
//TYPE OF STATE: SPLASH(0), MENU(1), LEVEL(2), EXIT(3)
//VALUE OF STATE: CREATION(0), START(1), UPDATE(2), STOP(3), RUN(4), DELETE(5)

#define DEBUG_LOG 1

#define IDLE_DIRECTION -1

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UPRIGTH 4
#define UPLEFT 5
#define DOWNRIGTH 6
#define DOWNLEFT 7
#define DIFFMOUSE 17            //cambio diferencial de ejes, raton (cursor)

#define SHOOT 8                 //SPACE  -> DISPARO
#define CHGWEAPON 9             //LALT   -> CAMBIO WEAPON
#define ESC 10                  //RALT   -> SALIR DE LA APLICACION
#define RESUME 11               //LCTRL  -> RESUME
#define QUIT 12                 //ESC    -> SALIR AL MENU
#define NEXT 13                 //INDICA AL NUEVO NIVEL
#define END 14                  //INDICA FINAL DEL JUEGO (CONTROLADO POR LOGICA)
#define TOGGLE 15               //INDICA CAMBIO DEL JUGADOR
#define TOGGLE_COLL 16          //PRESENTA MAPA COLISIONES
#define ERR_MSG 98
#define NO_MSG 99

#define KEY_ON 1
#define KEY_OFF 0

#define KEY_ON_COLL 1
#define KEY_ON_LIGHT 2
#define KEY_ON_COLL_LIGHT 3

#define MOUSE_ON 1
#define MOUSE_OFF 0

#define SWITCH_ON 1
#define SWITCH_OFF 0

#define IDLE_STATE -1

#define TYPE_STATE_SPLASH   0
#define TYPE_STATE_MENU     1
#define TYPE_STATE_LEVEL    2
#define TYPE_STATE_EXIT     3

#define VALUE_STATE_CREATION 0
#define VALUE_STATE_START    1
#define VALUE_STATE_RUN      2
#define VALUE_STATE_UPDATE   3
#define VALUE_STATE_STOP     4
#define VALUE_STATE_DELETE   5
#define VALUE_STATE_FINAL    6

//MENSAJES ENTRE ESTADOS
#define TO_START    0   //inicializa el estado
#define TO_RUN      1   //hace funcionar el estado
#define TO_STOP     2   //para el estado (ESC)              ==> TO_STOP + NEXT STATE + RETURN STATE
#define TO_UPDATE   3   //actualiza el estado actual.
#define TO_NEXT     4   //mueve al estado siguiente         ==> TO_NEXT + NEXT STATE
#define TO_FINISH   6   //finaliza el juego
#define TO_ERROR    7   //ha habido un error interno

#define TO_EVENT    8   //detectado evento de teclado, raton, etc. (Procesado)  ==> TO_EVENT + ID_EVENT (Teclado/Raton)


//DEFINICION DE TIPOS DE ENTITIES
#define ENTITY_TYPE_TILE 0              //TILE
#define ENTITY_TYPE_ACTOR 1             //ACTOR (JUGADOR, ENEMIGO)
#define ENTITY_TYPE_LIGHT 2             //LIGHT (LUZ)
#define ENTITY_TYPE_PART 3              //PARTICLE (MOTOR DE PARTICULAS)
#define ENTITY_TYPE_SWITCH_ACT 4        //PARTE ACTIVA DEL SWITCH
#define ENTITY_TYPE_SWITCH_PAS 41       //PARTE PASIVA DEL SWITCH
#define ENTITY_TYPE_PORTAL_UP 5         //ASCENSOR, RAMPA, TELETRANSPORTADOR (arriba)
#define ENTITY_TYPE_PORTAL_DOWN 51      //ASCENSOR, RAMPA, TELETRANSPORTADOR (abajo)
#define ENTITY_TYPE_PORTAL_UPDOWN 52    //ASCENSOR, RAMPA, TELETRANSPORTADOR (arriba-abajo)
#define ENTITY_TYPE_EXIT 6              //SALIDA DEL NIVEL
#define ENTITY_TYPE_EXIT_STOP 7         //PAUSA DEL NIVEL
#define ENTITY_TYPE_ITEM 8              //ITEM (key,weapon,ammo)
#define ENTITY_TYPE_BLOCK 9             //REACTIVE TILE
#define ENTITY_TYPE_GENERATOR 10        //GENERADOR ENEMIGOS

//EN ESTUDIO
#define ENTITY_TYPE_BEAM 11             //EFECTO DISPARO SIN PARTICULAS
#define ENTITY_TYPE_HAL  12             //HALOS SOBRE JUGADOR.

#define MAX_NUM_PLAYERS 4

//DEFINICION TILE SIZE
#define DEFAULT_TILE_SIZE 32


//DEFINICION DE TIPOS DE ENTITIES
/*
#define ENTITY_TYPE_TILE 0        //elemento estático. TIPO: TILE
#define ENTITY_TYPE_PLAY 1        //elemento dinámico, TIPO: JUGADOR
#define ENTITY_TYPE_ENEM 2        //elemento dinámioc, TIPO: ENEMIGO
#define ENTITY_TYPE_PORT 3        //elemento dinámico, TIPO: PORTAL
#define ENTITY_TYPE_EXIT 4        //elemento dinámico, TIPO: EXIT
#define ENTITY_TYPE_SWITCH_A 51   //elemento dinámico, TIPO: SWITCH_ACTIVO (elemento activo del trigger, manda la accion)
#define ENTITY_TYPE_SWITCH_B 52   //elemento dinámico, TIPO: SWITCH_PASIVO (elemento pasivo del trigger, ejecuta la accion)
#define ENTITY_TYPE_SLOPE 6       //elemento dinámico, TIPO: RAMPA
#define ENTITY_TYPE_PORTAL_A 71   //elemento dinámioo, TIPO: POSICION_INICIAL TELETRANSPORTADOR
#define ENTITY_TYPE_PORTAL_B 72   //elemento dinámioo, TIPO: POSICION_FINAL TELETRANSPORTADOR
#define ENTITY_TYPE_BLOCK 8       //elemento dinámico, TIPO: MURO DESTRUIBLE

//ENTITIES DISPAROS,EFECTOS, ETC
#define ENTITY_TYPE_SHOOT 9       //elemento donámico, TIPO: EFECTO DISPARO
#define ENTITY_TYPE LIGTH_SPOT 10 //elemento dinámico, TIPO: FUENTE DE LUZ
#define ENTITY_TYPE_SMOKE 11      //elemento dinamico, TIPO: RASTRO DE HUMO
#define ENTITY_TYPE_EXPLOSION 12  //elemento dinamico, TIPO: EXPLOSION
#define ENTITY_TYPE_LIGTH_BEAM 13 //elemento dinamico, TIPO: HAZ DE LUZ (?)
#define ENTITY_TYPE_HALO 14       //elemento dinamico, TIPO: HALO
#define ENTITY_TYPE_ITEM 15       //elemento dinamico, TIPO: ITEM (Bonus)
//definicion de typedef

#define ENTITY_TYPE_OTHER 16      //elemento dinamico, TIPO: DESCONOCIDO
*/

//2015-JALCARAZ. Definicion de nuevas estructuras
/////////////////////////////////////////////////////////////

//Ventana a mostrar en el screen
typedef struct{
    //posicion de los tiles a mostrar
    int x_inf;
    int y_inf;
    int x_sup;
    int y_sup;

}screenSize;

//Vertice de una estructura
typedef struct{
    float rel_pos_x;
    float rel_pos_y;
}relMovement;


//Contorno de una estructura.
typedef struct{
    relMovement nodes[20];
    int num_nodes;
    int coll;
}relMovementPol;


//Definicion de imagen
typedef struct{
    unsigned int imageID;
    float widht;
    float height;
    bool parallax;
    char *path_to_image;
    char *typeImg;
}ImageData;


//Referencia a otra entidad
typedef struct{
    unsigned int idEntity;
    int level;
    float x_diff_pos;
    float y_diff_pos;
    float rotate_pos;
}EntityRef;


/////////////////////////////////////////////////////////////

class GlobalNew{

public:

GlobalNew(){

    //tamanyo del screen
    widthScr = 640;
    heightScr = 480;
    depthScr = 16;


    //Parametros profiles
    log = 0;                //flag logs (nivel de logs)
    typeLog = 0;            //0->file; 1->file/cout
    profType = 0;           //0/1 -> switch on/off profile
    tasType = 0;            //0/1 -> switch on/off movement

    //framerrate
    framerrate = 60;

    //toggleColl
    toggleColl = 0;
    togglePlayer = 0;

    initialState = 1;
    delaybwshoot = 2;
    delaybwenem = 20;


    scriptDefinitionPath = "./data/script.ini";
    soundDefinitionPath = "./data/sounds.ini";
    stateDefinitionPath = "./data/stateDef.ini";
    imageDefinitionPath = "./data/imageDef.ini";
    //entityDefinitionPath = "./data/components2D_Final.ini";
    entityDefinitionPath = "./data/components2D.ini";
    typewriteDefinitionPath = "./data/tiff.ini";
    animationDefinitionPath = "./data/animationDef.ini";
    particleDefinitionPath = "./data/particleDef.ini";
    lightDefinitionPath = "./data/lights.ini";

    globalPath = "./data/global.ini";

    logPath = "./data/logs/Sin2DEng.log";
    ProfilePath = "./data/logs/ProfileEng.log";



    sinistarenginetitle = "SinistarEngine.0.001.01";
}


~GlobalNew(){

   //tamanyo del screen
    widthScr = 0;
    heightScr = 0;
    depthScr = 0;

    //Parametros profiles
    log = 0;                //flag logs (nivel de logs)
    typeLog = 0;            //0->file; 1->file/cout
    profType = 0;           //0/1 -> switch on/off profile
    tasType = 0;            //0/1 -> switch on/off movement

    //framerrate
    framerrate = 0;

    toggleColl = 0;
    togglePlayer = 0;

    //state
    initialState = 1;
    delaybwshoot = 0;
    delaybwenem = 0;

    scriptDefinitionPath = "";
    soundDefinitionPath = "";
    stateDefinitionPath = "";
    imageDefinitionPath = "";
    entityDefinitionPath = "";
    typewriteDefinitionPath = "";

    animationDefinitionPath = "";
    particleDefinitionPath = "";
    lightDefinitionPath  = "";

    globalPath = "";

    logPath = "";
    ProfilePath = "";


    sinistarenginetitle = "";
}

//GETS-SETS
////////////////////////////////////////////////////////////////////////

//widthScr => ancho de la pantalla a mostrar
int getWidthScr(){return widthScr;}
void setWidthScr(int _widthScr){widthScr = _widthScr;}

//heightScr => alto de la pantalla a mostrar
int getHeightScr(){return heightScr;}
void setHeightScr(int _heightScr){heightScr = _heightScr;}

//tamanyo del pixel a mostrar
int getDepthScr(){return depthScr;}
void setDepthScr(int _depthScr){depthScr = _depthScr;}

//RED
int getRedRGB(){return red_rgb;}
void setRedRGB(int _red_rgb){red_rgb = _red_rgb;}

//GREEN
int getGreenRGB(){return green_rgb;}
void setGreenRGB(int _green_rgb){green_rgb = _green_rgb;}

//BLUE
int getBlueRGB(){return blue_rgb;}
void setBlueRGB(int _blue_rgb){blue_rgb = _blue_rgb;}

//DDBUFFER
int getDDBuffer(){return ddbuffer;}
void setDDBuffer(int _ddbuffer){ddbuffer = _ddbuffer;}


//SOUND
////////////////////////////////////////////////////////////////////////////
int getSoundFrec(){return sound_frecuency;}
void setSoundFrec(int _sound_frecuency){sound_frecuency = _sound_frecuency;}

int getSoundFormat(){return sound_format;}
void setSoundFormat(int _sound_format){sound_format = _sound_format;}

int getSoundChannel(){return sound_channel;}
void setSoundChannel(int _sound_channel){sound_channel = _sound_channel;}

int getSoundSampleSize(){return sound_sample_size;}
void setSoundSampleSize(int _sound_sample_size){sound_sample_size = _sound_sample_size;}
////////////////////////////////////////////////////////////////////////////

//obtener el flag del logs
int getLog(){return log;}
void setLog(int _log){log = _log;}

int getTypeLog(){return typeLog;}
void setTypeLog(int _typeLog){typeLog = _typeLog;}

//->profile
int getProfType(){return profType;}
void setProfType(int _profType){profType = _profType;}

//->activate Tas
int getTasType(){return tasType;}
void setTasType(int _tasType){tasType = _tasType;}

int getToggleColl(){return toggleColl;}
void setToggleColl(int _toggleColl){toggleColl = _toggleColl;}

int getTogglePlayer(){return togglePlayer;}
void setTogglePlayer(int _togglePlayer){togglePlayer = _togglePlayer;}

//framerrate
int getFramerrate(){return framerrate;}
void setFramerrate(int _framerrate){framerrate = _framerrate;}

//init State
int getInitialState(){return initialState;}
void setInitialState(int _initialState){initialState = _initialState;}

//actual player
int getActPlayer(){return this->actPlayer;}
void setActPlayer(int _actPlayer){actPlayer = _actPlayer;}

//delays
int getDelayBWShoot(){return this->delaybwshoot;}
void setDelayBWShoot(int _delaybwshoot){delaybwshoot = _delaybwshoot;}

int getDelayBWEnem(){return this->delaybwenem;}
void setDelayBWEnem(int _delaybwenem){delaybwenem = _delaybwenem;}

//ficheros globales. Estados, Imagenes, Sonidos, Def Entidades, Datos globales.
char *getScriptDefinitionPath(){return scriptDefinitionPath;}       //->scripts (de momento no se utilizará)
char *getSoundDefinitionPath(){return soundDefinitionPath;}         //->sonidos (de momento no se utilizará)
char *getStateDefinitionPath(){return stateDefinitionPath;}         //->estados
char *getImageDefinitionPath(){return imageDefinitionPath;}         //->imagenes
char *getEntityDefinitionPath(){return entityDefinitionPath;}       //->definiciones
char *getTypewriteDefinitionPath(){return typewriteDefinitionPath;} //->tiff
char *getGlobalPath(){return globalPath;}                           //->datos globales.

char *getAnimationPath(){return animationDefinitionPath;}           //->path de animaciones (de momento no se utilizará)
char *getAnimationParticlesPath(){return particleDefinitionPath;}   //->path motor de particulas (de momento no se utilizará)
char *getLigthDefinitionPath(){return lightDefinitionPath;}         //->path definicion de luces.

char *getLogPath(){return logPath;}
char *getProfilePath(){return ProfilePath;}

char *getTitle(){return sinistarenginetitle;}                       //->titulo ventana
void setTitle(char *_title){sinistarenginetitle = _title;}

//KEYS (UP,DOWN,LEFT,RIGHT,FIRE,CHANGEFIRE,ESC)
////////////////////////////////////////////////////////////////////////
int getKEYUP_1(){return key_up_1;}
void setKEYUP_1(int _key_up){key_up_1 = _key_up;}
int getKEYDOWN_1(){return key_down_1;}
void setKEYDOWN_1(int _key_down){key_down_1 = _key_down;}
int getKEYLEFT_1(){return key_left_1;}
void setKEYLEFT_1(int _key_left){key_left_1 = _key_left;}
int getKEYRIGHT_1(){return key_right_1;}
void setKEYRIGHT_1(int _key_right){key_right_1 = _key_right;}
int getKEYSHOOT_1(){return key_shoot_1;}
void setKEYSHOOT_1(int _key_shoot){key_shoot_1 = _key_shoot;}
int getKEYCHGWEAPON_1(){return key_chgweapon_1;}
void setKEYCHGWEAPON_1(int _key_chgweapon){key_chgweapon_1 = _key_chgweapon;}
int getKEYESC_1(){return key_esc_1;}
void setKEYESC_1(int _key_esc){key_esc_1 = _key_esc;}
int getKEYRETURN_1(){return key_return_1;}
void setKEYRETURN_1(int _key_return){key_return_1 = _key_return;}
int getKEYEXIT_1(){return key_exit_1;}
void setKEYEXIT_1(int _key_exit){key_exit_1 = _key_exit;}

int getKEYUP_2(){return key_up_2;}
void setKEYUP_2(int _key_up){key_up_2 = _key_up;}
int getKEYDOWN_2(){return key_down_2;}
void setKEYDOWN_2(int _key_down){key_down_2 = _key_down;}
int getKEYLEFT_2(){return key_left_2;}
void setKEYLEFT_2(int _key_left){key_left_2 = _key_left;}
int getKEYRIGHT_2(){return key_right_2;}
void setKEYRIGHT_2(int _key_right){key_right_2 = _key_right;}
int getKEYSHOOT_2(){return key_shoot_2;}
void setKEYSHOOT_2(int _key_shoot){key_shoot_2 = _key_shoot;}
int getKEYCHGWEAPON_2(){return key_chgweapon_2;}
void setKEYCHGWEAPON_2(int _key_chgweapon){key_chgweapon_2 = _key_chgweapon;}
int getKEYESC_2(){return key_esc_2;}
void setKEYESC_2(int _key_esc){key_esc_2 = _key_esc;}
int getKEYRETURN_2(){return key_return_2;}
void setKEYRETURN_2(int _key_return){key_return_2 = _key_return;}
int getKEYEXIT_2(){return key_exit_2;}
void setKEYEXIT_2(int _key_exit){key_exit_2 = _key_exit;}

int getKEYUP_3(){return key_up_3;}
void setKEYUP_3(int _key_up){key_up_3 = _key_up;}
int getKEYDOWN_3(){return key_down_3;}
void setKEYDOWN_3(int _key_down){key_down_3 = _key_down;}
int getKEYLEFT_3(){return key_left_3;}
void setKEYLEFT_3(int _key_left){key_left_3 = _key_left;}
int getKEYRIGHT_3(){return key_right_3;}
void setKEYRIGHT_3(int _key_right){key_right_3 = _key_right;}
int getKEYSHOOT_3(){return key_shoot_3;}
void setKEYSHOOT_3(int _key_shoot){key_shoot_3 = _key_shoot;}
int getKEYCHGWEAPON_3(){return key_chgweapon_3;}
void setKEYCHGWEAPON_3(int _key_chgweapon){key_chgweapon_3 = _key_chgweapon;}
int getKEYESC_3(){return key_esc_3;}
void setKEYESC_3(int _key_esc){key_esc_3 = _key_esc;}
int getKEYRETURN_3(){return key_return_3;}
void setKEYRETURN_3(int _key_return){key_return_3 = _key_return;}
int getKEYEXIT_3(){return key_exit_3;}
void setKEYEXIT_3(int _key_exit){key_exit_3 = _key_exit;}

int getKEYUP_4(){return key_up_4;}
void setKEYUP_4(int _key_up){key_up_4 = _key_up;}
int getKEYDOWN_4(){return key_down_4;}
void setKEYDOWN_4(int _key_down){key_down_4 = _key_down;}
int getKEYLEFT_4(){return key_left_4;}
void setKEYLEFT_4(int _key_left){key_left_4 = _key_left;}
int getKEYRIGHT_4(){return key_right_4;}
void setKEYRIGHT_4(int _key_right){key_right_4 = _key_right;}
int getKEYSHOOT_4(){return key_shoot_4;}
void setKEYSHOOT_4(int _key_shoot){key_shoot_4 = _key_shoot;}
int getKEYCHGWEAPON_4(){return key_chgweapon_4;}
void setKEYCHGWEAPON_4(int _key_chgweapon){key_chgweapon_4 = _key_chgweapon;}
int getKEYESC_4(){return key_esc_4;}
void setKEYESC_4(int _key_esc){key_esc_4 = _key_esc;}
int getKEYRETURN_4(){return key_return_4;}
void setKEYRETURN_4(int _key_return){key_return_4 = _key_return;}
int getKEYEXIT_4(){return key_exit_4;}
void setKEYEXIT_4(int _key_exit){key_exit_4 = _key_exit;}
////////////////////////////////////////////////////////////////////////

int getFLAGMOUSE(){return flag_mouse;}
void setFLAGMOUSE(int _flag_mouse){flag_mouse = _flag_mouse;}


/*
char *getTypeState(int type){

    if (type == TYPE_STATE_SPLASH){
        return "SPLASH";
    }else if (type == TYPE_STATE_MENU){
        return "MENU";
    }else if (type == TYPE_STATE_LEVEL){
        return "LEVEL";
    }else if (type == TYPE_STATE_EXIT){
        return "EXIT";
    }else{
        return "UNKNOWN";
    }
}
*/

/*
#define VALUE_STATE_CREATION 0
#define VALUE_STATE_START    1
#define VALUE_STATE_RUN      2
#define VALUE_STATE_UPDATE   3
#define VALUE_STATE_STOP     4
#define VALUE_STATE_DELETE   5
*/


/*
char *getState(int state){

    if (state == VALUE_STATE_CREATION){
        return "CREATION";
    }else if (state == VALUE_STATE_START){
        return "START";
    }else if (state == VALUE_STATE_RUN){
        return "RUN";
    }else if (state == VALUE_STATE_UPDATE){
        return "UPDATE";
    }else if (state == VALUE_STATE_STOP){
        return "STOP";
    }else if (state == VALUE_STATE_DELETE){
        return "DELETE";
    }else{
        return "UNKNOWN";
    }
}
*/

/*
bool equalsRelMovementPol(const relMovementPol p1, const relMovementPol p2){

    if (p1.num_nodes != p2.num_nodes){
        return false;
    }else{
        bool res = true;
        for(int i=0; i<p1.num_nodes; i++){
            res = res && ((p1.nodes[i].rel_pos_x == p2.nodes[i].rel_pos_x) && (p1.nodes[i].rel_pos_y == p2.nodes[i].rel_pos_y));
        }
        return res;
    }
}
*/

////////////////////////////////////////////////////////////////////////

private:

//declaracion de variables globales del sistema
//datos generales.

int widthScr;      //ancho del screen
int heightScr;     //alto del screen
int depthScr;      //profundidad de pantalla

int red_rgb;       //red rgb
int green_rgb;     //green rgb
int blue_rgb;      //blue rgb

int ddbuffer;      //dd buffer

//set logs
int log;                //logs
int typeLog;            //tipo de logs
int profType;           //0/1 -> switch on/off profile
int tasType;            //0/1 -> switch on/off movement

//set audio
int sound_frecuency;    //frecuencia
int sound_format;       //formato (0=por defecto)
int sound_channel;      //canales de sonido (1=mono, 2=stereo)
int sound_sample_size;

//set framerrate
int framerrate;

//toggle Coll
int toggleColl;
//activado flag cambio jugador (debug purposes)
int togglePlayer;


//definicion del estado inicial.
int initialState;   //definicion del estado inicial
int actPlayer;      //jugador actual (1,2,3,4)

//definition
int delaybwshoot;
int delaybwenem;

//estos valores siempre seran los mismos
char *scriptDefinitionPath;
char *soundDefinitionPath;
char *stateDefinitionPath;
char *imageDefinitionPath;
char *entityDefinitionPath;
char *typewriteDefinitionPath;
char *lightDefinitionPath;
char *globalPath;

//dos nuevos mantenimientos.
char *animationDefinitionPath;
char *particleDefinitionPath;

//path de logs; path performing.
char *logPath;
char *ProfilePath;

//obtencion de la ventana.
char *sinistarenginetitle;

//identficador de elementos de teclado
int key_up_1;
int key_down_1;
int key_left_1;
int key_right_1;
int key_shoot_1;
int key_chgweapon_1;
int key_esc_1;
int key_return_1;
int key_exit_1;

int key_up_2;
int key_down_2;
int key_left_2;
int key_right_2;
int key_shoot_2;
int key_chgweapon_2;
int key_esc_2;
int key_return_2;
int key_exit_2;

int key_up_3;
int key_down_3;
int key_left_3;
int key_right_3;
int key_shoot_3;
int key_chgweapon_3;
int key_esc_3;
int key_return_3;
int key_exit_3;

int key_up_4;
int key_down_4;
int key_left_4;
int key_right_4;
int key_shoot_4;
int key_chgweapon_4;
int key_esc_4;
int key_return_4;
int key_exit_4;


//activado mouse?
int flag_mouse;





};

//extern GlobalNew *globalNewD;

#endif // GLOBALNEW_H_INCLUDED
