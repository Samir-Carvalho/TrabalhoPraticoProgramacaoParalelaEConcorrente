/*
//  cliente.cpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include "../include/cliente.hpp"
#include <unistd.h>
#include <chrono>
#include <iostream>
#include "../include/gerente.hpp"
#include "../include/garcom.hpp"

using namespace std;
Cliente::Cliente() {
	id = instances++; // = numero de instancias no momento de criação.
	sem_init(&sem_pedido_chegou,0,0); // o pedido ainda não chegou
}


void Cliente::start(){
	pthread_create(&thread, NULL, run, this);
}

void* Cliente::run(void* args){
	Gerente &g = Gerente::getManager();
	Cliente* cliente = (Cliente*) args;
	printf("Cliente %d começou\n", cliente->id+1);
	cliente->wait();
	//1. tenta esperar uma mesa
	if (sem_trywait(&g.sem_mesas) != 0){
		printf("Cliente %d está aguardando na fila\n", cliente->id+1);
		sem_wait(&g.sem_mesas);
	}
	printf("Cliente %d pegou uma mesa no bar\n", cliente->id+1);
	sleep(rand()%3+1);
	//2. escolher o pedido
	cliente->decidir(); 
	
	//3. inserir cliente na fila de atendimento;
	g.cliente_para_fila(cliente);
	printf("Cliente %d pediu atendimento\n", cliente->id+1);
	//4. esperar pedido voltar
	sem_wait(&cliente->sem_pedido_chegou);
	printf("Cliente %d pegou sua bebida e começou a beber\n", cliente->id+1);
	sleep(rand()%3+1);

	// 5. depois de beber liberar mesa
	sem_post(&g.sem_mesas);

	printf("Cliente %d terminou e liberou sua mesa\n", cliente->id+1);
	return NULL;
}

void Cliente::decidir() {
	printf("Cliente %d está escolhendo a sua bebida da rodada \n", id+1);
	sleep(rand()%1+2);
	
	p = Pedido(rand()%3); //escolhe uma bebida random
	printf("Cliente %d escolheu sua bebida :\n", id+1);
	p.print(id+1);
	sleep(1);
}