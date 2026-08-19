#include <iostream>
#include <climits>

using namespace std;

#define MAX 100

// Matrizes globais para facilitar o acesso entre funções didáticas
int m[MAX][MAX]; // Armazena os custos mínimos
int s[MAX][MAX]; // Armazena o ponto de quebra (k) ideal

// Função recursiva para imprimir a parentização a partir da tabela s
void imprimir_parenteses(int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        imprimir_parenteses(i, s[i][j]);
        imprimir_parenteses(s[i][j] + 1, j);
        cout << ")";
    }
}

void resolver_matrizes_iterativo(int p[], int n) {
    // Inicializa a diagonal principal com 0 (custo de multiplicar uma matriz por ela mesma)
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // L é o comprimento da cadeia de matrizes sendo analisada
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            // Testa todos os pontos de quebra 'k' entre i e j
            for (int k = i; k <= j - 1; k++) {
                // Fórmula: Custo = Custo(Esquerda) + Custo(Direita) + Custo da Multiplicação Final
                int custo = m[i][k] + m[k + 1][j] + (p[i - 1] * p[k] * p[j]);

                if (custo < m[i][j]) {
                    m[i][j] = custo;
                    s[i][j] = k; // Salva onde dividimos a matriz
                }
            }
        }
    }
}

int main() {
    // Dimensões das matrizes:
    // A1: 10x30, A2: 30x5, A3: 5x60, A4: 60x10
    // O vetor p representa as dimensões comuns
    int p[] = {10, 30, 5, 60, 10};
    int n = 4; // Total de matrizes (tamanho de p menos 1)

    resolver_matrizes_iterativo(p, n);

    cout << "==========================================" << endl;
    cout << "   OTIMIZACAO DE MULTIPLICACAO DE MATRIZES " << endl;
    cout << "==========================================" << endl;
    cout << "Custo Minimo (Escalares): " << m[1][n] << endl;
    cout << "Ordem Optima: ";
    imprimir_parenteses(1, n);
    cout << endl << "------------------------------------------" << endl;

    return 0;
}