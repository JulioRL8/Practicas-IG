#include "grua.h"
#include "cilindro.h"
#include "cube.h"

const double PI= 3.141516;

_grua::_grua()
{
    altoRueda= 4;
    anchoRueda= 2;
    largoCabina= 20;
    anchoCabina= 10;
    tamBaseGancho=3;
    largoGancho=1;
    anchoGancho=0.5;
    largoBrazos= 15;
    anchoBrazos= 1;
    diametroRotatorio= 5;
    altoRotatorio=1;

    posGanchos= tamBaseGancho/2-tamBaseGancho/5;
    rotacionGancho1= 25;
    rotacionGancho2=0;
    rotacionRotatorio=0;

    this->add(this->generarBase());
    this->add(this->generarGrua());
}

_mesh _grua::generarGancho(){
    _cube cub;
    _mesh cubo(cub);
    _mesh ganchos(cub);
    _mesh gancho;

    cubo.scalation(tamBaseGancho,tamBaseGancho,tamBaseGancho);
    cubo.translation(0,tamBaseGancho/2,0);

    ganchos.scalation(anchoGancho,largoGancho,tamBaseGancho-tamBaseGancho/3);
    ganchos.translation(posGanchos,largoGancho/2+tamBaseGancho,0);
    gancho.add(ganchos);
    ganchos.transpop_back();
    ganchos.translation(-posGanchos,largoGancho/2+tamBaseGancho,0);
    gancho.add(ganchos);


    gancho.add(cubo);

    return gancho;
}

_mesh _grua::generarBrazos(){
    _cilindro cilindro;
    _cube cubo(tamBaseGancho);
    _mesh brazo(cilindro);
    _mesh caja(cubo);
    _mesh salida;

    brazo.scalation(anchoBrazos,largoBrazos,anchoBrazos);
    brazo.translation(0,largoBrazos/2,0);
    //brazo.rotation(0,0,rotacionGancho1);
    //brazo.add(this->generarGancho());

    _mesh brazo1;
    brazo1.add(brazo);
    caja= this->generarGancho();
    caja.translation(0,largoBrazos,0);
    brazo1.add(caja);
    brazo1.rotation(0,0,rotacionGancho1);

    caja= _mesh(cubo);
    caja.add(brazo1);
    caja.translation(0,tamBaseGancho/2,0);

    brazo.translation(0,-largoBrazos,0);

    salida.add(caja);
    salida.add(brazo);

    salida.translation(0,largoBrazos,0);
    salida.rotation(0,0,rotacionGancho2);

    return salida;
}

_mesh _grua::generarGrua(){
    _cilindro cil(altoRotatorio, diametroRotatorio);

    _mesh salida(cil);
    salida.add(this->generarBrazos());
    salida.translation(0,altoRotatorio/2,0);
    salida.rotation(0,rotacionRotatorio,0);
    salida.translation(0,anchoCabina/2+altoRueda/2,0);

    return salida;
}

_mesh _grua::generarBase(){

    _cube cubo;
    _mesh base(cubo);
    _mesh salida;

    base.scalation(largoCabina, anchoCabina/2, anchoCabina);
    base.translation(0,anchoCabina/4+altoRueda/2,0);
    //this->add(base);
    salida.add(base);
    salida.add(this->generarRuedas());

    return salida;

}

_mesh _grua::generarRuedas(){
    _cilindro cil;
    _mesh rueda( (_object3D) cil );
    rueda.scalation(_vertex3f(altoRueda, anchoRueda, altoRueda));
    rueda.rotation(90,0,0);
    //rueda.rotation( _vertex3f(0,0,1));
    _mesh ruedas;
    rueda.translation(_vertex3f(largoCabina/2,altoRueda/2,anchoCabina/2));
    ruedas.add(rueda);
    rueda.translation(_vertex3f(0,0,-anchoCabina));
    ruedas.add(rueda);
    rueda.translation(_vertex3f(-largoCabina,0,0));
    ruedas.add(rueda);
    rueda.translation(_vertex3f(0,0,anchoCabina));
    ruedas.add(rueda);
    //base.add(ruedas);
    //this.add(ruedas);
    return ruedas;
}


void _grua::girarRotatorio(float angulo){
    rotacionRotatorio += angulo;
    if(rotacionRotatorio>360) rotacionRotatorio = (int) rotacionRotatorio % 360;
    else if(rotacionRotatorio<-360) rotacionRotatorio +=360;
    this->hijos[1]= this->generarGrua();
}

void _grua::girarEje1(float angulo){
    rotacionGancho1 += angulo;
    if(rotacionGancho1>150) rotacionGancho1 = 150;
    else if(rotacionGancho1<-150) rotacionGancho1 = -150;
    this->hijos[1]= this->generarGrua();
}

void _grua::girarEje2(float angulo){
    rotacionGancho2 += angulo;
    if(rotacionGancho2>90) rotacionGancho2 = 90;
    else if(rotacionGancho2<-90) rotacionGancho2 = -90;
    this->hijos[1]= this->generarGrua();
}

void _grua::moverGancho(float cuanto){
    posGanchos += cuanto;
    if(posGanchos>tamBaseGancho/2-tamBaseGancho/5) posGanchos= tamBaseGancho/2-tamBaseGancho/5;
    else if( posGanchos < anchoGancho) posGanchos= anchoGancho;
    this->hijos[1]= this->generarGrua();
}

void _grua::draw(ModelView model){

    this->drawMesh(model);
}
