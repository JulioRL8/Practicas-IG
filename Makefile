# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica1

#
GLUT_DIR=/usr
GL_DIR=/usr/X11R6

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraciķn
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I$(GLUT_DIR)/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I$(GLUT_DIR)/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -L$(GL_DIR)/lib64 -lGL -L$(GLUT_DIR)/lib64 -lglut -lpthread -lX11

# definicion del compilador
#
CC = g++ -std=c++11 -std=gnu++11

# sufijos
.SUFFIXES: .cc .c .o

# Reglas
# $< -> todas las dependencias que han cambiado
# $@ -> el objetivo
# $^ -> todas las dependencias

# como pasar de .cc a .o

.cc.o:
	$(CC) $(CXXFLAGS) -c $<

# como pasar de .o a ejecutable (sin sufijo)

.o:
	$(CC) -o $@ $^ $(LDFLAGS) 

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de dependencias
#
$(TARGETS) : basic_object3d.o object3d.o axis.o tetrahedron.o practica1.o cube.o PLY.o revolucion.o file_ply_stl.o cilindro.o cono.o esfera.o extrusion.o transformation.o mesh.o grua.o light.o texture.o tablero.o

practica1.o: practica1.cc

basic_object3d.o: basic_object3d.cpp basic_object3d.h

object3d.o: object3d.cc object3d.h

axis.o: basic_object3d.o axis.cpp axis.h

tetrahedron.o: tetrahedron.cc tetrahedron.h

cube.o: cube.cpp cube.h

PLY.o: PLY.cc PLY.h

file_ply_stl.o: file_ply_stl.cc file_ply_stl.h

revolucion.o: revolucion.cc revolucion.h

cilindro.o: cilindro.cpp cilindro.h

cono.o: cono.cpp cono.h

esfera.o: esfera.cpp esfera.h

extrusion.o: extrusion.cpp extrusion.h

transformation.o: transformation.cpp transformation.h

mesh.o: mesh.cpp mesh.h

grua.o: grua.cpp grua.h

light.o: light.cpp light.h

texture.o: texture.cpp texture.h

tablero.o: tablero.cpp tablero.h

#watt.o: watt.cpp watt.h

#
#
clean:
	rm -f *.o
#	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *

