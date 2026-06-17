#include<iostream>
#include "hashing.h"
using namespace std;

int main()  {
    int k; //< -- Chave
    int c1; //< -- Constante 1
    int c2; //< -- Constante 2
    int m; //< -- Tamanho da tabela
    int x; //< -- Variável de busca
    int pos; //< -- Posição que irá remover
    dado vetor[500]; //< -- Vetor
    
    cin >> m >> c1 >> c2;
    
    //Percorre pelo vetor definindo os valores vazios
    for(int i = 0; i < m; i++)  {
        vetor[i].k = -1;
        vetor[i].status = 0;
    }
    
    //Recebimento de chaves e condição de parada
    while(cin >> k && k != 0)   {
        hash_insert(vetor, m, k, c1, c2);
    }
    
    //< -- Variavel de busca -->
    cin >> x; 
    
    //< -- Loop para remoção dos números
    while (hash_remove(vetor, m, x, c1, c2) != -1) {
}
    
    for(int i = 0; i < m; i++)  {
        cout << vetor[i].k << " ";
    }
    
    return 0;
}