#include "tablero.h"

_tablero::_tablero(float tam)
{
    Vertices.resize(4);

    Vertices[0]= _vertex3f(-tam,0,tam);
    Vertices[1]= _vertex3f(tam,0,tam);
    Vertices[2]= _vertex3f(tam,0,-tam);
    Vertices[3]= _vertex3f(-tam,0,-tam);


    Triangles.resize(2);

    Triangles[0]= _vertex3ui(0,1,2);
    Triangles[1]= _vertex3ui(0,2,3);

}


void _tablero::draw_tex(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura->_id);
    if(textura!=NULL){
        glBegin(GL_QUADS);
            glTexCoord2f(0,1);
            glVertex3fv((GLfloat *) &Vertices[0]);
            glTexCoord2f(1,1);
            glVertex3fv((GLfloat *) &Vertices[1]);
            glTexCoord2f(1,0);
            glVertex3fv((GLfloat *) &Vertices[2]);
            glTexCoord2f(0,0);
            glVertex3fv((GLfloat *) &Vertices[3]);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}
