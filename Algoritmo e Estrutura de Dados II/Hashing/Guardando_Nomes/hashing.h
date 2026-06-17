#ifndef HASHING_H
#define HASHING_H
#include <string> //< -- Biblioteca para utilizar o string

using namespace std;

struct dado
{
    string info; // informacao
    int k; // chave
    int status; // 0: vazio, 1:ocupado, 2:removido
};

// Função auxiliar 1 para double hashing
int h1(string info, int m);

// Função auxiliar 2 para double hashing
int h2(string info, int m);

// Songagem double hashing
int dhash(string info, int i, int m);

// Função para inserção de elementos usando sondagem linear
int hash_insert(dado t[], int m, string info);

// Função para pesquisa usando sondagem linear
int hash_search(dado t[], int m, string info);

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, string info);

#endif

