/*===================================================================================
			Exercício 7 - Square Matrix
===================================================================================

Escreva um programa que leia um número inteiro N (0 ≤ N ≤ 100) correspondente à ordem de um vetor bidimensional de inteiros e construa o vetor de acordo com o exemplo acima.

Entrada
A entrada consiste em vários números inteiros, um por linha, correspondentes às ordens dos vetores a serem construídos. O fim da entrada é indicado por zero (0).

Saída
Para cada número inteiro de entrada, imprima o vetor correspondente de acordo com o exemplo. (Os valores dos vetores devem ser formatados em um campo de tamanho 3, justificados à direita e separados por um espaço. Não deve haver espaço após o último caractere de cada linha do vetor. Uma linha em branco deve ser impressa após cada vetor.)
*/

#include <iostream>
#include <iomanip>   // Necessário para usar setw()
#include <algorithm> // Necessário para usar min()

using namespace std;

int main() {
    int N;

    // O laço continua lendo valores até N ser igual a 0
    while (cin >> N && N != 0) {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // Descobre a menor distância até as 4 bordas
                int dist_topo = i + 1;
                int dist_baixo = N - i;
                int dist_esq = j + 1;
                int dist_dir = N - j;

                int valor = min({dist_topo, dist_baixo, dist_esq, dist_dir});

                // Formatação: o 1º elemento da linha não tem espaço antes dele
                if (j == 0) {
                    cout << setw(3) << valor;
                } else {
                    cout << " " << setw(3) << valor;
                }
            }
            cout << endl; // Quebra de linha ao fim de cada linha da matriz
        }
        cout << endl; // Linha em branco obrigatória após cada matriz
    }

    return 0;
}