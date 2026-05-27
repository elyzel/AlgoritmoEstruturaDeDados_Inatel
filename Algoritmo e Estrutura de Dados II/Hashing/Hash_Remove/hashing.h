#ifndef HASHING_H
#define HASHING_H

struct dado
{
    int k; //chave
    int status; //0 - vazio, 1 - ocupado, 2 - removido
};

//<-- Hashing Auxiliar -->
int hash_aux(int k, int m);
//<-- Sondagem Linear -->
int hash1(int k, int i, int m);
//<-- Hashing de Inserção -->
int hash_insert(dado T[], int m, int k);
//<-- Hashing de Buscar -->
int hash_search(dado T[], int m, int k);
//<-- Hashing de Remoçãor -->
int hash_remove(dado T[], int m, int k);


#endif