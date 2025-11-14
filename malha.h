#ifndef MALHA_H
#define MALHA_H

typedef struct {
    float x, y, z;
} Vertice;

typedef struct {
    int num_vertices;   
    int *indices;       
} Face;

typedef struct {
    int num_vertices;
    int num_faces;
    Vertice *vertices;
    Face *faces;
} Malha;

void lerOFF(const char *arquivo, Malha *m);

void imprimirMalha(const Malha *m);

void liberarMalha(Malha *m);

#endif
