#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse_model.h"
#include "geometry.h"

#define BUFF_SIZE 4096


size_t parse_model(FILE *fp, face **dest_faces)
{ 
    char *line = NULL;
    size_t len = 0;
    size_t read;

    size_t vertices_len = 0;
    vertex *vertices = (vertex *)malloc(sizeof(vertex) * BUFF_SIZE);
    // REALLOC vertices_len * 2 and so on if vertices_len >= BUFF_SIZE 

    while ((read = getline(&line, &len, fp)) != -1) {
        char *tok = strtok(line, " ");
        float x, y, z;
        if (!strcmp(tok, "v")) {
            tok = strtok(NULL, " ");
            x = atof(tok);
            // printf("%s\t", tok);
            tok = strtok(NULL, " ");
            y = atof(tok);
            // printf("%s\t", tok);
            tok = strtok(NULL, " ");
            // printf("%s", tok);
            z = atof(tok);
            // ADD error CHECKS
            vertex v = { .x = x, .y = y, .z = z };
            vertices[vertices_len++] = v;
            continue ;
        }
        break ;
    }
    free(line);
    line = NULL;
    face *faces = (face *)malloc(sizeof(face) * BUFF_SIZE);
    size_t faces_len = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char *tok = strtok(line, " ");
        if (!strcmp(tok, "f")) {
            char *a, *b, *c;
            a = strtok(NULL, " ");
            b = strtok(NULL, " ");
            c = strtok(NULL, " ");
            if (strchr(a, '/')) *(strchr(a, '/')) = 0;
            if (strchr(b, '/')) *(strchr(b, '/')) = 0;
            if (strchr(c, '/')) *(strchr(c, '/')) = 0;
            // printf("%d %d %d\n", atoi(a) - 1, atoi(b) - 1, atoi(c) - 1);
            face f = {
                .a = vertices[atoi(a) - 1],
                .b = vertices[atoi(b) - 1],
                .c = vertices[atoi(c) - 1]
            };
            faces[faces_len] = f;
            faces_len++;
        }
    }
    free(line);
    free(vertices);
    *dest_faces = faces;
    return (faces_len);
}
