#include<iostream>
#include<list> //< -- Biblioteca para listas ligadas

using namespace std;

int contar(list<int> lista) {
    list<int> ::iterator p; //<-- Contador especial para listas
    int total = 0;
    
    //<-- Percorre a lista contabilizando o total de vetores
    for(p = lista.begin(); p != lista.end(); p++)    { //<-- Laço de Repetição começa pelo ínicio e termina no fim da lista
        total = total + 1;
    }
    
    return total;
    
}

int main()  {
    int x; //<-- Recebe cada valor digitado
    list<int> lista; //<-- lista 
    int resultado;
    
    while(cin >> x && x != 0)   {
        lista.push_back(x); // <-- Lista que receberá os valores de x
    }
    
    resultado = contar(lista); //< -- Aplicar a função de contabilização
    
    cout << resultado << " ";
    
    return 0;
    
}