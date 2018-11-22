#include "light.h"

#include "vertex.h"

_light::_light(GLenum id, lightType type, _vertex4f position,_vertex4f ambient, _vertex4f difuse, _vertex4f specular)
{
    this->id= id;
    this->type=type;

    /*light_specular = specular.to_byte();//{ specular._0, specular._1, specular._2, specular._3 };
    light_ambient= { ambient._0, ambient._1, ambient._2, ambient._3 };
    light_position = { position._0, position._1, position._2, position._3 };
    light_difuse = { difuse._0, difuse._1, difuse._2, difuse._3};*/
    light_ambient= pegar(light_ambient, ambient);
    light_specular= pegar(light_specular, specular);
    light_difuse = pegar(light_difuse, difuse);
    light_position= pegar(light_position, position);
    
    /*light_difuse = pegar(light_difuse, {1.0, 0.0, 0.0, 1.0});
    light_position= pegar(light_position, {1.0, 1.0, 1.0, 0.0});
    /*
    glLightfv(id,GL_AMBIENT, light_ambient);
    glLightfv(id,GL_DIFFUSE, light_difuse);
    glLightfv(id, GL_SPECULAR, light_specular);
    glLightfv(id, GL_POSITION, light_position);

    glEnable(id);*/

    this->off();

}

void _light::on(){
    glLightfv(this->id,GL_AMBIENT, light_ambient);
    glLightfv(this->id,GL_DIFFUSE, light_difuse);
    glLightfv(this->id, GL_SPECULAR, light_specular);
    glLightfv(this->id, GL_POSITION, light_position);

    glEnable(id);
}

void _light::off(){
    glDisable(id);
}

void _light::Switch(){
    if(ON){ this->off(); ON=false;}
    else{ this->on(); ON= true;}
}

GLfloat* _light::pegar(GLfloat* destino, _vertex4f origen){
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
