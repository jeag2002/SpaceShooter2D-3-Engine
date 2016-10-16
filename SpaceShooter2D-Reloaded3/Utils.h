/*
Clase estatica de utilidades, con funcionalidades para ser utilizadas en toda la aplicsción
1-Generacion de un uniqueID por cada objeto de la aplicacion
*/

/*
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

class Utils{

public:

private:



};

#endif // UTILS_H_INCLUDED
*/

#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP
#include "GlobalNew.h"
#include <cmath>

namespace Utils{


    //Create one UID
    inline unsigned int generateUIDDSinistar(unsigned int seed){
        unsigned int res = 0;

        return res;
    }

    //Compare two relMovementPol p1 & p2
    inline bool equalsRelMovementPol(const relMovementPol p1, const relMovementPol p2){

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

    inline relMovement getNormal(const relMovement p1, const relMovement p2){

        relMovement normVector;
        float modulusVector = sqrt(pow((p2.rel_pos_x - p1.rel_pos_x),2) + pow((p2.rel_pos_y - p1.rel_pos_y),2));
        normVector.rel_pos_y = ((p2.rel_pos_x - p1.rel_pos_x)/modulusVector) * (-1.0f);
        normVector.rel_pos_x = ((p2.rel_pos_y - p1.rel_pos_y)/modulusVector) * (-1.0f);
        return normVector;
    }


    inline double getDistanceFromPointToLine(const relMovement p1, const relMovement p2, float x0, float y0){

        double output = 0.0f;

        double num = std::abs((p2.rel_pos_y - p1.rel_pos_y)*x0 - (p2.rel_pos_x - p1.rel_pos_x)*y0 +  (p2.rel_pos_x*p1.rel_pos_y) - (p2.rel_pos_y*p1.rel_pos_x));
        double den = sqrt(pow((p2.rel_pos_y - p1.rel_pos_y),2) + pow((p2.rel_pos_x - p1.rel_pos_x),2));

        output = num/den;

        return output;
    }

    /*
    bool AreCollinear(Point A, Point B, Point C)
    {
    double slopesDelta = (A.y - B.y) * (A.x - C.x) - (A.y - C.y) * (A.x - B.x);
    double tolerance = 1e-6;                // substitute for your own tolerance
    return tolerance > Math.Abs(slopesDelta);
    }
    */

    inline bool areCollineal (const relMovement A, const relMovement B, const relMovement C){

        double slopeDelta = (A.rel_pos_y - B.rel_pos_y) * (A.rel_pos_x - C.rel_pos_x)  - (A.rel_pos_y - C.rel_pos_y) * (A.rel_pos_x - B.rel_pos_x);
        double tolerance = 1e-5;
        return (tolerance > std::abs(slopeDelta));
    }

    inline double defineAngle(float x_cursor_real, float y_cursor_real, float x_pos, float y_pos){
         double angle = atan2(y_pos - y_cursor_real, x_cursor_real - x_pos) * 180 / 3.14;
         return angle;
    }


    inline char *getState(int state){

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

    inline char *getTypeState(int type){

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

    /*


    #define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UPRIGTH 4
#define UPLEFT 5
#define DOWNRIGTH 6
#define DOWNLEFT 7
#define DIFFMOUSE 15            //cambio diferencial de ejes, raton (cursor)

#define SHOOT 8                 //SPACE  -> DISPARO
#define CHGWEAPON 9             //LALT   -> CAMBIO WEAPON
#define ESC 10                  //RALT   -> SALIR DE LA APLICACION
#define RESUME 11               //LCTRL  -> RESUME
#define QUIT 12                 //ESC    -> SALIR AL MENU
#define NEXT 13                 //INDICA AL NUEVO NIVEL
#define END 14                  //INDICA FINAL DEL JUEGO (CONTROLADO POR LOGICA)
#define TOGGLE 15               //INDICA CAMBIO DEL JUGADOR
#define TOGGLE_COLL 16          //PRESENTA MAPA COLISIONES



    */


    inline char *getTypeMSG(int type){
        if (type == -1){return "IDLE";}
        else if (type == 0){return "UP";}
        else if (type == 1){return "DOWN";}
        else if (type == 2){return "LEFT";}
        else if (type == 3){return "RIGHT";}
        else if (type == 4){return "UPRIGHT";}
        else if (type == 5){return "UPLEFT";}
        else if (type == 6){return "DOWNRIGHT";}
        else if (type == 7){return "DOWNLEFT";}
        else if (type == 8){return "SHOOT";}
        else if (type == 9){return "CHGWEAPON";}
        else if (type == 10){return "ESC";}
        else if (type == 11){return "RESUME";}
        else if (type == 12){return "QUIT";}
        else if (type == 13){return "NEXT";}
        else if (type == 14){return "END";}
        else if (type == 15){return "TOGGLE PLAYER (DEBUG)";}
        else if (type == 16){return "TOGGLE COLL (DEBUG)";}
        else if (type == 17){return "MOUSE CURSOR";}
        else{return "UNKNOWN";}



    }


}

#endif // UTILS_H_INCLUDED
