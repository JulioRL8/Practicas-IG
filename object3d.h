/*
 * Practicas de IG
 * Domingo Martin Perandres© 2014-2018
 * dmartin@ugr.es
 *
 * GPL 3
 */

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"
#include "modelview.h"
#include "texture.h"

//COMENTARIO
class _object3D:public _basic_object3D
{
public:
   vector<_vertex3ui> Triangles;
   vector<_vertex3f>  normalesVertices;
   vector<_vertex3f>  normalesCaras;
   vector<_vertex2f> texturas;
   _texture *textura;

   void draw(ModelView model);
   void draw_line();
   void draw_fill();
   void draw_chess();
   void draw_flat();
   void draw_smooth();
   void draw_texIlu();
   void draw_tex();

   void crearNormalesCaras();
   void crearNormalesVertices();
   void crearTexturas(_texture textura);

};

#endif // OBJECT3D_H
