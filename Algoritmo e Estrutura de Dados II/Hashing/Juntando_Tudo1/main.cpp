#include<iostream>
#include "hashing.h"
using namespace std;

int main()  {
    int k; //< -- Chave
    int m; //< -- Tamanho do Array
    dado vetor[500]; //< -- Vetor
    int esc; //< -- Variável de Escolha
    
    cin >> m; 
    
    // <-- Percorre pelo vetor inserindo os valores iniciais da tabela
    for(int i = 0; i < m; i++)  {
        vetor[i].k = -1;
        vetor[i].status = 0;
    }
    
    //< -- Estrutura Condicional utilizando o Switch Case
    while(cin >> esc)   {
    
        switch(esc) {
            case 1:
            cin >> k;
            hash_insert(vetor, m, k);
            break; //< -- Quebra o laço de repetição
        
            case 2:
            cin >> k;
            cout << hash_search(vetor, m, k) << endl;
            break;
        
            case 3:
            cin >> k;
            hash_remove(vetor, m, k);
            break;
            
            case 4:
            for(int i = 0; i < m; i++)  {
            cout << vetor[i].k << " ";
            }
            cout << endl;
            break;
        
            case 5:
            return 0;
        }
    }
}