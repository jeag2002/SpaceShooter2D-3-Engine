#include "GLCollisionScript.h"

bool GLCollisionScript::processCollisionDynToDyn(relMovementPol rM1, relMovementPol rM2, std::string nomScriptCollision){
    bool res = AABBCollision(rM1,rM2,0);
    return res;
}


/*

algoritmo colision AABB Tutorial 8

    if ((*iter)->IsDead() == false && (*iter) != obj) {
      // Find the squared distance between the two objects
      GLfixed o1x = obj->GetX() >> 12;
      GLfixed o2x = (*iter)->GetX() >> 12;
      GLfixed o1y = obj->GetY() >> 12;
      GLfixed o2y = (*iter)->GetY() >> 12;
      GLfixed sqDist = (o1x - o2x) * (o1x - o2x) + (o1y - o2y) * (o1y - o2y);
      sqDist = sqDist >> 8;

      int hr1 = obj->GetHitRadius();
      int hr2 = (*iter)->GetHitRadius();

      if (sqDist < (hr1 + hr2) * (hr1 + hr2))
        return (*iter);
    }

*/

/*
// Collision x-axis?
bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
    two.Position.x + two.Size.x >= one.Position.x;
// Collision y-axis?
bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
    two.Position.y + two.Size.y >= one.Position.y;
// Collision only if on both axes
return collisionX && collisionY;
*/





bool GLCollisionScript::AABBCollision(relMovementPol rM1, relMovementPol rM2, int orientation){

    bool collision = false;

    /*
    float size1X = rM1.nodes[1].rel_pos_x - rM1.nodes[0].rel_pos_x;
    float size2X = rM2.nodes[1].rel_pos_x - rM2.nodes[0].rel_pos_x;

    float size1Y = rM1.nodes[2].rel_pos_y - rM1.nodes[1].rel_pos_y;
    float size2Y = rM2.nodes[2].rel_pos_y - rM2.nodes[1].rel_pos_y;

    bool collisionX = (((rM1.nodes[0].rel_pos_x + size1X) >= rM2.nodes[0].rel_pos_x) && ((rM2.nodes[0].rel_pos_x + size2X) >= rM1.nodes[0].rel_pos_x));
    bool collisionY = (((rM1.nodes[0].rel_pos_y + size1Y) >= rM2.nodes[0].rel_pos_y) && ((rM2.nodes[0].rel_pos_y + size2Y) >= rM1.nodes[0].rel_pos_y));

    return (collisionX && collisionY);
    */


    float size1X = rM1.nodes[1].rel_pos_x - rM1.nodes[0].rel_pos_x;
    float size2X = rM2.nodes[1].rel_pos_x - rM2.nodes[0].rel_pos_x;

    float size1Y = rM1.nodes[2].rel_pos_y - rM1.nodes[1].rel_pos_y;
    float size2Y = rM2.nodes[2].rel_pos_y - rM2.nodes[1].rel_pos_y;

    /*
    DEBUGLOGPEIGHT("GLGameLogic::processActiveCommands --> Pos player rM1 [%f,%f],[%f,%f],[%f,%f],[%f,%f]",
                            rM1.nodes[0].rel_pos_x,rM1.nodes[0].rel_pos_y,
                            rM1.nodes[1].rel_pos_x,rM1.nodes[1].rel_pos_y,
                            rM1.nodes[2].rel_pos_x,rM1.nodes[2].rel_pos_y,
                            rM1.nodes[3].rel_pos_x,rM1.nodes[3].rel_pos_y);

    DEBUGLOGPEIGHT("GLGameLogic::processActiveCommands --> Compare Pos map rM1 [%f,%f],[%f,%f],[%f,%f],[%f,%f]",
                            rM2.nodes[0].rel_pos_x,rM2.nodes[0].rel_pos_y,
                            rM2.nodes[1].rel_pos_x,rM2.nodes[1].rel_pos_y,
                            rM2.nodes[2].rel_pos_x,rM2.nodes[2].rel_pos_y,
                            rM2.nodes[3].rel_pos_x,rM2.nodes[3].rel_pos_y);
    */

    float x1_ref = rM1.nodes[0].rel_pos_x;
    float y1_ref = rM1.nodes[0].rel_pos_y;

    if (orientation == UP){
        y1_ref -= 1.0;
    }else if (orientation == DOWN){
        y1_ref += 1.0;
    }else if (orientation == LEFT){
        x1_ref -= 1.0;
    }else if (orientation == RIGHT){
        x1_ref += 1.0;
    }


    float x1Min = x1_ref;
    float x1Max = x1_ref+size1X;
    float y1Max = y1_ref+size1Y;
    float y1Min = y1_ref;

    // AABB 2
    float x2Min = rM2.nodes[0].rel_pos_x;
    float x2Max = rM2.nodes[0].rel_pos_x+size2X;
    float y2Max = rM2.nodes[0].rel_pos_y+size2Y;
    float y2Min = rM2.nodes[0].rel_pos_y;

    // Collision tests
    if( x1Max < x2Min || x1Min > x2Max ) return false;
    if( y1Max < y2Min || y1Min > y2Max ) return false;

    return true;



    /*
    float d1x = rM2.nodes[3].rel_pos_x - rM1.nodes[1].rel_pos_x;
    float d1y = rM2.nodes[3].rel_pos_y - rM1.nodes[1].rel_pos_y;
    float d2x = rM1.nodes[3].rel_pos_x - rM2.nodes[1].rel_pos_x;
    float d2y = rM1.nodes[3].rel_pos_y - rM2.nodes[1].rel_pos_y;

    if ((d1x > 0.0f) || (d1y > 0.0f)){ return false;}
    if ((d2x > 0.0f) || (d2y > 0.0f)){ return false;}
    return true;
    */

   /*
    float d1x = b->min.x - a->max.x;
    float d1y = b->min.y - a->max.y;
    float d2x = a->min.x - b->max.x;
    float d2y = a->min.y - b->max.y;

    if (d1x > 0.0f || d1y > 0.0f)
        return FALSE;

    if (d2x > 0.0f || d2y > 0.0f)
        return FALSE;

    return TRUE;
   */



    /*
    box->x > target->x + target->width &&
    box->x + box->width < target->x &&
    box->y > target->y + target->height &&
    box->y + box->height < target->y
    */

    return collision;
}


