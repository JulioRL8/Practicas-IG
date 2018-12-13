#include "light.h"

#include "vertex.h"

_light::_light(GLenum id, _vertex4f position, _vertex4f ambient, _vertex4f difuse, _vertex4f specular)
{
    this->id= id;

    light_ambient= /*(GLfloat*) &ambient;*/pegar(light_ambient, ambient);
    light_specular= pegar(light_ambient, specular);//(GLfloat*) &specular;
    light_difuse = pegar(light_difuse, difuse);//(GLfloat*) &difuse;//pegar(light_difuse, difuse);
    light_position= pegar(light_position, position);//(GLfloat*) &position;//pegar(light_position, position);
    
    this->off();

}

void _light::on(){
    ON=true;
    glLightfv(this->id, GL_AMBIENT, light_ambient);
    glLightfv(this->id, GL_DIFFUSE, light_difuse);
    glLightfv(this->id, GL_SPECULAR, light_specular);
    glLightfv(this->id, GL_POSITION, light_position);

    glEnable(id);
}

void _light::off(){
    ON=false;
    glDisable(id);
}

void _light::Switch(){
    if(ON){ this->off();}
    else{ this->on();}
}

bool _light::isOn(){
    return ON;
}

GLfloat* _light::pegar(GLfloat *destino, _vertex4f origen){
    /*for(int i=0; i<origen.size(); i++){
        destino[i]= origen;
    }*/
    destino= new GLfloat[4];
    destino[0]= origen._0;
    destino[1]= origen._1;
    destino[2]= origen._2;
    destino[3]= origen._3;

    return destino;
}
