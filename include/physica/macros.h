#ifndef PHYSICA_MACROS_H
#define PHYSICA_MACROS_H
#include <stdlib.h>
#include <math.h>
#define NEW(T) (T *)calloc(1, sizeof(T))
#define ONE(g) (ceilf(g) == 0 ? 1 : g)
#endif
