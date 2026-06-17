#ifndef HASHING_H
#define HASHING_H

struct dado
{
    int k;
    int status;
};

// Função auxiliar 1 para double hashing
int h1(int k, int m);

// Função auxiliar 2 para double hashing
int h2(int k, int m);

// Songagem double hashing
int dhash(int k, int i, int m);

// Função para inserção de elementos usando sondagem linear
int hash_insert(dado t[], int m, int k);

// Função para pesquisa usando sondagem linear
int hash_search(dado t[], int m, int k);

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, int k);

#endif
