#include "revolucion.h"
#include <cmath>

using namespace std;

const float PI= 3.1415926535897932384;

void _revolucion::crearMalla(vector<_vertex3f> perfil, int revoluciones){
    this->numVertices= perfil.size();
    int numVerticesTotal= numVertices * revoluciones;
    float incrementoAngulo= 2*PI/revoluciones;
    this->revolucion= revoluciones;

    Vertices.resize( numVertices );
    Triangles.clear();

    //Meter vertices del perfil
     vector<unsigned int> VerticesSinRepetir; //Vector que almacena la lista de vertices, que se usará para apuntar a los vertices reales( para no duplicar vertices)
    for(int i=0; i<numVertices; i++){
        Vertices[i]= perfil[i];
        VerticesSinRepetir.push_back(i);
    }

    //Ver si esta en sentido ascendente o descendente
    bool ascendente= perfil[0].y < perfil[numVertices-1].y;

    //Generar vertices

    for(int i=1; i< revoluciones; i++){
        for(int j=0; j<numVertices; j++){
            if(Vertices[j].x==0.0){
                VerticesSinRepetir.push_back(j);
            }else{
                float angulo= i*incrementoAngulo;
                float x= Vertices[j].x * cos(angulo);
                float z= Vertices[j].x * sin(angulo);
                Vertices.push_back(_vertex3f(x, Vertices[j].y, z));
                VerticesSinRepetir.push_back(Vertices.size()-1);
            }

        }

    }


    //Generar caras
    if(perfil[0].x<0.01 or perfil[perfil.size()-1].x<0.01){
        int desde, hasta;
        if(perfil[0].x<0.01) desde=1; else desde=0;
        if(perfil[perfil.size()-1].x<0.01) hasta= perfil.size()-2; else hasta= perfil.size()-1;

        //Caras internas
        for(int i=0; i<revoluciones; i++){
            for(int j=desde; j<hasta; j++){
                if(ascendente){
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[j+numVertices*i], VerticesSinRepetir[(j+numVertices*(i+1)+1)%numVerticesTotal], VerticesSinRepetir[(j+numVertices*(i+1))%numVerticesTotal] ));
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[j+numVertices*i], VerticesSinRepetir[j+numVertices*i+1], VerticesSinRepetir[(j+numVertices*(i+1)+1)%numVerticesTotal] ));
                }else{
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[j+numVertices*i], VerticesSinRepetir[(j+numVertices*(i+1))%numVerticesTotal], VerticesSinRepetir[(j+numVertices*(i+1)+1)%numVerticesTotal] ));
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[j+numVertices*i], VerticesSinRepetir[(j+numVertices*(i+1)+1)%numVerticesTotal], VerticesSinRepetir[j+numVertices*i+1] ));
                }

            }
        }

        //Caras superiores e inferiores

        if(perfil[0].x<0.01){
            for(int i=0; i<revoluciones; i++){
                if(ascendente){
                    //Triangles.push_back( _vertex3ui(VerticesSinRepetir[0+numVertices*i], VerticesSinRepetir[(0+numVertices*(i+1)+1)%numVerticesTotal], VerticesSinRepetir[(0+numVertices*(i+1))%numVerticesTotal] ));
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[0+numVertices*i], VerticesSinRepetir[0+numVertices*i+1], VerticesSinRepetir[(0+numVertices*(i+1)+1)%numVerticesTotal] ));
                }else{
                    //Triangles.push_back( _vertex3ui(VerticesSinRepetir[0+numVertices*i], VerticesSinRepetir[(0+numVertices*(i+1))%numVerticesTotal], VerticesSinRepetir[(0+numVertices*(i+1)+1)%numVerticesTotal] ));
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[0+numVertices*i], VerticesSinRepetir[(0+numVertices*(i+1)+1)%numVerticesTotal], VerticesSinRepetir[0+numVertices*i+1] ));
                }

            }
        }

        if(perfil[perfil.size()-1].x<0.01){
            for(int i=0; i<revoluciones; i++){
                if(ascendente){
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[numVertices-2+numVertices*i], VerticesSinRepetir[(numVertices-2+numVertices*(i+1)+1)%numVerticesTotal], VerticesSinRepetir[(numVertices-2+numVertices*(i+1))%numVerticesTotal] ));
                    //Triangles.push_back( _vertex3ui(VerticesSinRepetir[numVertices-2+numVertices*i], VerticesSinRepetir[numVertices-2+numVertices*i+1], VerticesSinRepetir[(numVertices-2+numVertices*(i+1)+1)%numVerticesTotal] ));
                }else{
                    Triangles.push_back( _vertex3ui(VerticesSinRepetir[numVertices-2+numVertices*i], VerticesSinRepetir[(numVertices-2+numVertices*(i+1))%numVerticesTotal], VerticesSinRepetir[(numVertices-2+numVertices*(i+1)+1)%numVerticesTotal] ));
                    //Triangles.push_back( _vertex3ui(VerticesSinRepetir[numVertices-2+numVertices*i], VerticesSinRepetir[(numVertices-2+numVertices*(i+1)+1)%numVerticesTotal], VerticesSinRepetir[numVertices-2+numVertices*i+1] ));
                }

            }
        }

    }else{
        for(int i=0; i<revoluciones; i++){
            for(int j=numVertices*i; j<numVertices*i+numVertices-1; j++){
                Triangles.push_back(_vertex3ui(VerticesSinRepetir[j],VerticesSinRepetir[(j+numVertices+1)%numVerticesTotal],VerticesSinRepetir[(j+numVertices)%numVerticesTotal]));
                Triangles.push_back(_vertex3ui(VerticesSinRepetir[j],VerticesSinRepetir[(j+1)%numVerticesTotal], VerticesSinRepetir[(j+numVertices+1)%numVerticesTotal]));
            }
        }
    }

}

