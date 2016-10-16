/*

20151018.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Configuración inicial SDL  (Ventana + EVENTOS DE TECLADO/RATON) + EGL + OPENGLES

https://github.com/Cpasjuste/sdl-1.2.13_gles_example/blob/master/sdl_gles_test.c
https://github.com/thp/sdl2-opengles-test/blob/master/common.cpp
http://mepem.com/pemcode/?p=35
http://stackoverflow.com/questions/14038585/white-textures-with-sdl-1-3-and-opengl-es-1-1
http://sdl.5483.n7.nabble.com/SDL-2-0-OpenGL-ES-1-1-NDK-home-bt-losing-the-draw-screen-td34626.html

*/


#ifndef GLLAUNCHSYSTEMSGL11_H_INCLUDED
#define GLLAUNCHSYSTEMSGL11_H_INCLUDED

//definicion inicial de la ventana gráfica (¿deberia definirla como parametros de entrada?)
#define DOUBLEBUFFER_SIZE           1
#define COLOURDEPTH_RED_SIZE  		5
#define COLOURDEPTH_GREEN_SIZE 		6
#define COLOURDEPTH_BLUE_SIZE 		5
#define COLOURDEPTH_DEPTH_SIZE		16

#include "Stdafx.h"

class GLLaunchSystemsGL11{

public:

    GLLaunchSystemsGL11(){

        gNew = NULL;
        ENTITY_DATA = NULL;
        gLogEngine = NULL;
        beforeTimeStamp = SDL_GetTicks();

        //definicion window, glcontext.
        window = NULL;
        context = NULL;
    }


    GLLaunchSystemsGL11(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
        gNew = _gNew;
        ENTITY_DATA = _ENTITY_DATA;
        gLogEngine = _log;
        beforeTimeStamp = SDL_GetTicks();

        //definicion window, glcontext.
        window = NULL;
        context = NULL;
    };

    //inicializa Sistemas OpenGLES 1.1 + SDL 1.3
    void initOpenGLESSystems(int major, int minor);

    //actualiza framebuffer OpenGLES 1.1 + SDL 1.3
    void swapSDLOpenGLESBuffer(){
        SDL_GL_SwapWindow(window);
    };

    //finaliza sistemas OpenGLES 1.1 + SDL 1.3
    void terminateSDLOpenGLES(){
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    };

    //initWindowsGL11 + setPerspectiveGL11
    void initOpenGLESWindow(){
        initWindowsGL11();
        INFOLOG("GLLaunchSystemsGL11::initOpenGLESWindow  --> INIT GL11");
        setPerspectiveOrthoGL11();
        INFOLOG("GLLaunchSystemsGL11::initOpenGLESWindow  --> INIT PERSPECTIVE ORTHO GL11");
    };

    void setOpenGLES112DDummy();
    void leaveOpenGLES112DDummy();

    //cambia de perspectiva ortho a no ortho (activa iluminacion si es necesario)
    void swapPerspectiveOpenGLES();

    //funcion de prueba encargado de renderizar una figura 2D, 3D para probar que todo funciona correctamente.
    void renderOpenGLES11Dummy();

    //Envia eventos de GLLaunchSystems --> GLStateManager
    bool processInputEvents(){
        sendEvents();
        return getEvents();
    }

    ~GLLaunchSystemsGL11(){};

private:

    //ATRIBUTOS
    GlobalNew *gNew;
    MemManagerNew *ENTITY_DATA;
    LogEngine *gLogEngine;

    GLDynamicEntityNew *player;
    long beforeTimeStamp;
    float diff_key;
    float value_key;
    float init_key;

    //OBJECT SDL_OPENGL
    SDL_DisplayMode mode;
    SDL_Window *window;
    SDL_GLContext context;

    //FUNCION DE INICIACILIZACION OPENGL-11
    void initWindowsGL11();                     //crea una ventana OpenGL ES
    void setPerspectiveOrthoGL11();             //set Perspectiva Ortho
    void setPerspectiveNoOrthoGL11();           //set Perspectiva no ortho

    void gluPerspective(double fovy, double aspect, double zNear, double zFar);

    //procesa eventos de GLStateManager --> GLLaunchSystems.
    bool getEvents();
    void sendEvents();

    void handleKeyPress(SDL_Keysym *keysym, char *statekey, int flipflop);
    void handleMouseKeyPress(Uint8 mouseKeysym, char *statekey, int flipflop);
    void handleMouseMotion(int _x, int _y);

};

#endif // GLLAUNCHSYSTEMS_H_INCLUDED
