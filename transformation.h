#ifndef _TRANSFORMATION_H
#define _TRANSFORMATION_H

#include "transtype.h"
#include "vertex.h"

class _transformation
{
public:
    transType type;
    _vertex3f parameters;
    _transformation(transType tipo, _vertex3f vector );
};

#endif // _TRANSFORMATION_H
