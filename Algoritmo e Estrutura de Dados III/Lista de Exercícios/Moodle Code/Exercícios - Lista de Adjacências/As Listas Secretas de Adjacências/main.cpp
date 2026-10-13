/*
Contexto: 

Em Graphlandia, os mensageiros usam rotas secretas para entregar mensagens entre as cidades. 
CodeMaster descobre sobre essas rotas e decide mapeá-las usando listas de adjacência para cada cidade, 
identificando todas as cidades conectadas diretamente a ela.


Entradas: 

A primeira linha contém dois inteiros N e M, onde N é o número de cidades (nós) (1 ≤ N ≤ 100) e M é o 
número de caminhos (arestas) (1 ≤ M ≤ N*(N-1)/2). As próximas M linhas descrevem os caminhos, cada uma 
contendo dois inteiros A e B (1 ≤ A, B ≤ N), indicando um caminho bidirecional entre as cidades A e B.

Saídas: 

Para cada cidade i (1 ≤ i ≤ N), imprima uma linha começando com o número de cidades diretamente 
conectadas a i, seguido pelos índices dessas cidades, ordenados em ordem crescente.

| Entrada: | Saída: |
| :--- | :--- |
| 4 4 | 2 2 4 |
| 1 2 | 2 1 3 |
| 2 3 | 2 2 4 |
| 3 4 | 2 1 3 |
| 4 1 | |
*/

#include<iostream>
#include<list>

using namespace std;

int main()  {

    int N;  //Número de Cidades
    int M;  //Números de Caminhos

    cin >> N >> M;

    //Criação da lista de adjascência
    list<int> adj[N + 1];

    //Leitura das arestas A e B, representando se é direcionado ou não direcionado
    for(int i = 0; i < M; i++)  {

        int A, B;

        cin >> A >> B;

        //O sentido de A e B é bidirecional, ou seja, quanto um como outro pode ser visitado.
        adj[A].push_back(B);
        adj[B].push_back(A);
    }

    for(int i = 1; i <= N; i++) {
        //Responsável por ordenar em forma crescente
        adj[i].sort();

        //Imprime a quantidade de cidades conectadas
        cout << adj[i].size();

        for(list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++)   {

            //Saída das cidades presentes na lista de adjacência
            cout << " " << *it;

        }
    }
    //Quebra de linha
    cout << "\n"; 
}