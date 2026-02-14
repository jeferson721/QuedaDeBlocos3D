#include "qdblocos.h"
#include "graficos.h"

int main(void)
{
	__Graficos__Iniciar();

	ListaDeBlocos minhaLista = { 0 };
	Vector3 pin = { -3.00f, 0.50f, 3.00f };
	uint16_t altura = 19;
	uint16_t largura = 7;
	uint16_t comprimento = 7;

	for (uint16_t y = 0;y < altura; y++){
		for (size_t x = 0; x < largura; x++){
			for (size_t z = 0; z < comprimento; z++){
				Vector3 posicao = { pin.x + x, pin.y + y, pin.z - z };
				AdicionarBloco(&minhaLista, posicao);
			}
		}
	}
	while (__Graficos__Roda()){
		__Graficos__IniciarDesenho3d();
		DesenharBlocos(&minhaLista);
		if (IsKeyDown(KEY_ESCAPE))break;
		__Graficos__FinalizarDesenho3d();
	}
	__Graficos__Fechar();
	return 0;
}