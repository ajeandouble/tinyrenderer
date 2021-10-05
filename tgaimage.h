#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct
{
	uint8_t r, g, b;
} tga_color;

typedef struct tga_image
{
	tga_color *dataBGR;
	void (*set)(struct tga_image *self, int x, int y, tga_color color);
	int width, height;
} tga_image;

tga_image tga_image_init(int width, int height);
tga_color tga_new_color(uint8_t r, uint8_t g, uint8_t b);

void tga_write(const char *filename, tga_image *image);

#endif
