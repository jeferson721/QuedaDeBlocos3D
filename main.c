#include "qdblocos.h"
#include "graficos.h"

int main(void) {
	__Graficos__Iniciar();
	__QdBlocos__Iniciar();

	while (__Graficos__Roda()) {
		__Graficos__IniciarDesenho3d();
		if (IsKeyDown(KEY_ESCAPE))break;
		__QdBlocos__Passo();
		__Graficos__FinalizarDesenho3d();		
	}

	__Graficos__Fechar();
	return 0;
}