#ifndef _CONO_H
#define _CONO_H

#include "revolucion.h"

class _cono : public _revolucion
{
public:
    _cono(float altura=1, int revoluciones=26);
    void crearTexturas();
};

#endif // _CONO_H
