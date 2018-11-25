#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/gl.h>

class _texture
{
private:
    GLuint id;
    GLenum tex;
public:
    _texture(String archivo);
    void WrapT(GLint valor);
    void WrapS(GLint valor);
    void MagFilter(GLint valor);
    void MinFilter(GLint valor);
};

#endif // _TEXTURE_H