bool GLCollisionScript::SphericalCollision(relMovementPol rM1, relMovementPol rM2){

     float minRM1X = min(rM1.nodes[0].rel_pos_x,min(rM1.nodes[1].rel_pos_x,min(rM1.nodes[2].rel_pos_x,rM1.nodes[3].rel_pos_x)));
     float maxRM1X = max(rM1.nodes[0].rel_pos_x,max(rM1.nodes[1].rel_pos_x,max(rM1.nodes[2].rel_pos_x,rM1.nodes[3].rel_pos_x)));

     float minRM1Y = min(rM1.nodes[0].rel_pos_y,min(rM1.nodes[1].rel_pos_y,min(rM1.nodes[2].rel_pos_y,rM1.nodes[3].rel_pos_y)));
     float maxRM1Y = max(rM1.nodes[0].rel_pos_y,max(rM1.nodes[1].rel_pos_y,max(rM1.nodes[2].rel_pos_y,rM1.nodes[3].rel_pos_y)));

     float minRM2X = min(rM2.nodes[0].rel_pos_x,min(rM2.nodes[1].rel_pos_x,min(rM2.nodes[2].rel_pos_x,rM2.nodes[3].rel_pos_x)));
     float maxRM2X = max(rM2.nodes[0].rel_pos_x,max(rM2.nodes[1].rel_pos_x,max(rM2.nodes[2].rel_pos_x,rM2.nodes[3].rel_pos_x)));

     float minRM2Y = min(rM2.nodes[0].rel_pos_y,min(rM2.nodes[1].rel_pos_y,min(rM2.nodes[2].rel_pos_y,rM2.nodes[3].rel_pos_y)));
     float maxRM2Y = max(rM2.nodes[0].rel_pos_y,max(rM2.nodes[1].rel_pos_y,max(rM2.nodes[2].rel_pos_y,rM2.nodes[3].rel_pos_y)));


     float rM1Middlex = minRM1X + (maxRM1X - minRM1X)/2.0f;
     float rM1Middley = minRM1Y + (maxRM1X - minRM1Y)/2.0f;

     float rM2Middlex = minRM2X + (maxRM2X - minRM2X)/2.0f;
     float rM2Middley = minRM2Y + (maxRM2X - minRM2Y)/2.0f;


     float radiusM1 = sqrt(pow((rM1Middlex - maxRM1X),2) + pow((rM1Middley - maxRM1Y),2));
     float radiusM2 = sqrt(pow((rM2Middlex - maxRM2X),2) + pow((rM2Middley - maxRM2Y),2));

     float centerDist = sqrt(pow ((rM1Middlex - rM2Middlex),2) + pow ((rM1Middley - rM2Middley),2));

     return ((centerDist) < (radiusM1 + radiusM2));


}




