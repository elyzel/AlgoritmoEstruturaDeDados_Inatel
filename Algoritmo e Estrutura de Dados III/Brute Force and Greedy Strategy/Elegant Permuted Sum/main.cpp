/*
Serão fornecidos n números inteiros A1, A2, A3, ..., An. Encontre uma permutação desses n números inteiros de modo que a soma das diferenças absolutas entre elementos adjacentes seja maximizada.

Suponha que n = 4 e os números inteiros fornecidos sejam 4, 2, 1, 5. A permutação 2, 5, 1, 4 resulta na soma máxima. Para essa permutação, a soma é abs(2-5) + abs(5-1) + abs(1-4) = 3 + 4 + 3 = 10.

Dentre todas as 24 permutações possíveis, não haverá nenhuma soma cujo valor exceda 10. Chamaremos esse valor, 10, de "soma permutada elegante".

Entrada
A primeira linha da entrada contém um número inteiro T (T < 100) que representa o número de casos de teste. Cada caso consiste em uma linha que começa com n (1 < n < 51), seguido por n números inteiros não negativos separados por um único espaço. Nenhum dos elementos da permutação fornecida excederá 1000.

Saída
Para cada caso, exiba o número do caso seguido pela soma permutada elegante.
*/

#include <iostream>
#include <vector>
#include <algorithm> // Para usar sort() e max()

using namespace std;

int main() {
    int T;
    if (cin >> T) {
        for (int caso = 1; caso <= T; caso++) {
            int n;
            cin >> n;

            // 1. Lê os n números no vector
            vector<int> A(n);
            for (int i = 0; i < n; i++) {
                cin >> A[i];
            }

            // 2. Ordena o vetor do menor para o maior
            sort(A.begin(), A.end());

            int soma = 0;

            // 3. Caso N seja PAR
            if (n % 2 == 0) {
                int k = n / 2;

                for (int i = 0; i <= k - 2; i++) soma -= 2 * A[i];
                soma -= A[k - 1];
                soma += A[k];
                for (int i = k + 1; i < n; i++) soma += 2 * A[i];
            } 
            // 4. Caso N seja ÍMPAR
            else {
                int k = n / 2;

                // Opção 1: Dois elementos centrais com peso -1
                int soma1 = 0;
                for (int i = 0; i <= k - 2; i++) soma1 -= 2 * A[i];
                soma1 -= A[k - 1];
                soma1 -= A[k];
                for (int i = k + 1; i < n; i++) soma1 += 2 * A[i];

                // Opção 2: Dois elementos centrais com peso +1
                int soma2 = 0;
                for (int i = 0; i <= k - 1; i++) soma2 -= 2 * A[i];
                soma2 += A[k];
                soma2 += A[k + 1];
                for (int i = k + 2; i < n; i++) soma2 += 2 * A[i];

                soma = max(soma1, soma2);
            }

            // Impressão no padrão do problema
            cout << "Case " << caso << ": " << soma << endl;
        }
    }

    return 0;
}
