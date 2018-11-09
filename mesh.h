#ifndef MESH_H
#define MESH_H

#include "object3d.h"
#include "transformation.h"
#include "cilindro.h"


class _mesh : public _object3D
{
protected:

    vector<_mesh> hijos;
    vector<_transformation> transformaciones;

public:



    _mesh();
    _mesh(_object3D objeto);
    _mesh(_revolucion cil);

    //Añadir hijos al nodo
    void add(_mesh hijo);
    void add(_object3D objeto);

    //Transformaciones
    void translation(_vertex3f vector);
    void scalation(_vertex3f vector);
    void rotation(_vertex3f vector);
    void translation(float x, float y, float z);
    void scalation(float x, float y, float z);
    void rotation(float x, float y, float z);

    //Metodo de dibujado
    void drawMesh(ModelView model);

    //Modificar las transformaciones
    void transpop_back();
};

#endif // MESH_H
