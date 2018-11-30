#ifndef CUBE_H
#define CUBE_H

#include "object3d.h"
#include "textura.h"

class _cube:public _object3D
{
private:
    bool texturaCompleta=false;
public:
   _cube(float Size=1.0);
   void asignarTextura(_textura* textura, bool completo=false);
   void crearTexturas();
};

#endif
