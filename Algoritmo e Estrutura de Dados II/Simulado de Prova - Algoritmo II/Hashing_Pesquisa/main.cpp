#include<iostream>
#include "hashing.h"

using namespace std;

int main()  {
    int k; //< -- Chave
    int m; //< -- Tamanho do Vetor
    dado vetor[500]; //< -- Vetor
    int x; //Variável de Busca

    cin >> m;

    //Percorre por todo vetor definindo os valores vazios
    for(int i = 0; i < m; i++)  {
        vetor[i].k = -1;
        vetor[i].status = 0;
    }

    //Recebimento dos valores e Laço de Repetição
    while(cin >> k && k != 0)   {
        hash_insert(vetor, m, k);
    }
    
    int resultado = hash_search(vetor, m, x); //< -- Localização do Hash armazenado na variavel "resultado"

    if(resultado != -1) {
        cout << "Chave " << x << " encontrada na posicao " << resultado;
    }
    else{
        cout << "Chave " << x << " não encontrada";
    }

    return 0;

}