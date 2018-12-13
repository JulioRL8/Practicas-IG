/*
 * Practicas de IG
 * Domingo Martin Perandres© 2014-2018
 * dmartin@ugr.es
 *
 * GPL 3
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include "stdlib.h"
#include "stdio.h"
#include <ctype.h>

#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"
#include "PLY.h"
#include "revolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "extrusion.h"
#include "grua.h"
#include "modelview.h"
#include "light.h"
#include "tablero.h"

using namespace _colors_ne;
using namespace std;

const float X_MIN=-.1;
const float X_MAX=.1;
const float Y_MIN=-.1;
const float Y_MAX=.1;
const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
const float BACK_PLANE_PERSPECTIVE=1000;
const float DEFAULT_DISTANCE=2;
const float ANGLE_STEP=1;

typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE, OBJECT_PLY, OBJECT_REV, OBJECT_CYLINDER, OBJECT_CONE, OBJECT_SPHERE, OBJECT_EXTRUSION, OBJECT_TAB, OBJECT_GRUA} _object;

typedef enum {MODE_RENDERING_SOLID,MODE_RENDERING_SOLID_CHESS, MODE_RENDERING_ILLUMINATION_FLAT_SHADING, MODE_RENDERING_ILLUMINATION_SMOOTH_SHADING, MODE_RENDERING_TEXTURE, MODE_RENDERING_TEXTURE_ILLUMINATION_FLAT_SHADING, MODE_RENDERING_TEXTURE_ILLUMINATION_SMOOTH_SHADING, MODE_NORMALES} _mode_rendering;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_angle_x=0;
GLfloat Observer_angle_y=0;
GLfloat Observer_distance=DEFAULT_DISTANCE;

// variables que controlan la ventana y la transformacion de perspectiva
// GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=800,UI_window_height=800;

_axis Axis;
_tetrahedron Tetrahedron;
_cube Cube;
_PLY ply("beethoven.ply");
_grua Grua;

_textura* textura1;
_textura* textura2;
_textura* textura3;




_extrusion cuadrado(){
    vector<_vertex3f> perfil;
    perfil.resize(5);
    perfil[0]= _vertex3f(-0.25,-0.5,0.5);
    perfil[1]= _vertex3f(0.25,-0.5,0.5);
    perfil[2]= _vertex3f(0.75,-0.5,0.0);
    perfil[3]= _vertex3f(0.0,-0.5,-0.75);
    perfil[4]= _vertex3f(-0.75,-0.5,0.0);
    /*perfil[0]= _vertex3f(-0.25,-0.5,0.5);
    perfil[1]= _vertex3f(0.25,-0.5,0.5);
    perfil[2]= _vertex3f(0.75,-0.5,0.0);
    perfil[3]= _vertex3f(0.25,-0.5,-0.5);
    perfil[4]= _vertex3f(0.0,-0.5,-0.25);
    perfil[5]= _vertex3f(-0.25,-0.5,-0.5);
    perfil[6]= _vertex3f(-0.75,-0.5,0.0);
    /*perfil[0]= _vertex3f(-0.25,-0.5,0.5);
    perfil[1]= _vertex3f(0.25,-0.5,0.5);
    perfil[2]= _vertex3f(0.75,-0.5,0.0);
    perfil[3]= _vertex3f(0.25,-0.5,-0.5);
    perfil[4]= _vertex3f(-0.25,-0.5,-0.5);
    perfil[5]= _vertex3f(-0.75,-0.5,0.0);
    /*perfil[0]= _vertex3f(-0.5,-0.5,0.5);
    perfil[1]= _vertex3f(0.5,-0.5,0.5);
    perfil[2]= _vertex3f(0.5,-0.5,-0.5);
    perfil[3]= _vertex3f(-0.5,-0.5,-0.5);*/
    /*perfil.push_back(_vertex3f(0.5,-0.5,0.5));
    perfil.push_back(_vertex3f(0.5,-0.5,-0.5));
    perfil.push_back(_vertex3f(-0.5,-0.5,-0.5));*/

    _extrusion ext= _extrusion(perfil, _vertex3f(1.0,1.0,1.0));
    return ext;
}

