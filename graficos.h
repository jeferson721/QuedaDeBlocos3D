#ifndef GRAFICOS_H

#define GRAFICOS_H
#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


void __Graficos__Iniciar(); // Inicia o motor gráfico.
void __Graficos__IniciarDesenho3d(void); // Inicia o processo de desenho em 3d.
void __Graficos__FinalizarDesenho3d(void); // Finaliza o processo de desenho em 3d.
void __Graficos__Fechar(); // Finaliza o motor gráfico.
float __Graficos__EscalaDeTrabalho(); // Retorna a escala de trabalho atual.

#endif