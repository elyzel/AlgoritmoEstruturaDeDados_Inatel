/*
O prefeito de Anatriacé, Leon Jaspos está sendo muito criticado pelas inundações constantes na cidade. 
Ele está reativando um sistema de drenagem de água e te contratou para ajudar a resolver o problema. 
A cidade conta com algumas bombas de água conectas a um sistema de encanamentos que leva até as regiões 
alagadas. Porém essas bombas foram compradas um pouco abaixo da capacidade definida em projeto para 
que sobrasse um pouco de dinheiro da licitação para que ele pudesse fazer uma manutenção em seu iate 
particular. Ele tem um mapa de todas as bombas e as conexões com as regiões alagadas, contendo o 
tamanho de cada um dos canos.
Sabendo que a bomba tem a capacidade de atender todas as regiões a uma distância menor ou igual a 15 km, 
ele precisa saber quais regiões vão continuar alagadas dado o local de instalação da bomba.

Entrada
A entrada começa com um número inteiro indicando a quantidade R de regiões alagadas. Em seguida é 
informado um valor inteiro indicando a quantidade C de encanamentos. As C linhas seguintes contêm 
três inteiros indicando o código da região origem, o código da região destino e o tamanho em 
quilômetros de cada cano. Por fim, é informado um valor B, indicando em qual região a bomba 
vai ser instalada.

Saída
A saída é uma lista de regiões que continuam alagadas, ou seja, que estão a mais de 15 km da bomba, 
conforme o exemplo abaixo. Caso nenhum região continue alagada, apresente a mensagem "Nenhuma região 
alagada".

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 11 | |
| 14 | |
| 0 1 5 | |
| 0 2 9 | |
| 0 3 10 | |
| 1 4 1 | |
| 2 5 1 | |
| 2 6 2 | 8 |
| 3 7 2 | 9 |
| 4 5 1 | 10 |
| 5 10 10 | |
| 6 7 6 | |
| 6 9 6 | |
| 7 8 5 | |
| 8 9 5 | |
| 9 10 8 | |
*/
#define INF 99999   //<-- Define INF como se fosse o ♾️

#include<iostream>
#include<list>

using namespace std;

//Estrutura básica de grafo utilizando o Djisktra
struct Aresta   {
    int origem, destino, peso;
};

//Função do Dijsktra
void dijkstra(list<Aresta> grafo[], int vertices, int origem)    {

    bool visitado[vertices];    //<-- Identificar se o vértice foi visitado ou não
    int distancia[vertices];    //<-- Identificar o valor da distancia entre os vértices
    int atual;  //<-- Valor que representará o vértice atual

    //Criação do ponteiro que percorrerá a lista de adjacência
    list<Aresta>::iterator it;

    //Percorrerá pela lista definindo os valores iniciais dos vértices
    for(int i = 0; i < vertices; i++)   {
        visitado[i] = false;    //Todos os vértices são considerados não visitados
        distancia[i] = INF;     //Todos os vértices tem a distância igual ao infinito
    }

    distancia[origem] = 0;

    atual = origem;

    //Laço para visitar todos os vértices não visitados
    while(!visitado[atual]) {

        visitado[atual] = true;


        for(it = grafo[atual].begin(); it != grafo[atual].end(); it++)  {

            //Obtenção do destino e peso 
            int d = it->destino;
            int p = it->peso;

            //Caso o caminho distancia atual seja menor que a distancia registrada do vértice origem para o destino:
            //O caminho com menor distancia é atualizada
            if(!visitado[d] && distancia[atual] + p < distancia[d]) {

                distancia[d] = distancia[atual] + p;

            }
        }

        int menor_distancia = INF;

        //Após verificar as regiões, precisa-se saber qual deles tem a menor distancia e passar a ser o atual
        for(int i = 0; i < vertices; i++)   {

            //Se os não visitados, tiverem uma distancia menor que o menor_caminho, o menor_caminho passa a receber o valor da menor distancia
            if(!visitado && distancia[i] < menor_distancia) {

                menor_distancia = distancia[i]; //Transferência do valor da menor distancia
                atual = i;  //Reposicionamento da região "atual"

            }
        }
    }

    //Criação de um bool para alagada
    bool alagada = false;

    //Percorre por todos os vértices
    for(int i = 0; i < vertices; i++)   {

        //Condição que leva a considerar a região como alagada
        if(distancia[i] > 15)   {

            //Imprime os vertices com distancia maior que 15
            cout << i << endl;
            alagada = true; //<-- considera o vertice como alagado

        }

        if(!alagada)    {
            cout << "Nenhuma regiao alagada" << endl;
        }
    }
}

int main()  {

    int vertices, arestas;
    int origem, destino, peso;
    int bomba;

    cin >> vertices >> arestas;

    list<Aresta> grafo[vertices];

    for(int i = 0; i < vertices; i++)   {

        cin >> origem >> destino >> peso;

        grafo[origem].push_back({origem, destino, peso});

        }

    cin >> bomba;

    dijkstra(grafo, vertices, bomba);

    return 0;

}
