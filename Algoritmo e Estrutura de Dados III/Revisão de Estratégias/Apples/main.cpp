/*
Rafael decidiu passar o fim de semana na fazenda de seu tio Anthony e, ao perceber que havia uma macieira no local, resolveu fazer uma torta de maçã.

Para preparar a torta, no entanto, Rafael precisaria coletar o maior número possível de maçãs e, para isso, decidiu pedir ajuda ao seu primo. O combinado era o seguinte: seu primo subiria na árvore e sacudiria vários galhos carregados de maçãs, fazendo-as cair. Enquanto elas caíam, Rafael ficaria no chão com uma cesta e tentaria pegá-las durante o trajeto da árvore até o solo. Como as maçãs caíam rapidamente, o impacto com o chão as danificaria; por isso, Rafael decidiu ignorar aquelas que não conseguisse pegar a tempo com sua cesta.

Podemos representar a situação da seguinte forma: Rafael está posicionado em uma área de N linhas e M colunas abaixo da árvore e pode mover-se uma posição na horizontal, vertical ou diagonal a cada segundo. Cada maçã cai em uma posição específica dessa área — digamos, [i, j] (linha i, coluna j) — e o momento exato em que Rafael precisa estar nessa posição para pegar a maçã é um instante t determinado.

Dada a posição inicial de Rafael, calcule a quantidade máxima de maçãs que ele consegue coletar com sua cesta, dentre as K maçãs derrubadas por seu primo.

Entrada
Haverá vários casos de teste. Cada caso de teste começa com três números inteiros: N, M e K (3 ≤ N, M ≤ 20; 1 ≤ K ≤ 1000), representando, respectivamente, o número de linhas e colunas da área abaixo da árvore e a quantidade de maçãs derrubadas pelo primo.

Em seguida, haverá K linhas, cada uma contendo três números inteiros — Xi, Yi e Ti (1 ≤ Xi ≤ N; 1 ≤ Yi ≤ M; 1 ≤ Ti ≤ 2*K) — representando, respectivamente, a linha e a coluna onde a i-ésima maçã caiu e o instante exato em que Rafael precisa estar nessa posição para pegá-la. A sequência de valores Ti fornecida na entrada é não decrescente; ou seja, Ti-1 ≤ Ti para todo 2 ≤ i ≤ K. Não há duas maçãs que caiam na mesma posição ao mesmo tempo.

Em seguida, são fornecidos dois números inteiros, X e Y (1 ≤ X ≤ N, 1 ≤ Y ≤ M), indicando a linha e a coluna onde Rafael se encontra no instante 0.

O último caso de teste é indicado quando N = M = K = 0; esse caso não deve ser processado.

Saída
Para cada caso de teste, imprima uma linha contendo um número inteiro que represente a quantidade máxima de maçãs que Rafael consegue pegar com sua cesta.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Estrutura para representar cada maçã
struct Maca {
    int x;
    int y;
    int t;
};

// Função para verificar se Rafael consegue ir da maçã A até a maçã B a tempo
bool alcancavel(const Maca& a, const Maca& b) {
    int dist = max(abs(a.x - b.x), abs(a.y - b.y));
    return dist <= (b.t - a.t);
}

int main() {
    // Otimização de Entrada e Saída
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;

    // Processa até que N == 0, M == 0 e K == 0
    while (cin >> N >> M >> K && !(N == 0 && M == 0 && K == 0)) {
        
        // Vetor de maçãs com tamanho K + 1 (1-indexado)
        vector<Maca> macas(K + 1);
        for (int i = 1; i <= K; i++) {
            cin >> macas[i].x >> macas[i].y >> macas[i].t;
        }

        // Posição inicial de Rafael no instante t = 0
        Maca rafael;
        cin >> rafael.x >> rafael.y;
        rafael.t = 0;
        macas[0] = rafael;

        // dp[i]: quantidade máxima de maçãs coletadas terminando na maçã i
        // Inicializado com -1 para representar estados inalcançáveis
        vector<int> dp(K + 1, -1);
        dp[0] = 0; // No início, pegou 0 maçãs

        int max_macas = 0;

        // Processa cada maçã i de 1 até K
        for (int i = 1; i <= K; i++) {
            // Verifica se a maçã i pode ser alcançada diretamente do ponto de partida
            if (alcancavel(macas[0], macas[i])) {
                dp[i] = 1;
            }

            // Tenta encadear a partir de qualquer maçã j anterior alcançável
            for (int j = 1; j < i; j++) {
                if (dp[j] != -1 && alcancavel(macas[j], macas[i])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            // Atualiza a resposta global
            if (dp[i] > max_macas) {
                max_macas = dp[i];
            }
        }

        cout << max_macas << "\n";
    }

    return 0;
}