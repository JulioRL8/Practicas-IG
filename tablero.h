#ifndef _TABLERO_H
#define _TABLERO_H

#include "object3d.h"

class _tablero : public _object3D
{
public:
    _tablero(float tam=1);
    void crearTexturas(_texture textura);
    void draw_tex();
};

#endif // _TABLERO_H
