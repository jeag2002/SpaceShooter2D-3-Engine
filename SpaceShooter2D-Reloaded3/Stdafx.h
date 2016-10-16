//.h general que carga todas los demas .h de la aplicación. evita ir declarandolo todo una y otra vez
#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED

//librerias ventana nativa <WIN32>
#ifdef WIN32
#include <windows.h>
#include <process.h>
#include <stddef.h>
#include <tchar.h>
#endif // WIN32

//GLEW
#ifdef GLEW
#include <gl/glew.h>
#endif //GLEW

//PTHREAD
#ifdef PTHREAD
#include <pthread.h>
#endif

//BOX2D
#ifdef BOX2D
#endif


//OPENGL ES 1.1
#ifdef GL11
#include "GLES/gl.h"
#include "GLES/egl.h"
#include "GLES/glext.h"
#include "GLES/glplatform.h"
#endif // GL11

//OPENGL ES 3.0
#ifdef GL30
#include  <GLES3/gl3.h>
#include  <EGL/egl.h>
#endif // GL30

//GLM
#ifdef GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif // GLM

//SDL12
#ifdef SDL12
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_gfx.h>
#undef main
#endif // SDL12

//SDL13
#ifdef SDL13
#include "SDL13/SDL/SDL.h"
#include "SDL13/SDL/SDL_image.h"
#include "SDL13/SDL/SDL_mixer.h"
#include "SDL13/SDL/SDL_ttf.h"
#undef main
#endif // SDL20

//SDL20
#ifdef SDL20
#include <SDL.h>
#include <SDL_opengles.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#undef main
#endif // SDL20

//LUA 5.1
extern "C"{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
};

//maths
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <time.h>

#include <algorithm>

//librerias comunes de mi aplicacion
#include "Utils.h"                     //clase de utilidades para toda la aplicacion
#include "LogEngine.h"                 //motor de logs
#include "MemManagerNew.h"             //gestor global de espacios de memoria del juego.
#include "Excepctions.h"               //gestor de excepciones.

//funciones macro comunes
#define DEBUGLOG(X)(gLogEngine->debug(X))
#define DEBUGLOGPONE(X,Y)(gLogEngine->debug(X,Y))
#define DEBUGLOGPTWO(X,Y,Z)(gLogEngine->debug(X,Y,Z))
#define DEBUGLOGPTHREE(X,Y,Z,Q)(gLogEngine->debug(X,Y,Z,Q))
#define DEBUGLOGPFOUR(X,Y,Z,Q,R)(gLogEngine->debug(X,Y,Z,Q,R))
#define DEBUGLOGPFIVE(X,Y,Z,Q,R,S)(gLogEngine->debug(X,Y,Z,Q,R,S))
#define DEBUGLOGPSIX(X,Y,Z,Q,R,S,T)(gLogEngine->debug(X,Y,Z,Q,R,S,T))
#define DEBUGLOGPSEVEN(X,Y,Z,Q,R,S,T,U)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U))
#define DEBUGLOGPEIGHT(X,Y,Z,Q,R,S,T,U,V)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V))
#define DEBUGLOGPNINE(X,Y,Z,Q,R,S,T,U,V,W)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W))
#define DEBUGLOGPTEN(X,Y,Z,Q,R,S,T,U,V,W,A)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W,A))
#define DEBUGLOGPELEVEN(X,Y,Z,Q,R,S,T,U,V,W,A,B)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W,A,B))
#define DEBUGLOGPTWELVE(X,Y,Z,Q,R,S,T,U,V,W,A,B,C)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W,A,B,C))
#define DEBUGLOGPTHIRTEEN(X,Y,Z,Q,R,S,T,U,V,W,A,B,C,D)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W,A,B,C,D))

#define INFOLOG(X)(gLogEngine->info(X))
#define INFOLOGPONE(X,Y)(gLogEngine->info(X,Y))
#define INFOLOGPTWO(X,Y,Z)(gLogEngine->info(X,Y,Z))
#define INFOLOGPTHREE(X,Y,Z,Q)(gLogEngine->info(X,Y,Z,Q))
#define INFOLOGPFOUR(X,Y,Z,Q,R)(gLogEngine->info(X,Y,Z,Q,R))
#define INFOLOGPFIVE(X,Y,Z,Q,R,S)(gLogEngine->info(X,Y,Z,Q,R,S))
#define INFOLOGPSIX(X,Y,Z,Q,R,S,T)(gLogEngine->info(X,Y,Z,Q,R,S,T))
#define INFOLOGPSEVEN(X,Y,Z,Q,R,S,T,U)(gLogEngine->info(X,Y,Z,Q,R,S,T,U))
#define INFOLOGPEIGHT(X,Y,Z,Q,R,S,T,U,V)(gLogEngine->info(X,Y,Z,Q,R,S,T,U,V))
#define INFOLOGPNINE(X,Y,Z,Q,R,S,T,U,V,W)(gLogEngine->info(X,Y,Z,Q,R,S,T,U,V,W))
#define INFOLOGPTEN(X,Y,Z,Q,R,S,T,U,V,W,A)(gLogEngine->info(X,Y,Z,Q,R,S,T,U,V,W,A))
#define INFOLOGPELEVEN(X,Y,Z,Q,R,S,T,U,V,W,A,B)(gLogEngine->info(X,Y,Z,Q,R,S,T,U,V,W,A,B))
#define INFOLOGPTWELVE(X,Y,Z,Q,R,S,T,U,V,W,A,B,C)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W,A,B,C))
#define INFOLOGPTHIRTEEN(X,Y,Z,Q,R,S,T,U,V,W,A,B,C,D)(gLogEngine->debug(X,Y,Z,Q,R,S,T,U,V,W,A,B,C,D))

#define WARNLOG(X)(gLogEngine->warn(X))
#define WARNLOGPONE(X,Y)(gLogEngine->warn(X,Y))
#define WARNLOGPTWO(X,Y,Z)(gLogEngine->warn(X,Y,Z))

#define ERRORLOG(X)(gLogEngine->error(X))
#define ERRORLOGP(X,Y)(gLogEngine->error(X,Y))

#define btoa(x) ((x)?"true":"false")

using namespace std;

#endif // STDAFX_H_INCLUDED
