#include "hashing.h"

// Função base para hashing
int hash_aux(int k, int m)
{
    int h = k % m;
    if (h < 0)
        h += m;
    return h;    
}

// Sondagem quadrática
int hash2(int k, int i, int m, int c1, int c2)
{
    return (hash_aux(k,m) + c1 * i + c2 * i * i) % m;
}

// Função para inserção de elementos usando sondagem quadrática
int hash_insert(dado t[], int m, int k, int c1, int c2)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = hash2(k, i, m, c1, c2);
        if (t[j].status != 1)
        {
            t[j].k = k;
            t[j].status = 1;
            return j;
        }
        else
            i++;
    } while (i != m);
    return -1; // tabela cheia
}

// Função para pesquisa usando sondagem quadrática
int hash_search(dado t[], int m, int k, int c1, int c2)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = hash2(k, i, m, c1, c2);
        if (t[j].k == k && t[j].status == 1)
            return j;
        i++;    
    } while (i < m);
    return -1;
}

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, int k, int c1, int c2)
{
    int j;
    
    j = hash_search(t, m ,k, c1, c2);
    if (j != -1)
    {
        t[j].status = 2;
        t[j].k = -1;
        return 0;
    }
    else
        return -1;
}