_revolucion revSimple(){
    vector<_vertex3f> perfil;
    perfil.resize(4);
    perfil[0]= _vertex3f(0.0,-0.5,0.0);
    perfil[1]= _vertex3f(0.5,-0.5,0.0);
    perfil[2]= _vertex3f(0.5,0.5,0.0);
    perfil[3]= _vertex3f(0.0,0.5,0.0);


    _revolucion ext= _revolucion(perfil, 3);
    return ext;
}

//Objeto Revolucionado
_cilindro cylinder(1,0.5);
_cono cone(1);
_revolucion revolucionado= revSimple();
_esfera sphere(0.5);
_extrusion extrusion= cuadrado();
_tablero tab;

//Definicion de luces
vector<_light> luces= {_light(GL_LIGHT0, _vertex4f(100,10,0,1)), _light(GL_LIGHT1, _vertex4f(-100,5,6,1), _vertex4f(1,1,1,1), _vertex4f(0.255,0,0.255,1), _vertex4f(0.255,0,0.255,1)) };

/*luces.add(_light(GL_LIGHT1, Directional, _vertex4f(0,0,1,0)));
luces.add(_light(GL_LIGHT1, Directional, _vertex4f(6,5,6,1)));*/


bool Draw_point=false;
bool Draw_line=true;
bool Draw_fill=false;
bool Draw_chess=false;
bool Draw_flat= false;
bool Draw_smooth= false;
bool Draw_normales= false;

int material=0;

_object Object=OBJECT_TETRAHEDRON;
_mode_rendering Mode_rendering=MODE_RENDERING_SOLID;
bool Light0_active= false;
bool Light1_active= false;

/***********************************************************************************************/


/**
 *
 *
 *@param
 *@returns
 */

void set_lights()
{
    if(luces[0].isOn()){ luces[0].on();}else{ luces[0].off();}
    if(luces[1].isOn()){ luces[1].on();}else{ luces[1].off();}
}

/**
 *
 *@param
 *@returns
 */

void set_materials()
{
   switch (material){
      case 0:{
         _vertex3f Material_diffuse(0.3,0.3,0.3);
         _vertex3f Material_specular(0.1,0.1,0.1);
         _vertex3f Material_ambient(0.05,0.05,0.05);
         float Material_shininess=1;

         glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&Material_diffuse);
         glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&Material_specular);
         glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&Material_ambient);
         glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Material_shininess);
      }
      break;

      case 1:{ // segundo material
       float mat_ambient[4] ={ 0.2125f, 0.1275f, 0.054f, 1.0f };
       float mat_diffuse[4] ={ 0.714f, 0.4284f, 0.18144f, 1.0f };
       float mat_specular[4] ={ 0.393548f, 0.271906f, 0.166721f, 1.0f };
       float shine = 25.6f;

       glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&mat_diffuse);
       glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&mat_specular);
       glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&mat_ambient);
       glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);

      }
      break;

      case 2:{ // tercer material
       float mat_ambient[4] ={ 0.329412f, 0.223529f, 0.027451f,1.0f };
       float mat_diffuse[4] ={ 0.780392f, 0.568627f, 0.113725f, 1.0f };
       float mat_specular[4]={ 0.992157f, 0.941176f, 0.807843f, 1.0f };
       float shine = 27.8974f;

       glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&mat_diffuse);
       glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&mat_specular);
       glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&mat_ambient);
       glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shine);
      }break;
   }
}


void set_textures(){
    if(textura1==NULL) textura1= new _textura("textura.jpg");
    if(textura2==NULL) textura2= new _textura("imagen_share.png");
    if(textura3==NULL) textura3= new _textura("dado.png");
}

