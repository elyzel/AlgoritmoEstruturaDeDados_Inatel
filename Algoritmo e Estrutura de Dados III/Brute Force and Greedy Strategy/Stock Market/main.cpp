/*
Um investidor iniciante quer aprender a investir no mercado de ações. Como não tem experiência, ele escolheu uma empresa e acompanhou diariamente o valor da ação durante N dias. Ao final, ele quis saber quanto dinheiro teria ganho se tivesse investido durante o período em que acompanhou o valor da ação. Para ser sincero, o investidor é multimilionário e possui muito dinheiro, o suficiente para comprar qualquer quantidade de ações da empresa. No entanto, como é muito cauteloso com seus investimentos, decidiu que nunca manteria mais de uma ação da empresa de cada vez.

Para cobrir os custos, a corretora cobra uma taxa fixa de C dólares por cada compra de ação.

Você deve calcular o lucro máximo que o investidor poderia ter obtido investindo durante os N dias, tendo também a opção de não investir dinheiro algum.

Entrada
A entrada consiste em vários casos de teste. A primeira linha de um caso de teste contém dois números inteiros, N e C (1 ≤ N ≤ 2 × 10⁵, 0 ≤ C ≤ 30). A segunda linha contém os N preços P1, P2, …, PN referentes aos dias 1, 2, …, N, respectivamente. Cada preço Pi satisfaz a condição 1 ≤ Pi ≤ 1000.
Saída
Para cada caso de teste na entrada, seu programa deve produzir exatamente uma linha contendo exatamente um número inteiro: o lucro máximo
do investidor, em dólares.

Anotações:
N = número de dias que observou a ação
C = número fixo de custo pela compra de cada ação

*/

#include <iostream>
#include <vector>
#include <algorithm> // Necessário para a função max()

using namespace std;

int main() {
    int N, C;

    // Lê a quantidade de dias N e a taxa C enquanto houver casos de teste
    while (cin >> N >> C) {
        
        // 1. Armazena todos os N preços em um vector
        vector<int> P(N);
        for (int i = 0; i < N; i++) {
            cin >> P[i];
        }

        // 2. Condições Iniciais (Dia 1 - índice 0 do vetor)
        int sem_acao = 0;            // Não comprou nenhuma ação (lucro = 0)
        int com_acao = -P[0] - C;    // Comprou no 1º dia (gasta o preço P[0] + taxa C)

        // 3. Transição dos estados do Dia 2 (índice 1) até o último dia (índice N - 1)
        for (int i = 1; i < N; i++) {
            // Guarda os valores do dia anterior antes de atualizar
            int sem_acao_anterior = sem_acao;
            int com_acao_anterior = com_acao;

            // Transição para o dia i:
            sem_acao = max(sem_acao_anterior, com_acao_anterior + P[i]);
            com_acao = max(com_acao_anterior, sem_acao_anterior - P[i] - C);
        }

        // O resultado final com maior lucro estará no estado 'sem_acao'
        cout << sem_acao << endl;
    }

    return 0;
}
