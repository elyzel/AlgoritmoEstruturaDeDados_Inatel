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
  int vertices, arestas, origem, destino, peso;
  cin >> vertices;
  list<Aresta> grafo[vertices];
  cin >> arestas;
  for(int i=0; i<arestas; i++){
    cin >> origem >> destino >> peso;
    grafo[origem].push_back({origem, destino, peso});
    grafo[destino].push_back({destino, origem, peso});
  }
  for(int i=0; i<vertices; i++){
    list<Aresta>::iterator it;
    cout << i << ": ";
    for(it = grafo[i].begin(); it != grafo[i].end(); it++){
      cout << "(";
      cout << it->destino << "," << it->peso;
      cout << "), ";
    }
    cout<<endl;
  }

  cout << prim_lista(grafo, vertices, 0);
}

/**
6
10
0 1 6
0 2 1
0 3 5
1 2 2
1 4 5
2 3 2
2 4 6
2 5 4
3 5 4
4 5 3

*/