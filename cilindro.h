#ifndef CILINDRO_H
#define CILINDRO_H

#include "revolucion.h"

class _cilindro : public _revolucion
{
public:
    _cilindro(float altura=1, float anchura=1, int revoluciones=26);
};

#endif // CILINDRO_H
