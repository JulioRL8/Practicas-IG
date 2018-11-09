#ifndef REVOLUCION_H
#define REVOLUCION_H

#include "object3d.h"

class _revolucion:public _object3D{
	public: 
        _revolucion(vector<_vertex3f> perfil, int revoluciones);

    protected:
        _revolucion();
        void crearMalla(vector<_vertex3f> perfil, int revoluciones);
};

#endif
