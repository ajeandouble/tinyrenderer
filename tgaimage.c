#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "tgaimage.h"

void tga_write(const char *filename, tga_image *image)
{
	FILE *fp = NULL;
	fp = fopen(filename, "wb");
	if (fp == NULL) return;

	uint8_t dataChannels = 3;
	uint8_t fileChannels = 3;

	int width = image->width;
	int height = image->height;
	tga_color *dataBGR = image->dataBGR;

	uint8_t header[18] = {0,
						  0,
						  2,
						  0,
						  0,
						  0,
						  0,
						  0,
						  0,
						  0,
						  0,
						  0,
						  (uint8_t)(width % 256),
						  (uint8_t)(width / 256),
						  (uint8_t)(height % 256),
						  (uint8_t)(height / 256),
						  (uint8_t)(fileChannels * 8),
						  0x20};
	fwrite(&header, 18, 1, fp);

	for (uint32_t i = 0; i < width * height; i++)
	{
			fputc(dataBGR[i].b, fp);
			fputc(dataBGR[i].g, fp);
			fputc(dataBGR[i].r, fp);
	}
	fclose(fp);
}

static inline void _set(tga_image *self, int x, int y, tga_color color) {
	tga_color *dataBGR = self->dataBGR;
	int width = self->width;
	dataBGR[x + y * width].b = color.b;
	dataBGR[x + y * width].g = color.g;
	dataBGR[x + y * width].r = color.r;
}

tga_image tga_image_init(int width, int height)
{
	tga_image new_tga_image;

	uint8_t dataChannels = 3;
	new_tga_image.dataBGR = calloc(width * height * dataChannels, sizeof(uint8_t));
	new_tga_image.set = _set;
	new_tga_image.width = width;
	new_tga_image.height = height;
	return new_tga_image;
}

tga_color tga_new_color(uint8_t r, uint8_t g, uint8_t b) {
	tga_color new_color = { .r = r, .g = g, .b = b };
	return new_color;
}
