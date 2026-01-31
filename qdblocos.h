#ifndef qdblocos_H

#define qdblocos_H

#include <stdio.h>
#include "raylib.h"
#include <stdlib.h>
#include <stdint.h>

#define _blocos_tam_max_ 10

typedef struct {
    Vector3 position;
} Bloco;

typedef struct {
    Bloco blocos[_blocos_tam_max_];
    uint16_t quantidade;
} ListaDeBlocos;


#endif
