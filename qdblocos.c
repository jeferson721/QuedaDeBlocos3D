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

static int Animar(ListaDeBlocos* lista) {
	int retorno =0;

	if (lista == NULL || lista->quantidade == 0)return retorno;

	if (Tempo == ProxHorarioAtualizacao) {
		for (uint16_t i = 0; i < lista->quantidade; i++) {
			Bloco* bloco = &lista->blocos[i];
			if (bloco->position.y <= 0.55f) { retorno = 2; return retorno;}
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

static void EspelharComponentePai(ListaDeBlocos* lista){
	if (lista == NULL || lista->quantidade == 0)return;

	for (uint16_t i = 0; i < lista->quantidade; i++) {
		Bloco* bloco = &lista->blocos[i];
		if (bloco->position.y == 0.50f) { continue; }
		Vector3 posicaoOriginal = (Vector3){ bloco->position.x, 0.5f,bloco->position.z };		
		DrawCubeWires(posicaoOriginal, 1.0f, 1.0f, 1.0f, bloco->cor);
	}
}

static void CopiarParaOutraLista(ListaDeBlocos* origem, ListaDeBlocos* destino) {
	if (origem == NULL || destino == NULL)return;
	for (uint16_t i = 0; i < origem->quantidade; i++) {
		destino->blocos[destino->quantidade+i] = origem->blocos[i];
	}
	destino->quantidade += origem->quantidade;
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

static int ColisaoEntreListaDeBlocos(ListaDeBlocos* lista1, ListaDeBlocos* lista2) {
	if (lista1 == NULL || lista2 == NULL)return 0;
	for (uint16_t i = 0; i < lista1->quantidade; i++) {
		Bloco* bloco1 = &lista1->blocos[i];
		for (uint16_t j = 0; j < lista2->quantidade; j++) {
			Bloco* bloco2 = &lista2->blocos[j];
			if (bloco1->position.x == bloco2->position.x && bloco1->position.y == bloco2->position.y) {
				return 1; // Colisão detectada
			}
		}
	}
	return 0; // Nenhuma colisão detectada
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


	AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f }, CorAleatoria());
	Aceleracao = AceleracaoPadrao;
	AtualizarTempo();
}

void __QdBlocos__Passo() {
	DesenharBlocos(&ComponentePai);
	DesenharBlocos(&ComponenteCenario);

	EspelharComponentePai(&ComponentePai);

	int animado=Animar(&ComponentePai);	
	//printf(" animado: %d\n", animado);

	if (animado==2)	{
		printf("\n\n ###############\n ###############\n ###############\n ###############\n ###############\n ###############\n ###############\n");
		CopiarParaOutraLista(&ComponentePai, &ComponenteCenario);
		LimparLista(&ComponentePai);
		Color cor = CorAleatoria();
		AdicionarBloco(&ComponentePai, (Vector3) { 0.0f, 19.50f, 0.00f },cor);
		AdicionarBloco(&ComponentePai, (Vector3) { 1.00f, 19.50f, 0.00f },cor);

	}

	int colisao = ColisaoEntreListaDeBlocos(&ComponentePai, &ComponenteCenario);
	printf("\n colisao %d", colisao);


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