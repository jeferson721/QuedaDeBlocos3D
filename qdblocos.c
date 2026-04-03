#include "qdblocos.h"

int MicroTempo;
int Tempo;
int AceleracaoPadrao;
int Aceleracao;
int ProxHorarioAtualizacao;
int InclementoDoHorario;
float DecrementoDeQueda;
ListaDeBlocos ComponentePai;
ListaDeBlocos ComponenteCenario;

static int AdicionarBloco(ListaDeBlocos* lista, Vector3 posicao, Color cor) {
	if (lista->quantidade >= _blocos_tam_max_)return 0;

	Bloco novoBloco = { 0 };
	novoBloco.position = posicao;
	novoBloco.cor = cor;

	lista->blocos[lista->quantidade] = novoBloco;
	lista->quantidade++;

	return 1;
}

static void DesenharBlocos(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];

		DrawCube(bloco->position, 1.0f, 1.0f, 1.0f, bloco->cor);
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

static int ColisaoEntreListaDeBlocos(ListaDeBlocos* lista1, ListaDeBlocos* lista2) {
	if (lista1 == NULL || lista2 == NULL)return 0;
	for (uint16_t i = 0; i < lista1->quantidade; i++) {
		Bloco* bloco1 = &lista1->blocos[i];
		for (uint16_t j = 0; j < lista2->quantidade; j++) {
			Bloco* bloco2 = &lista2->blocos[j];
			if (bloco1->position.y <= bloco2->position.y)continue;

			float distancia = Vector3Distance(bloco1->position, bloco2->position);
			if (distancia <= 1.0f)return 1; // Colisão detectada

		}
	}
	return 0; // Nenhuma colisão detectada
}

static int ColisaoEntreListaDeBlocosComImclemento(ListaDeBlocos* lista1, ListaDeBlocos* lista2, Vector3* inclemento) {
	if (lista1 == NULL || lista2 == NULL)return 0;
	for (uint16_t i = 0; i < lista1->quantidade; i++) {
		Bloco* bloco1 = &lista1->blocos[i];
		for (uint16_t j = 0; j < lista2->quantidade; j++) {
			Bloco* bloco2 = &lista2->blocos[j];
			if (bloco1->position.y < bloco2->position.y)continue;
			Vector3 posicaoComInclemento = (Vector3){ bloco1->position.x + inclemento->x, bloco1->position.y + inclemento->y, bloco1->position.z + inclemento->z };
			float distancia = Vector3Distance(posicaoComInclemento, bloco2->position);
			if (distancia < 1.0f)return 1; // Colisão detectada

		}
	}
	return 0; // Nenhuma colisão detectada
}

static int Animar(ListaDeBlocos* lista, ListaDeBlocos* lista2) {
	int retorno = 0;

	if (lista == NULL || lista->quantidade == 0)return retorno;

	if (Tempo == ProxHorarioAtualizacao) {
		for (uint16_t i = 0; i < lista->quantidade; i++) {
			Bloco* bloco = &lista->blocos[i];
			if (bloco->position.y <= 0.55f || ColisaoEntreListaDeBlocos(lista, lista2) != 0) {
				retorno = 2;
				return retorno;
			}
		}
	}

	if (Tempo == ProxHorarioAtualizacao) {
		for (uint16_t i = 0; i < lista->quantidade; i++) {
			Bloco* bloco = &lista->blocos[i];
			bloco->position.y -= DecrementoDeQueda;
		}
		ProxHorarioAtualizacao += InclementoDoHorario;
		retorno = 1;
	}

	return retorno;
}

static int AnimarSemTempoProgramado(ListaDeBlocos* lista, ListaDeBlocos* lista2) {
	int retorno = 0;

	if (lista == NULL || lista->quantidade == 0)return retorno;

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];
		if (bloco->position.y <= 0.55f || ColisaoEntreListaDeBlocos(lista, lista2) != 0) {
			retorno = 2;
			return retorno;
		}
	}

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];
		bloco->position.y -= DecrementoDeQueda;
	}

	retorno = 1;
	return retorno;
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

static uint16_t IndiceDoBlocoComMenorY(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return -1;
	uint16_t indiceMenorY = 0;
	for (uint16_t i = 1; i < lista->quantidade; i++) {
		if (lista->blocos[i].position.y < lista->blocos[indiceMenorY].position.y) {
			indiceMenorY = i;
		}
	}
	return indiceMenorY;
}

static void CopiarParaOutraLista(ListaDeBlocos* origem, ListaDeBlocos* destino) {
	if (origem == NULL || destino == NULL)return;
	for (uint16_t i = 0; i < origem->quantidade; i++) {
		destino->blocos[destino->quantidade + i] = origem->blocos[i];
	}
	destino->quantidade += origem->quantidade;
}

