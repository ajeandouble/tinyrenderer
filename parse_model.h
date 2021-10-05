#ifndef PARSE_MODEL_H
#define PARSE_MODEL_H

#include <stdio.h>
#include "geometry.h"


typedef struct { vertex a; vertex b; vertex c; } face;

size_t parse_model(FILE *fp, face **dest_faces);

#endif