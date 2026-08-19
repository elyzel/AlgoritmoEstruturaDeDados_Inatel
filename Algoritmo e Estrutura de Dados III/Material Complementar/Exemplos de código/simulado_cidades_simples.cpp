#define INF 99999
#include <iostream>
#include <list>
using namespace std;

struct Aresta{
  int origem, destino, peso;
};

int dijkstra_lista(list<Aresta> grafo[], int vertices, int origem, int destino){
  bool visitado[vertices];
  int pai[vertices], distancia[vertices], atual;
  list<Aresta>::iterator it;

  for(int i=0; i<vertices; i++){
    visitado[i] = false;
    pai[i] = -1;
    distancia[i] = INF;
  }
  distancia[origem] = 0;
  atual = origem;

  while(!visitado[atual]){
    visitado[atual] = true;
    for(it = grafo[atual].begin(); it != grafo[atual].end(); it++){
      int d = it->destino, p = it->peso;
      if(!visitado[d] && distancia[atual] + p < distancia[d]){
        distancia[d] = distancia[atual] + p;
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
  return distancia[destino];
}

int main(){
  int num_cidades, num_estradas, viagem_origem, viagem_destino, origem, destino, distancia;
  float idh;
  string nome;
  cin >> num_cidades;

  list<Aresta> grafo[num_cidades];
  float idhs[num_cidades];

  for(int i=0; i< num_cidades; i++){
    cin >> nome;
    cin >> idhs[i];
  }

  cin >> num_estradas;

  list<Aresta> estradas_temp;

  for(int j=0; j < num_estradas; j++){
    cin >> origem;
    cin >> destino;
    cin >> distancia;
    estradas_temp.push_back({origem, destino, distancia});
  }

  cin>>viagem_origem>>viagem_destino>>idh;

  list<Aresta>::iterator it;
  for(it = estradas_temp.begin(); it != estradas_temp.end(); it++){
    origem = it->origem;
    destino = it->destino;
    distancia = it->peso;

    if(idhs[origem] >= idh && idhs[destino] >= idh){
      grafo[origem].push_back({origem, destino, distancia});
      grafo[destino].push_back({destino, origem, distancia});
    }
  }
  cout << dijkstra_lista(grafo, num_cidades, viagem_origem, viagem_destino) << endl;
}