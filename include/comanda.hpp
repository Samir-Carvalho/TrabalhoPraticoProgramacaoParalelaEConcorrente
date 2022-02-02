/*
//  comanda.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#ifndef comanda_hpp
#define comanda_hpp

#include <stdio.h>
#include <unistd.h>
#include "../include/cliente.hpp"
#include "../include/pedido.hpp"

// Abstração que vincula um pedido a um cliente 
class Comanda {
private:
public:
	Pedido* p; //pedido que o cliente fez
	Cliente* c; // o cliente que fez o pedido
	Comanda(Cliente* c,Pedido* p); // construtor padrão.
};	

#endif /* comanda_hpp */
