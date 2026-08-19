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
  atual = destino;
  while(atual != origem){
    cout << atual + 1 << " <- ";
    atual = pai[atual];
  }
  cout << atual + 1 << endl;
  return distancia[destino];
}


int main(){
  int vertices, arestas, o, d, p;
  cin >> vertices;
  list<Aresta> grafo[vertices];
  cin >> arestas;
  for(int i=0; i<arestas; i++){
    cin >> o >> d >> p;
    o--; d--;
    grafo[o].push_front({o,d,p});
    grafo[d].push_front({d,o,p});
  }
  list<Aresta>::iterator it;
  for(int i=0; i<vertices; i++){
    cout<<i+1<<": ";
    for(it = grafo[i].begin(); it != grafo[i].end(); it++){
      cout << "(" ;
      cout << it->destino+1 << ", " << it->peso ;
      cout << "), ";
    }
    cout<<endl;
  }
  cout << dijkstra_lista(grafo, vertices, 0, 4) << endl;
  return 0;
}


/*
6 9
1 2 7
1 3 9
1 6 14
2 3 10
2 4 15
3 4 11
3 6 2
4 5 6
5 6 9

*/
