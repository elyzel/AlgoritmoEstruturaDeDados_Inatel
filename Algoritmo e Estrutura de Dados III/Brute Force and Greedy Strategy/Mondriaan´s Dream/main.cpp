/*
Quadrados e retângulos fascinavam o famoso pintor holandês Piet Mondriaan. Certa noite, após produzir os desenhos de sua "série do banheiro" (na qual teve de usar papel higiênico para desenhar, pois todo o seu papel comum já estava preenchido com quadrados e retângulos), ele sonhou em preencher um grande retângulo com retângulos menores de largura 2 e altura 1, de diversas maneiras.

Como especialista no assunto, percebeu imediatamente que precisaria de um computador para calcular o número de formas de preencher o grande retângulo — cujas dimensões também eram números inteiros. Ajude-o para que seu sonho não se transforme em pesadelo!

Entrada
O arquivo de entrada contém vários casos de teste. Cada caso de teste consiste em dois números inteiros: a altura H (1 ≤ H ≤ 11) e a largura W (1 ≤ W ≤ 11) do grande retângulo. A entrada termina quando H = W = 0.

Saída
Para cada caso de teste, imprima o número de maneiras diferentes de preencher o retângulo dado com retângulos menores de tamanho 2 por 1. Considere que o grande retângulo tem uma orientação fixa; ou seja, conte as pavimentações simétricas separadamente (como casos distintos).
*/

#include <iostream>
#include <vector>
#include <algorithm> // Necessário para swap()

using namespace std;

int H, W;

// Função recursiva (DFS) para encontrar todas as maneiras válidas de preencher a linha
void gerarTransicoes(int c, int mascaraAtual, int proximaMascara, vector<long long>& proximoDp, long long qtdManeiras) {
    // Se cobriu todas as colunas da linha atual com sucesso
    if (c == W) {
        proximoDp[proximaMascara] += qtdManeiras;
        return;
    }

    // Caso 1: A célula 'c' já está ocupada por um dominó da linha anterior
    if ((mascaraAtual & (1 << c)) != 0) {
        gerarTransicoes(c + 1, mascaraAtual, proximaMascara, proximoDp, qtdManeiras);
    } else {
        // Caso 2A: Colocar dominó VERTICAL (ocupa 'c' e projeta bit 1 na próxima linha)
        gerarTransicoes(c + 1, mascaraAtual, proximaMascara | (1 << c), proximoDp, qtdManeiras);

        // Caso 2B: Colocar dominó HORIZONTAL (ocupa 'c' e 'c+1' na linha atual)
        if (c + 1 < W && ((mascaraAtual & (1 << (c + 1))) == 0)) {
            gerarTransicoes(c + 2, mascaraAtual, proximaMascara, proximoDp, qtdManeiras);
        }
    }
}

int main() {
    // Lê H e W até que ambos sejam 0
    while (cin >> H >> W && !(H == 0 && W == 0)) {
        
        // Se a área for ímpar, impossível cobrir com dominós 2x1
        if ((H * W) % 2 != 0) {
            cout << 0 << endl;
            continue;
        }

        // Garante que W seja a menor dimensão para minimizar a máscara de bits
        if (H < W) {
            swap(H, W);
        }

        int totalMascaras = (1 << W); // 2^W estados possíveis
        vector<long long> dpAtual(totalMascaras, 0);

        // Estado inicial: 1 maneira de começar com a linha 0 vazia (máscara 0)
        dpAtual[0] = 1;

        // Processa linha por linha de 0 até H-1
        for (int r = 0; r < H; r++) {
            vector<long long> proximoDp(totalMascaras, 0);

            for (int mask = 0; mask < totalMascaras; mask++) {
                if (dpAtual[mask] > 0) {
                    gerarTransicoes(0, mask, 0, proximoDp, dpAtual[mask]);
                }
            }

            dpAtual = proximoDp;
        }

        // A resposta final é a quantidade de maneiras de terminar todas as H linhas
        // sem nenhum dominó projetando para fora (máscara final 0)
        cout << dpAtual[0] << endl;
    }

    return 0;
}
