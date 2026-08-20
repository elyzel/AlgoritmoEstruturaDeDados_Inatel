/*
Dois jogadores, Alberto e Wanderley, participam de um jogo. Um conjunto com um número par de cartas, cada uma contendo um número inteiro, é disposto sobre uma mesa, uma carta ao lado da outra, formando uma sequência. Alberto começa jogando e pode pegar uma das duas cartas nas extremidades da sequência (a primeira ou a última). Em seguida, Wanderley pode pegar uma das duas cartas nas extremidades da sequência restante, e Alberto pode novamente pegar uma carta da sequência, e assim por diante, até que Wanderley pegue a última carta.

Neste jogo, a pontuação de um jogador é a soma dos números das cartas que ele pegou. Alberto, o primeiro a jogar, busca maximizar sua pontuação. Wanderley, o segundo jogador, quer fazer com que Alberto obtenha a menor pontuação possível. Em suma, ambos querem jogar da melhor forma possível: Alberto quer maximizar seus pontos e Wanderley quer minimizar os pontos de Alberto.

Você deve escrever um programa que, dada a sequência de cartas, determine a maior pontuação que Alberto pode obter.

Entrada
A entrada contém vários casos de teste. Cada caso de teste é descrito em duas linhas. A primeira linha contém um número inteiro par N (2 ≤ N ≤ 10⁴), que indica o número de cartas na mesa. A segunda linha contém N números inteiros, descrevendo a sequência de cartas. Cada um dos N números inteiros cabe em 32 bits.

Saída
Para cada caso de teste, seu programa deve imprimir uma única linha contendo um único número inteiro: a maior pontuação que Alberto pode obter.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    // Processa múltiplos casos de teste até o Fim de Arquivo (EOF)
    while (cin >> N) {
        vector<long long> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }

        // Vetores para otimização de espaço:
        // dp2 guarda os resultados para intervalos de tamanho (tam - 2)
        // dp0 guarda os resultados para intervalos de tamanho tam
        vector<long long> dp2(N, 0);
        vector<long long> dp0(N, 0);

        // Caso Base: Intervalos de tamanho 2 (Alberto e Wanderley pegam 1 carta cada)
        // Alberto sempre escolhe a maior entre as duas cartas adjacentes
        for (int i = 0; i < N - 1; i++) {
            dp2[i] = max(A[i], A[i + 1]);
        }

        // Processa intervalos de tamanhos pares: 4, 6, 8, ..., N
        for (int tam = 4; tam <= N; tam += 2) {
            for (int i = 0; i <= N - tam; i++) {
                int j = i + tam - 1;

                // Opção 1: Alberto pega A[i]
                long long op1 = A[i] + min(dp2[i + 2], dp2[i + 1]);

                // Opção 2: Alberto pega A[j]
                long long op2 = A[j] + min(dp2[i + 1], dp2[i]);

                dp0[i] = max(op1, op2);
            }

            // O estado atual vira o estado anterior de 2 passos atrás
            dp2 = dp0;
        }

        // Se N == 2, a resposta já está em dp2[0]
        if (N == 2) {
            cout << dp2[0] << "\n";
        } else {
            cout << dp0[0] << "\n";
        }
    }

    return 0;
}