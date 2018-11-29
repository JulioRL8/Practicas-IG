#ifndef __TEXTURA__
#define __TEXTURA__

#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// NECESARIO PARA CARGAR LAS IMÁGENES DE DISCO
#include "./CImg/CImg.h"

class _textura{
  public:

   _textura(const char* fname);

   GLuint id(void);

   ~_textura();

  public:
   GLuint _id;

};

#endif
