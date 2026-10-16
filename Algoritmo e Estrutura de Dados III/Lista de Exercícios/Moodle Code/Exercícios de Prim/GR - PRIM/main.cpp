/*
Uma árvore geradora mínima para um grafo G, ponderado, não direcionado e conexo, é um subconjunto das 
arestas que G que mantém o grafo conexo, e cuja soma dos pesos das arestas é p menor possível.

Dentre os algoritmos que resolvem este problema, temos o de Prim, que coloca um vértice inicial na 
árvore e vai adicionando as arestas de menor custo entre um vértice inicial na árvore e outro fora 
dela, até que todos os vértices estejam conectados.

O pseudocódigo deste algoritmo é mostrado abaixo:

MST_PRIM(G,start)
    para cada u em V[G]
        intree[u] = false
        distance[u] = INT_MAX
        parent[u] = -1
    distance[start] = 0
    v = start
    enquanto(intree[v] == false)
        intree[v] = true
        para cada p em Adj[v]
            destino = p->v
            weight = p->peso
            if(distance[destino] > weight && intree[destino]==false)
                distance[destino] = weight
                parent[destino] = v
        v = 0
        dist = INT_MAX
        para cada u em V[G]
            se(intree[u]==false && dist>distance[u])
                dist = distance[u]
                v = u
Faça um programa que leia dos dados dos vértices e arestas de um grafo e os armazene em uma lista de adjacências. Dpois o programa deve mostrar a sua árvore geradora mínima.

Faça uma função para implementar o algoritmo de Prim. O cabeçalho desta função deve ser:

void prim(list<no>adj[], int nVertices, int start)
Entrada
A entrada consiste de várias linhas:
A primeira linha contém 3 inteiros: 

- o primeiro corresponde ao número de vértices do grafo. Você pode considerar que o grafo terá no 
máximo 10 vértices.

- o segundo define se o grafo é orientado (1) ou não orientado (0)

- o terceiro identifica o vértice inicial da árvore

As demais linhas três inteiros, que correspondem ao vértice de origem, o ´vertice de destino e 
o peso de cada aresta, respectivamente. A entrada de dados termina quando ocorrer uma linha com
 três números iguais a -1 (esta não deve ser inserida no grafo).

Saída
A saída deverá mostrar as arestas que constituem a árvore geradora mínima, bem como o custo total dela,
como no exemplo abaixo.

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 9 0 0 | Arvore Geradora Minima: |
| 0 1 4 | 0 1 |
| 0 7 8 | 1 2 |
| 1 2 8 | 2 3 |
| 1 7 11 | 3 4 |
| 2 3 7 | 2 5 |
| 2 5 4 | 5 6 |
| 2 8 2 | 6 7 |
| 3 4 9 | 2 8 |
| 3 5 14 | Custo: 37 |
| 4 5 10 | |
| 5 6 2 | |
| 6 7 1 | |
| 6 8 6 | |
| 7 8 7 | |
| -1 -1 -1 | |
*/

#include<iostream>
#include<list>
#define INF 999999

using namespace std;

struct Aresta   {
    
    int origem, destino, peso;

};

void prim(list<Aresta> adj[], int nVertices, int start) {
    
    bool intree[nVertices]; //<-- Responsável por conferir se o vértice
    //entrou na árvore geradora mínima
    int distance[nVertices]; //<-- Guarda o menor peso conhecido de uma
    //aresta que conecta aquele vértice à árvore
    int parent[nVertices];  //<-- Guarda de qual vértice vem a aresta escolhida

    //Define os valores iniciais de todos os vértices existentes
    for(int i = 0; i < nVertices; i++)  {
        intree[i] = false; //<-- Não pertence a arvore
        distance[i] = INF; //<-- O valor do peso da aresta é "infinito"
        parent[i] = -1; //<-- No inicio, nenhum vértice tem pai
    }

    distance[start] = 0; //<-- distancia do vértice origem

    int v = start;  //<-- 1° vértice que estamos inserindo na árvore

    //Enquanto o vértice v estiver fora da arvore, será executado.
    while(!intree[v]) = true;

    //Criação do ponteiro que percorrerá a lista de adjacência das arestas
    lists<Aresta>::iterator it;

    //Percorre todas as arestas existentes na lista de adj v
    for(it = adj[v].begin(); it != adj[v].end(); it++)  {

        int destino = it->destino; //<-- aponta a variavel destino para o valor que o iterator
        //está apontando.

        //Aponta a variável peso para o valor que it está apontando.
        int peso = it->peso;

        //Verificação de condição essencial sobre PRIM para executar as linhas abaixo.
        if(distance[destino] > peso && != intree[destino])  {
            //1° condição: A distancia até o destino deve ser menor que a melhor conexao atual
            //2° condição: O destino ainda não está na árvore

            distance[destino] = peso;   //<-- Redefini o valor da conexão melhor
            parent[destino] = v;    //<-- Se o vértice vizinho entrar, o vértice será conectado
            //ao vértice aprovado.
        }

        //Depois de analisar todos os vizinhos...
        v = 0;
        int dist = INF;

        //Percorre toda a lista de adj para encontrar a menor distancia entre os vértices
        for(int u = 0; u < nVertices; u++)  {

            //Se o vértice ainda está fora da arvores e a distancia é menor do que o encontrado:
            if(!intree[u] && dist > distance[u])    {
                
                dist = distance[u]; //<-- O valor de dist é redefinido para a distancia menor encontrada
                v = u; //v adquire o valor do vértice com menor peso
            }
        }

        //Definimos o custo igual a 0
        int custo = 0;

        cout << "Arvore Geradora Minima:" << endl;

        //Percorre todos os vértices existentes
        for(int i = 0; i < nVertices; i++)  {

            //Verifica se existe algum vértice pai
            //-1 representa que não tem pai
            if(parent[i] != -1) {
                cout << parent[i] << " " << i << endl;
                custo += distance[i];
            }
        }

        cout << "Custo: " << custo << endl;
    }

    int main()  {

        int vertices, orientado, start;
        int origem, destino, peso;

        cin >> vertices >> orientado >> start;

        //Cria o grafo com a quantidade de vertices descritas pelo usuário
        list<Aresta> grafo[vertices];

        while(cin >> origem >> destino >> peso) {

            if(origem != -1 && destino != -1 && peso != -1) {
                break;
            }

            //Caso seja somente direcional, será somente um sentido unilateral
            grafo[origem].push_back({origem, desitno, peso});

            //Caso seja, bidirecional será sentido duplo
            if(orientado == 0)  {
                grafo[destino].push_back({destino, origem, peso});
            }
        }

        //Aplica a função Prim
        prim(grafo, vertices, start);

        return 0;
    }


}