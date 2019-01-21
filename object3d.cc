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


void _object3D::crearColores(){
    this->colores.resize(Triangles.size());
    //float f= 1.0f/(Triangles.size()+1);

    /*int num=255;*/

    


    for(int i=0; i<Triangles.size(); i++){
        //colores[i]= (i+1)*f;
        /*int cuantos= i/num;
        int mod= i%num;

        if(cuantos>0){
            if(cuantos==1){
                colores[i]= _vertex3i(255,mod,0);
            }else if(cuantos>{
                colores[i]= _vertex3i(255,255,mod);
            }
        }*/

        float red= ((i+1) & 0x00FF0000) >>16;
        red /= 255.0;

        float green=((i+1) & 0x0000FF00) >> 8;
        green /= 255.0;

        float blue=((i+1) & 0x000000FF);
        blue /= 255.0;


        colores[i]= _vertex3f(red,green,blue);
        cout << red << " " <<  green << " " << blue << endl;
    }
}

void _object3D::draw_selection()
{
   glPolygonMode(GL_FRONT,GL_FILL);

   if(colores.empty()){ this->crearColores();}


   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<Triangles.size();i++){

      glColor3f(colores[i].x,colores[i].y,colores[i].z);


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

bool _object3D::estaSeleccionado(int i){
    bool esta=false;
    for(int j=0; j<this->seleccionados.size(); j++){
        if(seleccionados[j]==i){
            esta=true;
        }
    }

    return esta;
}

void _object3D::draw_fill()
{
   glPolygonMode(GL_FRONT,GL_FILL);

   glBegin(GL_TRIANGLES);
   for (unsigned int i=0;i<Triangles.size();i++){
      if( estaSeleccionado(i)){ glColor3f(0,1.0,0.0);}
      else glColor3f(0.0,0.0,1.0);
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

    if(texturas.empty()){
       this->crearTexturas();
    }

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_ALPHA_TEST);

    if(textura!=NULL && !texturas.empty()){

        glBindTexture(GL_TEXTURE_2D, textura->_id);
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        for (unsigned int i=0;i<Triangles.size();i++){
           glTexCoord2f(texturas[i][0]._0, texturas[i][0]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
           glTexCoord2f(texturas[i][1]._0, texturas[i][1]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
           glTexCoord2f(texturas[i][2]._0, texturas[i][2]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);

           /*cout << "Textura: " <<  texturas[i][0]._0 << " " << texturas[i][0]._1 << endl;
           cout << "Vertices: " << Triangles[i]._0 << endl;
           cout << "Textura: " <<  texturas[i][1]._0 << " " << texturas[i][1]._1 << endl;
           cout << "Vertices: " << Triangles[i]._1 << endl;
           cout << "Textura: " <<  texturas[i][2]._0 << " " << texturas[i][2]._1 << endl;
           cout << "Vertices: " << Triangles[i]._2 << endl << endl;*/

        }
        glEnd();
    }
    //glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);

}

void _object3D::draw_tex_smooth(){

    if(texturas.empty()){
       this->crearTexturas();
    }
    if(normalesVertices.size()==0){
        this->crearNormalesVertices();
    }

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textura->_id);


    if(textura!=NULL){
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        for (unsigned int i=0;i<Triangles.size();i++){
           glNormal3f(normalesVertices[Triangles[i]._0].x, normalesVertices[Triangles[i]._0].y, normalesVertices[Triangles[i]._0].z);
           glTexCoord2f(texturas[i][0]._0, texturas[i][0]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);

           glNormal3f(normalesVertices[Triangles[i]._1].x, normalesVertices[Triangles[i]._1].y, normalesVertices[Triangles[i]._1].z);
           glTexCoord2f(texturas[i][1]._0, texturas[i][1]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);

           glNormal3f(normalesVertices[Triangles[i]._2].x, normalesVertices[Triangles[i]._2].y, normalesVertices[Triangles[i]._2].z);
           glTexCoord2f(texturas[i][2]._0, texturas[i][2]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);

        }
        glEnd();
    }
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

}

void _object3D::draw_tex_flat(){

    if(texturas.empty()){
       this->crearTexturas();
    }
    if(normalesCaras.size()==0){
        this->crearNormalesCaras();
    }

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
    glEnable(GL_LIGHTING);
    glBindTexture(GL_TEXTURE_2D, textura->_id);


    if(textura!=NULL){
        glBegin(GL_TRIANGLES);
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        for (unsigned int i=0;i<Triangles.size();i++){

           glNormal3f(normalesCaras[i].x, normalesCaras[i].y, normalesCaras[i].z);
           glTexCoord2f(texturas[i][0]._0, texturas[i][0]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._0]);
           glTexCoord2f(texturas[i][1]._0, texturas[i][1]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._1]);
           glTexCoord2f(texturas[i][2]._0, texturas[i][2]._1);
           glVertex3fv((GLfloat *) &Vertices[Triangles[i]._2]);

        }
        glEnd();
    }
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

}



