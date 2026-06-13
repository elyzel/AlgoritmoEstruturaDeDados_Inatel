#include "hashing.h"

int hash1(int k, int m) {

    int h1;

    h1 = k % m;

    if(h1 < 0)
        h1 += m;
    
    return 0;
}

int hash2(int k, int m) {

    int h2;

    h2 = 1 + (k % (m - 1));

    if(h2 < 0)
        h2 += m;
    
    return 0;
}

int dhash(int k, int i, int m)  {

    int resultado;

    resultado = (hash1(k, m) + i * hash2(k, m)) % m;

    return 0;
    
}