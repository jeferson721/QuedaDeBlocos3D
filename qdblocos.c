#include "qdblocos.h"

int MicroTempo;
int Tempo;
int AceleracaoPadrao;
int Aceleracao;
int ProxHorarioAtualizacao;
int InclementoDoHorario;
float DecrementoDeQueda;
ListaDeBlocos ComponentePai;

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

static void LimparLista(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;
	for (uint16_t i = 0; i < lista->quantidade; i++) { 
		lista->blocos[i] = (Bloco){ 0 }; 
	}
	lista->quantidade = 0;
}

static void Animar(ListaDeBlocos* lista) {
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

static void AtualizarTempo() {
	InclementoDoHorario = MicroTempo / Aceleracao;
	ProxHorarioAtualizacao = InclementoDoHorario;
}

static void AddVetor(ListaDeBlocos* lista, Vector3 add) {
	if (lista == NULL || lista->quantidade == 0)return;

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];
		bloco->position.x += add.x;
		bloco->position.y += add.y;
		bloco->position.z += add.z;
	}

}

void __QdBlocos__Iniciar() {

	 MicroTempo = 100;
	 Tempo = 0;
	 AceleracaoPadrao = 1;
	 Aceleracao;
	 ProxHorarioAtualizacao;
	 InclementoDoHorario;
	 DecrementoDeQueda = 1.00f;
	 //ComponentePai = { 0 };

	AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f });
	Aceleracao = AceleracaoPadrao;
	AtualizarTempo();
}

void __QdBlocos__Passo() {
	DesenharBlocos(&ComponentePai);
	Animar(&ComponentePai);	

	if (IsKeyUp(KEY_S)) {
		Aceleracao = AceleracaoPadrao;
		AtualizarTempo();
	}

	if (IsKeyPressed(KEY_S)) {
		Aceleracao = AceleracaoPadrao * 20;
		AtualizarTempo();
	}

	if (IsKeyPressed(KEY_A)) {
		AddVetor(&ComponentePai, (Vector3) { -1.00f, 0.00f, 0.00f });
	}
	if (IsKeyPressed(KEY_D)) {
		AddVetor(&ComponentePai, (Vector3) { 1.00f, 0.00f, 0.00f });
	}

	if (Tempo == MicroTempo) {
		Tempo = 0;
		ProxHorarioAtualizacao = InclementoDoHorario;
	}
	else {
		Tempo++;
	}
}