bool GLCollisionScript::AABBCollisionToPlane(relMovementPol rM1, relMovementPol plane, int orientation){

    bool collision = false;

    float pos_x_player = rM1.nodes[0].rel_pos_x + 32.0f;
    float pos_y_player = rM1.nodes[0].rel_pos_y + 32.0f;

    if (orientation == UP){

        if (Utils::getDistanceFromPointToLine(plane.nodes[0],plane.nodes[1],pos_x_player,pos_y_player) <= 64.0f){

            if ((rM1.nodes[0].rel_pos_y >= plane.nodes[0].rel_pos_y) && (rM1.nodes[1].rel_pos_y >= plane.nodes[1].rel_pos_y)){

                if (
                ((plane.nodes[0].rel_pos_x <= rM1.nodes[0].rel_pos_x) && (rM1.nodes[1].rel_pos_x <= plane.nodes[1].rel_pos_x)) ||
                ((plane.nodes[0].rel_pos_x >= rM1.nodes[0].rel_pos_x) && (rM1.nodes[1].rel_pos_x <= plane.nodes[1].rel_pos_x) && (plane.nodes[0].rel_pos_x <= rM1.nodes[1].rel_pos_x)) ||
                ((plane.nodes[0].rel_pos_x <= rM1.nodes[0].rel_pos_x) && (rM1.nodes[1].rel_pos_x >= plane.nodes[1].rel_pos_x) && (plane.nodes[1].rel_pos_x >= rM1.nodes[0].rel_pos_x))
                )
                {
                    collision =  collision || ((rM1.nodes[0].rel_pos_y == plane.nodes[0].rel_pos_y) && (rM1.nodes[1].rel_pos_y == plane.nodes[1].rel_pos_y));
                }else{
                     collision = collision ||
                    ((rM1.nodes[0].rel_pos_x <= plane.nodes[1].rel_pos_x) && (plane.nodes[1].rel_pos_x <= rM1.nodes[1].rel_pos_x) &&
                    (rM1.nodes[0].rel_pos_y == plane.nodes[1].rel_pos_y) && (plane.nodes[1].rel_pos_y == rM1.nodes[1].rel_pos_y));
                }
            }else{
                collision = collision ||
                (plane.nodes[0].rel_pos_x >= rM1.nodes[0].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[0].rel_pos_y) &&
                (rM1.nodes[0].rel_pos_x >= plane.nodes[1].rel_pos_x) && (rM1.nodes[0].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[0], plane.nodes[1]);

                collision = collision ||
                (plane.nodes[0].rel_pos_x <= rM1.nodes[1].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[1].rel_pos_y) &&
                (rM1.nodes[1].rel_pos_x <= plane.nodes[1].rel_pos_x) && (rM1.nodes[1].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[1], plane.nodes[1]);
            }
        }
    }

    if (orientation == DOWN){

        if (Utils::getDistanceFromPointToLine(plane.nodes[0],plane.nodes[1],pos_x_player,pos_y_player) <= 64.0f){
            if ((rM1.nodes[2].rel_pos_y >= plane.nodes[0].rel_pos_y) && (rM1.nodes[3].rel_pos_y >= plane.nodes[1].rel_pos_y)){

                if (
                ((plane.nodes[0].rel_pos_x <= rM1.nodes[3].rel_pos_x) && (rM1.nodes[2].rel_pos_x <= plane.nodes[1].rel_pos_x)) ||
                ((plane.nodes[0].rel_pos_x >= rM1.nodes[3].rel_pos_x) && (rM1.nodes[2].rel_pos_x <= plane.nodes[1].rel_pos_x) && (plane.nodes[0].rel_pos_x <= rM1.nodes[2].rel_pos_x)) ||
                ((plane.nodes[0].rel_pos_x <= rM1.nodes[3].rel_pos_x) && (rM1.nodes[2].rel_pos_x >= plane.nodes[1].rel_pos_x) && (plane.nodes[1].rel_pos_x >= rM1.nodes[3].rel_pos_x))
                )
                {
                    collision =  collision || ((rM1.nodes[2].rel_pos_y == plane.nodes[0].rel_pos_y) && (rM1.nodes[3].rel_pos_y == plane.nodes[1].rel_pos_y));
                }
                else
                {
                     collision = collision ||
                    ((rM1.nodes[3].rel_pos_x <= plane.nodes[0].rel_pos_x) && (plane.nodes[0].rel_pos_x <= rM1.nodes[2].rel_pos_x) &&
                    (rM1.nodes[3].rel_pos_y == plane.nodes[0].rel_pos_y) && (plane.nodes[0].rel_pos_y == rM1.nodes[2].rel_pos_y));

                }
            }else{

                bool collision_1 =
                (plane.nodes[0].rel_pos_x >= rM1.nodes[2].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[2].rel_pos_y) &&
                (rM1.nodes[2].rel_pos_x >= plane.nodes[1].rel_pos_x) && (rM1.nodes[2].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[2], plane.nodes[1]);
                collision = collision || collision_1;

                collision = collision ||
                (plane.nodes[0].rel_pos_x <= rM1.nodes[3].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[3].rel_pos_y) &&
                (rM1.nodes[3].rel_pos_x <= plane.nodes[1].rel_pos_x) && (rM1.nodes[3].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[3], plane.nodes[1]);

            }
        }
    }

    if (orientation == RIGHT){
        if (Utils::getDistanceFromPointToLine(plane.nodes[0],plane.nodes[1],pos_x_player,pos_y_player) <= 64.0f){
            if ((rM1.nodes[1].rel_pos_x <= plane.nodes[0].rel_pos_x) && (rM1.nodes[2].rel_pos_x <= plane.nodes[1].rel_pos_x)){

                if (
                ((plane.nodes[0].rel_pos_y <= rM1.nodes[1].rel_pos_y) && (rM1.nodes[2].rel_pos_y <= plane.nodes[1].rel_pos_y)) ||
                ((plane.nodes[0].rel_pos_y >= rM1.nodes[1].rel_pos_y) && (rM1.nodes[2].rel_pos_y <= plane.nodes[1].rel_pos_y) && (plane.nodes[0].rel_pos_y <= rM1.nodes[2].rel_pos_y)) ||
                ((plane.nodes[0].rel_pos_y <= rM1.nodes[1].rel_pos_y) && (rM1.nodes[2].rel_pos_y >= plane.nodes[1].rel_pos_y) && (plane.nodes[1].rel_pos_y >= rM1.nodes[1].rel_pos_y))
                )
                {
                    collision =  collision || ((rM1.nodes[1].rel_pos_x == plane.nodes[0].rel_pos_x) && (rM1.nodes[2].rel_pos_x == plane.nodes[1].rel_pos_x));

                    collision = collision || ((rM1.nodes[1].rel_pos_y <= plane.nodes[0].rel_pos_y) && (rM1.nodes[2].rel_pos_y >= plane.nodes[0].rel_pos_y) &&
                                             (rM1.nodes[1].rel_pos_x == plane.nodes[0].rel_pos_x) && (rM1.nodes[2].rel_pos_x == plane.nodes[0].rel_pos_x));

                    collision = collision || ((rM1.nodes[1].rel_pos_y <= plane.nodes[1].rel_pos_y) && (rM1.nodes[2].rel_pos_y >= plane.nodes[1].rel_pos_y) &&
                                             (rM1.nodes[1].rel_pos_x == plane.nodes[1].rel_pos_x) && (rM1.nodes[2].rel_pos_x == plane.nodes[1].rel_pos_x));


                }

            }else{

                collision = collision ||
                (plane.nodes[0].rel_pos_x <= rM1.nodes[1].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[1].rel_pos_y) &&
                (rM1.nodes[1].rel_pos_x <= plane.nodes[1].rel_pos_x) && (rM1.nodes[1].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[1], plane.nodes[1]);

                bool collision_1 =
                (plane.nodes[0].rel_pos_x >= rM1.nodes[2].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[2].rel_pos_y) &&
                (rM1.nodes[2].rel_pos_x >= plane.nodes[1].rel_pos_x) && (rM1.nodes[2].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[2], plane.nodes[1]);

                collision = collision || collision_1;

            }
        }
    }

    if (orientation == LEFT){
        if (Utils::getDistanceFromPointToLine(plane.nodes[0],plane.nodes[1],pos_x_player,pos_y_player) <= 64.0f){
             if ((rM1.nodes[0].rel_pos_x >= plane.nodes[0].rel_pos_x) && (rM1.nodes[3].rel_pos_x >= plane.nodes[1].rel_pos_x)){

                if (
                ((plane.nodes[0].rel_pos_y <= rM1.nodes[0].rel_pos_y) && (rM1.nodes[3].rel_pos_y <= plane.nodes[1].rel_pos_y)) ||
                ((plane.nodes[0].rel_pos_y >= rM1.nodes[0].rel_pos_y) && (rM1.nodes[3].rel_pos_y <= plane.nodes[1].rel_pos_y) && (plane.nodes[0].rel_pos_y <= rM1.nodes[3].rel_pos_y)) ||
                ((plane.nodes[0].rel_pos_y <= rM1.nodes[0].rel_pos_y) && (rM1.nodes[3].rel_pos_y >= plane.nodes[1].rel_pos_y) && (plane.nodes[1].rel_pos_y >= rM1.nodes[0].rel_pos_y))
                )
                {
                    collision =  collision || ((rM1.nodes[0].rel_pos_x == plane.nodes[0].rel_pos_x) && (rM1.nodes[3].rel_pos_x == plane.nodes[1].rel_pos_x));

                    collision = collision || ((rM1.nodes[0].rel_pos_y <= plane.nodes[0].rel_pos_y) && (rM1.nodes[3].rel_pos_y >= plane.nodes[0].rel_pos_y) &&
                                             (rM1.nodes[0].rel_pos_x == plane.nodes[0].rel_pos_x) && (rM1.nodes[3].rel_pos_x == plane.nodes[0].rel_pos_x));

                    collision = collision || ((rM1.nodes[0].rel_pos_y <= plane.nodes[1].rel_pos_y) && (rM1.nodes[3].rel_pos_y >= plane.nodes[1].rel_pos_y) &&
                                             (rM1.nodes[0].rel_pos_x == plane.nodes[1].rel_pos_x) && (rM1.nodes[3].rel_pos_x == plane.nodes[1].rel_pos_x));
                }
            }else{

                collision = collision ||
                (plane.nodes[0].rel_pos_x >= rM1.nodes[0].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[0].rel_pos_y) &&
                (rM1.nodes[0].rel_pos_x >= plane.nodes[1].rel_pos_x) && (rM1.nodes[0].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[0], plane.nodes[1]);

                collision = collision ||
                (plane.nodes[0].rel_pos_x <= rM1.nodes[3].rel_pos_x) && (plane.nodes[0].rel_pos_y <= rM1.nodes[3].rel_pos_y) &&
                (rM1.nodes[3].rel_pos_x <= plane.nodes[1].rel_pos_x) && (rM1.nodes[3].rel_pos_y <= plane.nodes[1].rel_pos_y) &&
                Utils::areCollineal (plane.nodes[0], rM1.nodes[3], plane.nodes[1]);

            }
        }
    }


    return collision;
}