/**
 * Limpiar ventana
 *
 *@param
 *@returns
 */

void clear_window()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


/**
 * Funcion para definir la transformación de proyeccion
 *
 *@param
 *@returns
 */


void change_projection()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
   //  Front_plane>0  Back_plane>PlanoDelantero)
   glFrustum(X_MIN,X_MAX,Y_MIN,Y_MAX,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
}


/**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *@param
 *@returns
 */

void change_observer()
{
   set_lights();
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0,0,-Observer_distance);
   glRotatef(Observer_angle_x,1,0,0);
   glRotatef(Observer_angle_y,0,1,0);
}


/**
 * Funcion que dibuja los objetos
 *
 *@param
 *@returns
 */

void draw_objects()
{
   Axis.draw_line();

   if (Draw_point){
      glPointSize(5);
      glColor3fv((GLfloat *) &BLACK);
      switch (Object){
	 case OBJECT_TETRAHEDRON:Tetrahedron.draw_point();break;
	 case OBJECT_CUBE:Cube.draw_point();break;
	 case OBJECT_PLY:ply.draw_point();break;
     case OBJECT_REV:revolucionado.draw_point(); break;
     case OBJECT_CONE:cone.draw_point(); break;
     case OBJECT_CYLINDER:cylinder.draw_point(); break;
     case OBJECT_SPHERE:sphere.draw_point(); break;
     case OBJECT_EXTRUSION:extrusion.draw_point(); break;
     case OBJECT_GRUA:Grua.draw(points); break;
     case OBJECT_TAB: tab.draw(points); break;
	 default:break;
      }
   }

   if (Draw_line){
      glLineWidth(3);
      glColor3fv((GLfloat *) &MAGENTA);
      switch (Object){
	 case OBJECT_TETRAHEDRON:Tetrahedron.draw_line();break;
	 case OBJECT_CUBE:Cube.draw_line();break;
	 case OBJECT_PLY:ply.draw_line();break;
     case OBJECT_REV:revolucionado.draw_line(); break;
     case OBJECT_CONE:cone.draw_line(); break;
     case OBJECT_CYLINDER:cylinder.draw_line(); break;
     case OBJECT_SPHERE:sphere.draw_line(); break;
     case OBJECT_EXTRUSION:extrusion.draw_line(); break;
     case OBJECT_GRUA:Grua.draw(lines); break;
     case OBJECT_TAB: tab.draw(lines); break;
	 default:break;
      }
   }

   if(Draw_normales){
       switch (Object){
      case OBJECT_TETRAHEDRON:Tetrahedron.draw_normales();break;
      case OBJECT_CUBE:Cube.draw_normales();break;
      case OBJECT_PLY:ply.draw_normales();break;
      case OBJECT_REV:revolucionado.draw_normales(); break;
      case OBJECT_CONE:cone.draw_normales(); break;
      case OBJECT_CYLINDER:cylinder.draw_normales(); break;
      case OBJECT_SPHERE:sphere.draw_normales(); break;
      case OBJECT_EXTRUSION:extrusion.draw_normales(); break;
      case OBJECT_GRUA:Grua.draw(lines); break;
      case OBJECT_TAB: tab.draw(lines); break;
      default:break;
       }
   }

    if (Draw_fill){

        switch(Mode_rendering){

            case MODE_RENDERING_SOLID:
                    //set_materials();
                    glColor3fv((GLfloat *) &BLUE);
                    //glEnable(GL_LIGHTING);
                      switch (Object){
	                 case OBJECT_TETRAHEDRON:Tetrahedron.draw_fill();break;
	                 case OBJECT_CUBE:Cube.draw_fill();break;
	                 case OBJECT_PLY:ply.draw_fill();break;
                     case OBJECT_REV:revolucionado.draw_fill(); break;
                     case OBJECT_CONE:cone.draw_fill(); break;
                     case OBJECT_CYLINDER:cylinder.draw_fill(); break;
                     case OBJECT_SPHERE:sphere.draw_fill(); break;
                     case OBJECT_EXTRUSION:extrusion.draw_fill(); break;
                     case OBJECT_GRUA:Grua.draw(FILL); break;
                     case OBJECT_TAB: tab.draw(FILL); break;
	                 default:break;
                    }
                    //glDisable(GL_LIGHTING);
            break;

            case MODE_RENDERING_SOLID_CHESS:
                //set_materials();


                switch (Object){
	             case OBJECT_TETRAHEDRON:Tetrahedron.draw_chess();break;
	             case OBJECT_CUBE:Cube.draw_chess();break;
	             case OBJECT_PLY:ply.draw_chess();break;
                 case OBJECT_REV:revolucionado.draw_chess(); break;
                 case OBJECT_CONE:cone.draw_chess(); break;
                 case OBJECT_CYLINDER:cylinder.draw_chess(); break;
                 case OBJECT_SPHERE:sphere.draw_chess(); break;
                 case OBJECT_EXTRUSION:extrusion.draw_chess(); break;
                 case OBJECT_GRUA:Grua.draw(chess); break;
                 case OBJECT_TAB: tab.draw(chess); break;
	             default:break;
                  }


            break;
        
            case MODE_RENDERING_ILLUMINATION_FLAT_SHADING:
                    set_materials();

                      switch (Object){
                     case OBJECT_TETRAHEDRON:Tetrahedron.draw_flat();break;
                     case OBJECT_CUBE:Cube.draw_flat();break;
                     case OBJECT_PLY:ply.draw_flat();break;
                     case OBJECT_REV:revolucionado.draw_flat(); break;
                     case OBJECT_CONE:cone.draw_flat(); break;
                     case OBJECT_CYLINDER:cylinder.draw_flat(); break;
                     case OBJECT_SPHERE:sphere.draw_flat(); break;
                     case OBJECT_EXTRUSION:extrusion.draw_flat(); break;
                     case OBJECT_GRUA:Grua.draw(flat); break;
                     case OBJECT_TAB: tab.draw(flat); break;
                     default:break;
                     }
            break;

            case MODE_RENDERING_ILLUMINATION_SMOOTH_SHADING:
                    set_materials();
        
                      switch (Object){
                     case OBJECT_TETRAHEDRON:Tetrahedron.draw_smooth();break;
                     case OBJECT_CUBE:Cube.draw_smooth();break;
                     case OBJECT_PLY:ply.draw_smooth();break;
                     case OBJECT_REV:revolucionado.draw_smooth(); break;
                     case OBJECT_CONE:cone.draw_smooth(); break;
                     case OBJECT_CYLINDER:cylinder.draw_smooth(); break;
                     case OBJECT_SPHERE:sphere.draw_smooth(); break;
                     case OBJECT_EXTRUSION:extrusion.draw_smooth(); break;
                     case OBJECT_GRUA:Grua.draw(smooth); break;
                     case OBJECT_TAB: tab.draw(smooth); break;
                     default:break;
                     }
            break;

            case MODE_RENDERING_TEXTURE:
                switch (Object){
               case OBJECT_TETRAHEDRON:Tetrahedron.asignarTextura(textura2); Tetrahedron.draw_tex();break;
               case OBJECT_CUBE: Cube.asignarTextura(textura3, true); Cube.draw_tex();break;
               case OBJECT_PLY:ply.draw_smooth();break;
               case OBJECT_REV:revolucionado.asignarTextura(textura2); revolucionado.draw_tex(); break;
               case OBJECT_CONE: cone.asignarTextura(textura1); cone.draw_tex(); break;
               case OBJECT_CYLINDER:cylinder.asignarTextura(textura2); cylinder.draw_tex(); break;
               case OBJECT_SPHERE: sphere.asignarTextura(textura2); sphere.draw_tex(); break;
               case OBJECT_EXTRUSION:extrusion.asignarTextura(textura2); extrusion.draw_tex(); break;
               case OBJECT_GRUA: Grua.addTextures(textura2); Grua.draw(texture); break;
               case OBJECT_TAB: tab.asignarTextura(textura2); tab.draw_tex();break;
               default:break;
               }
            break;

            case MODE_RENDERING_TEXTURE_ILLUMINATION_FLAT_SHADING:
                set_materials();
                switch (Object){
               case OBJECT_TETRAHEDRON:Tetrahedron.asignarTextura(textura2); Tetrahedron.draw_tex_flat();break;
               case OBJECT_CUBE: Cube.asignarTextura(textura3, true); Cube.draw_tex_flat();break;
               case OBJECT_PLY:ply.draw_smooth();break;
               case OBJECT_REV:revolucionado.asignarTextura(textura2); revolucionado.draw_tex_flat(); break;
               case OBJECT_CONE: cone.asignarTextura(textura1); cone.draw_tex_flat(); break;
               case OBJECT_CYLINDER:cylinder.asignarTextura(textura2); cylinder.draw_tex_flat(); break;
               case OBJECT_SPHERE: sphere.asignarTextura(textura2); sphere.draw_tex_flat(); break;
               case OBJECT_EXTRUSION:extrusion.asignarTextura(textura2); extrusion.draw_tex_flat(); break;
               case OBJECT_GRUA: Grua.addTextures(textura2); Grua.draw(texture_flat); break;
               case OBJECT_TAB: tab.asignarTextura(textura2); tab.draw_tex_flat();break;
               default:break;
               }
           break;

            case MODE_RENDERING_TEXTURE_ILLUMINATION_SMOOTH_SHADING:
                set_materials();

                switch (Object){
               case OBJECT_TETRAHEDRON:Tetrahedron.asignarTextura(textura2); Tetrahedron.draw_tex_smooth();break;
               case OBJECT_CUBE: Cube.asignarTextura(textura3, true); Cube.draw_tex_smooth();break;
               case OBJECT_PLY:ply.draw_smooth();break;
               case OBJECT_REV:revolucionado.asignarTextura(textura2); revolucionado.draw_tex_smooth(); break;
               case OBJECT_CONE: cone.asignarTextura(textura1); cone.draw_tex_smooth(); break;
               case OBJECT_CYLINDER:cylinder.asignarTextura(textura2); cylinder.draw_tex_smooth(); break;
               case OBJECT_SPHERE: sphere.asignarTextura(textura2); sphere.draw_tex_smooth(); break;
               case OBJECT_EXTRUSION:extrusion.asignarTextura(textura2); extrusion.draw_tex_smooth(); break;
               case OBJECT_GRUA: Grua.addTextures(textura2); Grua.draw(texture_smooth); break;
               case OBJECT_TAB: tab.asignarTextura(textura2); tab.draw_tex_smooth();break;
               default:break;
               }
           break;
      }

    
   }

  
}


