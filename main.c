#include "qdblocos.h"
#include "graficos.h"

uint8_t time;

static void Animar(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0 || time != 0)return;

	for (uint16_t i = 0; i < lista->quantidade; i++) {

		Bloco* bloco = &lista->blocos[i];
		if (bloco->position.y > 0.0f) {
			bloco->position.y -= 1.0f; // Velocidade de queda
		}

	}
}


int main(void)
{
	__Graficos__Iniciar();
	time = 0;

	ListaDeBlocos minhaLista = { 0 };

	Vector3 pin = { -3.00f, 0.50f, 3.00f };
	//uint16_t altura = 1;//19 
	//uint16_t largura = 7;//7
	//uint16_t comprimento = 7;//7

	//for (uint16_t y = 0;y < altura; y++){
	//	for (size_t x = 0; x < largura; x++){
	//		for (size_t z = 0; z < comprimento; z++){
	//			Vector3 posicao = { pin.x + x, pin.y + y, pin.z - z };
	//			AdicionarBloco(&minhaLista, posicao);
	//		}
	//	}
	//}

	AdicionarBloco(&minhaLista, (Vector3) { 0.0f, 19.0f, 0.0f });



	while (__Graficos__Roda()) {
		__Graficos__IniciarDesenho3d();
		DesenharBlocos(&minhaLista);
		Animar(&minhaLista);
		if (IsKeyDown(KEY_ESCAPE))break;
		__Graficos__FinalizarDesenho3d();


		time++;
		if (time == 100)time = 0;
	}

	__Graficos__Fechar();
	return 0;
}