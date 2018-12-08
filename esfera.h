#ifndef _ESFERA_H
#define _ESFERA_H

#include "revolucion.h"

class _esfera : public _revolucion
{
private:
    int revoluciones;
public:
    _esfera(float radio=0.5, int revoluciones=26);
};

#endif // _ESFERA_H
