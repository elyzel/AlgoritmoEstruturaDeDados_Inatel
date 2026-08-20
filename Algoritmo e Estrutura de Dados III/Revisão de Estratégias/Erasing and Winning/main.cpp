/*
Juliano é fã do programa de TV "Apagar e Ganhar", no qual os participantes são escolhidos por sorteio e recebem dinheiro por participarem.

No programa, o apresentador escreve um número de N dígitos em um quadro. Em seguida, o participante deve apagar exatamente D dígitos do número no quadro; o número formado pelos dígitos restantes corresponde ao valor do prêmio em dinheiro para o participante.

Juliano foi finalmente selecionado para participar do programa e pediu a você que escrevesse um programa que, dado o número que o apresentador escreveu no quadro e a quantidade de dígitos que Juliano deve apagar, determine o maior valor de prêmio que ele pode ganhar.

Entrada
A entrada contém vários casos de teste. A primeira linha de um caso de teste contém dois números inteiros N e D (1 ≤ D < N ≤ 10⁵), indicando, respectivamente, a quantidade de dígitos do número que o apresentador escreveu no quadro e a quantidade de dígitos que devem ser apagados. A linha seguinte contém o número que o apresentador escreveu; o número não começa com zero.

O fim da entrada é indicado por uma linha contendo apenas dois zeros, separados por um espaço.

Saída
Para cada caso de teste na entrada, seu programa deve produzir uma única linha na saída, contendo o maior prêmio que Juliano pode ganhar.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, D;

    // O laço encerra quando N == 0 e D == 0
    while (cin >> N >> D && !(N == 0 && D == 0)) {
        string numero;
        cin >> numero;

        string resultado = "";
        int apagados = 0;

        for (int i = 0; i < N; i++) {
            char digitoAtual = numero[i];

            // Enquanto houver caracteres no resultado, ainda pudermos apagar dígitos,
            // e o último dígito colocado for menor que o atual: removemos o último!
            while (!resultado.empty() && apagados < D && resultado.back() < digitoAtual) {
                resultado.pop_back(); // Remove o topo da pilha
                apagados++;
            }

            // Adiciona o dígito atual à nossa resposta
            resultado.push_back(digitoAtual);
        }

        // O tamanho final desejado é exatamente (N - D) dígitos.
        // Se ainda não apagamos tudo o que precisava (ex: números já decrescentes "9876"),
        // cortamos os dígitos excedentes do final.
        int tamanhoFinal = N - D;
        resultado = resultado.substr(0, tamanhoFinal);

        cout << resultado << "\n";
    }

    return 0;
}