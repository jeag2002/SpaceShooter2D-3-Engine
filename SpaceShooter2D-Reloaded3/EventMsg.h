/*

20151021.0.001.0 JALCARAZ SPACESHOOTER2D-RELOADED3

Clase mensaje de eventos entre cliente y servidor.
*/


#ifndef EVENTMSG_H_INCLUDED
#define EVENTMSG_H_INCLUDED

#define NIL_MSG_TYPE 99

class EventMsg{

    public:

        EventMsg(){
            typeMsg = NIL_MSG_TYPE;
            value = 0.0f;
            diff = 0.0f;
            init = 0.0f;
            fromID = 0;
            toID = 0;
            on = 0;
        };

        EventMsg(int _typeMsg, int _fromID, int _toID){
            typeMsg = _typeMsg;
            value = 0.0f;
            diff = 0.0f;
            init = 0.0f;
            fromID = _fromID;
            toID = _toID;
        };

        EventMsg(int _typeMsg, float _value, int _fromID, int _toID){
            typeMsg = _typeMsg;
            value = _value;
            diff = 0;
            on = 0;
            init = 0.0f;
            fromID = _fromID;
            toID = _toID;
        };

        EventMsg(int _typeMsg, int _on){
            typeMsg = _typeMsg;
            value = 0;
            init = 0.0f;
            diff = 0;
            on = _on;
            fromID = 0;
            toID = 0;
        }

        EventMsg(int _typeMsg, int _on, float _value){
            typeMsg = _typeMsg;
            on = _on;
            value = _value;
            diff = 0;
            init = 0.0f;
            fromID = 0;
            toID = 0;
        }

        EventMsg(int _typeMsg, int _on, float _value, float _diff){
            typeMsg = _typeMsg;
            on = _on;
            value = _value;
            diff = _diff;
            fromID = 0;
            toID = 0;
        }

        EventMsg(int _typeMsg, int _on, float _value, float _diff, float _init){
            typeMsg = _typeMsg;
            on = _on;
            value = _value;
            diff = _diff;
            init = _init;
            fromID = 0;
            toID = 0;
        }

        EventMsg(int _typeMsg, int _on, float _value, float _diff, float _init, int _fromID, int _toID){
            typeMsg = _typeMsg;
            on = _on;
            value = _value;
            diff = _diff;
            init = _init;
            fromID = _fromID;
            toID = _toID;
        }


        EventMsg(int _typeMsg){
            typeMsg = _typeMsg;
            value = 0;
            init = 0.0f;
            diff = 0;
            on = 0;
            fromID = 0;
            toID = 0;
        }


        ~EventMsg(){
            typeMsg = NIL_MSG_TYPE;
            value = 0.0f;
            init = 0.0f;
            diff = 0.0f;
            on = 0;
            fromID = 0;
            toID = 0;
        };

        int getTypeMsg(){return typeMsg;}
        int getMsgValue(){return value;}
        int getFromID(){return fromID;}
        int getToID(){return toID;}
        int getOn(){return on;}
        float getValue(){return value;}
        float getDiff(){return diff;}
        float getInit(){return init;}

    private:

        int typeMsg;
        float value;
        float init;
        float diff;
        int on;               //on=1 pulsada la tecla; off =0 dejada de pulsar.
        int fromID;
        int toID;
        long idMachine;        //preparado para juego multijugador. identificador maquina cliente
        long idMachineForward; //preparado para juego multijugador. identificador maquina destino.
};

#endif // EVENTMSG_H_INCLUDED
