/*
//  barman.cpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include "../include/barman.hpp"
#include "../include/gerente.hpp"
#include <string>

Barman::Barman(){
	id = instances++; //id = numero de instancias no momento de criação.
}

/// cria a thread e executa a função run, passando como argumento uma referencia da instancia.
void Barman::start(){
	pthread_create(&thread, NULL, run, this);
}

// executa o comportamento da classe.
void* Barman::run(void *args){
	// recupera o gerente (acesso a variáveis globais e semáforos)
	Gerente& g = Gerente::getManager();

	// restaura referencia a instancia que gerou essa thread.
	Barman& barman = *((Barman*)args);
	
	// aguarda liberação do lock.
	barman.wait();
	printf("\t\tBarman %d começou\n", barman.id+1);
	
	while (g.bar_aberto){
		//espera um pedido chegar;
		sem_wait(&g.sem_sinal);
		Comanda* comanda = g.pegar_comanda();
		if (comanda == NULL) {
			printf("\t\tBarman pegou uma comanda nula run to the hills!!\n\n");
			exit(-1);
		}
		printf("\t\tBarman %d pegou a comanda do cliente %d\n", barman.id+1, comanda->c->id+1);
		
		//2.enquanto prepara verifica a disponibilidade dos ingredientes

		sem_wait(&g.sem_controle_bebida);
		if (g.bebidas[comanda->p->prot] < 1) 
			barman.preparar_bebida(comanda->p->prot); //se acabou repõe
		g.bebidas[comanda->p->prot]--;
		sem_post(&g.sem_controle_bebida);

		sleep(1); // demora pra servir.
		printf("\t\tBarman %d serviu a a bebida do cliente %d\n", barman.id+1, comanda->c->id+1);
		
		
		sleep(2); // servir e finalizar a bebida
		
		printf("\t\tBarman %d preparou a bebida do cliente %d\n", barman.id+1, comanda->c->id+1);
		
		//3.devolve o pedido.
		g.bebida_para_fila(comanda);
	}
	
	return NULL;
}

void Barman::preparar_bebida(Bebida p){
	if (p == 0) printf("\t\tAcabou a bebida tipo 0. O Barman %d está preparando mais.\n", id+1 );
	else if (p == 1) printf("\t\tAcabou a bebida tipo 1. O Barman %d está preparando mais.\n", id+1 );
	else if (p == 2) printf("\t\tAcabou a bebida tipo 2. O Barman %d está preparando mais.\n", id+1 );
	else exit(-1);

	sleep(rand()%2+3);
	Gerente::getManager().bebidas[p] = MAX_BEBIDAS;
}
