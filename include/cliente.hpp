/*
//  cliente.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#ifndef cliente_hpp
#define cliente_hpp

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "../include/pedido.hpp"
#include "../include/threadedClass.hpp"

// classe que representa o cliente.
class Cliente: public ThreadedClass {
private:
	
	static void* run(void* args); // função para thread.
	void decidir(); // decidir qual pedido fazer.
	
public:
	inline static int instances = 0; // contador de instancias.
  Cliente(); // construtor padrão.
	Pedido p; // pedido que vai fazer.
	sem_t sem_pedido_chegou; // semaforo unico do cliente que está aguardando o pedido
	//herança: função que cria a thread.
	void start(void);
};

#endif /* cliente_hpp */
