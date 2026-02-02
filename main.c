#include "qdblocos.h"

static int AdicionarBloco(ListaDeBlocos* lista, Vector3 posicao) {
	if (lista->quantidade >= _blocos_tam_max_)return 0;

	Bloco novoBloco = { 0 };
	novoBloco.position = posicao;

	lista->blocos[lista->quantidade] = novoBloco;
	lista->quantidade++;

	return 1;
}

static void DesenharBlocos(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];
		DrawCube(bloco->position, 1.0f, 1.0f, 1.0f, BLUE);
		DrawCubeWires(bloco->position, 1.0f, 1.0f, 1.0f, BLACK);
	}
}

static void TesteBloco() {
	const int screenWidth = 800;
	const int screenHeight = 450;
	InitWindow(screenWidth, screenHeight, "QuedaDeBlocos3D");
	Camera camera = { 0 };
	camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
	camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	DisableCursor();
	SetTargetFPS(60);

	ListaDeBlocos minhaLista = { 0 };

	AdicionarBloco(&minhaLista, (Vector3) { 0.5f, 0.5f, -0.5f });
	AdicionarBloco(&minhaLista, (Vector3) { 0.5f, 1.5f, -0.5f });
	AdicionarBloco(&minhaLista, (Vector3) { 0.5f, 2.5f, -0.5f });
	AdicionarBloco(&minhaLista, (Vector3) { 0.5f, 3.5f, -0.5f });
	AdicionarBloco(&minhaLista, (Vector3) { 0.5f, 4.5f, -0.5f });

	while (!WindowShouldClose())
	{
		UpdateCamera(&camera, CAMERA_FREE);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);
		DesenharBlocos(&minhaLista);
		DrawGrid(10, 1.0f);
		EndMode3D();
		DrawFPS(10, 10);
		EndDrawing();
		if (IsKeyDown(KEY_ESCAPE))break;
	}
	CloseWindow();

}



int main(void)
{
	
	return 0;
}