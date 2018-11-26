#include "texture.h"
#include <string>

_texture::_texture(string archivo, GLenum texture)
{
    std::vector<unsigned char> data;

   if(0<= texture < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) tex= texture; else tex= GL_TEXTURE0;

   CImg<unsigned char> imagen;
   imagen.load(archivo);

   // empaquetamos bien los datos
   for (long y = 0; y < logo.height(); y ++)
      for (long x = 0; x < logo.width(); x ++)
      {
     unsigned char *r = imagen.data(x, y, 0, 0);
     unsigned char *g = imagen.data(x, y, 0, 1);
     unsigned char *b = imagen.data(x, y, 0, 2);
     data.push_back(*r);
     data.push_back(*g);
     data.push_back(*b);
      }

   glGenTextures(1, &id);
   glBindTexture(GL_TEXTURE_2D, id);

   glActiveTexture(this->tex);
   this->WrapS(GL_REPEAT);
   this->WrapT(GL_REPEAT);
   this->MinFilter(GL_NEAREST);
   this->MagFilter(GL_NEAREST);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(),
        0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

void _texture::WrapS(GLint valor){
    glActiveTexture(this->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, valor);
}

void _texture::WrapT(GLint valor){
    glActiveTexture(this->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, valor);
}

void _texture::MinFilter(GLint valor){
    glActiveTexture(this->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, valor);
}

void _texture::MagFilter(GLint valor){
    glActiveTexture(this->tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, valor);
}

void _texture::enable(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
    //glDisable(GL_TEXTURE_2D);
}

void _texture::disable(){
    glDisable(GL_TEXTURE_2D);
}
