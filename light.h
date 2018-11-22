#ifndef _LIGHT_H
#define _LIGHT_H

#include "lighttype.h"
#include "GL/gl.h"
#include "vertex.h"

class _light
{
private:
    bool ON=false;
    GLenum id;
    lightType type;
    GLfloat *light_specular;
    GLfloat *light_ambient;
    GLfloat *light_position;
    GLfloat *light_difuse;

    GLfloat* pegar(GLfloat destino[4], _vertex4f origen);
public:
    _light(GLenum id, lightType type, _vertex4f position=_vertex4f(1,1,1,1),_vertex4f ambient=_vertex4f(1,1,1,1),
           _vertex4f difuse=_vertex4f(1,1,1,1), _vertex4f specular=_vertex4f(1,1,1,1));
    void on();
    void off();
    void Switch();

};

#endif // _LIGHT_H