void _object3D::draw(ModelView model){
    switch(model){
        case points: this->draw_point();break;
        case lines: this->draw_line();break;
        case FILL: this->draw_fill();break;
        case chess: this->draw_chess();break;
        case flat: this->draw_flat();break;
        case smooth: this->draw_smooth();break;
        case texture: this->draw_tex();break;
        case texture_smooth: this->draw_tex_smooth();break;
        case texture_flat: this->draw_tex_flat();break;
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

void _object3D::asignarTextura(_textura *textura){
    if(this->textura!= textura){
        this->textura= textura;
    }
}

void _object3D::crearTexturas(){
    cout << "o3d\n";

    texturas.resize(Triangles.size());

    for(int i=0; i<Triangles.size(); i+=2){
        texturas[i].resize(3);
        texturas[i][0]= _vertex2f(0,1);
        texturas[i][1]= _vertex2f(1,1);
        texturas[i][2]= _vertex2f(1,0);

        texturas[i+1].resize(3);
        texturas[i+1][0]= _vertex2f(0,1);
        texturas[i+1][1]= _vertex2f(1,0);
        texturas[i+1][2]= _vertex2f(0,0);
    }
}

void _object3D::draw_normales()
{
    if (normalesVertices.empty())
        crearNormalesVertices();
        crearNormalesCaras();
    auto t = 0.1f;



    glPointSize(1);
    glBegin(GL_LINES);

    for (auto i = 0u; i < Vertices.size(); ++i) {
        _vertex3f actual = Vertices[i];
        _vertex3f parametrico;

        /*parametrico.x = actual.x + normalesVertices[i].x * t;
        parametrico.y = actual.y + normalesVertices[i].y * t;
        parametrico.z = actual.z + normalesVertices[i].z * t;*/
        parametrico.x = actual.x + normalesCaras[i].x * t;
        parametrico.y = actual.y + normalesCaras[i].y * t;
        parametrico.z = actual.z + normalesCaras[i].z * t;


        glVertex3fv((GLfloat*) &actual);
        glVertex3fv((GLfloat*) &parametrico);
    }

    glEnd();
}

void _object3D::seleccionado(float *color){

        int num=0; bool encontrado=false; float diferencia=20;
        for(int i=0; i<colores.size(); i++){
            if( (abs(colores[i].x-color[0]) + abs(colores[i].y-color[1])  + abs(colores[i].z-color[2])) < diferencia  ){
                num=i;
                diferencia= (abs(colores[i].x-color[0]) + abs(colores[i].y-color[1])  + abs(colores[i].z-color[2]));
            }
            //cout << colores[i].x << " " <<  color[0] << endl << colores[i].y << " " << color[1]  << endl << colores[i].z <<" " <<  color[2] << endl;
        }

        bool esta= false;
        int pos=0;
        
        if(diferencia < 0.000001){
            for( int j=0; j<this->seleccionados.size(); j++){
                if(seleccionados[j]==num){ pos=j; esta=true;}
            }

            if(esta){
                seleccionados.erase(seleccionados.begin()+pos);
            }else{
                seleccionados.push_back(num);
            }
        }


    

}

