#include "qdblocos.h"
#include "graficos.h"

int main(void)
{
	__Graficos__Iniciar();

	while (__Graficos__Roda())
	{
		__Graficos__IniciarDesenho3d();
		DrawCube((Vector3){ 0.50f, 0.50f, -0.50f }, 1.0f, 1.0f, 1.0f, BLUE);
		DrawCubeWires((Vector3){ 0.50f, 0.50f, -0.50f }, 1.0f, 1.0f, 1.0f, BLACK);
		if (IsKeyDown(KEY_ESCAPE))break;
		__Graficos__FinalizarDesenho3d();
	}
	__Graficos__Fechar();
	return 0;
}