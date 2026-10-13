/*
Faça um programa que leia dos dados dos vértices e arestas de um grafo e os armazene em uma lista de adjacências. Depoism mostre o grafo gerado.
Cada nó da lista de adjacências deve conter o vértice de destino e o peso da aresta.

Use a struct abaixo para implementar seu programa. 

struct no
{
    int v; // vertice adjacente
    int peso; // peso da aresta
};
Faça uma função para criar as arestas. O cabeçalho desta função deve ser:

void cria_aresta(list<no>adj[], int u, int v, int p, int orientado)
Entrada
A entrada consiste de várias linhas:
- a primeira linha contém dois inteiros: o primeiro corresponde ao número de vértices do grafo, e o segundo define se o grafo é orientado (1)
 ou não orientado (0).

- as demais linhas três inteiros, que correspondem ao vértice de origem, o ´vertice de destino e o peso de cada aresta, respectivamente. 
A entrada de dados termina quando ocorrer uma linha com três números iguais a -1 (esta não deve ser inserida no grafo).

Saída
A saída deverá mostrar a lista de adjacências gerada, como no exemplo abaixo.
*/

#include<iostream>
#include<list>

using namespace std;

struct no{
    int v; //< -- vertice
    int p; //< -- peso
};

void cria_aresta(list<no>adj[], int u, int v, int p, int orientado) {
    // u = vertice de origem, v = vertice de destino, p = peso da aresta, orientado = se unidirecional ou bidirecional

    //< -- Acessado a lista "u" e coloca no final da lista os valores "v" e "p".
    adj[u].push_back({v,p});

    //< -- Verifica o tipo de grafo, ou seja, verifica se é direcionado ou não direcionado
    //< -- A funcionalidade dessa função é, caso seja não direcionado, o valor do peso será tanto de u -> v quanto de v -> u
    if(orientado == 0)  {

        adj[v].push_back({u,p});
    }
}

int main()  {

    int n; //< -- Número de Vértices
    int orientado;//< -- Verifica qual o tipo de grafo(Direcionado ou Não Direcionado)

    cin >> n >> orientado;

    //< -- Criação de Lista de Adjacências
    list<no> adj[n];

    //< -- u = vertice de origem, v = vertice de destino, p = peso da aresta
    int u, v, p;

    while(cin >> u >> v >> p)   {
        //< -- Verifica se todos os valores de "u", "v", e "p" resultam em -1
        //< -- Caso sim, o laço se rompe.
        if(u == -1 && v == -1 && p == -1)   {
            break;
        }

        //< - Cria a aresta de acordo com os valores fornecidos pelo usuario
        cria_aresta(adj, u, v, p, orientado);
    }

    for(int i = 0; i < n; i++)  {

        //< -- Ponteiro que percorre pela lista de adjascência
        list<no>::iterator it;

        for(it = adj[i].begin(); it != adj[i].end(); it++)   {
            cout << i << " " << it->v << " " << it->p << endl;
        }
    }

    return 0;

}