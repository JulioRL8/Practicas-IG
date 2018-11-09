#include "esfera.h"

const float PI= 3.1415926535897932384;

_esfera::_esfera(float radio, int revoluciones)
{
    vector<_vertex3f> perfil;
    const int vertices=26;
    perfil.resize(vertices+1);
    perfil[0]= _vertex3f(0,-radio,0);

    float angulo= PI/vertices;
    for(int i=1; i<=vertices; i++){
        perfil[i]= _vertex3f(perfil[0].y * sin(angulo*i),perfil[0].y * cos(angulo*i),0);
    }

    crearMalla(perfil,revoluciones);

}
