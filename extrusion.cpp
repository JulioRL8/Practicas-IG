#include "extrusion.h"

_extrusion::_extrusion(vector<_vertex3f> perfil, _vertex3f vector)
{
    Vertices.resize(perfil.size()*2);
    for(int i=0; i<perfil.size(); i++){
        Vertices[i]= perfil[i];
    }

    //Crear vertices
    for(int i=0; i<perfil.size(); i++){
        Vertices[i+perfil.size()]= perfil[i]+vector;
    }


    //Crear caras laterales
    for(int i=0; i<perfil.size(); i++){
        Triangles.push_back(_vertex3ui(i, (i+1)%perfil.size(), i+perfil.size()  ));
        int ineg;
        if(i==0) ineg=perfil.size()-1; else ineg=i-1;
        Triangles.push_back(_vertex3ui(i, i+perfil.size(), perfil.size()+ ((ineg)%perfil.size())  ));
    }

    //Caras inferiores y superiores
    if( perfil.size()%2==0){
        for(int i=0; i<perfil.size()-2; i+=2){
            Triangles.push_back(_vertex3ui(i, (i+2)%perfil.size(), i+1  ));
            Triangles.push_back(_vertex3ui(i, perfil.size()-1, i+2  ));
        }
        for(int i=0; i<perfil.size()-2; i+=2){
            Triangles.push_back(_vertex3ui((i+perfil.size()), i+1+perfil.size(), (i+2)%perfil.size()+perfil.size()  ));
            Triangles.push_back(_vertex3ui(i+perfil.size(), (i+2)%perfil.size()+perfil.size() , perfil.size()+perfil.size()-1 ));
        }
    }else{
        for(int i=0; i<perfil.size()-2; i+=2){
            Triangles.push_back(_vertex3ui(i, (i+2)%perfil.size(), i+1  ));
            Triangles.push_back(_vertex3ui(i, perfil.size()-1, i+2  ));
        }
        for(int i=0; i<perfil.size()-2; i+=2){
            Triangles.push_back(_vertex3ui((i+perfil.size()), i+1+perfil.size(), (i+2)%perfil.size()+perfil.size()  ));
            Triangles.push_back(_vertex3ui(i+perfil.size(), (i+2)%perfil.size()+perfil.size() , perfil.size()+perfil.size()-1 ));
        }
    }
}
