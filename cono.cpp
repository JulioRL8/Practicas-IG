#include "cono.h"

_cono::_cono(float altura, int revoluciones){
   vector<_vertex3f> perfil;
   perfil.resize(3);
   perfil[0]= _vertex3f(0,altura/2,0);
   perfil[1]= _vertex3f(altura/4,-altura/2,0);
   perfil[2]= _vertex3f(0,-altura/2,0);

   crearMalla(perfil,revoluciones);
}

void _cono::crearTexturas(){

    float partesx= 1.0/ (revolucion);

    for(int i=0; i<revolucion; i++){
        vector< _vertex2f> tex;

        tex.resize(3);
        tex[1]= _vertex2f(partesx*i, 0.75);
        tex[2]= _vertex2f(partesx*i+partesx, 0.75);
        tex[0]= _vertex2f(0.5, 0);

        texturas.push_back(tex);

    }
        for(int i=0; i<revolucion; i++){
            vector< _vertex2f> tex;

            tex.resize(3);
            tex[1]= _vertex2f(0.5, 1);
            tex[0]= _vertex2f(partesx*i, 0.75);
            tex[2]= _vertex2f(partesx*(i+1), 0.75);

            texturas.push_back(tex);

        }






 }
