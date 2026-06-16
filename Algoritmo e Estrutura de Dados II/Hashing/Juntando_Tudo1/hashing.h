#ifndef HASHING_H
#define HASHING_H

struct dado
{
    int k; //< -- Chave
    int status; //< -- 0 - vazio, 1 - ocupado, 2 - removido
};

// Função base para hashing
int hash_aux(int k, int m);

// Sondagem linear
int hash1(int k, int i, int m);

// Função para inserção de elementos usando sondagem linear
int hash_insert(dado t[], int m, int k);

// Função para pesquisa usando sondagem linear
int hash_search(dado t[], int m, int k);

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, int k);

#endif

