/*========================================================================
			Exercício 5 - Fibonacci
========================================================================


Escreva um programa que leia um número e imprima o número de Fibonacci correspondente a esse número lido. Lembre-se de que os primeiros elementos da sequência de Fibonacci são 0 e 1, e cada termo seguinte é a soma dos dois anteriores. Todos os números de Fibonacci calculados neste programa devem caber em um número de 64 bits sem sinal (*unsigned*).

Entrada
A primeira linha da entrada contém um único número inteiro T, indicando o número de casos de teste. Cada caso de teste contém um único número inteiro N (0 ≤ N ≤ 60), correspondente ao N-ésimo termo da sequência de Fibonacci.

Saída
Para cada caso de teste na entrada, imprima a mensagem "Fib(N) = X", onde X é o N-ésimo termo da sequência de Fibonacci.
*/
#include <iostream>

using namespace std;

int main() {
    // Vetor para guardar os termos de 0 a 60, pois o int geraria número negativos ou incorretos e "fib[61]" é a criação de um vetor para armazenar 61 posições.
    unsigned long long fib[61];

    // Termos base da sequência de Fibonacci
    fib[0] = 0;
    fib[1] = 1;

    // Preenche o vetor até N = 60
    // "int i = 2" significa que o laço inicia "i" com valor de 2
    // a fórmula da matemática de Fibonacci é fib[i] = fib[i - 1] + fib[i -2]

    for (int i = 2; i <= 60; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int T; // Quantidade de casos de teste
    if (cin >> T) {

	// O laço funcionará somente T vezes.
        while (T--) {
            int N;
            cin >> N;
            // Exibe a resposta formatada como o Beecrowd exige
            cout << "Fib(" << N << ") = " << fib[N] << endl;
        }
    }

    return 0;
}