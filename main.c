#include "qdblocos.h"
#include "graficos.h"

uint8_t MicroTempo = 100;
uint8_t Tempo = 0;
uint8_t Aceleração = 1;
uint8_t ProxHorarioAtualizacao;
uint8_t InclementoDoHorario;
float DecrementoDeQueda = 1.00f;
ListaDeBlocos Peçapai = { 0 };


static void Animar(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;

	if (Tempo== ProxHorarioAtualizacao)
	{
		printf("\n L___> ms");
		for (uint16_t i = 0; i < lista->quantidade; i++) {

			Bloco* bloco = &lista->blocos[i];
			if (bloco->position.y > 0.50f) {
				bloco->position.y -= DecrementoDeQueda;
			}
		}
		ProxHorarioAtualizacao += InclementoDoHorario;
	}

	
}


int main(void) {
	__Graficos__Iniciar();
	AdicionarBloco(&Peçapai, (Vector3) { 0.0f, 19.50f, 0.00f });

	InclementoDoHorario = MicroTempo / Aceleração;
	ProxHorarioAtualizacao = InclementoDoHorario;

	while (__Graficos__Roda()) {
		__Graficos__IniciarDesenho3d();
		DesenharBlocos(&Peçapai);
		Animar(&Peçapai);
		if (IsKeyDown(KEY_ESCAPE))break;
		if (IsKeyDown(KEY_E))
		{
			InclementoDoHorario = 100;
			InclementoDoHorario = MicroTempo / Aceleração;
			ProxHorarioAtualizacao = InclementoDoHorario;
		}
		__Graficos__FinalizarDesenho3d();
		if (Tempo == MicroTempo) {
			printf("\n***** TEMPO *****");
			Tempo = 0;
			ProxHorarioAtualizacao = InclementoDoHorario;
		}
		else{
			Tempo++;
		}
	}

	__Graficos__Fechar();
	return 0;
}