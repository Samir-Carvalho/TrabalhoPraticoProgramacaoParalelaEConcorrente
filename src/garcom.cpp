/*
//  garcom.cpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include "../include/garcom.hpp"
#include "../include/gerente.hpp"
#include <unistd.h>
#include <chrono>
#include <iostream>

Garcom::Garcom(){
	id = instances++; // numero de instancias no momento de criação.
}
using namespace std;

void Garcom::start(){
	pthread_create(&thread, NULL, run, this);
}

void Garcom::atender(){
	//encaminha para o gerente
	Cliente* c = Gerente::getManager().atender_cliente();
	if (c == NULL) {
		printf("\tErro, garçom %d pegou um cliente nulo para atender\n\n", id+1);
		exit(-1);	
	}
	printf("\tGarçom %d atendendo cliente %d \n", id+1, c->id+1);
	sleep(rand()%2+1);
	Comanda* comanda = new Comanda(c,&c->p);
	printf("\tGarçom %d preparou comanda e enviou à fila\n", id+1);
	Gerente::getManager().comanda_para_fila(comanda);
}

void Garcom::servir(){
	Comanda* comandaPronta = Gerente::getManager().pegar_bebida();
	if (comandaPronta == NULL){
		printf("\tErro, garçom %d pegou um pedido nulo\n\n", id+1);
		exit(-1);	
	}
	printf("\tGarçom %d pegou a comanda do cliente %d\n", id+1, comandaPronta->c->id+1);
	sleep(rand()%3+1);
	sem_post(&(comandaPronta->c->sem_pedido_chegou)); //levou a comanda
	delete comandaPronta;
}

void* Garcom::run(void *args){
	Gerente& g = Gerente::getManager();
	Garcom& garcom = *((Garcom*)args);
	garcom.wait(); // sincronia de threads global
	printf("\tGarçom %d começou e está esperando para atender um cliente\n", garcom.id+1);
	
	while (g.bar_aberto > 0){
		// esperar chamada para atendimento;
		sem_wait(&g.sem_sinal_atendimento);
		printf("\tGarçom %d recebeu uma chamada de atendimento\n", garcom.id+1);
		// 1 atendimento é novo pedido		
		if (g.prioridade == 0) {
			// 1.1 atender
			garcom.atender();
		}
		// 2 atendimento é pedido pronto 
		else {
			// 2.1 levar pedido para cliente
			garcom.servir();
		}
	}
	
	// 3 voltar para 1 enquanto bar aberto;
	printf("\tGarçom %d terminou\n", garcom.id);
	return nullptr;
}


