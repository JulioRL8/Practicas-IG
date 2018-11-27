#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/gl.h>
#include <vector>
#include "CImg/CImg.h"

class _texture
{
private:
    GLuint id;
    GLenum tex;
public:
    _texture(char* archivo, GLenum texture=GL_TEXTURE0);
    //~_texture();
    void WrapT(GLint valor);
    void WrapS(GLint valor);
    void MagFilter(GLint valor);
    void MinFilter(GLint valor);

    void enable();
    void disable();
};

#endif // _TEXTURE_H
