#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Matriz de entrada com o "custo/moedas" de cada célula
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };

    int linhas = grid.size();
    int colunas = grid[0].size();

    // Matriz de DP do mesmo tamanho para guardar as respostas acumuladas
    vector<vector<int>> dp(linhas, vector<int>(colunas, 0));

    // Caso base: O início é o próprio valor
    dp[0][0] = grid[0][0];

    // Preenche a primeira fileira (só dá pra vir da esquerda)
    for (int j = 1; j < colunas; j++) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Preenche a primeira coluna (só dá pra vir de cima)
    for (int i = 1; i < linhas; i++) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Preenche o resto da matriz escolhendo o MELHOR caminho (Cima vs Esquerda)
    for (int i = 1; i < linhas; i++) {
        for (int j = 1; j < colunas; j++) {
            dp[i][j] = grid[i][j] + max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    cout << "Matriz com os resultados calculados (DP):" << endl;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            cout << dp[i][j] << "\t";
        }
        cout << endl;
    }

    cout << "\nO valor maximo coletado ate o final e: " << dp[linhas - 1][colunas - 1] << endl;

    return 0;
}