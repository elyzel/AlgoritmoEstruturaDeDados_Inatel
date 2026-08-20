#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    // Processa até o Fim de Arquivo (EOF)
    while (cin >> N) {
        vector<long long> w(N);
        for (int i = 0; i < N; i++) {
            cin >> w[i];
        }

        // 1. Ordena os pesos das ovelhas
        sort(w.begin(), w.end());

        long long menorCustoGlobal = INF;

        // 2. Itera sobre todos os tamanhos possíveis K para o grupo A
        // Por simetria, basta testar K de 1 até N / 2
        for (int K = 1; K <= N / 2; K++) {
            int tamB = N - K;

            // dp[c] guarda o menor custo acumulado tendo escolhido 'c' elementos para o grupo A
            vector<long long> dp(K + 1, INF);
            dp[0] = 0;

            for (int i = 1; i <= N; i++) {
                long long x = w[i - 1];
                int max_c = min(i, K);
                int min_c = max(0, i - tamB);

                // Atualização in-place de trás para frente
                for (int c = max_c; c >= min_c; c--) {
                    long long melhorTransicao = INF;

                    // Opção 1: Colocar a ovelha atual no grupo B
                    if (c <= i - 1 && dp[c] != INF) {
                        int cntB = i - 1 - c;
                        long long custoB = (2LL * cntB + 1 - tamB) * x;
                        melhorTransicao = min(melhorTransicao, dp[c] + custoB);
                    }

                    // Opção 2: Colocar a ovelha atual no grupo A
                    if (c > 0 && dp[c - 1] != INF) {
                        int cntA = c - 1;
                        long long custoA = (2LL * cntA + 1 - K) * x;
                        melhorTransicao = min(melhorTransicao, dp[c - 1] + custoA);
                    }

                    dp[c] = melhorTransicao;
                }
            }

            menorCustoGlobal = min(menorCustoGlobal, dp[K]);
        }

        cout << menorCustoGlobal << "\n";
    }

    return 0;
}