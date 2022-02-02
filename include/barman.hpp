/*
//  barman.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#ifndef barman_hpp
#define barman_hpp

#include <stdio.h>
#include <string>
#include "../include/comanda.hpp"
#include "../include/threadedClass.hpp"

using namespace std;

class Barman: public ThreadedClass{
protected:
	
	inline static int instances = 0; //contador de instancias da classe
	static void* run(void* args); //função para ser colocada como uma thread.
	
	void preparar_bebida(Bebida p); //preparar mais bebida p e atualiza valor de forma atômica.
	
public:
	Barman();
	//herança: função que cria a thread.
	void start(void);
};


#endif /* barman_hpp */
