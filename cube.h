#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"
#include "texture.h"

class _cube:public _object3D
{
public:
   _cube(float Size=1.0);
   void crearTextura(_texture textura);
};

#endif
