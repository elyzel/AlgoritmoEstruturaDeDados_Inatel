/*
Você tem em mãos um array de números inteiros positivos, não necessariamente distintos.

Vamos escolher alguns dos números do array, isto é, um subconjunto não vazio do array original. O valor de um subconjunto é a soma dos elementos nele contidos.

Qual é o menor valor de subconjunto que não pode ser obtido?

Por exemplo, considere o array [2, 1, 5]. Os seguintes subconjuntos podem ser formados: [1], [2], [5], [1, 2], [1, 5], [2, 5], [1, 2, 5]. Seus valores são: 1, 2, 5, 3, 6, 7, 8, respectivamente. O menor valor de subconjunto que não pode ser obtido neste caso é 4.

Entrada
A primeira linha conterá um número T (1 ≤ T ≤ 1000), indicando quantos casos de teste seguirão.

Para cada caso de teste, a primeira linha conterá um número N (1 ≤ N ≤ 10000), indicando quantos números o array contém. A linha seguinte conterá N números inteiros positivos separados por espaços, variando de 1 a 10⁹.

Saída
Para cada caso de teste, imprima uma única linha contendo a resposta para o problema.
*/

#include <iostream>
#include <vector>
#include <algorithm> // Necessário para sort()

using namespace std;

int main() {
    int T;
    if (cin >> T) {
        while (T--) {
            int N;
            cin >> N;

            // 1. Lê os N elementos no vector
            vector<long long> A(N);
            for (int i = 0; i < N; i++) {
                cin >> A[i];
            }

            // 2. Ordena o vetor do menor para o maior
            sort(A.begin(), A.end());

            // 3. Descobre o menor valor não formável
            long long menor_impossivel = 1;

            for (int i = 0; i < N; i++) {
                if (A[i] > menor_impossivel) {
                    break; // Encontrou a menor soma impossível
                }
                menor_impossivel += A[i];
            }

            // 4. Exibe o resultado
            cout << menor_impossivel << endl;
        }
    }

    return 0;
}
