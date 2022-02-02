/*
//  main.hpp
//  Trabalho_Prático PPC - Bar
//
//  Samir Avelino Carvalho
*/

#include <iostream>
#include "include/cliente.hpp"
#include "include/barman.hpp"
#include "include/garcom.hpp"
#include "include/gerente.hpp"

using namespace std;

int main(int argc, const char * argv[]) {

	Gerente& ger = Gerente::getManager();
  
  //(i) número de clientes presentes no estabelecimento,
  cout << "Digite a quantidade de clientes no bar: ";
  static int qtdCliente;
  cin >> qtdCliente;
  ger.setN_Cliente(qtdCliente);

  //(ii) número de garçons que estão trabalhando, 
  cout << "Digite a quantidade de garçons no bar: ";
  static int qtdGarcom;
  cin >> qtdGarcom;
  ger.setN_Garcom(qtdGarcom);

  //(iii) capacidade de atendimento dos garçons
  // a capacidade de atendimento dos garçons foi definid
  //como a qtd de Barman no bar. 
  //Se tiver apenar 1 barman, a bebida vai ser preparada
  //uma por vez

  cout << "Digite a quantidade de barman no bar: ";
  static int qtdBarman;
  cin >> qtdBarman;
  ger.setN_Barman(qtdBarman);

	Cliente clientes[qtdCliente];
	Barman barmans[qtdBarman];
	Garcom garcons[qtdGarcom];
	
	for (auto & c : clientes) c.start();
	for (auto & c : barmans) c.start();
	for (auto & g : garcons) g.start();
	ger.abrir_bar();

	for (auto & c : clientes) c.join();
	cout<<"Todos os clientes foram atendidos e o bar fechou!\n";
}
