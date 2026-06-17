#include "hashing.h"
#include <string> //< -- Biblioteca para utilizar o string

using namespace std; //< -- Utilizar sempre que utilizar string

// Função auxiliar 1 para double hashing
int h1(string info, int m)
{
    int soma = 0;

    // # Percorre cada caractere da string somando seus códigos ASCII
    // < -- info.lenght significa final do vetor -- >
    for (int i = 0; i < info.length(); i++) {
        soma += info[i]; // < -- Soma da string de acordo com o ASCII
    }

    int h = soma % m;
    if (h < 0)
        h += m;
    return h;  
}

// Função auxiliar 2 para double hashing
int h2(string info, int m)
{
    int soma = 0;
    
    for (int i = 0; i < info.length(); i++) {
        soma += info[i];
    }
    
    int h = 1 + (soma % (m-1));
    if (h < 0)
        h += m;
    return h;    
}

// Songagem double hashing
int dhash(string info, int i, int m)
{
    return (h1(info, m) + i * h2(info, m)) % m;
}

// Função para inserção de elementos usando Double Hashing
int hash_insert(dado t[], int m, string info)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = dhash(info, i, m);
        if (t[j].status != 1)
        {
            t[j].info = info; //< -- Verificação da string para conferir igualdade
            t[j].k = h1(info, m); //< -- Hash da String
            t[j].status = 1;
            return j;
        }
        else
            i++;
    } while (i != m);
    return -1; // tabela cheia
}

// Função para pesquisa usando Double Hashing
int hash_search(dado t[], int m, string info)
{
    int i;
    int j;
    
    i = 0;
    do
    {
        j = dhash(info, i, m);
        if (t[j].info == info) //< -- Mudança para se a string for igual, retornará seu valor
            return j;
        i++;    
    } while (t[j].status != 0 && i < m);
    return -1;
}

// Função para remoção de elementos em tabelas hash
int hash_remove(dado t[], int m, string info)
{
    int j;
    
    j = hash_search(t, m ,info);
    if (j != -1)
    {
        t[j].status = 2;
        t[j].k = -1;
        return 0;
    }
    else
        return -1;
}


