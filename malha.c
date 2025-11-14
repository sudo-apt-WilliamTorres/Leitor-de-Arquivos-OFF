#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malha.h"

void lerOFF(const char *arquivo, Malha *m) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) {
        printf("Erro: não foi possível abrir %s\n", arquivo);
        exit(1);
    }

    char header[10];
    fscanf(fp, "%s", header);

    if (strcmp(header, "OFF") != 0) {
        printf("Erro: arquivo não está no formato OFF.\n");
        fclose(fp);
        exit(1);
    }

    fscanf(fp, "%d %d %*d", &m->num_vertices, &m->num_faces);

    m->vertices = (Vertice *) malloc(m->num_vertices * sizeof(Vertice));
    m->faces = (Face *) malloc(m->num_faces * sizeof(Face));

    for (int i = 0; i < m->num_vertices; i++) {
        fscanf(fp, "%f %f %f",
               &m->vertices[i].x,
               &m->vertices[i].y,
               &m->vertices[i].z);
    }

    for (int i = 0; i < m->num_faces; i++) {
        int n;
        fscanf(fp, "%d", &n);  

        m->faces[i].num_vertices = n;
        m->faces[i].indices = (int *) malloc(n * sizeof(int));

        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &m->faces[i].indices[j]);
        }
    }

    fclose(fp);
}

void imprimirMalha(const Malha *m) {
    printf("==== MALHA CARREGADA ====\n");
    printf("Vertices: %d\n", m->num_vertices);
    printf("Faces: %d\n\n", m->num_faces);

    printf("Lista de vertices:\n");
    for (int i = 0; i < m->num_vertices; i++) {
        printf("V%d: %.2f %.2f %.2f\n",
               i,
               m->vertices[i].x,
               m->vertices[i].y,
               m->vertices[i].z);
    }

    printf("\nLista de faces:\n");
    for (int i = 0; i < m->num_faces; i++) {
        printf("F%d (%d vertices): ", i, m->faces[i].num_vertices);
        for (int j = 0; j < m->faces[i].num_vertices; j++) {
            printf("%d ", m->faces[i].indices[j]);
        }
        printf("\n");
    }
}

void liberarMalha(Malha *m) {
    for (int i = 0; i < m->num_faces; i++) {
        free(m->faces[i].indices);
    }
    free(m->faces);
    free(m->vertices);
}
