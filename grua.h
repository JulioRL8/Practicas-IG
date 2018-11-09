#ifndef _GRUA_H
#define _GRUA_H

#include "mesh.h"

class _grua : public _mesh
{
private:
    float altoRueda, anchoRueda, largoCabina, anchoCabina, tamBaseGancho,largoGancho, anchoGancho, largoBrazos, anchoBrazos, altoRotatorio, diametroRotatorio;
    float posGanchos, rotacionGancho1, rotacionGancho2, rotacionRotatorio;

    _mesh generarBase();
    _mesh generarRuedas();
    _mesh generarBrazos();
    _mesh generarGancho();
    _mesh generarGrua();

public:
    _grua();


    void girarRotatorio(float angulo);
    void girarEje1(float angulo);
    void girarEje2(float angulo);
    void moverGancho(float cuanto);

    void draw(ModelView model);
};

#endif // _GRUA_H
