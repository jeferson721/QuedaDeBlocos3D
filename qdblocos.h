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

int AdicionarBloco(ListaDeBlocos* lista, Vector3 posicao); // Adiciona um bloco à lista, retornando 1 se bem-sucedido ou 0 se a lista estiver cheia.
void DesenharBlocos(ListaDeBlocos* lista); // Desenha os blocos na tela usando as funções de desenho do Raylib.
void LimparLista(ListaDeBlocos* lista); // Limpa a lista de blocos, definindo a quantidade para 0 e zerando os blocos.
#endif
