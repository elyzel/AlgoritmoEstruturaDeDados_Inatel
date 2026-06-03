#include <iostream>
#include "hashing.h"
using namespace std;

int main()  {
    int k;  //< -- Chave
    int m;  //< -- Tamanho da tabela
    int c1; //< -- Primeira Constante
    int c2; //< -- Segunda Constante

    cin >> k >> m >> c1 >> c2;

    for(int i = 0; i < m; i++)  {
       
        cout << hash2(k, i, m, c1, c2);
        
        cout << " ";
    }

    return 0;
}