#include <cube.h>

#include <cmath>

_cube::_cube(float Size){

    Vertices.resize(8);

    Vertices[0]= _vertex3f(-Size/2, -Size/2, Size/2);
    Vertices[1]= _vertex3f(Size/2, -Size/2, Size/2);
    Vertices[2]= _vertex3f(Size/2, -Size/2, -Size/2);
    Vertices[3]= _vertex3f(-Size/2, -Size/2, -Size/2);
    Vertices[4]= _vertex3f(-Size/2, Size/2, Size/2);
    Vertices[5]= _vertex3f(Size/2, Size/2, Size/2);
    Vertices[6]= _vertex3f(Size/2, Size/2, -Size/2);
    Vertices[7]= _vertex3f(-Size/2, Size/2, -Size/2);

    Triangles.resize(12);

    Triangles[0]= _vertex3ui(0,1,5);
    Triangles[1]= _vertex3ui(0,5,4);
    Triangles[2]= _vertex3ui(1,2,6);
    Triangles[3]= _vertex3ui(1,6,5);
    Triangles[4]= _vertex3ui(2,3,7);
    Triangles[5]= _vertex3ui(2,7,6);
    Triangles[6]= _vertex3ui(3,0,4);
    Triangles[7]= _vertex3ui(3,4,7);
    Triangles[8]= _vertex3ui(4,5,6);
    Triangles[9]= _vertex3ui(4,6,7);
    Triangles[10]= _vertex3ui(3,2,1);
    Triangles[11]= _vertex3ui(3,1,0);

}

void _cube::crearTexturas(){

    texturas.resize(Triangles.size());

    if(texturaCompleta){
        int cara=1;
        float partesx= 1/4;
        float partesy= 1/3;
        for(int i=0; i<Triangles.size()-4; i+=2){
            texturas[i].resize(3);
            texturas[i][0]= _vertex2f(partesx*cara,partesy*2);
            texturas[i][1]= _vertex2f(fmod(partesx*(cara+1),4.0f),partesy*2);
            texturas[i][2]= _vertex2f(fmod(partesx*(cara+1),4.0f),partesy);

            texturas[i+1].resize(3);
            texturas[i+1][0]= _vertex2f(partesx*cara,partesy*2);
            texturas[i+1][1]= _vertex2f(fmod(partesx*(cara+1),4.0f),partesy);
            texturas[i+1][2]= _vertex2f(partesx,partesy);
            cara= (cara+1)%4;
        }
        cara=1;
        float pos=1;
        for(int i=Triangles.size()-4; i<Triangles.size(); i+=2){
            texturas[i].resize(3);
            texturas[i][0]= _vertex2f(partesx*cara,partesy*pos);
            texturas[i][1]= _vertex2f(fmod(partesx*(cara+1),4.0f),partesy*pos);
            texturas[i][2]= _vertex2f(fmod(partesx*(cara+1),4.0f),partesy*(pos-1));

            texturas[i+1].resize(3);
            texturas[i+1][0]= _vertex2f(partesx*cara,partesy*pos);
            texturas[i+1][1]= _vertex2f(fmod(partesx*(cara+1),4.0f),partesy*(pos-1));
            texturas[i+1][2]= _vertex2f(partesx,partesy*(pos-1));
            pos= 3;
        }
    }else{
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


}

void _cube::asignarTextura(_textura* textura, bool completo){

    if(this->textura!= textura){
        this->textura= textura;
    }
    texturaCompleta=completo;

    
}

