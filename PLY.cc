
#include <PLY.h>
#include <file_ply_stl.h>

_PLY::_PLY(string fichero){
	_file_ply archivo;

	if (archivo.open(fichero)){
    		archivo.read(Vertices,Triangles);
		
	}
	else{
		cout << "El archivo PLY, no ha podido abrirse.\n";
	}
}
