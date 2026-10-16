/*
Poles está desenvolvendo uma árvore de habilidades para o seu jogo de RPG. Ele quer que os personagens 
possam escolher, partindo de uma habilidade principal, algumas ramificações possíveis. Cada habilidade 
pode ser desbloqueada por diferentes caminhos de upgrades, porém todos os upgrades são direcionados.

Para cada upgrade de habilidade, o personagem deve gastar alguns pontos de experiência e pode adquirir 
alguma pontuação de poder.

Ele quer saber, dada um determinada árvore de habilidades, qual é o custo mínimo de experiência para 
desbloquear todas as habilidades.

Entrada
A entrada começa com um número inteiro indicando a quantidade H de habilidades. As H linhas seguintes 
contêm o nome (palavra) e o poder (número real) de cada habilidade (cada habilidade tem um código 
automático de 0 a H de acordo com a entrada de dados). 

Em seguida é informado um valor inteiro indicando a quantidade U de upgrades possíveis. As U linhas 
seguintes contêm três inteiros indicando o código da habilidade origem, o código da habilidade destino 
e o custo de cada upgrade.

Saída
A saída é um número inteiro indicando o custo mínimo para desbloquear todas as habilidades.

| Exemplo de entrada | Exemplo de saída |
| :--- | :--- |
| 10 | |
| Base 0 | |
| Dash 1 | |
| Thief 3 | |
| Hunter 3 | |
| Assassin 4 | |
| BeastMaster 5 | |
| Berserker 7 | |
| WildMagic 2 | |
| Vengeance 4 | |
| Life 5 | |
| 12 | 23 |
| 0 1 1 | |
| 1 2 2 | |
| 1 3 2 | |
| 3 4 3 | |
| 3 5 3 | |
| 3 6 4 | |
| 0 7 2 | |
| 7 8 3 | |
*/

#include <iostream>
#include <list>
#include <string>
#define INF 999999
using namespace std;

struct Aresta{
  int origem, destino, peso;
};

// Mesmo Prim do modelo: soma o custo das arestas da AGM
int prim_lista(list<Aresta> grafo[], int vertices, int origem){

  bool visitado[vertices];
  int pai[vertices], distancia[vertices], atual;

  for(int i=0; i<vertices; i++){
    visitado[i] = false;
    pai[i] = -1;
    distancia[i] = INF;
  }

  atual = origem;
  distancia[atual] = 0;

  while(!visitado[atual]){

    visitado[atual] = true;
    list<Aresta>::iterator it;

    for(it=grafo[atual].begin(); it!=grafo[atual].end(); it++){

      int d = it->destino, p = it->peso;

      if(!visitado[d] && p < distancia[d]){

        distancia[d] = p;
        pai[d] = atual;

      }
    }

    int menor_distancia = INF;

    for(int i=0; i<vertices; i++){

      if(!visitado[i] && distancia[i] < menor_distancia){

        menor_distancia = distancia[i];
        atual = i;

      }
    }
  }

  int custo = 0;

  for(int i=0; i<vertices; i++){

    custo += distancia[i];

  }

  return custo;

}

int main(){

  int H, U, origem, destino, custo;
  string nome;
  double poder;               // o poder é lido, mas não entra no cálculo

  cin >> H;

  list<Aresta> grafo[H];

  for(int i=0; i<H; i++){

    cin >> nome >> poder;

  }

  cin >> U;

  for(int i=0; i<U; i++){

    cin >> origem >> destino >> custo;

    grafo[origem].push_back({origem, destino, custo});
    grafo[destino].push_back({destino, origem, custo});

  }

  cout << prim_lista(grafo, H, 0) << endl;

  return 0;

}