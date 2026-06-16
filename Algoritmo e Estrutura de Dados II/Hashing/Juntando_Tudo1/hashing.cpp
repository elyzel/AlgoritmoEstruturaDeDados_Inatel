#include "hashing.h"

// Função base para hashing
int hash_aux(int k, int m)
{
    int h = k % m;
    if (h < 0)
        h += m;
    return h;    
}

// Sondagem linear
int hash1(int k, int i, int m)
{
    return (hash_aux(k,m) + i) % m;
}


// Função para inserção de elementos usando sondagem linear
int hash_insert(dado t[], int m, int k)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = hash1(k, i, m);
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
        j = hash1(k, i, m);
        if (t[j].k == k && t[j].status == 1)
            return j;
        i++;    
        
        if(t[j].status == 0)    {
            return -1;
        }
        
    } while (i < m);
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


