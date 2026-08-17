#include <iostream>
#include <list>
#define INF 999999
using namespace std;
struct Aresta{
  int origem, destino, peso;
};

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
    for(it=grafo[atual].begin();it!=grafo[atual].end();it++){
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
  int peso_mst = 0;
  for(int i=0; i<vertices; i++){
    peso_mst += distancia[i];
  }
  return peso_mst;
}



int main(){
  int vertices, arestas, origem, destino, peso, custo_total, economia=0;
  while(cin >> vertices >> arestas && vertices != 0 && arestas != 0){
    list<Aresta> grafo[vertices];
    custo_total = 0;
    for(int i=0; i<arestas; i++){
      cin >> origem >> destino >> peso;
      custo_total += peso;
      grafo[origem].push_back({origem, destino, peso});
      grafo[destino].push_back({destino, origem, peso});
    }

    economia += custo_total - prim_lista(grafo, vertices, 0);
  }
  cout << economia << endl;
  return 0;
}