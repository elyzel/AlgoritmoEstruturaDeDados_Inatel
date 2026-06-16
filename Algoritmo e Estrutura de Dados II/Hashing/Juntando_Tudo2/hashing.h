#ifndef HASHING_H
#define HASHING_H

struct dado
{
    int k;
    int status;
};

// Função base para hashing
int hash_aux(int k, int m);

// Sondagem quadrática
int hash2(int k, int i, int m, int c1, int c2);

// Função para inserção de elementos usando sondagem linear
int hash_insert(dado t[], int m, int k, int c1, int c2);

// Função para pesquisa usando sondagem linear
int hash_search(dado t[], int m, int k, int c1, int c2);

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, int k, int c1, int c2);

#endif

