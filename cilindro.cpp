#include "cilindro.h"

_cilindro::_cilindro(float altura, float anchura, int revoluciones)
{
    vector<_vertex3f> perfil;
    perfil.resize(4);
    perfil[0]= _vertex3f(0,-altura/2,0);
    perfil[1]= _vertex3f(anchura/2,-altura/2,0);
    perfil[2]= _vertex3f(anchura/2,altura/2,0);
    perfil[3]= _vertex3f(0,altura/2,0);

    crearMalla(perfil, revoluciones);
}