_revolucion::_revolucion(vector<_vertex3f> perfil, int revoluciones){
    /*vector<_vertex3f> perfil;
    perfil.resize(4);
    perfil[3]= _vertex3f(0,-0.5,0);
    perfil[2]= _vertex3f(0.5,-0.5,0);
    perfil[1]= _vertex3f(0.5,0.5,0);
    perfil[0]= _vertex3f(0,0.5,0);

    perfil[0]= _vertex3f(0,-0.5,0);
    perfil[1]= _vertex3f(0.5,-0.5,0);
    perfil[2]= _vertex3f(0.5,0.5,0);
    perfil[3]= _vertex3f(0,0.5,0);*/

    crearMalla(perfil,revoluciones);

}

_revolucion::_revolucion(){
    //Para crear los sub objetos de revolucion
}

void _revolucion::crearTexturas(){
    cout << "revolucion\n";
    /*bool ascendente= Vertices[0].y < Vertices[1].y;
    float partesy= 1.0/numVertices;
    float partesx= 1.0/ revolucion;
    int cuantos= numVertices;
    int inicio=numVertices-1;
    int hasta=0;
    if(Vertices[0].y < 0.01) hasta++; cuantos--;
    if(Vertices[numVertices-1].y < 0.01) inicio--; cuantos--;
    if(!ascendente) { int aux= inicio; inicio=hasta; hasta= aux;}

    Texturas.resize(Triangles.size());

    /*if(ascendente){

        int j= inicio;
        int donde=0;
        for(int i=0; i<Triangles.size(); i+=2){

            texturas[i].resize(3);

            texturas[i][0]= _vertex2f(partesx*,partesy*inicio);
            texturas[i][1]= _vertex2f(partesx*,partesy*inicio);
            texturas[i][2]= _vertex2f(partesx*,partesy*inicio);

            texturas[i+1].resize(3);
            texturas[i+1][0]= _vertex2f(partesx*,partesy*inicio);
            texturas[i+1][1]= _vertex2f(partesx*,partesy*inicio);
            texturas[i+1][2]= _vertex2f(partesx*,partesy*inicio);

            donde++;
            if(donde > cuantos) donde=0;
        }
    }*/
    float desde=0;
    int hasta= numVertices-1;
    float partesy= 1.0/ (numVertices-1);
    float partesx= 1.0/ (revolucion);

    if(Vertices[0].x < 0.01) desde=1;
    if(Vertices[numVertices-1].x= 0.01) hasta--;

    //Caras del centro
    for(int i=0; i<revolucion; i++){
        for(int j=desde;  j<hasta; j++){
            vector< _vertex2f> tex;

            tex.resize(3);
            tex[0]= _vertex2f(partesx*i, 1-partesy*j);
            tex[1]= _vertex2f(partesx*i+partesx, 1-partesy*(j));
            tex[2]= _vertex2f(partesx*i+partesx, 1-partesy*(j)-partesy);

            texturas.push_back(tex);

            tex[0]= _vertex2f(partesx*i, 1-partesy*j);
            tex[1]= _vertex2f(partesx*i+partesx, 1-partesy*j-partesy);
            tex[2]= _vertex2f(partesx*i, 1-partesy*j-partesy);

            texturas.push_back(tex);

        }
    }


    //Cara inferior
    if(Vertices[0].x < 0.01){
        for(int i=0; i<revolucion; i++){
            vector< _vertex2f> tex;

            tex.resize(3);
            tex[0]= _vertex2f(0, 1);
            tex[2]= _vertex2f(partesx*(i+1), 1-partesy);
            tex[1]= _vertex2f(partesx*i, 1-partesy);

            texturas.push_back(tex);

            /*tex[0]= _vertex2f(partesx*i, 1);
            tex[2]= _vertex2f(partesx*i+partesx, 1-partesy);
            tex[1]= _vertex2f(partesx*i, 1-partesy);

            texturas.push_back(tex);*/
        }
    }

    //Cara superior
    if(Vertices[numVertices-1].x < 0.01){
        for(int i=0; i<revolucion; i++){
            vector< _vertex2f> tex;

            tex.resize(3);
            tex[0]= _vertex2f(partesx*i, partesy);
            tex[2]= _vertex2f(partesx*i+partesx, partesy);
            tex[1]= _vertex2f(0, 0);

            texturas.push_back(tex);

        }
    }

 }

