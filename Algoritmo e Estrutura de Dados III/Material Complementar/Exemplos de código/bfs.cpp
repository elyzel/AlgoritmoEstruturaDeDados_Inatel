#include<iostream>
#include<list>
using namespace std;

struct Aresta {
	int origem, destino, peso;
};

//bool bfs(bool grafo[][5], int vertices, int origem){
bool bfs(list<Aresta> grafo[], int vertices, int origem){
	bool visitado[vertices];
	list<int> fila_visitacao;
	list<Aresta>::iterator it;
	
	
	for(int i=0; i<vertices; i++)
		visitado[i] = false;
	
	fila_visitacao.push_back(origem);
	visitado[origem] = true;
	
	while( !fila_visitacao.empty()){
		int atual = fila_visitacao.front();
		cout<<atual<<endl;
		// for(int i=0; i<vertices; i++){
		// 	if(grafo[atual][i])
		for(it = grafo[atual].begin(); it != grafo[atual].end(); it++){
			int i = it->destino;//(*it).destino;
			if(!visitado[i]){				
				fila_visitacao.push_back(i);
				visitado[i] = true;
			}
		}
		fila_visitacao.pop_front();
	}
	
	for(int i=0; i<vertices; i++){
		if(!visitado[i])
			return false;
	}
	return true;
	
}



int main(){
	int vertices, arestas, origem, destino;
	
	cin>>vertices>>arestas;
	
	// Grafo n�o ponderado e n�o direcionado
	
	// bool grafo[vertices][vertices];
	list<Aresta> grafo[vertices];
	list<Aresta>::iterator it;
	
	// for(int i=0;i<vertices;i++)
	// 	for(int j=0; j<vertices; j++)
	// 		grafo[i][j] = false;
	
	for(int i=0; i<arestas; i++){
		cin>>origem>>destino;
		grafo[origem].push_back({origem, destino, 0});
		grafo[destino].push_back({destino, origem, 0});
		// grafo[origem][destino] = true;
		// grafo[destino][origem] = true;
	}
	
	for(int i=0;i<vertices;i++){
		// for(int j=0; j<vertices; j++)
		// 	cout<<grafo[i][j]<<" ";
		cout<<i<<": ";
		for(it = grafo[i].begin(); it != grafo[i].end(); it++){
			cout << it->destino << "; ";
			//cout << (*it).destino << "; ";
		}
		cout<<endl;
	}
	
	return 0;
}