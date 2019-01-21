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
#include "textura.h"

//COMENTARIO
class _object3D:public _basic_object3D
{
public:
   vector<_vertex3ui> Triangles;
   vector<_vertex3f>  normalesVertices;
   vector<_vertex3f>  normalesCaras;
   vector<vector<_vertex2f> > texturas;
   _textura *textura;
   vector<int> seleccionados;
   vector<_vertex3f> colores;

   void seleccionado(float *color);
   bool estaSeleccionado(int i);
   void crearColores();

   void draw(ModelView model);
   void draw_selection();
   void draw_line();
   void draw_fill();
   void draw_chess();
   void draw_flat();
   void draw_smooth();
   void draw_tex_smooth();
   void draw_tex_flat();
   void draw_tex();

   void draw_normales();

   void crearNormalesCaras();
   void crearNormalesVertices();
   void asignarTextura(_textura* textura);
   virtual void crearTexturas();

};

#endif // OBJECT3D_H
