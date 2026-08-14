/*
A produção de vodka na cidade de São Petersburgo é famosa mundialmente. Reza a lenda que a vodka produzida é distribuída diretamente para as casas de alguns dos executivos de alto escalão da empresa por meio da rede de abastecimento de água. Ou seja, basta abrir a torneira para que a vodka saia geladíssima (afinal, a tubulação opera a temperaturas negativas durante a maior parte do ano). Isso gera diversos problemas de segurança, pois há pessoas que escavam as ruas em busca das supostas tubulações de vodka que saem da empresa.

Esse não é o único desafio enfrentado na produção local de vodka. Para garantir os padrões de qualidade exigidos, a bebida é produzida em um único destilador, que possui uma vida útil máxima de M anos. A manutenção varia de acordo com a idade do equipamento: o custo de manutenção é Ci (onde i é a idade do destilador) e deve ser pago anualmente, inclusive para destiladores novos. O preço de aquisição de um destilador novo (idade 0) é P; destiladores usados ​​em fábricas russas são revendidos para destilarias ao redor do mundo — onde continuam em operação por muitos anos — ou para museus. O preço de venda de um destilador com idade i é Vi.

Observe que um destilador com idade M não pode mais ser utilizado e deve ser vendido. Sua tarefa neste problema é decidir em quais momentos a empresa deve substituir o destilador para minimizar o custo de produção ao final de N anos (contados a partir do ano 1). Considere que a substituição do destilador só pode ser realizada no início do ano.

Entrada
A entrada contém múltiplos casos de teste e termina com EOF. A primeira linha de cada caso de teste contém 4 números inteiros: N (1 ≤ N ≤ 2000), I (1 ≤ I ≤ M), M (1 ≤ M ≤ 2000) e P (1 ≤ P ≤ 1000), representando, respectivamente, o período de produção, a idade inicial do destilador, a idade máxima do destilador e o preço de um destilador novo. A segunda linha de cada caso de teste contém M inteiros, separados por espaços, correspondentes ao custo de manutenção Ci (1 ≤ Ci ≤ 1000), para i = 0, 1, 2, ..., M - 1. A próxima e última linha contém M inteiros, separados por espaços, correspondentes ao valor de venda Vi (1 ≤ Vi ≤ P), para i = 1, 2, ..., M.

Saída
Para cada caso de teste, imprima duas linhas. Na primeira, imprima o custo mínimo para o período dado. Na segunda, uma sequência crescente de inteiros, separados por espaços, indicando os anos em que as máquinas são trocadas. Se a máquina nunca for trocada, imprima apenas 0. Se houver mais de uma sequência possível, escolha aquela em que as máquinas são trocadas o mais cedo possível e sempre que possível (por exemplo, entre as sequências "1 4 7" e "1 2 8 10 14", escolha a segunda).
*/

#include <iostream>
#include <vector>
#include <algorithm> // Necessário para min()

using namespace std;

int main() {
    int N, I, M, P;

    // O programa lê múltiplos casos de teste até o Fim de Arquivo (EOF)
    while (cin >> N >> I >> M >> P) {
        
        // 1. Vetor de custos de manutenção C[0 ... M-1]
        vector<int> C(M);
        for (int i = 0; i < M; i++) {
            cin >> C[i];
        }

        // 2. Vetor de valor de venda V[1 ... M] (1-indexado para facilitar)
        vector<int> V(M + 1);
        for (int i = 1; i <= M; i++) {
            cin >> V[i];
        }

        // 3. Matriz DP: dp[ano][idade]
        // Dimensões: (N + 2) linhas por (M + 1) colunas, tudo zerado
        vector<vector<int>> dp(N + 2, vector<int>(M + 1, 0));

        // Preenchimento de trás para frente (do ano N até o ano 1)
        for (int ano = N; ano >= 1; ano--) {
            for (int idade = 0; idade <= M; idade++) {
                
                // Opção de Trocar
                int custo_troca = (P - V[idade]) + C[0] + dp[ano + 1][1];

                if (idade == M) {
                    // Idade máxima atingida: é obrigatório trocar
                    dp[ano][idade] = custo_troca;
                } else {
                    // Opção de Manter
                    int custo_manter = C[idade] + dp[ano + 1][idade + 1];

                    // Pega o menor custo entre as duas opções
                    dp[ano][idade] = min(custo_troca, custo_manter);
                }
            }
        }

        // O custo mínimo total começa no ano 1 com a idade inicial I
        cout << dp[1][I] << endl;

        // 4. Reconstrução do Caminho (Descobrir em quais anos houve troca)
        vector<int> trocas;
        int idade_atual = I;

        for (int ano = 1; ano <= N; ano++) {
            int custo_troca = (P - V[idade_atual]) + C[0] + dp[ano + 1][1];
            int custo_manter = (idade_atual < M) ? (C[idade_atual] + dp[ano + 1][idade_atual + 1]) : 1e9;

            // Se for obrigatório trocar OU se trocar for mais barato / empatar:
            if (idade_atual == M || custo_troca <= custo_manter) {
                trocas.push_back(ano);
                idade_atual = 1; // Nova máquina operou no ano atual, vira idade 1 no próximo
            } else {
                idade_atual++; // Manteve a máquina, fica 1 ano mais velha
            }
        }

        // 5. Impressão dos anos de troca
        if (trocas.empty()) {
            cout << 0 << endl;
        } else {
            for (int i = 0; i < (int)trocas.size(); i++) {
                if (i > 0) cout << " ";
                cout << trocas[i];
            }
            cout << endl;
        }
    }

    return 0;
}
