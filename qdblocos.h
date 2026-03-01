#ifndef qdblocos_H

#define qdblocos_H

#include <stdio.h>
#include "raylib.h"
#include <stdlib.h>
#include <stdint.h>


#define _blocos_tam_max_ 1000

typedef struct {
    Vector3 position;
} Bloco;

typedef struct {
    Bloco blocos[_blocos_tam_max_];
    uint16_t quantidade;
} ListaDeBlocos;

void __QdBlocos__Passo(); // Função principal para atualizar e desenhar os blocos.
void __QdBlocos__Iniciar(); // Função de inicialização para configurar o estado inicial dos blocos e a aceleração.

#endif
