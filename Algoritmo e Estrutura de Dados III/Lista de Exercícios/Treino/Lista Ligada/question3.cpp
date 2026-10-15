/*
Enunciado

Crie uma struct Produto:

struct Produto {
    string nome;
    float preco;
};

Crie uma:

list<Produto>

Adicione três produtos usando push_back().

Depois percorra a lista utilizando um iterador e mostre os produtos.
*/

#include<iostream>
#include<string>
#include<list>

using namespace std;

struct Produto{
    string nome;
    float preco;
};

int main()  {

    list<Produto> produtos; //< --   Criação da Lista Ligada

    int opcao;

    do{

        Produto p1; //< -- Chama os dados do Struct

        cout << "Olá" << endl;
        cout << "Digite 1 se deseja cadastrar um produto" << endl;
        cout << "Digite 0, para encerrar.." << endl;
        cin >> opcao;

        if(opcao == 1)  {
        cout << "Digite o nome do produto" << endl;
        cin >> p1.nome;
        cout << "Digite o preco do produto" << endl;
        cin >> p1.preco;

        produtos.push_back(p1);

        cout << "Produto cadastrado!" << endl;
        }

    }   while(opcao != 0);

    list<Produto>::iterator it;

    for(it = produtos.begin(); it != produtos.end(); it++)   {

        cout << "Nome: " << it->nome << endl;
        cout << "Preco: " << it->preco << endl;
        cout << "=============" << endl;
    }

    cout << " ";

    return 0;
}
