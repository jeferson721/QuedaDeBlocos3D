#include "graficos.h"

Camera3D CameraMain;                 // Câmera.	
float SensibilidadeDeMovimento;      // Fator multiplicador do incremento no movimentos do teclado.		
float SensibilidadeDoMouse;          // Fator multiplicador do incremento no movimentos da câmera.		
int LarguraDaJanela;                 // Largula da janela grafica
int AlturaDaJanela;                  // Altura da janela grafica
float RaioOrbital;                   // Raio do orbital da camera
float PhiOrbital;                    // Cordenada esferica phi para o orbital da camera
float ThetaOrbital;                  // Cordenada esferica theta para o orbital da camera		
float NumPi;                         // Numero de pi
float NumPi2;                        // Numero de pi multiplicado por 2	

void __Graficos__Iniciar() {
	LarguraDaJanela = 758;
	AlturaDaJanela = 758;
	RaioOrbital = 30;
	PhiOrbital = 1.570796325f;
	ThetaOrbital = 1.570796325f;
	NumPi = 3.141592653f;
	NumPi2 = 6.283185307f;
	SensibilidadeDeMovimento = 1.5f;								     // Sense do teclado
	SensibilidadeDoMouse = 0.001f;									     // Sense do mouse
	SetTargetFPS(100);												     // Frames por segundo
	SetConfigFlags(FLAG_MSAA_4X_HINT);								     // Suavização de bordas	
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);								 // Frag janela redimensionavel
	InitWindow(LarguraDaJanela, AlturaDaJanela, "Queda De Blocos em 3D");// Dados da janela
	SetTraceLogLevel(LOG_ALL);                                           // Define o nível de log para exibir TODAS as mensagens LOG_DEBUG   LOG_ERROR   LOG_NONE
	Camera3D camedssdra = { 0 };										 // Nova camera
	CameraMain = camedssdra;										     // Camera global
	CameraMain.fovy = 45.0f;										     // Abertura da lente
	CameraMain.projection = CAMERA_PERSPECTIVE;						     // Perspectiva ou ortografica
}

void __Graficos__IniciarDesenho3d(void) {
	DrawText("|  QUEDA DE BLOCOS  V:1.00 | POR: JEFERSON  |", 10, 10, 10, BLACK); // Desenha texto na tela
	DrawText(TextFormat(" FPS: %d", GetFPS()), 10, 30, 10, PINK);                 // Mostra o FPS na tela

	if (!WindowShouldClose()) {
		// Detecta informações do mouse
		Vector2 mouseDelta = GetMouseDelta();
		float wheelMovement = GetMouseWheelMove();

		// Atualiza o valor do raio
		if (wheelMovement > 0) { RaioOrbital -= SensibilidadeDeMovimento; }
		else if (wheelMovement < 0) { RaioOrbital += SensibilidadeDeMovimento; }
		if (IsKeyDown(KEY_KP_ADD))RaioOrbital -= SensibilidadeDeMovimento / 10;
		if (IsKeyDown(KEY_KP_SUBTRACT))RaioOrbital += SensibilidadeDeMovimento / 10;

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
		CameraMain.position = (Vector3){ xesf,yesf + 10.00f,zesf };  // Atualiza posição da câmera
		CameraMain.target = (Vector3){ 0.0f, 10.00f,0.0f };          // Para onde a camera aponta
		CameraMain.up = (Vector3){ 0.0f, 1.0f,0.0f };                // Define eixo Vertical	

		// Desenha
		BeginDrawing();                                          // Configure a tela (framebuffer) para começar a desenhar.		
		ClearBackground(RAYWHITE);                               // Definir cor de fundo(cor limpa do framebuffer)
		BeginMode3D(CameraMain);                                 // Finalizar desenho de shader personalizado (usar shader padrão)
	}
	// Desenha uma grade para dar uma melhor noção de espaço
	//DrawGrid(10, 1.0f);
	//DrawSphereWires((Vector3) { 0, 0, 0 }, 1, 50, 50, BLACK);

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


int __Graficos__Roda() {
	return !WindowShouldClose();
}


