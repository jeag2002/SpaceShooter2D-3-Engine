#ifndef GLLAUNCHSYSTEMS_H_INCLUDED
#define GLLAUNCHSYSTEMS_H_INCLUDED

#include "Stdafx.h"
#include "GLLaunchSystemsGL11.h"

class GLLaunchSystems{

public:

    GLLaunchSystems(){
        #ifdef GL11
            gLaunchSystemsGL11 = new GLLaunchSystemsGL11();
        #endif
    };



    GLLaunchSystems(GlobalNew *_gNew, MemManagerNew *_ENTITY_DATA, LogEngine *_log){
        #ifdef GL11
            gLaunchSystemsGL11 = new GLLaunchSystemsGL11(_gNew, _ENTITY_DATA, _log);
        #endif
    };

    void initOpenGLESSystems(int major, int minor){
        #ifdef GL11
            gLaunchSystemsGL11->initOpenGLESSystems(major, minor);
        #endif
    };

    void swapSDLOpenGLESBuffer(){
        #ifdef GL11
            gLaunchSystemsGL11->swapSDLOpenGLESBuffer();
        #endif
    };

    void terminateSDLOpenGLES(){
        #ifdef GL11
            gLaunchSystemsGL11->terminateSDLOpenGLES();
        #endif
    };

    void initOpenGLESWindow(){
        #ifdef GL11
            gLaunchSystemsGL11->initOpenGLESWindow();
        #endif
    };


    void swapPerspectiveOpenGLES(){
        #ifdef GL11
            gLaunchSystemsGL11->swapPerspectiveOpenGLES();
        #endif
    };

    void renderOpenGLESDummy(){
        #ifdef GL11
            gLaunchSystemsGL11->renderOpenGLES11Dummy();
        #endif
    };

    bool processInputEvents(){
        #ifdef GL11
            return gLaunchSystemsGL11->processInputEvents();
        #endif
    };

    ~GLLaunchSystems(){
        #ifdef GL11
            delete gLaunchSystemsGL11;
        #endif
    };




private:

    GlobalNew *gNew;
    MemManagerNew *ENTITY_DATA;
    LogEngine *log;

    GLLaunchSystemsGL11 *gLaunchSystemsGL11;



};

#endif // GLLAUNCHSYSTEMS_H_INCLUDED
