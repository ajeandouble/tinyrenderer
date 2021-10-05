#include "geometry.h"
#include "tgaimage.h"
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ABS(x) ((x) < 0 ? -(x) : (x))

void draw_line(int x0, int y0, int x1, int y1, tga_image *image, tga_color color)
{
	bool steep = false;
	if (ABS(x0 - x1) < ABS(y0 - y1))
	{
		int swap;
		swap = x0;
		x0 = y0;
		y0 = swap;
		swap = x1;
		x1 = y1;
		y1 = swap;
		steep = true;
	}
	if (x0 > x1)
	{
		int swap;
		swap = x0;
		x0 = x1;
		x1 = swap;
		swap = y0;
		y0 = y1;
		y1 = swap;
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = ABS(dy) * 2;
	int error2 = 0;
	int y = y0;

    // TODO: if-else outside loop
	for (int x = x0; x <= x1; x++)
	{
		if (steep)
		{
			image->set(image, y, x, color);
		}
		else
		{
			image->set(image, x, y, color);
		}
		error2 += derror2;
		if (error2 > dx)
		{
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

static inline tga_color _random_color()
{
	tga_color c = {
		.r = rand() % 255,
		.g = rand() % 255,
		.b = rand() % 255,
	};
	printf("%d\n", c.r);
	return c;
}

static inline void draw_line_vertices(vertex a, vertex b, tga_image *image, tga_color color)
{
	int x0 = (a.x + 1.) * WIDTH / 2.;
	int y0 = (a.y + 1.) * HEIGHT / 2.;
	int x1 = (b.x + 1.) * WIDTH / 2.;
	int y1 = (b.y + 1.) * HEIGHT / 2.;
    printf("x0=%d y0=%d x1=%d y1=%d", x0, y0, x1, y1);
	draw_line(x0, y0, x1, y1, image, color);
}

static inline void fill_triangle_line(point a, point b, tga_image *image, tga_color color)
{
	int x0 = a.x;
	int y0 = a.y;
	int x1 = b.x;
	int y1 = b.y;
    printf("FTLINES\tx0=%d y0=%d x1=%d y1=%d", x0, y0, x1, y1);
    fflush(stdout);
	draw_line(x0, y0, x1, y1, image, color);
}

float sign (fPoint a, fPoint b, fPoint c)
{
    return (a.x - c.x) * (b.y - c.y) - (b.x - c.x) * (a.y - c.y);
}

bool PointInTriangle (fPoint pt, fPoint v1, fPoint v2, fPoint v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void draw_triangle(triangle t, tga_image *image, tga_color color)
{
    tga_color random_color = _random_color();
	vertex a = t.a;
	vertex b = t.b;
	vertex c = t.c;

	vertex swap;
	if (a.y > b.y)
	{
		swap = a;
		a = b;
		b = swap;
	}
	if (a.y > c.y)
	{
		swap = a;
		a = c;
		c = swap;
	}
	if (b.y > c.y)
	{
		swap = b;
		b = c;
		c = swap;
	}

    tga_color red = tga_new_color(255, 0 ,0);
    tga_color green = tga_new_color(0, 255, 0);
    tga_color blue = tga_new_color(0, 0, 255);

	//        A
	//       /\
    //      /  \
    //     /____\
    //    B      C
	float dx1 = 0, dx2 = 0, dx3 = 0;
	if (b.y - a.y > 0) { dx1 = (b.x - a.x) / (b.y - a.y); printf("dx1\n"); }
	if (c.y - a.y > 0) { dx2 = (c.x - a.x) / (c.y - a.y); printf("dx2\n"); }
	if (c.y - b.y > 0) { dx3 = (c.x - b.x) / (c.y - b.y); printf("dx3\n"); }

    printf("dx1=%f dx2=%f dx3=%f\n", dx1, dx2, dx3);
    fPoint A = { .x = (a.x + 1.) * WIDTH / 2., .y = (a.y + 1.) * HEIGHT / 2. };
    fPoint B = { .x = (b.x + 1.) * WIDTH / 2., .y = (b.y + 1.) * HEIGHT / 2. };
    fPoint C = { .x = (c.x + 1.) * WIDTH / 2., .y = (c.y + 1.) * HEIGHT / 2. };
    int total_height = C.y - A.y;
    printf("total_height=%d\n", total_height);

	float nx = t.c.x - t.a.x;
	float ny = t.c.y - t.a.y;
	float nz = t.c.z - t.a.z;
	
	float nx_ = t.b.x - t.a.x;
	float ny_ = t.b.y - t.a.y;
	float nz_ = t.b.z - t.a.z;

	// CROSS PRODUCT?
	// NO IDEA WHY IT WORKS YET

	float NX = (ny * nz_) - (nz * ny_);
	float NY = (nz * nx_) - (nx * nz_);
	float NZ = (nx * ny_) - (ny * nx_);

	float normalize_ratio =  1 / sqrt(NX*NX+NY*NY+NZ*NZ);
	NX *= normalize_ratio;
	NY *= normalize_ratio;
	NZ *= normalize_ratio;
	float intensity = -1 * NZ;
	printf("intensyt=%f\n", intensity);

    int maxX = MAX(A.x, MAX(B.x, C.x));
    int minX = MIN(A.x, MIN(B.x, C.x));
    int maxY = MAX(A.y, MAX(B.y, C.y));
    int minY = MIN(A.y, MIN(B.y, C.y));
	tga_color shade = tga_new_color((int)(intensity * 255), (int)(intensity * 255), (int)(intensity * 255));
    if (intensity > 0)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			for (int y = minY; y <= maxY; ++y)
			{
				fPoint pt = { .x = x, .y = y };
				if (PointInTriangle(pt, A, B, C)) {
					image->set(image, x, y, shade);
				}
			}
		}
		draw_line_vertices(a, b, image, red);
		draw_line_vertices(b, c, image, red);
		draw_line_vertices(c, a, image, red);
	}
}
