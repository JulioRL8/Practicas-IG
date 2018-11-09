#ifndef _EXTRUSION_H
#define _EXTRUSION_H

#include "object3d.h"

class _extrusion : public _object3D
{
public:
    _extrusion(vector<_vertex3f> perfil, _vertex3f vector);
};

#endif // _EXTRUSION_H
