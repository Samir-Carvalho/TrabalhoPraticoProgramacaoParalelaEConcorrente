/*
//  pedido.cpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include "../include/pedido.hpp"
#include <string>
#include <iostream>

Pedido::Pedido(int c){
	id = instances++; // = numero de instancias no momento de criação.
	prot = Bebida(c);
}

Pedido::Pedido(){
	id = instances++;
	prot = Bebida(0);
}

void Pedido::print(int id){

	std::string string_pedido = "\tPedido Cliente ";
	string_pedido.append(std::to_string(id));
	string_pedido.append(" Pedido: ");
	if (prot == bebida) string_pedido.append("Bebida");
	
	string_pedido.append("\n");
	std::cout << string_pedido;
}	