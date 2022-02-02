/*
//  garcom.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#ifndef garcom_hpp
#define garcom_hpp

#include <stdio.h>
#include "../include/threadedClass.hpp"
#include "../include/comanda.hpp"
#include <queue> // fila


// Classe que representa um garçom
class Garcom: public ThreadedClass {
private:
	inline static int instances = 0;
	static void* run(void* args);
	static sem_t sem_fila;
	
public:
	Garcom();
	//herança: função que cria a thread.
	void start(void);
	void atender(); //recebe um pedido de um cliente/
	void servir(); //levar uma bebida a um cliente.
};

#endif /* garcom_hpp */
