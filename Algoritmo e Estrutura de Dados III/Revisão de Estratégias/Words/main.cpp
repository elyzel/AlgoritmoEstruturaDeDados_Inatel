/*
Dados dois conjuntos de palavras formadas por zeros e uns, você deve escrever um programa para determinar se existem concatenações de palavras de cada um dos conjuntos que geram a mesma palavra. Por exemplo, se um conjunto A contém as palavras 010 e 11 e outro conjunto B contém as palavras 0 e 101, então a palavra 01011010 pode ser formada tanto pela concatenação de palavras de A quanto pela concatenação de palavras de B.


010 · 11 · 010 = 01011010 = 0 · 101 · 101 · 0

Entrada
A entrada contém vários casos de teste. A primeira linha de um caso de teste contém dois números inteiros, N1 (1 ≤ N1) e N2 (N2 ≤ 20), que indicam, respectivamente, o número de palavras no primeiro conjunto e o número de palavras no segundo conjunto. Cada uma das N1 linhas seguintes contém uma palavra do primeiro conjunto. Cada uma das N2 linhas seguintes contém uma palavra do segundo conjunto.

Nota: Cada palavra tem pelo menos um e no máximo 40 caracteres, todos zeros e uns.

Saída
Para cada caso de teste, seu programa deve imprimir uma única linha contendo um único caractere. Se for possível encontrar uma concatenação de uma ou mais palavras do primeiro conjunto que seja igual a uma concatenação de uma ou mais palavras do segundo conjunto, então o caractere deve ser 'S'; caso contrário, o caractere deve ser 'N'.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estrutura para representar o estado da busca
struct Estado {
    string sobra;
    int dono; // 1 se a sobra pertence a A, 2 se a sobra pertence a B
};

// Função para verificar se um estado já foi explorado (evita loops infinitos)
bool jaVisitado(const vector<Estado>& visitados, const string& sobra, int dono) {
    for (size_t i = 0; i < visitados.size(); i++) {
        if (visitados[i].dono == dono && visitados[i].sobra == sobra) {
            return true;
        }
    }
    return false;
}

int main() {
    int N1, N2;

    // Processa os casos de teste até o Fim de Arquivo (EOF)
    while (cin >> N1 >> N2) {
        vector<string> A(N1);
        for (int i = 0; i < N1; i++) {
            cin >> A[i];
        }

        vector<string> B(N2);
        for (int i = 0; i < N2; i++) {
            cin >> B[i];
        }

        // Fila para a Busca em Largura e vetor de estados visitados
        vector<Estado> fila;
        vector<Estado> visitados;

        bool possivel = false;

        // 1. INICIALIZAÇÃO: Compara todas as palavras iniciais de A com B
        for (int i = 0; i < N1; i++) {
            for (int j = 0; j < N2; j++) {
                string u = A[i];
                string v = B[j];

                // Caso especial: duas palavras já são idênticas logo no início
                if (u == v) {
                    possivel = true;
                    break;
                }

                // Se u começa com v (A é mais longa que B)
                if (u.length() > v.length() && u.substr(0, v.length()) == v) {
                    string sobra = u.substr(v.length());
                    if (!jaVisitado(visitados, sobra, 1)) {
                        Estado est = {sobra, 1};
                        fila.push_back(est);
                        visitados.push_back(est);
                    }
                }
                // Se v começa com u (B é mais longa que A)
                else if (v.length() > u.length() && v.substr(0, u.length()) == u) {
                    string sobra = v.substr(u.length());
                    if (!jaVisitado(visitados, sobra, 2)) {
                        Estado est = {sobra, 2};
                        fila.push_back(est);
                        visitados.push_back(est);
                    }
                }
            }
            if (possivel) break;
        }

        // 2. BUSCA EM LARGURA (BFS)
        int inicioFila = 0;

        while (inicioFila < (int)fila.size() && !possivel) {
            Estado atual = fila[inicioFila];
            inicioFila++; // Avança na fila sem precisar de bibliotecas extras

            string sobra = atual.sobra;
            int dono = atual.dono;

            if (dono == 1) { // A está na frente, tentamos encaixar peças de B
                for (int j = 0; j < N2; j++) {
                    string v = B[j];

                    // Encaixe perfeito!
                    if (sobra == v) {
                        possivel = true;
                        break;
                    }

                    // Sobra de A é maior que a palavra de B
                    if (sobra.length() > v.length() && sobra.substr(0, v.length()) == v) {
                        string nova_sobra = sobra.substr(v.length());
                        if (!jaVisitado(visitados, nova_sobra, 1)) {
                            Estado prox = {nova_sobra, 1};
                            fila.push_back(prox);
                            visitados.push_back(prox);
                        }
                    }
                    // Palavra de B é maior que a sobra de A (B passa à frente)
                    else if (v.length() > sobra.length() && v.substr(0, sobra.length()) == sobra) {
                        string nova_sobra = v.substr(sobra.length());
                        if (!jaVisitado(visitados, nova_sobra, 2)) {
                            Estado prox = {nova_sobra, 2};
                            fila.push_back(prox);
                            visitados.push_back(prox);
                        }
                    }
                }
            } else { // B está na frente, tentamos encaixar peças de A
                for (int i = 0; i < N1; i++) {
                    string u = A[i];

                    // Encaixe perfeito!
                    if (sobra == u) {
                        possivel = true;
                        break;
                    }

                    // Sobra de B é maior que a palavra de A
                    if (sobra.length() > u.length() && sobra.substr(0, u.length()) == u) {
                        string nova_sobra = sobra.substr(u.length());
                        if (!jaVisitado(visitados, nova_sobra, 2)) {
                            Estado prox = {nova_sobra, 2};
                            fila.push_back(prox);
                            visitados.push_back(prox);
                        }
                    }
                    // Palavra de A é maior que a sobra de B (A passa à frente)
                    else if (u.length() > sobra.length() && u.substr(0, sobra.length()) == sobra) {
                        string nova_sobra = u.substr(sobra.length());
                        if (!jaVisitado(visitados, nova_sobra, 1)) {
                            Estado prox = {nova_sobra, 1};
                            fila.push_back(prox);
                            visitados.push_back(prox);
                        }
                    }
                }
            }
        }

        if (possivel) {
            cout << "S" << endl;
        } else {
            cout << "N" << endl;
        }
    }

    return 0;
}
