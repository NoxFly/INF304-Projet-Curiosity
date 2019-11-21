#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SIZE 256

typedef enum { LIBRE, EAU, ROCHER } Case;

#define CALCWEIGHT(r) (r>25? LIBRE : r>5? ROCHER : EAU);

unsigned u = 0;

typedef struct {
    int width, height;
    Case matrix[MAX_SIZE][MAX_SIZE];
} Map;

Case getRandomPlace() {
    srand(++u);
    return CALCWEIGHT(rand() % 100);
}

char convert(Case c) {
    switch(c) {
        case LIBRE:     return '.'; break;
        case ROCHER:    return '#'; break;
        case EAU:       return '~';
    }
}

void printMap(Map map) {
    for(int i=0; i < map.height; i++) {
        for(int j=0; j < map.width; j++) {
            printf("%c", convert(map.matrix[i][j]));
        }
        printf("\n");
    }
}


void genMap(Map *map, int width, int height) {
    map->width = width;
    map->height = height;

    u = 0;

    for(int i=0; i < map->height; i++) {
        for(int j=0; j < map->width; j++) {
            map->matrix[i][j] = getRandomPlace();
        }
    }
}

int main(int argc, char **argv) {
    Map m;
    genMap(&m, 30, 30);
    printMap(m);
}