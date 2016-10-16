#include "GLImage.h"


int GLImage::power_of_two(int input)
{
	int value = 1;

	while ( value < input ) {
		value <<= 1;
	}
	return value;
}


//http://code.bluedinosaurs.com/articles/blending.html

GLImageDef *GLImage::processBMPOld(const char *path_to_img, int params[]){

    GLuint pointerToGL = 0;
    GLImageDef *res = new GLImageDef();

    GLuint texture;
	int w, h;
	SDL_Surface *surface;
	SDL_Surface *image;
	SDL_Rect area;
	Uint32 saved_flags = 0;
	Uint8  saved_alpha = 0;

	GLfloat *texcoord = new GLfloat[4];

    surface = SDL_LoadBMP(path_to_img);

    if(!surface)
    {
        WARNLOGPONE("GLImage::processBMP --> NO PUEDO CARGAR ARCHIVO IMAGEN [%s]", path_to_img);
    }else{


	/* Use the surface width and height expanded to powers of 2 */
	w = power_of_two(surface->w);
	h = power_of_two(surface->h);
	texcoord[0] = 0.0f;			/* Min X */
	texcoord[1] = 0.0f;			/* Min Y */
	texcoord[2] = (GLfloat)surface->w / w;	/* Max X */
	texcoord[3] = (GLfloat)surface->h / h;	/* Max Y */

	image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			24,

#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF,
			0x0000FF00,
			0x00FF0000,
			0xFF000000
#else
			0xFF000000,
			0x00FF0000,
			0x0000FF00,
			0x000000FF
#endif
		       );
	if ( image == NULL ) {
		return res;
	}

	/* Save the alpha blending attributes */
	//saved_flags = surface->flags&(SDL_SRCALPHA|SDL_RLEACCELOK);
	//saved_alpha = surface->format->alpha;

    SDL_PixelFormat *fmt = surface->format;
	saved_flags = fmt->Amask;
	saved_alpha = saved_flags >> fmt->Ashift;
	saved_alpha = saved_alpha << fmt->Aloss;

	//if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		//SDL_SetAlpha(surface, 0, 0);
    if (saved_flags != 0){
		SDL_SetSurfaceAlphaMod(surface,0);
    }
	//}

	/* Copy the surface into the GL texture image */
	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	/* Restore the alpha blending attributes */
	//if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		//SDL_SetAlpha(surface, saved_flags, saved_alpha);
    if (saved_flags != 0){
		SDL_SetSurfaceAlphaMod(image,saved_alpha);
    }
	//}

	/* Create an OpenGL texture for the image */
	glGenTextures(1, &pointerToGL);
	glBindTexture(GL_TEXTURE_2D, pointerToGL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterx(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); //-> Ojo! no funcionara si las imagenes no son ^2

	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RGB,
		     image->w, image->h,
		     0,
		     GL_RGB,
		     GL_UNSIGNED_BYTE,
		     image->pixels);

	res->setImageID((unsigned int)pointerToGL);
    res->setHeight(image->h);
    res->setWidth(image->w);
    res->setPathToImage(path_to_img);
    DEBUGLOGPONE("GLImage::processBMPOld LOAD FILE %s",res->getPathToImage());
    res->setTypeImg(BMP);

	SDL_FreeSurface(image);

    }

    return res;
}


