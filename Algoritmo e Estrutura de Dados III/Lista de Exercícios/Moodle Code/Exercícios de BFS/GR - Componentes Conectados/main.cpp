/*
Como vimos, é possível saber se um grafo é conexo usando um percurso em largura: se todos os vértices forem visitados, então o grafo é conexo.

Faça um programa que faça uso do algoritmo de busca em largura e verifique se um dado grafo é ou não conexo.

Entrada

A entrada consiste de várias linhas:

A primeira linha contém 2 inteiros: 

- o primeiro corresponde ao número de vértices do grafo. Você pode considerar que a rede não tem mais que 10 vértices. 

- o segundo identifica o vértice inicial (start) 

As demais linhas têm dois números inteiros, que correspondem aos vértices de origem e destino de uma aresta.

A entrada de dados termina quando ocorrer uma linha com dois números iguais a -1 (que não deve ser considerada).

Saída
Na saída, o programa deve dizer se o grafo é ou não conexo.

Observação: para este problema, considere que o grafo é não direcionado, e que cada aresta tem peso 1.

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 9 0 | Conexo |
| 0 1 | |
| 0 7 | |
| 1 2 | |
| 1 7 | |
| 2 3 | |
| 2 5 | |
| 2 8 | |
| 3 4 | |
| 3 5 | |
| 4 5 | |
| 5 6 | |
| 6 7 | |
| 6 8 | |
| 7 8 | |
| -1 -1 | |
*/

#include<iostream>
#include<list>

using namespace std;

struct Aresta   {
    int origem, destino, peso;
};

//Limite de vértices conforme o enunciado da questão
bool visitado[10]; 

//Se for conexo, é um valor positivo
bool conexo = true;

void bfs(list<Aresta> grafo[], int nVertices, int s) {
//list<Aresta> grafo[] -> representa a criação do grafo
//int vertices -> representa o número total de vertices
//int s -> posição do vértice inicial

    //Criação da lista de adjacência em relação a visitacao da fila
    list<int> fila_visitacao;

    //Criação do ponteiro que percorrerá pela lista de adjacência
    list<Aresta>::iterator it;

    //Percorre a lista de adjacência definindo que nenhum foi visitado
    for(int i = 0; i < nVertices; i++)  {
        visitado[i] = false;
    }

    //Adicione o vértice s na lista e considera como visitada, logo que é
    //a origem do grafo
    fila_visitacao.push_back(s);
    visitado[s] = true;

    //Varre todo vetor até visitar todos os vértices
    while(!fila_visitacao.empty())    {
        //Adiciona a variável atual ao primeiro vértice da fila
        int atual = fila_visitacao.front();
        //Remove o primeiro vértice da lista
        fila_visitacao.pop_front();

        for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)  {
            
            //A variável representa o destino do ponteiro na lista
            int vizinho = it->destino;

            //Verifica se o vizinho foi visitado ou não
            if(!visitado[vizinho])  {
                //Ao visitar o vizinho, o considera como visitado e adiciona a lista
                visitado[vizinho] = true;
                fila_visitacao.push_back(vizinho);
            }
        }
    }
//Função adicionada para armazenar para quem não foi visitado, será considerado
//não conexo.
    for(int i = 0; i < nVertices; i++)  {
        if(!visitado[i])    {
            conexo = false;
            break;
        }
    }
}

int main()  {

    int vertices, s;
    int origem, destino;

    cin >> vertices >> s;

    //Criação da lista de adjacência
    list<Aresta> grafo[vertices];

    while(cin >> origem >> destino) {
        if(origem == -1 && destino == -1)   {
            break;
        }
        //Define o tipo de grafo, nesse caso é não direcional. O peso da aresta é 1, conforme o enunciado.
        //Pois tem sentido de ir e voltar
        grafo[origem].push_back({origem, destino, 1});
        grafo[destino].push_back({destino, origem, 1});
    }

    bfs(grafo, vertices, s);

    if(conexo)  {
        cout << "Conexo" << endl;
    }   else    {
        cout << "Não conexo" << endl;
    }

    return 0;

} 