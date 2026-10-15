/*
Faça um programa que leia dos dados dos vértices e arestas de um grafo não orientado, e os armazene 
em uma lista de adjacências. Depois o programa deve mostrar o percurso em largura do grafo gerado.

Faça uma função para implementar o percurso em largura. O cabeçalho desta função deve ser:

void bfs(list<no>adj[], int nVertices, int s)

O algoritmo de busca em largura é mostrado abaixo:

BFS(adj[], nVertices, s) ​
    for u = 0 até nVertices-1
        if u != s
            state[u] = ‘u’ // undiscovered​
            pai[u] = -1 // sem pais  ​
 ​
    state[s] = ‘d’ // discovered​
    pai[s] = -1 ​
    Q.push_back(s)​
 ​
    while (!Q.empty())​
        u = *Q.begin()​
        Q.pop_front() ​
        print u ​
        for (p=adj[u].begin();p!=adj[u].end();p++)​
            v = p->v
            print (u,v) ​
            if state[v] = ‘u’​
                state[v] = ‘d’ ​
                pai[v] = u ​
                Q.push_back(v)​
        state[u] = ‘p’ // processed​
Entrada
A entrada consiste de várias linhas:
- a primeira linha contém dois inteiros: o primeiro corresponde ao número de vértices do grafo, e o segundo ao vértice inicial. 

- as demais linhas três inteiros, que correspondem ao vértice de origem, o ´vertice de destino e o peso de cada aresta, respectivamente. 
A entrada de dados termina quando ocorrer uma linha com três números iguais a -1 (esta não deve ser inserida no grafo).

Saída
A saída deverá mostrar os vértices e arestas visitados, como no exemplo abaixo.

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 5 0 | 0 |
| 0 1 0 | 0 1 |
| 0 4 0 | 0 4 |
| 1 2 0 | 1 |
| 1 3 0 | 1 0 |
| 1 4 0 | 1 2 |
| 2 3 0 | 1 3 |
| 3 4 0 | 1 4 |
| -1 -1 -1 | 4 |
| | 4 0 |
| | 4 1 |
| | 4 3 |
| | 2 |
| | 2 1 |
| | 2 3 |
| | 3 |
| | 3 1 |
| | 3 2 |
| | 3 4 |
*/

#include<iostream>
#include<list>

using namespace std;

//Struct que compõe o grafo
struct Aresta{
    int origem, destino, peso;
};

//Função que representa o "BFS" ou também conhecido como Breadth-First Search
//Tradução: Busca em Largura
void bfs(list<Aresta> adj[], int nVertices, int s)   {
    
    //Verificação se o grafo foi visitado ou não
    bool visitado[nVertices];

    //Definição dos vértices pais em relação aos outros vértices
    int pai[nVertices];

    //Criação da lista de adjacência única para visitação
    list<int> fila_visitacao;

    //Criação da lista de adjacência para valores da struct
    list<Aresta>::iterator it;

    //Inicialização dos vértices
    for(int i = 0; i < nVertices; i++)  {
        //Definição que todos os vértices inicialmente não foram visitados
        visitado[i] = false;
        //A variável pai começa por -1, pois começa pela origem do grafo
        pai[i] = -1;
    }

    //Inserção do vértice inicial na fila
    fila_visitacao.push_back(s);
    visitado[s] = true;

    //empty?
    while(!fila_visitacao.empty())   {
        
        //Consulta o primeiro vértice da fila
        int atual = fila_visitacao.front();

        //Remove o PRIMEIRO vértice da fila
        fila_visitacao.pop_front();

        //Imprime o vértice visitado
        cout << atual << endl;

        //Criação do ponteiro para percorrer pela lista de adjacência
        for(it = adj[atual].begin();it != adj[atual].end(); it++)   {

            //Acessa o destino da aresta atual
            int vizinho = it->destino;

            //Imprime o vértice atual e seus vizinhos
            cout << atual << " " << vizinho << endl;

            //Verifica se os vizinho do vértice foram visitados ou não
            //Se for visitados todos os vizinhos, encerra o laço de repetição
            //Se não for visitado os vizinhos, até terminar
            if((!visitado[vizinho]))    {
                //Se foi visitado, identifica o vizinho como "true"
                //Ou seja, foi visitado.
                visitado[vizinho] = true;
                //Transfere o vértice atual para o vizinho
                pai[vizinho] = atual;
                //Adiciona os vizinhos ao final da fila
                fila_visitacao.push_back(vizinho);
            }
        }
    }
}

int main()  {
    int vertices, s;
    int origem, destino, peso;

    cin >> vertices >> s;

    list<Aresta> grafo[vertices];

    while(cin >> origem >> destino >> peso) {

        if(origem == -1 && destino == -1 && peso == -1) {
            break;
        }

        grafo[origem].push_back({origem, destino, peso});
        grafo[destino].push_back({destino, origem, peso});
    }

    bfs(grafo, vertices, s);

    return 0;
}