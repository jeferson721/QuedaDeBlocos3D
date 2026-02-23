#include "qdblocos.h"

int AdicionarBloco(ListaDeBlocos* lista, Vector3 posicao) {
	if (lista->quantidade >= _blocos_tam_max_)return 0;

	Bloco novoBloco = { 0 };
	novoBloco.position = posicao;

	lista->blocos[lista->quantidade] = novoBloco;
	lista->quantidade++;

	return 1;
}

void DesenharBlocos(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];
		DrawCube(bloco->position, 1.0f, 1.0f, 1.0f, BLUE);
		DrawCubeWires(bloco->position, 1.0f, 1.0f, 1.0f, BLACK);
		/*
		DrawCube((Vector3){ 0.50f, 0.50f, -0.50f }, 1.0f, 1.0f, 1.0f, BLUE);
		DrawCubeWires((Vector3){ 0.50f, 0.50f, -0.50f }, 1.0f, 1.0f, 1.0f, BLACK);
		*/
	}
}

void LimparLista(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;
	for (uint16_t i = 0; i < lista->quantidade; i++) { 
		lista->blocos[i] = (Bloco){ 0 }; 
	}
	lista->quantidade = 0;
}

void Animar(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;

	if (Tempo == ProxHorarioAtualizacao) {

		for (uint16_t i = 0; i < lista->quantidade; i++) {

			Bloco* bloco = &lista->blocos[i];
			if (bloco->position.y > 0.50f) {
				bloco->position.y -= DecrementoDeQueda;
			}
		}
		ProxHorarioAtualizacao += InclementoDoHorario;
	}
}

void AtualizarTempo() {
	InclementoDoHorario = MicroTempo / Aceleração;
	ProxHorarioAtualizacao = InclementoDoHorario;
}