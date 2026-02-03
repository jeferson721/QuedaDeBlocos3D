#include "graficos.h"

Camera3D Camera = { 0 };                                            // Câmera.	
float SensibilidadeDeMovimento;                                     // Fator multiplicador do incremento no movimentos do teclado.		
float SensibilidadeDoMouse;                                         // Fator multiplicador do incremento no movimentos da câmera.		
float Escala;                                                       // Escala do objetos
int LarguraDaJanela = 758;                                          // Largula da janela grafica
int AlturaDaJanela = 758;                                           // Altura da janela grafica

void __Graficos__Iniciar() {
	Escala = 1;                                                          // Escala dos objetos
	SensibilidadeDeMovimento = 0.1f;								     // Sense do teclado
	SensibilidadeDoMouse = 0.001f;									     // Sense do mouse
	SetTargetFPS(100);												     // Frames por segundo
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);								 // Frag janela redimensionavel
	InitWindow(LarguraDaJanela, AlturaDaJanela, "Queda De Blocos em 3D");// Dados da janela
	SetTraceLogLevel(LOG_ALL);                                           // Define o nível de log para exibir TODAS as mensagens LOG_DEBUG   LOG_ERROR   LOG_NONE
	Camera.fovy = 45.0f;												 // Abertura da lente
	Camera.projection = CAMERA_PERSPECTIVE;								 // Perspectiva ou ortografica
}

