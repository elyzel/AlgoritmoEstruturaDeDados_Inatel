/*========================================================================
			Exercício 3 - Even Quare
========================================================================

Leia um número inteiro N. Imprima o quadrado de cada um dos valores pares de 1 a N, incluindo N, se for o caso.

Entrada
A entrada contém um número inteiro N (5 < N < 2000).

Saída
Imprima o quadrado de cada um dos valores pares de 1 a N, conforme o exemplo fornecido.

Cuidado! Algumas linguagens imprimem automaticamente 1e+006 em vez de 1000000. Por favor, configure seu programa para imprimir no formato correto, definindo a precisão da saída.
*/

#include <iostream>

using namespace std;

int main() {
    int N;

    // Entrada do valor N
    if (cin >> N) {
        // Laço de 2 até N de 2 em 2
        for (int i = 2; i <= N; i += 2) {
            // Formatação exata esperada pelo Beecrowd
            cout << i << "^2 = " << i * i << endl;
        }
    }

    return 0;
}