/*
 * Practicas de IG
 * Domingo Martin Perandres© 2014-2018
 * dmartin@ugr.es
 *
 * GPL 3
 */

#include "object3d.h"

using namespace _colors_ne;

/**
 *
 *@param
 *@returns
 */

void _object3D::draw_line()
{
   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<Triangles.size();i++){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
   }
   glEnd();
}


/**
 *
 *@param
 *@returns
 */

void _object3D::draw_fill()
{
   glPolygonMode(GL_FRONT,GL_FILL);
   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<Triangles.size();i++){
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
   }
   glEnd();
}


/**
 *
 *@param
 *@returns
 */

void _object3D::draw_chess()
{
   glPolygonMode(GL_FRONT,GL_FILL);
   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<Triangles.size();i++){
      if (i%2==0) glColor3fv((GLfloat *) &RED);
      else glColor3fv((GLfloat *) &GREEN);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
      glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
   }
   glEnd();
}


void _object3D::draw_flat(){

    if(normalesCaras.size()==0){
        this->crearNormalesCaras();
    }

    glPolygonMode(GL_FRONT,GL_FILL);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_FLAT);


    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
       glNormal3f(normalesCaras[i].x, normalesCaras[i].y, normalesCaras[i].z);
       glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
       glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
       glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();



    glDisable(GL_LIGHTING);
}

void _object3D::draw_smooth(){

    if(normalesVertices.size()==0){
        this->crearNormalesVertices();
    }

    glPolygonMode(GL_FRONT,GL_FILL);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    glBegin(GL_TRIANGLES);
    for (unsigned int i=0;i<Triangles.size();i++){
       glNormal3f(normalesVertices[Triangles[i]._0].x, normalesVertices[Triangles[i]._0].y, normalesVertices[Triangles[i]._0].z);
       glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
       glNormal3f(normalesVertices[Triangles[i]._1].x, normalesVertices[Triangles[i]._1].y, normalesVertices[Triangles[i]._1].z);
       glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
       glNormal3f(normalesVertices[Triangles[i]._2].x, normalesVertices[Triangles[i]._2].y, normalesVertices[Triangles[i]._2].z);
       glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
    }
    glEnd();

    glDisable(GL_LIGHTING);
}

void _object3D::draw_tex(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    if(texturas.size()!=0 && textura!=NULL){
        glBegin(GL_TRIANGLES);
        for (unsigned int i=0;i<Triangles.size();i++){
           glTexCoord2f(texturas[i][0]._0, texturas[i][0]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
           glTexCoord2f(texturas[i][1]._0, texturas[i][1]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
           glTexCoord2f(texturas[i][2]._0, texturas[i][2]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);
        }
        glEnd();
    }else{
        this->draw_chess();
    }


}



void _object3D::draw(ModelView model){
    switch(model){
        case points: this->draw_point();break;
        case lines: this->draw_line();break;
        case FILL: this->draw_fill();break;
        case chess: this->draw_chess();break;
        case flat: this->draw_flat();break;
        case smooth: this->draw_smooth();break;
    }
}

void _object3D::crearNormalesCaras(){
    normalesCaras.resize(Triangles.size());

    for(int i=0; i<Triangles.size(); i++){
        _vertex3f a= Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];
        _vertex3f b= Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];
        normalesCaras[i]= a.cross_product(b).normalize();
    }
}

void _object3D::crearNormalesVertices(){

    this->crearNormalesCaras();
    normalesVertices.resize(Vertices.size());

    for(int i=0; i<Vertices.size(); i++){
        _vertex3f aux= _vertex3f(0,0,0);
        int num=0;

        _vertex3f v= Vertices[i];
        for(int j=0; j<Triangles.size(); j++){
            if(Vertices[Triangles[j]._0] == v || Vertices[Triangles[j]._1] == v || Vertices[Triangles[j]._2] == v){
                aux += normalesCaras[j];
                num++;
            }
        }

        aux /= num;
        normalesVertices[i]= aux;
    }

}

