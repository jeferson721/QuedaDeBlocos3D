#include "qdblocos.h"
#include "graficos.h"

int main(void)
{
	__Graficos__Iniciar();

	while (true)
	{
		__Graficos__IniciarDesenho3d();
		DrawCube((Vector3){ -4.0f, 0.0f, 2.0f }, 2.0f, 5.0f, 2.0f, RED);
		if (IsKeyDown(KEY_ESCAPE))break;
		__Graficos__FinalizarDesenho3d();
	}
	__Graficos__Fechar();
	return 0;
}