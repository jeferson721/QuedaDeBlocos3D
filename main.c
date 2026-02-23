#include "qdblocos.h"
#include "graficos.h"





int main(void) {
	__Graficos__Iniciar();
	AdicionarBloco(&Peçapai, (Vector3) { 0.0f, 19.50f, 0.00f });
	Aceleração = AceleraçãoPadrão;
	AtualizarTempo();

	while (__Graficos__Roda()) {
		__Graficos__IniciarDesenho3d();
		DesenharBlocos(&Peçapai);
		Animar(&Peçapai);
		if (IsKeyDown(KEY_ESCAPE))break;

		if (IsKeyDown(KEY_E)){
			Aceleração = 100;
			AtualizarTempo();
		}
	
		__Graficos__FinalizarDesenho3d();
		if (Tempo == MicroTempo) {			
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