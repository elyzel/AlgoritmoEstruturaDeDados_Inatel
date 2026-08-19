#define MAX_V 100
#include<iostream>
#include<list>
using namespace std;

struct Aresta{
	int origem, destino;
};

//void dfs(bool grafo[MAX_V][MAX_V], int vertices, int origem, bool visitado[]){
void dfs(list<Aresta> grafo[], int vertices, int origem, bool visitado[]){
	visitado[origem] = true;
	list<Aresta>::iterator it;
	//for(int destino=0; destino<vertices; destino++){
		//if(grafo[origem][destino] && !visitado[destino]){
    for(it=grafo[origem].begin(); it != grafo[origem].end(); it++){
    	int destino = it->destino;//(*it).destino;
    	if( !visitado[destino]){
				dfs(grafo, vertices, destino, visitado);
		}
	}
	cout<<origem<<endl;
}

int main(){
	
	int vertices, origem, destino;
	cin >> vertices;
	
	list<Aresta> grafo[vertices];
	
	//bool grafo[MAX_V][MAX_V];
	// for(int i=0; i<vertices; i++){
	// 	for(int j=0; j<vertices; j++){
	// 		grafo[i][j] = false;
	// 	}
	// }
	
	while(cin >> origem >> destino && origem != -1 && destino != -1){
		// grafo[origem][destino] = true;
		// grafo[destino][origem] = true;
		grafo[origem].push_back({origem, destino});
		grafo[destino].push_back({destino, origem});

	}
	
	bool visitado[vertices];
	for(int i=0; i<vertices; i++)
		visitado[i] = false;
	
	dfs(grafo, vertices, 0, visitado);
	
	
	return 0;
}