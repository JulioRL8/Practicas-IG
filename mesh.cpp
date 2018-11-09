#include "mesh.h"

_mesh::_mesh()
{
}

_mesh::_mesh(_object3D objeto)
{
    this->Triangles= objeto.Triangles;
    this->Vertices= objeto.Vertices;
}

_mesh::_mesh(_revolucion cil){
    this->Triangles= cil.Triangles;
    this->Vertices= cil.Vertices;
}

void _mesh::rotation(_vertex3f vector){
    _transformation transformacion(ROTATION, vector);

    transformaciones.push_back(transformacion);
}

void _mesh::rotation(float x, float y, float z){
    _transformation transformacion(ROTATION, _vertex3f(x,y,z));

    transformaciones.push_back(transformacion);
}

void _mesh::scalation(_vertex3f vector){
    _transformation transformacion(SCALATION, vector);

    transformaciones.push_back(transformacion);
}

void _mesh::scalation(float x, float y, float z){
    _transformation transformacion(SCALATION, _vertex3f(x,y,z));

    transformaciones.push_back(transformacion);
}

void _mesh::translation(_vertex3f vector){
    _transformation transformacion(TRANSLATION, vector);

    transformaciones.push_back(transformacion);
}

void _mesh::translation(float x, float y, float z){
    _transformation transformacion(TRANSLATION, _vertex3f(x,y,z));

    transformaciones.push_back(transformacion);
}

void _mesh::add(_mesh hijo){
    hijos.push_back(hijo);
}

void _mesh::transpop_back(){
    transformaciones.pop_back();
}


void _mesh::drawMesh(ModelView model){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    for(int i=transformaciones.size()-1; i>=0; i--){
        _vertex3f vector= _vertex3f(transformaciones[i].parameters);
        switch(transformaciones[i].type){
            case SCALATION: glScalef(vector.x,vector.y,vector.z); break;
            case TRANSLATION: glTranslatef(vector.x,vector.y,vector.z); break;
            case ROTATION:
                if(vector.x!=0){
                    glRotatef(vector.x,1.0,0.0,0.0);
                }else if(vector.y!=0){
                    glRotatef(vector.y,0.0,1.0,0.0);
                }else if(vector.z!=0){
                    glRotatef(vector.z,0.0,0.0,1.0);
                }
                break;
        }

        //transformaciones.pop_back();
    }

    for(int i=0; i<hijos.size();i++){
        hijos[i].drawMesh(model);
    }

    if(this->Vertices.size()>0) this->draw(model);

    glPopMatrix();

}
