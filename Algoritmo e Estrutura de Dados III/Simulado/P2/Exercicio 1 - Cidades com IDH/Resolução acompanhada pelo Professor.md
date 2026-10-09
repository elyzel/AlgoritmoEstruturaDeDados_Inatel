>[!QUESTION]
>Um turista esta planejando seu roteiro de viagem. Considerando que ele só quer visitar uma lista de cidades com um determinado nível de IDH ou maior, desenvolva um código para ajudar ele a definir quanto de combustível ele precisa comprar. Ou seja, dado a cidade de origem e a cidade de destino, calcule e retorne a distância mínima para fazer essa rota.    
>  
A entrada começa com um inteiro C que é o número de cidades a serem consideradas. Nas C linhas seguintes são dadas as informações de cada cidade: uma string contendo o nome da cidade e um número real que é o IDH da cidade (cada cidade deve ter um código automático que um número inteiro de 0 a C-1 dado na ordem em que a cidade foi inserida). Em seguida é informado um numero E, que é o número de estradas que conectam as C cidades. As próximas E linhas contêm três inteiros Co, Cd e D que são respectivamente o código da cidade de origem, o código da cidade de destino e a distância de cada uma das E estradas (todas as estradas permitem navegação nos dois sentidos). Por fim, são informados dois inteiros Vo e Vd que representam o código da cidade origem e o código da cidade de destino da viagem e um número real H que representa o IDH mínimo que uma cidade precisa ter para ser considerada na rota.  
>  
A saída deve ser um inteiro representando a menor rota para sair da cidade Vo e chegar na cidade Vd passando apenas por cidades com um IDH maior que H.

![[Pasted image 20261009181455.png]]


# Resposta 1: Diskstra Manipulado

```cpp
#define INF 99999

#include <iostream>
#include <list>
#include<string>

using namespace std;

struct Aresta{

  int origem, destino, peso;

};

  

int dijkstra_lista(list<Aresta> grafo[], int vertices, int origem, int destino){

  bool visitado[vertices];

  int pai[vertices], distancia[vertices], atual;

  list<Aresta>::iterator it;

  
// Definição dos valores dos vetores
  for(int i=0; i<vertices; i++){

    visitado[i] = false;

    pai[i] = -1;

    distancia[i] = INF;

  }

  distancia[origem] = 0;

  atual = origem;

  
// Definição de rotas entre os vértices
  while(!visitado[atual]){

    visitado[atual] = true;

    for(it = grafo[atual].begin(); it != grafo[atual].end(); it++){

      int d = it->destino, p = it->peso;

      if(!visitado[d] && distancia[atual] + p < distancia[d]){

        distancia[d] = distancia[atual] + p;

        pai[d] = atual;

      }

    }

//Define a menor distancia entre os vértices
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
	
	list<Aresta> grafo[MAX_CIDADES];
/* cidade, e, cidade origem, cidade destino, distancia, vertice origem, vertice destino */
	int c, e, co, cd, d, vo, vd; 
	string nome;
	float h, idhs[MAX_CIDADES];
	
	cin >> c;
	
	for(i = 0; i < c; i++){
		cin >> nome;
		cin >> idhs[i];
	}
	
	cin >> e;
	Aresta temp[e]
	
	for(i = 0; i < e; i++){
		cin >> co >> cd >> d;
		grafo[co].push_back({co, cd, d});
		grafo[cd].push_back({cd, co, d})
	}
	
	cin >> vo >> vd >> h;
	
	cout << dijkstra(grafo, c, ,vo, vd, idhs, h) << endl;
  
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

```

# Resposta 2: Diskstra Convencional e Filtro no Final

```cpp
#define INF 99999

#include <iostream>
#include <list>
#include<string>

using namespace std;

struct Aresta{

  int origem, destino, peso;

};

  

int dijkstra_lista(list<Aresta> grafo[], int vertices, int origem, int destino){

  bool visitado[vertices];

  int pai[vertices], distancia[vertices], atual;

  list<Aresta>::iterator it;

  
// Definição dos valores dos vetores
  for(int i=0; i<vertices; i++){

    visitado[i] = false;

    pai[i] = -1;

    distancia[i] = INF;

  }

  distancia[origem] = 0;

  atual = origem;

  
// Definição de rotas entre os vértices
  while(!visitado[atual]){

    visitado[atual] = true;

    for(it = grafo[atual].begin(); it != grafo[atual].end(); it++){

      int d = it->destino, p = it->peso;

      if(!visitado[d] && distancia[atual] + p < distancia[d] && idhs[d] >= h){

        distancia[d] = distancia[atual] + p;

        pai[d] = atual;

      }

    }

//Define a menor distancia entre os vértices
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
	
	list<Aresta> grafo[MAX_CIDADES];
/* cidade, e, cidade origem, cidade destino, distancia, vertice origem, vertice destino */
	int c, e, co, cd, d, vo, vd; 
	string nome;
	float h, idhs[MAX_CIDADES];
	
	cin >> c;
	
	for(i = 0; i < c; i++){
		cin >> nome;
		cin >> idhs[i];
	}
	
	cin >> e;
	
	for(i = 0; i < e; i++){
		cin >> co >> cd >> d;
		grafo[co].push_back({co, cd, d});
		grafo[cd].push_back({cd, co, d})
	}
	
	cin >> vo >> vd >> h;
	
	cout << dijkstra(grafo, c, ,vo, vd, idhs, h) << endl;
  
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

```