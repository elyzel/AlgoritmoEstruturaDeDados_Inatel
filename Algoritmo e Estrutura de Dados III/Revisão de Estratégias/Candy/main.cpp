/*
O pequeno Charlie é um garoto simpático e viciado em doces. Ele é até assinante da revista *All Candies Magazine* e foi selecionado para participar do Concurso Internacional de Coleta de Doces.

Nesse concurso, um número aleatório de caixas contendo doces é disposto em M linhas e N colunas (totalizando M x N caixas). Cada caixa possui um número indicando quantos doces ela contém.

O competidor pode escolher uma caixa (qualquer uma) e pegar todos os doces que ela contém. Mas há um porém (sempre há um porém): ao escolher uma caixa, todas as caixas das linhas imediatamente acima e imediatamente abaixo são esvaziadas, assim como a caixa à esquerda e a caixa à direita da caixa escolhida. O competidor continua escolhendo caixas até que não restem mais doces.

A figura abaixo ilustra isso, passo a passo. Cada célula representa uma caixa e a quantidade de doces que ela contém. Em cada passo, a caixa escolhida é circulada e as células sombreadas representam as caixas que serão esvaziadas. Após oito passos, o jogo termina e Charlie coletou 10 + 9 + 8 + 3 + 7 + 6 + 10 + 1 = 54 doces.

Para valores pequenos de M e N, Charlie consegue encontrar facilmente o número máximo de doces que pode coletar, mas, quando os números são muito grandes, ele fica completamente perdido. Você pode ajudar Charlie a maximizar o número de doces que ele pode coletar?

Entrada
A entrada contém vários casos de teste. A primeira linha de um caso de teste contém dois números inteiros positivos M e N (1 ≤ M x N ≤ 10⁵), separados por um único espaço, indicando o número de linhas e colunas, respectivamente. Cada uma das M linhas seguintes contém N números inteiros separados por espaços simples, representando a quantidade inicial de doces na caixa correspondente. Inicialmente, cada caixa conterá pelo menos 1 e no máximo 10³ doces.

O fim da entrada é indicado por uma linha contendo dois zeros separados por um único espaço.

Saída
Para cada caso de teste na entrada, seu programa deve imprimir uma única linha contendo um único valor: o número inteiro que indica a quantidade máxima de doces que Charlie pode coletar.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Função que calcula a soma máxima de elementos não adjacentes em um vetor (House Robber)
int resolver1D(const vector<int>& v) {
    int n = (int)v.size();
    if (n == 0) return 0;
    if (n == 1) return v[0];

    int anterior2 = 0; // Representa dp[i-2]
    int anterior1 = 0; // Representa dp[i-1]

    for (int i = 0; i < n; i++) {
        int atual = max(anterior1, anterior2 + v[i]);
        anterior2 = anterior1;
        anterior1 = atual;
    }

    return anterior1;
}

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;

    // Processa até encontrar M = 0 e N = 0
    while (cin >> M >> N && !(M == 0 && N == 0)) {
        vector<int> maxPorLinha(M);

        // ETAPA 1: Processa cada linha individualmente
        for (int i = 0; i < M; i++) {
            vector<int> linha(N);
            for (int j = 0; j < N; j++) {
                cin >> linha[j];
            }
            maxPorLinha[i] = resolver1D(linha);
        }

        // ETAPA 2: Processa a melhor combinação entre linhas não adjacentes
        int respostaFinal = resolver1D(maxPorLinha);

        cout << respostaFinal << "\n";
    }

    return 0;
}