#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "tgaimage.h"

void draw_line(int x0, int y0, int x1, int y1, tga_image *image, tga_color color);

typedef struct {
  float x;
  float y;
  float z;
} vertex;

typedef struct {
  int x;
  int y;
} point;

typedef struct {
  float x;
  float y;
} fPoint;

typedef struct {
  int x0;
  int y0;
  int x1;
  int y1;
} line;

typedef struct {
  vertex a;
  vertex b;
  vertex c;
} triangle;

void draw_triangle(triangle t, tga_image *image, tga_color color);

#endif
