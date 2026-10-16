/*
Um turista esta planejando seu roteiro de viagem. Considerando que ele só quer visitar uma lista de 
cidades com um determinado nível de IDH ou maior, desenvolva um código para ajudar ele a definir 
quanto de combustível ele precisa comprar. Ou seja, dado a cidade de origem e a cidade de destino, 
calcule e retorne a distância mínima para fazer essa rota.  

A entrada começa com um inteiro C que é o número de cidades a serem consideradas. Nas C linhas seguintes 
são dadas as informações de cada cidade: uma string contendo o nome da cidade e um número real que é 
o IDH da cidade (cada cidade deve ter um código automático que um número inteiro de 0 a C-1 dado na 
ordem em que a cidade foi inserida). Em seguida é informado um numero E, que é o número de estradas 
que conectam as C cidades. As próximas E linhas contêm três inteiros Co, Cd e D que são respectivamente 
o código da cidade de origem, o código da cidade de destino e a distância de cada uma das E estradas 
(todas as estradas permitem navegação nos dois sentidos). Por fim, são informados dois inteiros Vo e 
Vd que representam o código da cidade origem e o código da cidade de destino da viagem e um número real 
H que representa o IDH mínimo que uma cidade precisa ter para ser considerada na rota.

A saída deve ser um inteiro representando a menor rota para sair da cidade Vo e chegar na cidade Vd 
passando apenas por cidades com um IDH maior que H.

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 5 | |
| anatrice 15.4 | |
| odarilheo 10.1 | |
| tantisara 15.2 | |
| ujesania 10.3 | |
| maribal 15.1 | |
| 7 | |
| 2 1 1 | 4 |
| 2 0 3 | |
| 1 0 4 | |
| 0 3 1 | |
| 1 4 2 | |
| 0 4 1 | |
| 3 4 2 | |
| 2 4 13.0 | |
*/

#include <iostream>
#include <list>
#include <string>
using namespace std;

const int MAX = 1000;            // limite máximo de cidades
const int INF = 1000000000;      // "infinito"

struct Cidade {
  string nome;
  double idh;
};

struct Aresta {
  int origem, destino, peso;
};

int dijkstra_lista(list<Aresta> grafo[], int vertices, int origem, int destino,
                   Cidade cidades[], double H) {

  if (cidades[origem].idh < H || cidades[destino].idh < H)
    return -1;

  bool visitado[MAX];
  int distancia[MAX];
  int atual;
  list<Aresta>::iterator it;

  for (int i = 0; i < vertices; i++) {
    visitado[i] = false;
    distancia[i] = INF;
  }
  distancia[origem] = 0;
  atual = origem;

  while (!visitado[atual]) {
    visitado[atual] = true;

    for (it = grafo[atual].begin(); it != grafo[atual].end(); it++) {
      int d = it->destino, p = it->peso;

      if (cidades[d].idh < H) continue;

      if (!visitado[d] && distancia[atual] + p < distancia[d])
        distancia[d] = distancia[atual] + p;
    }

    int menor_distancia = INF;
    for (int i = 0; i < vertices; i++) {
      if (!visitado[i] && distancia[i] < menor_distancia) {
        menor_distancia = distancia[i];
        atual = i;
      }
    }
  }

  return (distancia[destino] == INF) ? -1 : distancia[destino];
}

int main() {
  int C, E;

  cin >> C;
  Cidade cidades[MAX];
  for (int i = 0; i < C; i++)
    cin >> cidades[i].nome >> cidades[i].idh;

  cin >> E;
  list<Aresta> grafo[MAX];
  for (int i = 0; i < E; i++) {
    int co, cd, dist;
    cin >> co >> cd >> dist;
    grafo[co].push_front({co, cd, dist});
    grafo[cd].push_front({cd, co, dist});
  }

  int Vo, Vd;
  double H;
  cin >> Vo >> Vd >> H;

  cout << dijkstra_lista(grafo, C, Vo, Vd, cidades, H) << endl;
  return 0;
}