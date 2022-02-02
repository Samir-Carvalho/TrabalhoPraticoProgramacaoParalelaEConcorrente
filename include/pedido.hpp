/*
//  pedido.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#ifndef pedido_hpp
#define pedido_hpp

#include <stdio.h>

// Opções de bebidas 0,1,2
enum Bebida: int {
	bebida = 0,
  bebida1,
  bebida2
};


// Representação de um pedido
class Pedido {
private:
	inline static int instances = 0; //contagem de instancias
public:
	int id; //id do pedido
	Bebida prot; // bebida
	 
	Pedido(int p); //construtor especifico
	Pedido(); // construtor padrão para alocação estática de atributos de cliente.
	void print(int id);
};

#endif /* Pedido_hpp */
