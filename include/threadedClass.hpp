/*
//  trhreadedclass.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#ifndef ThreadedClass_hpp
#define ThreadedClass_hpp


#include <pthread.h>

/// Classe base de todas as classes com threads.
/// é necessário implementar uma função estática em cada classe que for derivada desta, para ser o ponteiro na hora de criar a thread.
class ThreadedClass {
protected:

	pthread_t thread; // thread da instancia

	void wait(); // aguarda liberação do lock para continuar executando. (aguardar barreira/broadcast).
	
public:
	int id; // id da instancia
	virtual void start(void) = 0; // todas as classes devem implementar sua criação de thread.
	
	void join(void); // pthread_join
	
};

#endif /* ThreadedClass_hpp */
