#include "geometry.h"
#include "parse_model.h"
#include "tgaimage.h"
#include "lightning.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 800

int main(int ac, char **av)
{
	FILE *input_file;

	if (ac == 1)
		input_file = stdin;
	else if (ac != 2)
	{
		fprintf(stderr, "usage: tinyrenderer <input_file>\n");
		exit(-1);
	}
	else
		input_file = fopen(av[1], "r");
	if (!input_file)
		exit(-1);
	tga_image image = tga_image_init(WIDTH, HEIGHT);
	tga_color red = tga_new_color(255, 0, 0);
	tga_color blue = tga_new_color(0, 255, 0);

	face *faces;
	size_t faces_len = parse_model(input_file, &faces);

	for (size_t i = 0; i < faces_len; ++i)
	{
		triangle t = { .a = faces[i].a, .b = faces[i].b, .c = faces[i].c };
		tga_color new_color = find_color(t);
		draw_triangle(t, &image, new_color);
	}

	srand(time(0));
	//printf("%d %d %d\n", rand(), rand(), rand());
	// TEST
	// vertex a = { .x = -1, .y = -0.27, .z = .0 };
	// vertex b = { .x = -1, .y =  0.25, .z = .0 };
	// vertex c = { .x = 1, .y = -0.74, .z = .0 };
	// triangle t = { .a = a, .b = b, .c = c };

	// draw_line(0, 0, 100, 100, &image, red);
	
	// draw_triangle(t, &image, red);
	// TGAImage image(100, 100, TGAImage::RGB);

	tga_write("output.tga", &image);
	//image.flip_vertically();
	//image.write_tga_file("output.tga");
	return 0;
}
