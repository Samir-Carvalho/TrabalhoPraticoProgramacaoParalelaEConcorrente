/*
//  threadedclass.cpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include <stdio.h>
#include "../include/threadedClass.hpp"
#include "../include/gerente.hpp"


void ThreadedClass::join() {
	pthread_join(thread, NULL); // join
}

void ThreadedClass::wait(){
	pthread_rwlock_rdlock(&(Gerente::barrier_lock)); // aguarda para leitura lock que é trancado antes de qualquer thread iniciar.
}