static void ReflexaoDoComponentePai(ListaDeBlocos* lista) {
	if (lista == NULL || lista->quantidade == 0)return;

	uint16_t indiceMenorY = IndiceDoBlocoComMenorY(lista);
	ListaDeBlocos reflexao = { 0 };
	CopiarParaOutraLista(&ComponentePai, &reflexao);

	for (uint8_t i = 0; i < 100; i++){
		int animado = AnimarSemTempoProgramado(&reflexao, &ComponenteCenario);
		if (animado == 2)break;
	}

	for (uint16_t i = 0; i < reflexao.quantidade; i++) {
		Color cor = reflexao.blocos[i].cor;
		cor.a = 50;	
		DrawCube(reflexao.blocos[i].position, 1.0f, 1.0f, 1.0f, cor);
		DrawCubeWires(reflexao.blocos[i].position, 1.0f, 1.0f, 1.0f, reflexao.blocos[i].cor);
	}

	LimparLista(&reflexao);
}

static Color CorAleatoria()
{
	int r = rand() % 10;

	switch (r)
	{
	case 0: return RED;
	case 1: return GREEN;
	case 2: return BLUE;
	case 3: return YELLOW;
	case 4: return ORANGE;
	case 5: return PURPLE;
	case 6: return PINK;
	case 7: return SKYBLUE;
	case 8: return LIME;
	case 9: return GOLD;
	}

	return WHITE; // Valor padrão caso algo dê errado
}

static void ChamarUmPolimino(void) {
	int numaleto = rand() % 7;
	Color cor = CorAleatoria();

	if (numaleto == 0) {
		// O: quatro blocos formando um quadrado 2x2
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 18.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 18.50f, 0.00f }, cor);
	}
	else if (numaleto == 1) {
		// I: quatro blocos em sequência
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 3.00f, 19.50f, 0.00f }, cor);
	}
	else if (numaleto == 2) {
		// T: uma sequência de três blocos com um adicionado ao abaixo do bloco central.
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 18.50f, 0.00f }, cor);
	}
	else if (numaleto == 3) {
		// J: uma sequência de três blocos, com um adicionado abaixo da extremidade direita.
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 18.50f, 0.00f }, cor);
	}
	else if (numaleto == 4) {
		// L: uma sequência de três blocos, com um adicionado abaixo da extremidade esquerda.
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 18.50f, 0.00f }, cor);
	}
	else if (numaleto == 5) {
		// S: duas sequências de dominós na horizontal, sendo o de cima deslocado para a direita.
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 18.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 18.50f, 0.00f }, cor);
	}
	else if (numaleto == 6) {
		// Z: duas sequências de dominós na horizontal, sendo o de cima deslocado para a esquerda.
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 18.50f, 0.00f }, cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 2.00f, 18.50f, 0.00f }, cor);
	}
	else {
		// Caso algo dê errado na geração do número aleatório.
		printf("\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas\n Erro na geracao das pecas");
	}


}

// --- Funções públicas ---

void __QdBlocos__Iniciar() {

	MicroTempo = 100;
	Tempo = 0;
	AceleracaoPadrao = 1;
	Aceleracao;
	ProxHorarioAtualizacao;
	InclementoDoHorario;
	DecrementoDeQueda = 1.00f;
	//ComponentePai = { 0 };
	ChamarUmPolimino();
	Aceleracao = AceleracaoPadrao;
	AtualizarTempo();
}

void __QdBlocos__Passo() {

	DesenharBlocos(&ComponentePai);
	DesenharBlocos(&ComponenteCenario);
	ReflexaoDoComponentePai(&ComponentePai);

	int animado = Animar(&ComponentePai, &ComponenteCenario);

	Vector3 incle_a = { -1.00f, 0.00f, 0.00f };
	Vector3 incle_d = { 1.00f, 0.00f, 0.00f };

	if (animado == 2) {		
		printf("\n Chamar novo Polimino  \n");
		CopiarParaOutraLista(&ComponentePai, &ComponenteCenario);
		LimparLista(&ComponentePai);
		ChamarUmPolimino();
	}

	if (IsKeyUp(KEY_S)) {
		Aceleracao = AceleracaoPadrao;
		AtualizarTempo();
	}

	if (IsKeyPressed(KEY_S)) {
		Aceleracao = AceleracaoPadrao * 20;
		AtualizarTempo();
	}

	if (IsKeyPressed(KEY_A)) {
		if (!ColisaoEntreListaDeBlocosComImclemento(&ComponentePai, &ComponenteCenario, &incle_a)) {
			AddVetor(&ComponentePai, incle_a);
		}
	}

	if (IsKeyPressed(KEY_D)) {
		if (!ColisaoEntreListaDeBlocosComImclemento(&ComponentePai, &ComponenteCenario, &incle_d)) {
			AddVetor(&ComponentePai, incle_d);
		}
	}

	if (Tempo == MicroTempo) {
		Tempo = 0;
		ProxHorarioAtualizacao = InclementoDoHorario;
	}
	else {
		Tempo++;
	}
}