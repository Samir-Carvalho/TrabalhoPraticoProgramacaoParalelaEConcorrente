/*
//  gerente.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/



#ifndef gerente_hpp
#define gerente_hpp

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <map>
#include "../include/cliente.hpp"
#include "../include/comanda.hpp"
#include <iostream>

using namespace std;

static int N_CLIENTES = 1;
static int N_GARCOM = 1;
static int N_BARMAN = 1; 


#define N_MESAS 5
#define N_BEBIDAS 3
#define MAX_BEBIDAS 2


class Gerente{
private:
	inline static Gerente* defaultManager = NULL;
	Gerente(); // construtor privado para usar apenas na singleton. // para que apenas uma instancia da classe possa existir e ser utilizada por toda aplicação
	~Gerente();
	void init(); // inicializa todos os recursos.
	std::queue<Cliente*>fila_clientes;
	std::queue<Comanda*>fila_comandas;
	std::queue<Comanda*>fila_bebidas_prontas ;
  
  
public:

	// variaveis globais 
  inline static int prioridade = 0; // controle de prioridade pedidos novos
  
  static void setN_Cliente(int c){
    N_CLIENTES = c;
  }

  static void setN_Garcom(int g){
    N_GARCOM = g;
  }

  static void setN_Barman(int b){
    N_BARMAN = b;
  }
  
	inline static int bar_aberto = N_CLIENTES;

	//contagem de bebidas disponíveis
	int bebidas[3];

	/// Usando um lock RW como barreira para todas as classes.
	/// Todas as classes aguardam esse lock ser liberado para leitura para continuar.
	/// Assim, nenhuma thread tenta acessar nada até que tudo esteja preparado.
	inline static pthread_rwlock_t barrier_lock = PTHREAD_RWLOCK_INITIALIZER;
	
	// controle de acesso por volume;
	sem_t sem_mesas; // representa clientes que possuem uma mesa no bar;
	
	// controle de fluxo sinais
	sem_t sem_sinal_atendimento; 	// representa um sinal de atendimento (pedido pronto || cliente chamou)
	sem_t sem_sinal; 		// representa um sinal de preparo para do pedido (pedido chegou);
	sem_t sem_sinal_fim_expediente; // representa o fim do expediente, todos os clientes foram atendidos;
	//controle de acesso a variáveis
	sem_t sem_controle_clientes; 	// opera como um lock para interagir com a fila de clientes
	sem_t sem_controle_comandas; 	// opera como um lock para interagir com a fila de comandas
	sem_t sem_controle_bebidas; 		// opera como um lock para interagir com a fila de bebidas
	sem_t sem_controle_contador;	// opera como um lock para interagir com a contagem de clientes no estabelecimento (encerramento do programa)
	sem_t sem_controle_bebida;	// opera como um lock para interagir com os recursos disponíveis para fazer a bebida 


	void abrir_bar(); 			// libera as threads
	static Gerente& getManager(); 		//pega o singleton do gerente.
	
	void cliente_para_fila(Cliente* c); // insere cliente na fila de atendimento de forma atomica e emite sinal para garçom
	Cliente* atender_cliente(); 		// retira e retorna o primeiro cliente da fila de forma atomica.

	void comanda_para_fila(Comanda* c);	// insere comanda na fila de preparo de forma atomica e emite sinal
	Comanda* pegar_comanda();			// retira e retorna a primeira comanda da fila de forma atomica.

	void bebida_para_fila(Comanda* p);	// insere comanda na fila de comandas prontos de forma atomica e emite sinal para garçom
	Comanda* pegar_bebida();				// retira e retorna a primeiro da fila de forma atomica.
};

#endif /* gerente_hpp */
