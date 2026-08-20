/*
Maria é uma senhora aposentada que faz bolos. Ela começou a fazer isso para ajudar na renda da família.

Para assar um bolo, Maria precisa de certa quantidade de ingredientes diferentes. Cada ingrediente tem um custo fixo por unidade. Ela dispõe de D unidades de dinheiro para gastar. Dentre os tipos de bolo, é necessário escolher apenas um tipo, de modo que o número de bolos assados ​​seja o maior possível.

Calcule o número máximo de bolos de um único tipo que podem ser assados.

Entrada
A primeira linha contém um inteiro T (T ≤ 100) indicando o número de casos de teste.

Em cada caso de teste, a primeira linha contém três inteiros D (1 ≤ D ≤ 10⁹), I (1 ≤ I ≤ 100) e B (1 ≤ B ≤ 100), indicando o dinheiro que Maria possui, o número de ingredientes existentes e a quantidade de tipos de bolo, respectivamente. Na linha seguinte, haverá I inteiros indicando o preço de uma unidade de cada ingrediente. Em seguida, haverá B linhas descrevendo cada bolo. O i-ésimo bolo é descrito da seguinte forma: um número Qi (1 ≤ Qi ≤ 100) que indica quantos ingredientes diferentes são necessários. Seguem-se Qi pares de números indicando o índice do ingrediente e a quantidade necessária, todos na mesma linha, separados por espaços em branco.

A quantidade de cada ingrediente em um bolo estará entre 1 e 1000. Cada unidade de um ingrediente custará entre 1 e 1000. Os ingredientes na descrição do bolo serão únicos. Os identificadores dos ingredientes estarão entre 0 e I-1.

Saída
Para cada caso de teste, imprima o número máximo de bolos de um único tipo que podem ser assados.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            long long D;
            int I, B;
            cin >> D >> I >> B;

            // 1. Lê o preço de uma unidade de cada ingrediente (índices 0 a I-1)
            vector<long long> preco(I);
            for (int i = 0; i < I; i++) {
                cin >> preco[i];
            }

            long long max_bolos = 0;

            // 2. Processa cada um dos B tipos de bolo
            for (int b = 0; b < B; b++) {
                int Q;
                cin >> Q;

                long long custo_bolo = 0;

                // Lê os Q pares (índice_ingrediente, quantidade_necessária)
                for (int k = 0; k < Q; k++) {
                    int indice;
                    long long quantidade;
                    cin >> indice >> quantidade;

                    custo_bolo += preco[indice] * quantidade;
                }

                // Calcula quantos bolos deste tipo Maria consegue fazer com o orçamento D
                if (custo_bolo > 0) {
                    long long bolos_possiveis = D / custo_bolo;
                    max_bolos = max(max_bolos, bolos_possiveis);
                }
            }

            // 3. Imprime a quantidade máxima de bolos possível
            cout << max_bolos << "\n";
        }
    }

    return 0;
}