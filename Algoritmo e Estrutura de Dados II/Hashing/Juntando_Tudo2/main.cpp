#include<iostream>
#include "hashing.h"
using namespace std;

int main()  {
    int k;
    int c1;
    int c2;
    int m;
    dado vetor[500];
    int esc;
    
    cin >> m >> c1 >> c2; //Como se trata de exercício de Sondagem Quadrática, precisa-se dos três valores: k, c1 e c2
    
    //< -- Percorre pelo vetor atribuindo os valores iniciais
    for(int i = 0; i < m; i++)  {
        vetor[i].k = -1; //< -- Chave
        vetor[i].status = 0; //0 - vazio, 1 - ocupado e 2 - removido
    }
    
    while(cin >> esc)   {
        switch(esc) {
            case 1:
            cin >> k;
            hash_insert(vetor, m, k, c1, c2);
            break;
            
            case 2:
            cin >> k;
            cout << hash_search(vetor, m, k, c1, c2) << endl;
            break;
            
            case 3:
            cin >> k;
            hash_remove(vetor, m, k, c1, c2);
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