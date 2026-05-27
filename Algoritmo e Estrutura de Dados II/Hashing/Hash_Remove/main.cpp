#include<iostream>
#include "hashing.h"

using namespace std;

int main()  {
    //Variaveis
    int m; //< -- tamanho da tabela
    int k; //< --chave
    int n; //< -- chave a ser removida
    dado vetor[500];  //<-- Array
    
    cin >> m;
    
    // < -- Percorre o array para definir o array do status como 0 (vazio) ou 1 (ocupado) -- >
    for(int i = 0; i < m; i++)  {
        vetor[i].k = -1;    // < -- Lembre-se, o -1 na chave representa que está vazio e aberto para ser substituído.
        vetor[i].status = 0;
    }
    
    //<-- Inserção dos elementos até o usuário digitar 0
    while(cin >> k && k != 0)   {
        hash_insert(vetor, m, k);
    }
    
    cin >> n;
    
    int resultado = hash_remove(vetor, m, n); // <-- Aplicação do Hash de Remoção

    
    //< -- Exibição da tabela após a remoção
    for(int i = 0; i < m; i++)  {
        cout << vetor[i].k << " ";
    }
    
    return 0;
}