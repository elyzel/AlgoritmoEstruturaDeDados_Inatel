#include <iostream>
#include <list>

using namespace std;

// Função que recebe a lista por valor e retorna a soma dos nós
int soma(list<int> lista) {
    int total = 0; // Variável para acumular a soma dos valores
    list<int>::iterator it; // Variável iteradora para percorrer cada nó da lista

    // Laço de repetição para percorrer do início ao fim da lista
    for(it = lista.begin(); it != lista.end(); it++) {
        total = total + *it;
    }

    return total;
}

int main() {
    int valor_lido; // Variável para armazenar cada número digitado pelo usuário
    list<int> lista_encadeada; // Variável que armazena os nós inseridos
    int soma_final; // Variável para guardar o resultado retornado pela função

    // Inserção de dados até encontrar a condição de parada (zero)
    while(cin >> valor_lido && valor_lido != 0) {
        lista_encadeada.push_back(valor_lido); //o push-back insere um novo elemento no final  da sua estrutura
        /*Exemplo: Inserido -> 4 logo [0,1,2,3,4]
                                               ^ 
                                               |
                                               | -->  Última posição*/ 
    }

    // Processamento da soma
    soma_final = soma(lista_encadeada);

    // Saída com o valor final
    cout << soma_final << endl;

    return 0; // Finalização obrigatória da execução
}