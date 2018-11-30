#include "textura.h"

using namespace cimg_library;
using namespace std;

_textura::_textura(const char* fname)
{
   this->_id = 0;
   if (fname == 0)
      return;

   std::vector<unsigned char> data;

   CImg<unsigned char> imagen;
   imagen.load(fname);

   // empaquetamos bien los datos (RGB)
   for (long y = 0; y < imagen.height(); y ++)
      for (long x = 0; x < imagen.width(); x ++)
      {
	 unsigned char *r = imagen.data(x, y, 0, 0);
	 unsigned char *g = imagen.data(x, y, 0, 1);
	 unsigned char *b = imagen.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, &this->_id);
   glBindTexture(GL_TEXTURE_2D, this->_id);


   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}

GLuint _textura::id(void)
{
   return this->_id;
}


_textura::~_textura()
{
   if (this->_id)
      glDeleteTextures(1, &this->_id);
}
