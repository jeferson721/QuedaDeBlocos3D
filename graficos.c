#include "graficos.h"

Camera3D CameraMain;                 // Câmera.	
float SensibilidadeDeMovimento;      // Fator multiplicador do incremento no movimentos do teclado.		
float SensibilidadeDoMouse;          // Fator multiplicador do incremento no movimentos da câmera.		
float Escala;                        // Escala do objetos
int LarguraDaJanela;                 // Largula da janela grafica
int AlturaDaJanela;                  // Altura da janela grafica
Vector3 Mira;                        // Posição da mira da camera	
float RaioOrbital;                   // Raio do orbital da camera
float PhiOrbital;                    // Cordenada esferica phi para o orbital da camera
float ThetaOrbital;                  // Cordenada esferica theta para o orbital da camera		
float NumPi;                         // Numero de pi
float NumPi2;                        // Numero de pi multiplicado por 2	

void __Graficos__Iniciar() {
	LarguraDaJanela = 758;
	AlturaDaJanela = 758;
	Mira = (Vector3){ 0,0,0 };
	RaioOrbital = 5;
	PhiOrbital = 1.570796325f;
	ThetaOrbital = 1.570796325f;
	NumPi = 3.141592653f;
	NumPi2 = 6.283185307f;
	Escala = 1;                                                          // Escala dos objetos
	SensibilidadeDeMovimento = 0.1f;								     // Sense do teclado
	SensibilidadeDoMouse = 0.001f;									     // Sense do mouse
	SetTargetFPS(100);												     // Frames por segundo
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);								 // Frag janela redimensionavel
	InitWindow(LarguraDaJanela, AlturaDaJanela, "Queda De Blocos em 3D");// Dados da janela
	SetTraceLogLevel(LOG_ALL);                                           // Define o nível de log para exibir TODAS as mensagens LOG_DEBUG   LOG_ERROR   LOG_NONE
	Camera3D camedssdra = { 0 };										 // Nova camera
	CameraMain = camedssdra;										     // Camera global
	CameraMain.fovy = 45.0f;										     // Abertura da lente
	CameraMain.projection = CAMERA_PERSPECTIVE;						     // Perspectiva ou ortografica
}

void __Graficos__IniciarDesenho3d(void) {
	DrawText("|  QUEDA DE BLOCOS  V:4.00 | POR: JEFERSON  |", 10, 10, 10, BLACK); // Desenha texto na tela
	DrawText(TextFormat(" FPS: %d", GetFPS()), 10, 30, 10, PINK);                 // Mostra o FPS na tela

	if (!WindowShouldClose()) {
		// Posicionamento da mira.
		if (IsKeyDown(KEY_KP_4)) { Mira.x -= Escala * SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_6)) { Mira.x += Escala * SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_8)) { Mira.y += Escala * SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_2)) { Mira.y -= Escala * SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_7)) { Mira.z -= Escala * SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_9)) { Mira.z += Escala * SensibilidadeDeMovimento; }

		// Detecta informações do mouse
		Vector2 mouseDelta = GetMouseDelta();
		float wheelMovement = GetMouseWheelMove();

		// Atualiza o valor do raio
		if (wheelMovement > 0) { RaioOrbital -= Escala * SensibilidadeDeMovimento; }
		else if (wheelMovement < 0) { RaioOrbital += Escala * SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_ADD))RaioOrbital -= Escala * SensibilidadeDeMovimento;
		if (IsKeyDown(KEY_KP_SUBTRACT))RaioOrbital += Escala * SensibilidadeDeMovimento;

		// Ativa o controle orbital com botão direito
		if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) { PhiOrbital += mouseDelta.x * SensibilidadeDoMouse; ThetaOrbital -= mouseDelta.y * SensibilidadeDoMouse; }

		// Impõe respeito as coordenadas esfericas do orbital da câmera
		if (RaioOrbital < 1) { RaioOrbital = 1; }
		if (PhiOrbital < 0) { PhiOrbital = NumPi2; }
		if (PhiOrbital > NumPi2) { PhiOrbital = 0; }
		if (ThetaOrbital < 0) { ThetaOrbital = 0; }
		if (ThetaOrbital > NumPi) { ThetaOrbital = NumPi; }

		// Converte de coordenadas esfericas para cartesianas
		float xesf = RaioOrbital * sinf(ThetaOrbital) * cosf(PhiOrbital);
		float yesf = RaioOrbital * cosf(ThetaOrbital);
		float zesf = RaioOrbital * sinf(ThetaOrbital) * sinf(PhiOrbital);

		// Define a posição da câmera
		CameraMain.position = (Vector3){ (xesf + Mira.x),(yesf + Mira.y) ,(zesf + Mira.z) };    // Atualiza posição da câmera
		CameraMain.target = Mira;                                                               // Mantém a câmera sempre apontando				
		CameraMain.up = (Vector3){ 0.0f, 1.0f,0.0f };                                           // Define eixo Vertical	

		// Desenha
		BeginDrawing();                                          // Configure a tela (framebuffer) para começar a desenhar.		
		ClearBackground(RAYWHITE);                               // Definir cor de fundo(cor limpa do framebuffer)
		BeginMode3D(CameraMain);                                 // Finalizar desenho de shader personalizado (usar shader padrão)

		// Eixos para referencia	
		float posisao = 0.25f * Escala;							// Tamanho
		float larg_comeco = 0.05f * Escala;						// Raio do começo
		float larg_fim = 0.0001f * Escala;						// Raio do fim
		int detalhes = 15;									    // Nivel de detalhes			
		DrawCylinderEx((Vector3) { Mira.x, Mira.y, Mira.z + posisao }, (Vector3) { Mira.x, Mira.y, Mira.z - posisao }, larg_comeco, larg_fim, detalhes, BLUE);	    // EIXO Z  
		DrawCylinderEx((Vector3) { Mira.x, Mira.y + posisao, Mira.z }, (Vector3) { Mira.x, Mira.y - posisao, Mira.z }, larg_comeco, larg_fim, detalhes, GREEN);	    // EIXO	Y 
		DrawCylinderEx((Vector3) { Mira.x + posisao, Mira.y, Mira.z }, (Vector3) { Mira.x - posisao, Mira.y, Mira.z }, larg_comeco, larg_fim, detalhes, RED);	    // EIXO X 

	}
	// Desenha uma grade para dar uma melhor noção de espaço
	DrawGrid(10, 1.0f);
	DrawSphereWires((Vector3) { 0, 0, 0 }, 1, 50, 50, BLACK);

}

void __Graficos__FinalizarDesenho3d(void) {
	if (!WindowShouldClose()) {
		EndMode3D();               // Finaliza o modo 3D e retorna para o modo 2D
		EndDrawing();              // Finaliza o desenho e apresenta na tela (framebuffer)
	}		
}

void __Graficos__Fechar(void) {
	if (!WindowShouldClose()) {
		CloseWindow(); // Fechar janela
	}
}

float __Graficos__EscalaDeTrabalho(void){
	return Escala;
}