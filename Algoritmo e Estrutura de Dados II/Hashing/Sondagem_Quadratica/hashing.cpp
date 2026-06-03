#include "hashing.h"

//<-- Hashing Auxiliar-->
int hash_aux(int k, int m)  {
    int h = k % m;
    
    if(h < 0)   {
        h += m;
    }
    
    return h;
}

//<-- Sondagem Quadrática -->
int hash2(int k, int i, int m, int c1, int c2)  {
    int resultado;
    int j;
    
    j = hash_aux(k, m);
    
    resultado = j + c1*i + c2*(i*i);

    int h = resultado % m;
    
    return h;
}