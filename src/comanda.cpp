/*
//  comanda.cpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include "../include/comanda.hpp"

Comanda::Comanda(Cliente* c, Pedido* p){
	this->p = p;
	this->c = c;
}
