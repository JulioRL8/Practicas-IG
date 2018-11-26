#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <GL/gl.h>
#include <string>

class _texture
{
private:
    GLuint id;
    GLenum tex;
public:
    _texture(string archivo, GLenum tex);
    //~_texture();
    void WrapT(GLint valor);
    void WrapS(GLint valor);
    void MagFilter(GLint valor);
    void MinFilter(GLint valor);

    void enable();
    void disable();
};

#endif // _TEXTURE_H
