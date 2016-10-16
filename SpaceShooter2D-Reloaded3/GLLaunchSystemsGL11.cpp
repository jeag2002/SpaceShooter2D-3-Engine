#include "GLLaunchSystemsGL11.h"

//--> inicializa el entorno OPENGLES+SDL2.0
 void GLLaunchSystemsGL11::initOpenGLESSystems(int major, int minor){

    //Arranque motor SDL 2.0
    if  (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0){
        WARNLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ENTORNO SDL VIDEO, AUDIO, JOYSTICK NO INICIALIZADO %s",SDL_GetError());
        exit(-1);
    }else{
        DEBUGLOG("GLLaunchSystemsGL11::initOpenGLESSystems --> SDL 2.0 ENGINE CONFIGURED");
    }

    //Arranque motor IMG PNG/JPG
    int imgFlags = IMG_INIT_PNG || IMG_INIT_JPG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        WARNLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems -->  ERROR CARGA SOPORTE IMAGENES PNG/JPG: %s", IMG_GetError() );
        exit(-1);
    }else{
        DEBUGLOG("GLLaunchSystemsGL11::initOpenGLESSystems --> SDL IMAGE 2.0 ENGINE CONFIGURED");
    }

    //Arranque motor TrueType
    if( TTF_Init() != 0 ){
        WARNLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR CARGA MOTOR TRUETYPE %s", TTF_GetError() );
        exit(-1);
    }else{
        DEBUGLOG("GLLaunchSystemsGL11::initOpenGLESSystems --> SDL TTF 2.0 ENGINE CONFIGURED");
    }

    //Arranque motor Audio
    if( Mix_OpenAudio( gNew->getSoundFrec(), MIX_DEFAULT_FORMAT, gNew->getSoundChannel(), gNew->getSoundSampleSize() ) != 0 ){
        WARNLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR CARGA MOTOR SONIDO %s", Mix_GetError() );
        exit(-1);
    }else{
        DEBUGLOG("GLLaunchSystemsGL11::initOpenGLESSystems --> SDL MIX/AUDIO 2.0 ENGINE CONFIGURED");
    }

	int status = SDL_GetDesktopDisplayMode(0, &mode);

	if (status<0){
        WARNLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR AL CAPTURAR EL MODO NATIVO DE PANTALLA %s",SDL_GetError());
        exit(-1);
	}else{
	    Uint32 f;
	    f = mode.format;
        DEBUGLOGPFOUR("GLLaunchSystemsGL11::initOpenGLESSystems --> DISPLAY(0) (%d x %d) @ %i bpp %s", mode.w, mode.h, SDL_BITSPERPIXEL(f), SDL_GetPixelFormatName(f));
	}

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, gNew->getDDBuffer());
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, gNew->getRedRGB() );
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, gNew->getGreenRGB());
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, gNew->getBlueRGB() );
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, gNew->getDepthScr());

    //if ((major != 0) && (minor != 0)) {
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
    //    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
    //}

    window=SDL_CreateWindow(gNew->getTitle(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            gNew->getWidthScr(),
            gNew->getHeightScr(),
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (window==0){
        INFOLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR AL CREAR LA VENTANA: %s", SDL_GetError());
        exit(-1);
    }

    context=SDL_GL_CreateContext(window);

    if (context==NULL){
        INFOLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR AL CREAR EL CONTEXTO OPENGL ES: %s", SDL_GetError());
        exit(-1);
    }

    status=SDL_GL_MakeCurrent(window, context);

    if (status<0){
        INFOLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> ERROR AL ASOCIAR EL ACTUAL CONTEXTO OPENGL ES: %s", SDL_GetError());
        exit(-1);
    }

    SDL_GL_SetSwapInterval(1);

    char *vendor = (char *)glGetString(GL_VENDOR);
    if (vendor != NULL){DEBUGLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> OPENGL ES 1.1 VENDOR [%s]",vendor);}

    char* version = (char *)glGetString(GL_VERSION);
    if (version != NULL){DEBUGLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> OPENGL ES 1.1 VERSION [%s]",version);}

    char* renderer = (char *)glGetString(GL_RENDERER);
    if (renderer != NULL){DEBUGLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> OPENGL ES 1.1 RENDER VERSION [%s]",renderer);}

    char* extensionList = (char *)glGetString(GL_EXTENSIONS);
    if (extensionList != NULL){
        char *data = "";
        data = strtok(extensionList, " ");

        while(data != NULL){
            DEBUGLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> OPENGL ES 1.1 SUPPORTED EXTENSION [%s]", data);
            data = strtok(NULL, " ");
        }
    }

    INFOLOG("GLLaunchSystemsGL11::initOpenGLESSystems --> OPENGL ES 1.1 CONFIGURED");

    DEBUGLOGPONE("GLLaunchSystemsGL11::initOpenGLESSystems --> CONFIGURE ACT PLAYER [%d]", gNew->getActPlayer());
}



void GLLaunchSystemsGL11::initWindowsGL11()
{

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);

}

void GLLaunchSystemsGL11::setPerspectiveOrthoGL11()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrthof(0.0f, float(gNew->getWidthScr()), float(gNew->getHeightScr()),0.0f, -1.0f, 1.0f );



}


void GLLaunchSystemsGL11::swapPerspectiveOpenGLES(){

}

void GLLaunchSystemsGL11::handleMouseMotion(int _x, int _y){
     EventMsg *msg;

     if (gNew->getFLAGMOUSE() == KEY_ON){
         msg = new EventMsg(DIFFMOUSE,KEY_ON,float(_x),float(_y));
         DEBUGLOGPTHREE("GLLaunchSystemsGL11::handleMouseMotion -- [%s] <x:%f,y:%f>",Utils::getTypeMSG(msg->getTypeMsg()),msg->getValue(),msg->getDiff());
         ENTITY_DATA->setEventMsgToStateManager(msg);
     }

}

void GLLaunchSystemsGL11::handleMouseKeyPress(Uint8 mouseKeysym, char *statekey, int flipflop){

        EventMsg *msg;

        if (gNew->getFLAGMOUSE() == KEY_ON){
            if (mouseKeysym == SDL_BUTTON_LEFT){
                msg = new EventMsg(SHOOT,flipflop);
                ENTITY_DATA->setEventMsgToStateManager(msg);
                DEBUGLOGPONE("GLLaunchSystemsGL11::handleMouseKeyPress --> SEND SHOOT KEY %S TO STATE_MANAGER",statekey);
            }else if (mouseKeysym == SDL_BUTTON_RIGHT){
                msg = new EventMsg(CHGWEAPON,flipflop);
                ENTITY_DATA->setEventMsgToStateManager(msg);
                DEBUGLOGPONE("GLLaunchSystemsGL11::handleMouseKeyPress --> SEND CHGWEAPON KEY %S TO STATE_MANAGER",statekey);
            }
        }
}

void GLLaunchSystemsGL11::handleKeyPress(SDL_Keysym *keysym, char *statekey, int flipflop){

    SDL_Keycode left;
    SDL_Keycode right;
    SDL_Keycode up;
    SDL_Keycode down;
    SDL_Keycode fire;
    SDL_Keycode chgweapon;
    SDL_Keycode esc;
    SDL_Keycode exit;
    SDL_Keycode return_key;

    int left_flag = 0;
    int right_flag = 0;
    int up_flag = 0;
    int down_flag = 0;
    int fire_flag = 0;
    int chgweapon_flag = 0;
    int esc_flag = 0;
    int exit_flag = 0;
    int return_flag = 0;

    player = ENTITY_DATA->getPlayer(gNew->getActPlayer()-1);

    switch (gNew->getActPlayer()){
        case 1:
            left_flag = gNew->getKEYLEFT_1();
            right_flag = gNew->getKEYRIGHT_1();
            up_flag = gNew->getKEYUP_1();
            down_flag = gNew->getKEYDOWN_1();
            chgweapon_flag = gNew->getKEYCHGWEAPON_1();
            fire_flag = gNew->getKEYSHOOT_1();
            esc_flag = gNew->getKEYESC_1();
            exit_flag = gNew->getKEYEXIT_1();
            return_flag = gNew->getKEYRETURN_1();
        break;
        case 2:
            left_flag = gNew->getKEYLEFT_2();
            right_flag = gNew->getKEYRIGHT_2();
            up_flag = gNew->getKEYUP_2();
            down_flag = gNew->getKEYDOWN_2();
            chgweapon_flag = gNew->getKEYCHGWEAPON_2();
            fire_flag = gNew->getKEYSHOOT_2();
            esc_flag = gNew->getKEYESC_2();
            exit_flag = gNew->getKEYEXIT_2();
            return_flag = gNew->getKEYRETURN_2();
        break;
        case 3:
            left_flag = gNew->getKEYLEFT_3();
            right_flag = gNew->getKEYRIGHT_3();
            up_flag = gNew->getKEYUP_3();
            down_flag = gNew->getKEYDOWN_3();
            chgweapon_flag = gNew->getKEYCHGWEAPON_3();
            fire_flag = gNew->getKEYSHOOT_3();
            esc_flag = gNew->getKEYESC_3();
            exit_flag = gNew->getKEYEXIT_3();
            return_flag = gNew->getKEYRETURN_3();
        break;
        case 4:
            left_flag = gNew->getKEYLEFT_4();
            right_flag = gNew->getKEYRIGHT_4();
            up_flag = gNew->getKEYUP_4();
            down_flag = gNew->getKEYDOWN_4();
            chgweapon_flag = gNew->getKEYCHGWEAPON_4();
            fire_flag = gNew->getKEYSHOOT_4();
            esc_flag = gNew->getKEYESC_4();
            exit_flag = gNew->getKEYEXIT_4();
            return_flag = gNew->getKEYRETURN_4();
        break;
        default:
            left_flag = gNew->getKEYLEFT_1();
            right_flag = gNew->getKEYRIGHT_1();
            up_flag = gNew->getKEYUP_1();
            down_flag = gNew->getKEYDOWN_1();
            chgweapon_flag = gNew->getKEYCHGWEAPON_1();
            fire_flag = gNew->getKEYSHOOT_1();
            esc_flag = gNew->getKEYESC_1();
            exit_flag = gNew->getKEYEXIT_1();
            return_flag = gNew->getKEYRETURN_1();
        break;
    }




    EventMsg *msg;
    switch ( keysym->sym )
	{
        //left key
        //case 1073741916:
        case SDLK_LEFT:

            diff_key = 0.2f * (float(SDL_GetTicks()-beforeTimeStamp)/1000.0f) * float(DEFAULT_TILE_SIZE);
            value_key = player->getEntityXPos() - diff_key;
            init_key = player->getEntityXPos();

            beforeTimeStamp = SDL_GetTicks();

            msg = new EventMsg(LEFT,flipflop,value_key,diff_key,init_key);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND LEFT KEY (%d) TO STATE_MANAGER ACTION (%d)",LEFT,flipflop);
        break;

        //right right
        //case 1073741918:
        case SDLK_RIGHT:

            diff_key = 0.2f * (float(SDL_GetTicks()-beforeTimeStamp)/1000.0f) * float(DEFAULT_TILE_SIZE);
            value_key = player->getEntityXPos() + diff_key;
            init_key = player->getEntityXPos();
            beforeTimeStamp = SDL_GetTicks();

            msg = new EventMsg(RIGHT,flipflop,value_key,diff_key,init_key);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND RIGHT KEY (%d) TO STATE_MANAGER ACTION (%d)",RIGHT,flipflop);
        break;

        //up key
        //case 1073741920:
        case SDLK_UP:

            diff_key = 0.2f * (float(SDL_GetTicks()-beforeTimeStamp)/1000.0f) * float(DEFAULT_TILE_SIZE);
            value_key = player->getEntityYPos() - diff_key;
            init_key = player->getEntityYPos();
            beforeTimeStamp = SDL_GetTicks();

            msg = new EventMsg(UP,flipflop,value_key,diff_key,init_key);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND UP KEY (%d) TO STATE_MANAGER ACTION (%d)",UP,flipflop);
        break;

        //down key
        //case 1073741914:
        case SDLK_DOWN:

            diff_key = 0.2f * (float(SDL_GetTicks()-beforeTimeStamp)/1000.0f) * float(DEFAULT_TILE_SIZE);
            value_key = player->getEntityYPos() + diff_key;
            init_key = player->getEntityYPos();
            beforeTimeStamp = SDL_GetTicks();

            msg = new EventMsg(DOWN,flipflop,value_key,diff_key,init_key);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND DOWN KEY (%d) TO STATE_MANAGER ACTION (%d)",DOWN,flipflop);
        break;

        //shoot
        case SDLK_SPACE:

            //indicar desfases puede venir bien para rachas de disparos....

            msg = new EventMsg(SHOOT,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND SHOOT KEY (%d) TO STATE_MANAGER ACTION (%d)",SHOOT,flipflop);
        break;

        //change weapon
        case SDLK_LALT:
            msg = new EventMsg(CHGWEAPON,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND CHANGE WEAPON KEY (%d) TO STATE_MANAGER ACTION (%d)",CHGWEAPON,flipflop);
        break;

        //ESC
        case SDLK_ESCAPE:
            msg = new EventMsg(ESC,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND ESC KEY (%d) TO STATE_MANAGER ACTION (%d)",ESC,flipflop);
        break;

        //LCTRL
        case SDLK_LCTRL:
            msg = new EventMsg(RESUME,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND RESUME KEY (%d) TO STATE_MANAGER ACTION (%d)",RESUME,flipflop);
        break;

        //RALT
        case SDLK_RALT:
            msg = new EventMsg(QUIT,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
            //DEBUGLOGPTWO("GLLaunchSystemsGL11::handleKeyPress --> SEND QUIT KEY (%d) TO STATE_MANAGER ACTION (%d)",QUIT,flipflop);
        break;

        //TAB (TAB ENTRE JUGADORES)
        case SDLK_TAB:
            msg = new EventMsg(TOGGLE,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
        break;

        //TAB (MOSTRAR MAPA DE COLISIONES)
        case SDLK_LSHIFT:
            msg = new EventMsg(TOGGLE_COLL,flipflop);
            ENTITY_DATA->setEventMsgToStateManager(msg);
        break;

	}
}

void GLLaunchSystemsGL11::sendEvents(){

    SDL_Event event;

     while (SDL_PollEvent(&event)){
        switch (event.type){
            case SDL_KEYDOWN:
                handleKeyPress(&event.key.keysym,"PRESSED",KEY_ON);
                break;

            case SDL_KEYUP:
                handleKeyPress(&event.key.keysym,"UNPRESSED",KEY_OFF);
                break;

            case SDL_MOUSEBUTTONDOWN:
                handleMouseKeyPress(event.button.button, "PRESSED", KEY_ON);
                break;

            case SDL_MOUSEBUTTONUP:
                handleMouseKeyPress(event.button.button, "UNPRESSED", KEY_OFF);
                break;

            case SDL_MOUSEMOTION:
                handleMouseMotion(event.motion.x,event.motion.y);
                break;
        }     }
}

bool GLLaunchSystemsGL11::getEvents(){
     bool retMsg = false;

     while(!ENTITY_DATA->isEmptyQueueMsgFromToGLLaunch() && !retMsg){

         EventMsg *rEventMsg = ENTITY_DATA->getEventMsgFromToGLLaunch();

         DEBUGLOGPTWO("GLLaunchSystemsGL11::getEvents --> GET KEY (%d) FROM STATE_MANAGER (%d)",rEventMsg->getTypeMsg(),rEventMsg->getOn());

         if (rEventMsg->getTypeMsg() == QUIT){
            ENTITY_DATA->deleteLevels(0,ENTITY_DATA->getNumRows(),ENTITY_DATA->getNumLevels());
            ENTITY_DATA->deletePlayers();
            INFOLOG("GLLaunchSystemsGL11::getEvents --> QUIT EVENT. EXIT APP");
            retMsg = true;
         }else{
            retMsg = false;
         }
     }

     return retMsg;
}


//Funciones realizadas en otras implementaciones SDL + OpenGL ES 11 (version SpaceShooter"D-2)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void GLLaunchSystemsGL11::initWindowsGL11()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(255.0f, 0.0f, 0.0f, 0.0f);
    glClearDepthf(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void GLLaunchSystemsGL11::setPerspectiveOrthoGL11()
{
    GLfloat ratio;
    int height = gNew->getHeightScr();
    if (height==0){height=1;}

    ratio=((GLfloat)gNew->getWidthScr()/(GLfloat)gNew->getHeightScr());
    glViewport(0, 0, (GLsizei)gNew->getWidthScr(), (GLsizei)gNew->getHeightScr());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void GLLaunchSystemsGL11::setPerspectiveNoOrthoGL11(){

}

void GLLaunchSystemsGL11::gluPerspective(double fovy, double aspect, double zNear, double zFar){
	const double pi180 = 0.017453292519943295769236907684886;
	double top, bottom, left, right;
	top = zNear * tan(pi180*fovy/2);
	bottom = -top;
	right = aspect*top;
	left = -right;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustumf(left, right, bottom, top, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}
////////////////////////////////////////////////////////////////////////////////////////////////////


void GLLaunchSystemsGL11::renderOpenGLES11Dummy(){


    DEBUGLOG("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> INI");

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    int IdTexture = ENTITY_DATA->getImageDef("BACK_2");

    DEBUGLOGPONE("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> %d",IdTexture);

    glBindTexture(GL_TEXTURE_2D, IdTexture);
    float vtxcoords[] = {
        0, 0,
        gNew->getWidthScr(), 0,
        0, gNew->getHeightScr(),
        gNew->getWidthScr(), gNew->getHeightScr()
    };
    float texcoords[] = { 0, 0, 1, 0, 0, 1, 1, 1 };

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    //glBindTexture(GL_TEXTURE_2D, texture_from_png);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    DEBUGLOG("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> FIN");
}
*/

/*
/*
void GLLaunchSystemsGL11::renderOpenGLES11Dummy()
{
    DEBUGLOG("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> INI");

    //glClear(GL_COLOR_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    GLuint IdTexture = (GLuint)ENTITY_DATA->getImageDef("MAP_1");
    DEBUGLOGPONE("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> %d",IdTexture);

    //glBindTexture(GL_TEXTURE_2D, 3);
    glBindTexture(GL_TEXTURE_2D, IdTexture);
    float vtxcoords[] = {
        0, 0,
        640, 0,
        0, 480,
        640, 480,
    };
    float texcoords[] = { 0, 0, 1, 0, 0, 1, 1, 1 };

    glVertexPointer(2, GL_FLOAT, 0, vtxcoords);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    DEBUGLOG("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> FIN");
}

void GLLaunchSystemsGL11::setOpenGLES112DDummy(){
    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, gNew->getWidthScr(), gNew->getHeightScr());

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrthof(0.0f, gNew->getWidthScr(),gNew->getHeightScr(), 0.0f, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void GLLaunchSystemsGL11::leaveOpenGLES112DDummy(){
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void GLLaunchSystemsGL11::initWindowsGL11()
{
    glViewport( 0, 0, gNew->getWidthScr(), gNew->getHeightScr());
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrthof( -2.0, 2.0, -2.0, 2.0, -20.0, 20.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);


}

void GLLaunchSystemsGL11::setPerspectiveOrthoGL11()
{

}

void GLLaunchSystemsGL11::setPerspectiveNoOrthoGL11(){

}


void GLLaunchSystemsGL11::renderOpenGLES11Dummy(){

    GLbyte vertices[8 * 3] =
    {
        -1,  1,  1,
        1,  1,  1,
        1, -1,  1,
        -1, -1,  1,

        -1,  1, -1,
        1,  1, -1,
        1, -1, -1,
        -1, -1, -1
    };


    GLubyte colors[8 * 4] =
    {
        0  ,255,  0,255,
        0  ,  0,255,255,
        0  ,255,  0,255,
        255,  0,  0,255,

        0  ,  0,255,255,
        255,  0,  0,255,
        0  ,  0,255,255,
        0  ,255,  0,255
    };

    GLubyte triangles[12 * 3] =
    {

    1,0,3,
    1,3,2,

    2,6,5,
    2,5,1,

    7,4,5,
    7,5,6,

    0,4,7,
    0,7,3,

    5,4,0,
    5,0,1,

    3,7,6,
    3,6,2
    };

    DEBUGLOG("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> INI");

    glClearColor( 0.0, 0.0, 0.0, 1.0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 3, GL_BYTE, 0, vertices );

    glEnableClientState( GL_COLOR_ARRAY );

    glColorPointer( 4, GL_UNSIGNED_BYTE, 0, colors );

    glDrawElements( GL_TRIANGLES, 12 * 3, GL_UNSIGNED_BYTE, triangles );
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    glMatrixMode(GL_MODELVIEW);
    glRotatef(5.0, 1.0, 1.0, 1.0);

    setOpenGLES112DDummy();

    GLfloat texcoords[4 * 2];
	GLfloat vertx[4 * 2];

	int IdTexture = ENTITY_DATA->getImageDef("BACK_2");
    DEBUGLOGPONE("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> LOAD BACK_2 TEXTURE (%d)",IdTexture);

    glBindTexture(GL_TEXTURE_2D, IdTexture);
	texcoords[0] = 0; texcoords[1] = 0; vertx[0] = 0;                       vertx[1] = 0;
	texcoords[2] = 1; texcoords[3] = 0; vertx[2] = 0+gNew->getWidthScr();   vertx[3] = 0;
	texcoords[4] = 0; texcoords[5] = 1; vertx[4] = 0;                       vertx[5] = 0+gNew->getHeightScr();
	texcoords[6] = 1; texcoords[7] = 1; vertx[6] = 0+gNew->getWidthScr();   vertx[7] = 0+gNew->getHeightScr();

	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 2, GL_FLOAT, 0, vertx );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glTexCoordPointer( 2, GL_FLOAT, 0, texcoords );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

    leaveOpenGLES112DDummy();

    DEBUGLOG("GLLaunchSystemsGL11::renderOpenGLES11Dummy --> FIN");
}

*/




