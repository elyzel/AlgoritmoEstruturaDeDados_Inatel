/*
As corridas de dragsters não são muito populares no Brasil, mas atraem multidões nos EUA. Os fãs gostam de ver carros correndo a velocidades de até 400 km/h, mesmo que apenas por alguns segundos. Muitos competidores são mecânicos amadores que apenas acoplaram foguetes e outras engenhocas para criar carros ultrarrápidos.

As competições de dragsters são torneios de eliminação, onde cada confronto consiste em dois competidores correndo lado a lado e apenas um deles sendo declarado vencedor (o mais rápido, obviamente). Os vencedores são então colocados em novas corridas, até que reste apenas um competidor, que é declarado vencedor.

Rubens é um piloto experiente, com carreira em diversas categorias, incluindo Fórmula 1. No entanto, depois de enfrentar algumas dificuldades, ele decidiu se dedicar às corridas de dragsters. Usando sua vasta experiência na Fórmula 1, ele pode, observando os competidores, dizer qual é a probabilidade de cada um prevalecer durante uma corrida entre qualquer par deles.

Embora Rubens seja um bom piloto, ele\ não é muito bom em matemática nem em computação, então ele pediu sua ajuda para escrever um programa que, dadas as probabilidades calculadas por Rubens para todas as corridas entre cada par de pilotos e a descrição da estrutura do torneio, determina sua probabilidade de vencer o torneio.

Entrada
A entrada consiste em vários casos de teste. A primeira linha de um caso de teste contém um único número inteiro N, indicando o número de competidores neste torneio (2≤N≤300). Na descrição do torneio, cada competidor é identificado por um número inteiro de 1 a N, e as corridas são identificadas por números inteiros de N + 1 a 2 x N - 1. Rubens é sempre identificado pelo número 1. As N próximas linhas descrevem a matriz de probabilidade calculada por Rubens. A i-ésima linha contém N números reais M [i, j] separados por espaços (0 ≤ M [i, j] ≤ 1, para 1 ≤ i ≤ N e 1 ≤ j ≤ N). Cada entrada de matriz M[i, j] indica a probabilidade do competidor i vencer uma corrida contra o competidor j (0,001 ≤ M[i, j] ≤ 0,999 e M[i, j] + M[j, i] = 1 fori ≠ j, e M[i, j] = 0 para i = j).

As probabilidades serão sempre dadas com três casas decimais. Cada uma das próximas linhas N - 1 contém dois números inteiros A, B, descrevendo uma raça. A e B são identificadores de corrida ou competidor (1 ≤ A ≤ 2 x N - 1 e 1 ≤ B ≤ 2 x N - 1). A primeira dessas linhas descreve a corrida N + 1, a próxima linha descreve a corrida N + 2 e assim por diante. Quando um identificador de corrida k aparece na entrada como A, isso significa que o vencedor da corrida k correrá contra B; da mesma forma, quando um identificador de corrida k aparece como B, o vencedor da corrida k concorrerá contra A.

O final da entrada é indicado por uma linha contendo um único zero.

Saída
Para cada caso de teste na entrada, seu programa deve imprimir uma única linha, contendo um único número real, com precisão de seis casas decimais, indicando a probabilidade de Rubens vencer o torneio.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Variáveis globais simples para facilitar o acesso
int N;
vector<vector<double>> M; // Matriz de probabilidades de vitória
vector<int> esq;          // Quem disputa pelo lado esquerdo da partida
vector<int> dir;          // Quem disputa pelo lado direito da partida

// Função simples que calcula as chances de vitória em uma partida
vector<double> calcular(int no) {
    // Vetor com as chances de cada competidor (1 a N) vencer este confronto
    vector<double> prob(N + 1, 0.0);

    // CASO BASE: Se o nó for um competidor individual (de 1 a N)
    if (no <= N) {
        prob[no] = 1.0; // 100% de chance de ser ele mesmo
        return prob;
    }

    // PASSO RECURSIVO: Calcula os resultados das duas subchaves primeiro
    vector<double> probEsq = calcular(esq[no]);
    vector<double> probDir = calcular(dir[no]);

    // Calcula a chance de cada competidor do lado esquerdo vencer
    for (int i = 1; i <= N; i++) {
        if (probEsq[i] > 0.0) {
            double chanceContraDireita = 0.0;
            for (int j = 1; j <= N; j++) {
                if (probDir[j] > 0.0) {
                    chanceContraDireita += probDir[j] * M[i][j];
                }
            }
            prob[i] = probEsq[i] * chanceContraDireita;
        }
    }

    // Calcula a chance de cada competidor do lado direito vencer
    for (int j = 1; j <= N; j++) {
        if (probDir[j] > 0.0) {
            double chanceContraEsquerda = 0.0;
            for (int i = 1; i <= N; i++) {
                if (probEsq[i] > 0.0) {
                    chanceContraEsquerda += probEsq[i] * M[j][i];
                }
            }
            prob[j] = probDir[j] * chanceContraEsquerda;
        }
    }

    return prob;
}

int main() {
    // Executa enquanto N for diferente de 0
    while (cin >> N && N != 0) {
        
        // 1. Cria e lê a matriz M de tamanho (N+1) x (N+1)
        M.assign(N + 1, vector<double>(N + 1, 0.0));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cin >> M[i][j];
            }
        }

        int total = 2 * N;
        esq.assign(total, 0);
        dir.assign(total, 0);
        vector<bool> temPai(total, false);

        // 2. Lê as N - 1 partidas do torneio
        for (int k = N + 1; k <= 2 * N - 1; k++) {
            int A, B;
            cin >> A >> B;
            esq[k] = A;
            dir[k] = B;
            temPai[A] = true; // A disputa uma partida, logo tem um "pai"
            temPai[B] = true; // B disputa uma partida, logo tem um "pai"
        }

        // 3. A grande final é a única partida que NÃO tem pai
        int partidaFinal = 0;
        for (int k = N + 1; k <= 2 * N - 1; k++) {
            if (!temPai[k]) {
                partidaFinal = k;
                break;
            }
        }

        // 4. Calcula a probabilidade a partir da final
        vector<double> resultado = calcular(partidaFinal);

        // 5. Imprime a probabilidade de Rubens (competidor 1) com 6 casas decimais
        cout << fixed << setprecision(6) << resultado[1] << endl;
    }

    return 0;
}