/**
 * Evento de dibujado
 *
 *@param
 *@returns
 */

void draw_scene(void)
{
   clear_window();
   change_observer();
   draw_objects();
   glutSwapBuffers();
}


/**
 * Evento de cambio de tamaño de la ventana
 *@param
 *@returns
 */

void resize(int Ancho1,int Alto1)
{
// 	change_projection();
   glViewport(0,0,Ancho1,Alto1);
   glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
   string nombre;
   switch (toupper(Tecla1)){
      case '1':Object=OBJECT_TETRAHEDRON;break;
      case '2':Object=OBJECT_CUBE;break;
      case '3':Object=OBJECT_CONE;break;
      case '4':Object=OBJECT_CYLINDER;break;
      case '5':Object=OBJECT_SPHERE;break;
      case '6':Object=OBJECT_PLY;
      case '7':Object=OBJECT_GRUA; break;
      case '8':Object=OBJECT_TAB; break;


            /*cout << "Introduzca el archivo PLY: "; cin >> nombre; ply= _PLY(nombre); break;*/
      //case '7':Object=OBJECT_EXTRUSION; break;
      
      //case '9':Object=OBJECT_GRUA; break;
    
      case 'P':Draw_point=!Draw_point;break;
      case 'L':Draw_line=!Draw_line;break;
      case 'F':Draw_fill=!Draw_fill;break;
      case 'C':Draw_chess=!Draw_chess;break;
      case 'N':Draw_normales=!Draw_normales;break;
      /*case 'Z':Draw_flat= !Draw_flat; break;
      case 'X':Draw_smooth= !Draw_smooth; break;*/

      /*case 'J': Light0_active= !Light0_active;break;//luces[0].Switch();
      case 'K': Light1_active= !Light1_active;break;//luces[1].Switch();*/
      
      case 'J': luces[0].Switch();break;
      case 'K': luces[1].Switch();break;

       case 'M': material = (material + 1)%3;break;

      case 'T':Grua.moverGancho(0.05);break;
      case 'G':Grua.moverGancho(-0.05);break;
      case 'Y':Grua.girarEje1(5);break;
      case 'H':Grua.girarEje1(-5);break;
      case 'U':Grua.girarEje2(5);break;
      //case 'J':Grua.girarEje2(-5);break;
      case 'I':Grua.girarRotatorio(5);break;
      //case 'K':Grua.girarRotatorio(-5);break;


      case 'Q':exit(0);
   }
   glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{
   switch (Tecla1){
      case GLUT_KEY_LEFT:Observer_angle_y--;break;
      case GLUT_KEY_RIGHT:Observer_angle_y++;break;
      case GLUT_KEY_UP:Observer_angle_x--;break;
      case GLUT_KEY_DOWN:Observer_angle_x++;break;
      case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
      case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
      case GLUT_KEY_F1: Mode_rendering= MODE_RENDERING_SOLID; break;
      case GLUT_KEY_F2: Mode_rendering= MODE_RENDERING_SOLID_CHESS; break;
      case GLUT_KEY_F3: Mode_rendering= MODE_RENDERING_ILLUMINATION_FLAT_SHADING; break;
      case GLUT_KEY_F4: Mode_rendering= MODE_RENDERING_ILLUMINATION_SMOOTH_SHADING; break;
      case GLUT_KEY_F5: Mode_rendering= MODE_RENDERING_TEXTURE; break;
      case GLUT_KEY_F6: Mode_rendering= MODE_RENDERING_TEXTURE_ILLUMINATION_FLAT_SHADING; break;
      case GLUT_KEY_F7: Mode_rendering= MODE_RENDERING_TEXTURE_ILLUMINATION_SMOOTH_SHADING; break;


 
   }
   glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
   // se indica cual sera el color para limpiar la ventana	(r,v,a,al)
   glClearColor(1,1,1,1);

   set_textures();

   // se habilita el z-bufer
   glEnable(GL_DEPTH_TEST);
   //
   change_projection();
   //
   glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
   // se llama a la inicialización de glut
   glutInit(&argc, argv);

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   // Las posibilidades son:
   // GLUT_SIMPLE -> memoria de imagen simple
   // GLUT_DOUBLE -> memoria de imagen doble
   // GLUT_INDEX -> memoria de imagen con color indizado
   // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
   // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
   // GLUT_DEPTH -> memoria de profundidad o z-bufer
   // GLUT_STENCIL -> memoria de estarcido
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
   // al bucle de eventos)
   glutCreateWindow("Practica 3");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc(draw_scene);
   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc(resize);
   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc(normal_keys);
   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc(special_keys);

   // funcion de inicialización
   initialize();

   // inicio del bucle de eventos
   glutMainLoop();
   return 0;
}
