/*
  Harry, Rony e Hermione fizeram o favor de perder o Mapa do Maroto. E como solução para os seus problemas eles resolveram propor um desafio para um bruxo da Escola de Magia e Telecomunicações de Santa Rita. Eles pensaram que seria melhor criar, de forma temporária, um programa para ler apenas alguns pontos específicos de Hogwarts e suas distâncias e armazenar essas informações em um Grafo. As salas são os vértices e as distâncias são os pesos das arestas.

     Faça um programa que leia os dados dos vértices e arestas e os armazene em uma Lista de Adjacências.

Entrada

A primeira linha contém dois inteiro correspondendo ao número de vértices do grafo e o segundo define se o grafo é orientado (1) ou não 
orientado (0). As demais linhas contém três inteiros correspondentes ao vértice de origem, o vértice de destino e o peso de cada aresta, 
respectivamente. A entrada termina quando ocorrer uma linha com três números iguais a -1 (esta não deve ser registrada).

Saída

A saída deverá mostrar a lista de adjacências gerada

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 5 1 | 0 2 4 |
| 4 1 3 | 0 1 2 |
| 0 2 4 | 1 3 2 |
| 1 3 2 | 2 4 7 |
| 3 1 3 | 3 1 3 |
| 0 1 2 | 3 4 2 |
| 2 4 7 | 4 1 3 |
| 3 4 2 | 4 0 1 |
| 4 0 1 | |
| -1 -1 -1 | |
*/

#include<iostream>
#include<list>

using namespace std;

struct no{
    int v;  //Vértice
    int p;  //Peso da Aresta
};

int main()  {
    int N;      //<-- Número de vértices
    int M;      //<-- Condição para saber se é orientado ou não

    /*
    Se o grafo é orientado, os vértices tem um sentido único.
    Se o grafo não é orientado, os vértices tem um sentido duplo de ir e voltar.
    */

    cin >> N >> M;

    list<no> adj[N];

    int v;  //Vértice de origem
    int u;  //Vértice de destino
    int p;  //Peso das arestas

    while(cin >> v >> u >> p)   {

       if(v == -1 && u == -1 && p == -1) {
            break;
       }

        if(M == 1)  {

            adj[v].push_back({u,p});
        }  
    
        if(M == 0) {

            adj[u].push_back({v,p});
            adj[v].push_back({u,p});

        }

    }
    for(int i = 0; i < N; i++){

        list<no>::iterator it;

        for(it = adj[i].begin();it != adj[i].end();it++)    {

        cout << i << " " << it->v << " " << it->p << endl;

        }
    }

    return 0;

}