bool GLCollisionScript::evaluateIfSameBlockMap(relMovementPol rM1, relMovementPol rM2, int orientation){
    bool sameBlockMap = false;
    return sameBlockMap;
}


bool GLCollisionScript::AABBCollisionToMap(relMovementPol rM1, int orientation, int level){


    bool collition = false;
    int orientationMap = 0;

    //orientationMap = orientation;

    std::vector<GLCollision *>planes = ENTITY_DATA->getCollisionStaticMap(level,orientation);

    for(int i=0; i<planes.size(); i++){
        bool coll_1 = AABBCollisionToPlane(rM1, planes[i]->getRelMovementPol(),orientation);
        collition = collition || coll_1;

        GLCollision *data_1 = new GLCollision();
        relMovementPol rMP_1 = planes[i]->getRelMovementPol();

        if (coll_1){
            rMP_1.coll = 1;
        }else{
            rMP_1.coll = 0;
        }

        data_1->setRelMovementPol(rMP_1);
        ENTITY_DATA->setCollisionStaticMapData(level, orientation, i, data_1);

    }

    if (orientation == UP){orientationMap = DOWN;}
    else if (orientation == DOWN){orientationMap = UP;}
    else if (orientation == LEFT){orientationMap = RIGHT;}
    else if (orientation == RIGHT){orientationMap = LEFT;}

    std::vector<GLCollision *>planes_1 = ENTITY_DATA->getCollisionStaticMap(level,orientationMap);

    for(int i=0; i<planes_1.size(); i++){
        bool coll_2 = AABBCollisionToPlane(rM1, planes_1[i]->getRelMovementPol(),orientation);
        collition = collition || coll_2;

        GLCollision *data_2 = new GLCollision();
        relMovementPol rMP_2 = planes_1[i]->getRelMovementPol();

        if (coll_2){
            rMP_2.coll = 1;
        }else{
            rMP_2.coll = 0;
        }

        data_2->setRelMovementPol(rMP_2);
        ENTITY_DATA->setCollisionStaticMapData(level, orientationMap, i, data_2);

    }

    planes.clear();
    planes_1.clear();


    return collition;
}


