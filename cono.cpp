#include "cono.h"

_cono::_cono(float altura, int revoluciones){
   vector<_vertex3f> perfil;
   perfil.resize(3);
   perfil[0]= _vertex3f(0,altura/2,0);
   perfil[1]= _vertex3f(altura/4,-altura/2,0);
   perfil[2]= _vertex3f(0,-altura/2,0);

   crearMalla(perfil,revoluciones);
}
