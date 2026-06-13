#include<iostream>
#include "hashing.h"

using namespace std;

int main()  {
    int k; //Chave
    int m; //Tamanho do Array
    int i; //Contador

    cin >> k >> m;

    for(int i = 0; i < m; i++)  {

        cout << dhash(k, i, m);

        cout << " ";
    }

}