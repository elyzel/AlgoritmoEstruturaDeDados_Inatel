#include<iostream>
#include "hashing.h"
#include<string>

using namespace std;

int main()  {
    int k; //< -- Chave
    string info; //< -- String
    int m; //< -- Tamanho do Array
    int esc; //< -- variavel de escolha
    dado vetor[500]; //< -- Vetor
    
    cin >> m;
    
    //Percorre por todo o vetor para definir os valores vazios
    for(int i = 0; i < m; i++)  {
        vetor[i].info = ""; //< -- Declara no info como vazio
        vetor[i].k = -1;
        vetor[i].status = 0;
    }
    
    while(cin >> esc) {
        switch(esc) {
            case 1:
            cin >> info;
            hash_insert(vetor, m, info);
            break;
            
            case 2:
            cin >> info;
            k = hash_search(vetor, m, info); // k recebe o valor do hash da string e posiciona no vetor
            
                if (k != -1)
                    cout << info << " encontrado na posicao " << k << endl; //Aqui mostra em qual posição está
                else
                    cout << info << " nao encontrado" << endl; //Caso não esteja, mostra que não foi encontrado
            
            break;
            
            case 3:
            cin >> info;
            hash_remove(vetor, m, info);
            break;
            
            case 4:
            for(int i = 0; i < m; i++)  {
                if(vetor[i].status == 1) {
                    cout << vetor[i].info << endl;
                }   else    {
                    cout << "vazio" << endl;
                }    
            }
            
            break;
            
            case 5:
            return 0;
        }
    }
    
}