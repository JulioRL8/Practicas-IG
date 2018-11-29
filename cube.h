#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"
#include "textura.h"

class _cube:public _object3D
{
public:
   _cube(float Size=1.0);
   void crearTexturas() override;
};

#endif
