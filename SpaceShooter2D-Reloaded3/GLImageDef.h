#ifndef GLIMAGEDEF_H_INCLUDED
#define GLIMAGEDEF_H_INCLUDED

#include "GlobalNew.h"

/*

unsigned int imageID;
float widht;
float height;
bool parallax;
char *path_to_image;
char *typeImg;

*/


class GLImageDef{

public:

GLImageDef(){
imageID = -1;
width = 0.0f;
height = 0.0f;
parallax = true;
for(int i=0; i<200; i++){path_to_image[i]=' ';typeImg[i]=' ';}
};

~GLImageDef(){
imageID = -1;
width = 0.0f;
height = 0.0f;
parallax = true;
for(int i=0; i<200; i++){path_to_image[i]=' ';typeImg[i]=' ';}
};

void copyImage(GLImageDef *glImageDef){
  imageID = glImageDef->getImageID();
  width = glImageDef->getWidth();
  height = glImageDef->getHeight();

  for(int i=0; i<200; i++){path_to_image[i]=' ';typeImg[i]=' ';}

  for(int i=0; i<200; i++){
    path_to_image[i] = glImageDef->getPathToImage()[i];
  }

  for(int j=0; j<200; j++){
    typeImg[j] = glImageDef->getTypeImg()[j];
  }

  parallax = glImageDef->isParallax();
};

void setImageID(unsigned int _imageID){imageID = _imageID;}
unsigned int getImageID(){return imageID;}

void setWidth(int _width){width = _width;}
int getWidth(){return width;}

void setHeight(int _height){height = _height;}
int getHeight(){return height;}

bool isParallax(){return parallax;}
void setParallax(bool _parallax){parallax = _parallax;}

char *getTypeImg(){return typeImg;}

void setTypeImg(const char *_typeImg){

int i=0;
while (i<200 && _typeImg[i] != '\0'){
        typeImg[i] = _typeImg[i];
        i++;
}


}

char *getPathToImage(){return path_to_image;}
void setPathToImage(const char *_path_to_image){

int i=0;
while (i<200 && _path_to_image[i] != '\0'){
        path_to_image[i] = _path_to_image[i];
        i++;
}

}

private:

unsigned int imageID;
float width;
float height;
bool parallax;
char path_to_image[200];
char typeImg[200];


};

#endif // GLIMAGEDEF_H_INCLUDED
