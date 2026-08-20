/*
Andrea, Carlos e Marcelo são amigos próximos e passam os fins de semana à beira da piscina. Enquanto Andrea toma sol, os dois amigos jogam "Bubbles". Andrea, uma cientista da computação muito inteligente, já lhes disse que não entende por que eles passam tanto tempo jogando um jogo tão simples.

Usando um notebook, Carlos e Marcelo geram um número inteiro aleatório N e uma sequência, também aleatória, que é uma permutação de 1, 2, ..., N.

O jogo então começa. Os jogadores jogam alternadamente e, a cada turno, um jogador faz uma jogada. Marcelo é sempre o primeiro a jogar. Uma jogada consiste em escolher um par de elementos consecutivos que estejam fora de ordem na sequência e trocar esses dois elementos de lugar. Por exemplo, dada a sequência 1, 5, 3, 4, 2, um jogador pode trocar 3 e 5 ou 4 e 2, mas não pode trocar 3 e 4 nem 5 e 2. Continuando com o exemplo, se o jogador decidir trocar 5 e 3, a nova sequência será 1, 3, 5, 4, 2.

Mais cedo ou mais tarde, a sequência estará ordenada. O jogador que não conseguir fazer uma jogada perde. Andrea, com desdém, sempre diz que seria mais simples jogar "Ímpar ou Par", com o mesmo resultado. Sua missão, caso decida aceitá-la, é determinar quem vence o jogo, dada a permutação inicial P.

Entrada
A entrada contém vários casos de teste. Cada caso de teste é composto por uma única linha, na qual todos os números inteiros são separados por um espaço. Cada linha contém um número inteiro N (2 ≤ N ≤ 10⁵), seguido pela sequência inicial P = (X1, X2, ..., XN) de N números inteiros distintos, com 1 ≤ Xi ≤ N para 1 ≤ i ≤ N.

O fim da entrada é indicado por uma linha contendo apenas um zero.

Saída
Para cada caso de teste na entrada, seu programa deve imprimir uma única linha contendo o nome do vencedor: Carlos ou Marcelo.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Variável acumuladora global para a contagem de inversões
long long totalInversoes = 0;

// Função que intercala dois subarrays e contabiliza as inversões
void intercalar(vector<int>& arr, vector<int>& temp, int inicio, int meio, int fim) {
    int i = inicio;    // Ponteiro da metade esquerda
    int j = meio + 1;  // Ponteiro da metade direita
    int k = inicio;    // Ponteiro do vetor temporário

    while (i <= meio && j <= fim) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            // Se o elemento da direita for menor, há inversão com todos
            // os elementos restantes da metade esquerda: (meio - i + 1)
            temp[k++] = arr[j++];
            totalInversoes += (meio - i + 1);
        }
    }

    // Copia os elementos restantes da esquerda (se houver)
    while (i <= meio) {
        temp[k++] = arr[i++];
    }

    // Copia os elementos restantes da direita (se houver)
    while (j <= fim) {
        temp[k++] = arr[j++];
    }

    // Devolve os elementos ordenados de volta ao vetor original
    for (i = inicio; i <= fim; i++) {
        arr[i] = temp[i];
    }
}

// Algoritmo clássico de Divisão e Conquista: Merge Sort
void mergeSort(vector<int>& arr, vector<int>& temp, int inicio, int fim) {
    if (inicio >= fim) return;

    int meio = inicio + (fim - inicio) / 2;

    mergeSort(arr, temp, inicio, meio);
    mergeSort(arr, temp, meio + 1, fim);
    intercalar(arr, temp, inicio, meio, fim);
}

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    // Processa até que N seja 0
    while (cin >> N && N != 0) {
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }

        vector<int> temp(N);
        totalInversoes = 0;

        // Executa a contagem por Divisão e Conquista
        mergeSort(arr, temp, 0, N - 1);

        // Se o total de jogadas for ímpar, Marcelo vence; se for par, Carlos vence
        if (totalInversoes % 2 != 0) {
            cout << "Marcelo\n";
        } else {
            cout << "Carlos\n";
        }
    }

    return 0;
}