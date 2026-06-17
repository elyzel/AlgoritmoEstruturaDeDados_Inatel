#include<iostream>
#include <list>

using namespace std;

int main()  {

    //< -- Declaração da lista ligada
    list<int> lista;

    //Variável
    int valor;

    while(cin >> valor && valor != 0)   {

        //< -- push_back inicia a inserir no final da lista
        //< -- push_front inicia a inserir no inicio da lista
        lista.push_front(valor); 
    }

    int Q;

    cin >> Q;

    //< -- Criação de um iterator para percorrer pela lista iniciando no indice 0 -- >
    list<int>::iterator it = lista.begin();

    //Percorre por todo vetor, inserindo o valor e avançando 1 endereco
    for(int i = 0; i < Q; i++)  {
        it++;
    }

    //Mostra o valor de onde parou o ponteiro
    cout << *it << endl;

    return 0;

}