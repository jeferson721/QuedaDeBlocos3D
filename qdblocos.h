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

uint8_t MicroTempo = 100;
uint8_t Tempo = 0;
uint8_t AceleraçãoPadrão = 1;
uint8_t Aceleração;
uint8_t ProxHorarioAtualizacao;
uint8_t InclementoDoHorario;
float DecrementoDeQueda = 1.00f;
ListaDeBlocos Peçapai = { 0 };

int AdicionarBloco(ListaDeBlocos* lista, Vector3 posicao); // Adiciona um bloco à lista, retornando 1 se bem-sucedido ou 0 se a lista estiver cheia.
void DesenharBlocos(ListaDeBlocos* lista); // Desenha os blocos na tela usando as funções de desenho do Raylib.
void LimparLista(ListaDeBlocos* lista); // Limpa a lista de blocos, definindo a quantidade para 0 e zerando os blocos.
void Animar(ListaDeBlocos* lista); // Anima os blocos, atualizando suas posições com base no tempo e na aceleração.
void AtualizarTempo(); // Atualiza o tempo de animação, calculando o próximo horário de atualização com base na aceleração.

#endif
