#include "hashing.h"

//<-- Hashing Auxiliar-->
int hash_aux(int k, int m)  {
    //Operação para descobrir a posição do hash
    int h = k % m;
    
    //Condicao de parada
    if(h < 0)   {
        h += m;
    }
    
    //Retorno do valor do h
    return h;
}

//<-- Sondagem Linear-->
int hash1(int k, int i, int m)  {

    int resultado1;
    
    resultado1 = hash_aux(k, m) + i;
    
    resultado1 = resultado1 % m;
    
    return resultado1;
}

//<-- Hashing de Inserção -->
int hash_insert(dado T[], int m, int k) {
int i = 0; 
    int j;     
    
    do  {
        // Função
        j = hash1(k, i, m); 
        
        // Condição de parada (0 vazio, 1 ocupado)
        if(T[j].status != 1)   {
            T[j].k = k;
            T[j].status = 1;
            return j;
        }
        else    {
            i = i + 1;
        }
    }   while(i != m);
    
    return -1;
}

//<-- Hashing de Busca -->
int hash_search(dado T[], int m, int k){
    int i = 0;
    int j;
    
    do{
        
        j = hash1(k, i, m);
        
        if(T[j].k == k)
            return j;
        
        i += 1;
        
    }   while(T[j].status != 0 && i < m);
    
    return -1;
}

//<-- Hashing de Remoção
int hash_remove(dado T[], int m, int k) {
    
    int j = hash_search(T, m, k);
    
    if(j != -1) {
        T[j].status = 2;
        T[j].k = -1;
        
        return 0;
    }
    else    {    
        return -1;
    }
}