/*

if (Abs(a.c[0] – b.c[0]) > (a.r[0] + b.r[0])) xOverlap = false;
if (Abs(a.c[1] – b.c[1]) > (a.r[1] + b.r[1])) yOverlap = false;
if (Abs(a.c[2] – b.c[2]) > (a.r[2] + b.r[2])) zOverlap = false;

anyOverlap = xOverlap && yOverlap && zOverlap;

*/

/*

if (rect1.x < rect2.x + rect2.width &&
   rect1.x + rect1.width > rect2.x &&
   rect1.y < rect2.y + rect2.height &&
   rect1.height + rect1.y > rect2.y) {
    // collision detected!
}


*/

/*
    bool res = false;

    GLLuaScript *scriptColl = ENTITY_DATA->getLuaScript(nomScriptCollision);

    if (scriptColl!=NULL){

        DEBUGLOGPTWO("GLCollisionScript::processCollision --> EXECUTE SCRIPT [%s] ==> [%s]",nomScriptCollision.c_str(),scriptColl->getFileName());

        GLLuaScript::relMovementPol_GL rM1_GL;
        rM1_GL.num_nodes = rM1.num_nodes;

        for (int i=0;i<rM1.num_nodes;i++){
            rM1_GL.nodes[i].rel_pos_x = rM1.nodes[i].rel_pos_x;
            rM1_GL.nodes[i].rel_pos_y = rM1.nodes[i].rel_pos_y;
        }

        GLLuaScript::relMovementPol_GL rM2_GL;
        rM2_GL.num_nodes = rM2.num_nodes;

        for (int i=0;i<rM2.num_nodes;i++){
            rM2_GL.nodes[i].rel_pos_x = rM2.nodes[i].rel_pos_x;
            rM2_GL.nodes[i].rel_pos_y = rM2.nodes[i].rel_pos_y;
        }


        //INPUT PARAMS
        scriptColl->inputParameterToRMList("rM1");
        scriptColl->setInputRMovParameter("rM1", "relMovementPol_GL", rM1_GL);
        scriptColl->inputParameterToRMList("rM2");
        scriptColl->setInputRMovParameter("rM2", "relMovementPol_GL", rM2_GL);

        //OUTPUT PARAMS
        scriptColl->outputParameterToList("Output");
        scriptColl->setOutputParameter("Output","boolean","");

        scriptColl->executeLuaCollScript();

        //RES
        std::tuple<std::string, std::string, std::string> oParam = scriptColl->getOutputParameterDef("Output");
        std::string collision = std::get<2>(oParam);

        DEBUGLOGPONE("GLCollisionScript::processCollision --> RESULT: (%s)",collision.c_str());
    }else{
        WARNLOGPONE("GLCollisionScript::processCollision --> SCRIPT [%s] NOT FOUND. EXECUTING AS LOCAL",nomScriptCollision.c_str());
    }
*/