GLImageDef *GLImage::processJPGPNG(const char *path_to_img, int params[], enum TextureImage::Format format){

    GLuint pointerToGL = 0;
    GLImageDef *res = new GLImageDef();

    SDL_Surface *surface = IMG_Load(path_to_img);
    if (surface == NULL) {
        WARNLOGPTWO("GLImage::processJPGPNG --> ERROR ARCHIVO IMAGEN %s %s", path_to_img, IMG_GetError());
    }else{

        SDL_PixelFormat fmt;
        memset(&fmt, 0, sizeof(fmt));
        if (format == TextureImage::RGBA) {
            fmt.format = SDL_PIXELFORMAT_RGBA8888;
            fmt.BitsPerPixel = 32;
            fmt.BytesPerPixel = 4;
            fmt.Rmask = 0x000000ff;
            fmt.Gmask = 0x0000ff00;
            fmt.Bmask = 0x00ff0000;
            fmt.Amask = 0xff000000;
        } else {
            fmt.format = SDL_PIXELFORMAT_RGB888;
            fmt.BitsPerPixel = 24;
            fmt.BytesPerPixel = 3;
            fmt.Rmask = 0x0000ff;
            fmt.Gmask = 0x00ff00;
            fmt.Bmask = 0xff0000;
            fmt.Amask = 0x000000;
        }

        SDL_Surface *tmp = SDL_ConvertSurface(surface, &fmt, 0);
        SDL_FreeSurface(surface);

        if (tmp == NULL) {
            WARNLOGPONE("GLImage::processJPGPNG --> SDL_ConvertSurface: %s", SDL_GetError());
            return res;
        }

        glGenTextures(1, &pointerToGL);

        glBindTexture(GL_TEXTURE_2D, pointerToGL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterx(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); //-> Ojo! no funcionara si las imagenes no son ^2

        SDL_LockSurface(tmp);
        GLenum gl_format = ((format == TextureImage::RGBA) ? GL_RGBA : GL_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, gl_format, tmp->w, tmp->h, 0,
                gl_format, GL_UNSIGNED_BYTE, tmp->pixels);
        SDL_UnlockSurface(tmp);

        glBindTexture(GL_TEXTURE_2D, 0);

        res->setImageID((unsigned int)pointerToGL);
        res->setHeight(tmp->h);
        res->setWidth(tmp->w);
        res->setPathToImage(path_to_img);
        DEBUGLOGPONE("GLImage::processJPGPNG LOAD FILE %s",res->getPathToImage());

        if (format == TextureImage::RGBA){
           res->setTypeImg(PNG);
        }else{
           res->setTypeImg(JPG);
        }

        SDL_FreeSurface(tmp);
    }


    return res;
}




GLImageDef *GLImage::processImageToGL(const char *path_to_img, const char *extension, int params[]){

    if (strncmp(extension, BMP, strlen(BMP))==0){
        return processBMP(path_to_img,params);
    }else if (strncmp(extension, JPG, strlen(JPG))==0){
        return processJPGPNG(path_to_img,params, TextureImage::RGB);
    }else if (strncmp(extension, PNG, strlen(PNG))==0){
        return processJPGPNG(path_to_img,params, TextureImage::RGBA);
    }else if (strncmp(extension, TGA, strlen(TGA))==0){
        return processTGA(path_to_img);
    }else{
        GLImageDef *img = new GLImageDef();
        return img;
    }
}

GLubyte* GLImage::ConvertToTransparent(SDL_Surface *frame){

	GLubyte color_trans[3] = {0x00, 0x00, 0x00};

	GLubyte* colores;

	GLuint it;
    GLuint jt;

	GLubyte rvalue;
    GLubyte gvalue;
    GLubyte bvalue;

	int textpos = 0;
	unsigned long rgbvalue;


	colores = new GLubyte[frame->h*frame->w*4];



	for (jt=0; jt<frame->h; jt++){
        for (it=0; it<frame->w; it++){

			if (frame->format->BytesPerPixel==3){

				rvalue=*((GLubyte*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel);
				gvalue=*((GLubyte*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel+1);
				bvalue=*((GLubyte*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel+2);

            }else if (frame->format->BytesPerPixel==4){

				rgbvalue=*(unsigned long*)((unsigned char*)frame->pixels+jt*frame->pitch+it*frame->format->BytesPerPixel);
				rvalue = (rgbvalue & 0xFF00FF00);
				gvalue = ((rgbvalue<<16) & 0x00FF0000);
                bvalue = ((rgbvalue>>16) & 0x000000FF);
			}


			colores[textpos] = rvalue;
			colores[textpos+1] = gvalue;
			colores[textpos+2] = bvalue;

			if ((rvalue==color_trans[0]) && (gvalue==color_trans[1]) && (bvalue==color_trans[2])){
				colores[textpos+3]=0x00;
			}else{
				colores[textpos+3]=0xFF;
			}

			textpos += 4;
		}
    }

	return colores;
}


GLImageDef *GLImage::processBMP(const char *path_to_img, int params[]){

    GLImageDef *res = new GLImageDef();
    GLuint _id;

    GLubyte *datapixels;


    SDL_Surface *surface = SDL_LoadBMP(path_to_img);



    if (!surface){
        ERRORLOGP("GLImage::processBMP --> Error al cargar la textura %s", SDL_GetError());
        exit(1);
    }


    if (params[4] == POWER2){
        surface = ConvertToPower2(surface, BMP);
    }


    if (params[0] == BGR_RGB_FLAG){
        surface = ConvertToRGBA(surface);
    }


    if (params[5] == BMP_TRANSPARENT){
        datapixels = ConvertToTransparent(surface);
    }else{
        datapixels = surface->pixels;
    }



    //opciones
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    if (params[1] == LINEAL){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else if (params[1] == NEAREST){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    if (params[2] == REPEAT){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }else if (params[2] == CLAMP){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    if (params[3] == MIPMAP){
        glTexParameterx(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); //-> Ojo! no funcionara si las imagenes no son ^2
    }


    if (params[5] == BMP_TRANSPARENT){
        glTexImage2D(GL_TEXTURE_2D, 0,  GL_RGBA,
                     surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, datapixels);
    }else{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    }


    res->setImageID((unsigned int)_id);
    res->setHeight(surface->h);
    res->setWidth(surface->w);
    res->setPathToImage(path_to_img);
    res->setTypeImg(BMP);

    SDL_FreeSurface(surface);
    return res;
}


GLImageDef *GLImage::processTGA(const char *strFileName){


  FILE *f = fopen(strFileName, "rb");
  GLubyte *pixels = NULL;
  unsigned int y;
  int i;

  GLImageDef *res = new GLImageDef();
  GLuint _id;
  GLuint *id;

  try{

        if (f)
        {
            unsigned short width = 0, height = 0;
            unsigned char headerLength = 0;
            unsigned char imageType = 0;
            unsigned char bits = 0;
            int format= 0;
            int lineWidth = 0;

            fread(&headerLength, sizeof(unsigned char), 1, f);

            fseek(f,1,SEEK_CUR);

            fread(&imageType, sizeof(unsigned char), 1, f);

            fseek(f, 9, SEEK_CUR);

            fread(&width,  sizeof(unsigned short), 1, f);
            fread(&height, sizeof(unsigned short), 1, f);
            fread(&bits,   sizeof(unsigned char), 1, f);

            fseek(f, headerLength + 1, SEEK_CUR);

            if(imageType != 10){
                if(bits == 24){
                    format = bits >> 3;
                    lineWidth = format * width;
                    pixels = (GLubyte *) malloc (lineWidth * height);

                    for(y = 0; y < height; y++){
                        GLubyte *line = &(pixels[lineWidth * y]);
                        fread(line, lineWidth, 1, f);

                        for(i=0;i<lineWidth ; i+=format)
                        {
                            int temp  = line[i];
                            line[i]   = line[i+2];
                            line[i+2] = temp;
                        }
                    }
                }else{
                    fclose(f);
                    *id = 0;
                }
            }
            fclose(f);

            glGenTextures(1, &_id);
            glBindTexture(GL_TEXTURE_2D, _id);
            glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            free(pixels);

            res->setImageID((unsigned int)_id);
            res->setHeight(height);
            res->setWidth(width);
            res->setPathToImage(strFileName);
            DEBUGLOGPONE("GLImage::processTGA LOAD FILE %s",res->getPathToImage());
            res->setTypeImg(TGA);

        }else{
            throw "no se ha podido encontrar fichero o formato erroneo";
        }

    }catch (char *str_error){
        WARNLOGPTWO("GLImage::LoadTGAImageToGL --> OPENGL ERROR FLAG %d DESC %s", glGetError(),str_error);
        exit(1);
    }

    return res;
}


GLImageDef *GLImage::processParallaxImageToGL(const char *file, relMovementPol windows){


     GLuint _id;
     GLImageDef *res = new GLImageDef();

     int sizeFileName =0;
     for(sizeFileName=0; sizeFileName<200 && file[sizeFileName]!=' '; sizeFileName++){}
     char *fileParallax = new char(sizeFileName+1);
     int i = 0;
     for(i=0; i<sizeFileName; i++){fileParallax[i]=file[i];}
     fileParallax[sizeFileName]='\0';

     int initialW = 0;
     int initialH = 0;


     DEBUGLOGPONE("GLImage::processParallaxImageToGL Processing File --> [%s]",fileParallax);

     SDL_Surface *surface = IMG_Load(fileParallax);

     if (surface != NULL){

            initialW = surface->w;
            initialH = surface->h;


            int w = (int)(windows.nodes[1].rel_pos_x - windows.nodes[0].rel_pos_x);
            int h = (int)(windows.nodes[1].rel_pos_y - windows.nodes[0].rel_pos_y);

          	SDL_Surface *image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			24,

            #if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
                0x0000ff,
                0x00ff00,
                0xff0000,
                0x000000
            #else
                0xff0000,
                0x00ff00,
                0x0000ff,
                0x000000
            #endif
            );

            if (image != NULL){
                SDL_Rect area;
                area.x = windows.nodes[0].rel_pos_x;
                area.y = windows.nodes[0].rel_pos_y;
                area.w = w;
                area.h = h;

                SDL_Rect area_1;

                area_1.x = 0.0f;
                area_1.y = 0.0f;
                area_1.w = 640.0f;
                area_1.h = 480.0f;

                SDL_BlitSurface(surface, &area, image, &area_1);

                glDeleteTextures(1, &_id);
                glGenTextures(1, &_id);
                glBindTexture(GL_TEXTURE_2D, _id);


                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

                res->setImageID((unsigned int)_id);
                res->setHeight(initialH);
                res->setWidth(initialW);
                res->setPathToImage(file);

                SDL_FreeSurface(image);
                SDL_FreeSurface(surface);

            }else{
                WARNLOGPONE("GLImage::processParallaxImageToGL --> ERROR AL CREAR LA TEXTURA PARALLAX %s", SDL_GetError());
                exit(1);
            }
     }else{
        WARNLOGPONE("GLImage::processParallaxImageToGL --> IMPOSIBILIDAD DE CARGAR LA IMAGEN %s", SDL_GetError());
        exit(1);
     }

     delete fileParallax;

    return res;
}





SDL_Surface *GLImage::ConvertToPower2(SDL_Surface *surface, std::string extension){

	int w = power_of_two(surface->w);
	int h = power_of_two(surface->h);

	SDL_Surface *image = SDL_CreateRGBSurface(
			SDL_SWSURFACE,
			w, h,
			24,

#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x0000ff,
			0x00ff00,
			0xff0000,
			0x000000
#else
			0xff0000,
			0x00ff00,
			0x0000ff,
			0x000000
#endif
    );

	if ( image == NULL ) {
        WARNLOG("GLImage::ConvertToPower2 --> redimension failed");
		return surface;
	}else{

	    //procesamos ALPHA (si no es BMP)
        if (strncmp(extension.c_str(), BMP, strlen(BMP))<=0){
        }

        SDL_Rect area;
        area.x = 0;
        area.y = 0;
        area.w = surface->w;
        area.h = surface->h;
        SDL_BlitSurface(surface, &area, image, &area);
        return image;
	}
}


SDL_Surface *GLImage::ConvertToRGBA(SDL_Surface *frame){

    GLuint it;
    GLuint jt;

            for (jt=0; jt<frame->h; jt++)
            {
                for (it=0; it<frame->w; it++)
                {GLuint *id;
                    switch (frame->format->BytesPerPixel)
                    {
                        case 3:
                             {
                                 unsigned char rvalue;
                                 unsigned char bvalue;

                                 rvalue=*((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel);
                                 bvalue=*((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel+2);
                                 *((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel)=bvalue;
                                 *((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel+2)=rvalue;
                             }
                             break;
                        case 4:
                             {
                                 unsigned long rgbvalue;

                                 rgbvalue=*(unsigned long*)((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel);
                                 rgbvalue=(rgbvalue & 0xFF00FF00) | ((rgbvalue<<16) & 0x00FF0000) |
                                          ((rgbvalue>>16) & 0x000000FF);
                                 *(unsigned long*)((unsigned char*)frame->pixels+
                                     jt*frame->pitch+it*frame->format->BytesPerPixel)=rgbvalue;
                             }
                             break;
                    }
                }
            }

        switch (frame->format->BytesPerPixel)
        {
            case 3:
                 {
                     GLuint it;
                     GLuint jt;
                     unsigned char rvalue;
                     unsigned char gvalue;
                     unsigned char bvalue;

                     for (jt=0; jt<frame->h/2; jt++)
                     {
                         for (it=0; it<frame->w; it++)
                         {
                             rvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel);
                             gvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+1);
                             bvalue=*((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+2);

                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel);
                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+1)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+1);
                             *((unsigned char*)frame->pixels+
                                 jt*frame->pitch+it*frame->format->BytesPerPixel+2)=
                                 *((unsigned char*)frame->pixels+
                                     (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+2);

                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel)=rvalue;
                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+1)=gvalue;
                             *((unsigned char*)frame->pixels+
                                 (frame->h-jt-1)*frame->pitch+it*frame->format->BytesPerPixel+2)=bvalue;

                         }
                     }
                 }
                 break;

    }

    return frame;
}









