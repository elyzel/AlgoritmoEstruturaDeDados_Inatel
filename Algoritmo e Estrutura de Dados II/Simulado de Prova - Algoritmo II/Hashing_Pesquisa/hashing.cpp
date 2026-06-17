#include "hashing.h"

// Função auxiliar 1 para double hashing
int h1(int k, int m)
{
    int h = k % m;
    if (h < 0)
        h += m;
    return h;    
}

// Função auxiliar 2 para double hashing
int h2(int k, int m)
{
    int h = 1 + (k % (m-1));
    if (h < 0)
        h += m;
    return h;    
}

// Songagem double hashing
int dhash(int k, int i, int m)
{
    return (h1(k, m) + i * h2(k, m)) % m;
}

// Função para inserção de elementos usando sondagem linear
int hash_insert(dado t[], int m, int k)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = dhash(k, i, m);
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

// Função para pesquisa usando sondagem linear
int hash_search(dado t[], int m, int k)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = dhash(k, i, m);
        if (t[j].k == k)
            return j;
        i++;    
    } while (t[j].status != 0 && i < m);
    return -1;
}

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, int k)
{
    int j;
    
    j = hash_search(t, m ,k);
    if (j != -1)
    {
        t[j].status = 2;
        t[j].k = -1;
        return 0;
    }
    else
        return -1;
}

