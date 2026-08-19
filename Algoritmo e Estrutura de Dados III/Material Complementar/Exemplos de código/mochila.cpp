#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

// Estrutura para representar o Item
struct Item {
    int id;
    int peso;
    int valor;
};

// Configurações de limite para as tabelas de PD e Arrays
const int MAX_ITENS = 100;
const int MAX_CAPACIDADE = 100;

// Matrizes globais para memória e processamento
int memo[MAX_ITENS][MAX_CAPACIDADE];
int dp_table[MAX_ITENS][MAX_CAPACIDADE];

// --- 1. FORÇA BRUTA ITERATIVA (BINÁRIA) ---
int fb_iterativa(int n, int cap, Item itens[]) {
    int melhor_valor = 0;
    int combinacoes = pow(2, n);

    for (int i = 0; i < combinacoes; i++) {
        int peso_atual = 0;
        int valor_atual = 0;
        for (int j = 0; j < n; j++) {
            // Verifica se o j-ésimo bit está ativo na combinação i
            if ((i >> j) & 1) {
                peso_atual += itens[j].peso;
                valor_atual += itens[j].valor;
            }
        }
        if (peso_atual <= cap && valor_atual > melhor_valor) {
            melhor_valor = valor_atual;
        }
    }
    return melhor_valor;
}

// --- 2. FORÇA BRUTA RECURSIVA ---
int fb_recursiva(int i, int n, int cap, Item itens[]) {
    if (i == n || cap == 0) return 0;

    int nao_escolher = fb_recursiva(i + 1, n, cap, itens);

    int escolher = 0;
    if (itens[i].peso <= cap) {
        escolher = itens[i].valor + fb_recursiva(i + 1, n, cap - itens[i].peso, itens);
    }
    return max(escolher, nao_escolher);
}

// --- 3. ALGORITMO GULOSO ---
// Nota: Usamos um Selection Sort manual aqui para não depender de std::sort com vectores
void ordenar_itens_por_valor(Item itens[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (itens[i].valor < itens[j].valor) {
                swap(itens[i], itens[j]);
            }
        }
    }
}

int solucao_gulosa(int n, int cap, Item itens_originais[]) {
    // Criamos uma cópia para não desordenar o array original das outras funções
    Item itens[MAX_ITENS];
    for(int i=0; i<n; i++) itens[i] = itens_originais[i];

    ordenar_itens_por_valor(itens, n);

    int valor_total = 0;
    int cap_restante = cap;
    for (int i = 0; i < n; i++) {
        if (cap_restante >= itens[i].peso) {
            cap_restante -= itens[i].peso;
            valor_total += itens[i].valor;
        }
    }
    return valor_total;
}

// --- 4. PD RECURSIVA (TOP-DOWN) ---
int pd_top_down(int i, int n, int cap, Item itens[]) {
    if (i == n || cap == 0) return 0;
    if (memo[i][cap] != -1) return memo[i][cap];

    int nao_escolher = pd_top_down(i + 1, n, cap, itens);
    int escolher = 0;
    if (itens[i].peso <= cap) {
        escolher = itens[i].valor + pd_top_down(i + 1, n, cap - itens[i].peso, itens);
    }
    return memo[i][cap] = max(escolher, nao_escolher);
}

// --- 5. PD ITERATIVA (BOTTOM-UP) ---
int pd_bottom_up(int n, int cap_total, Item itens[]) {
    // Limpar tabela interna
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=cap_total; j++) dp_table[i][j] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cap_total; j++) {
            if (itens[i-1].peso <= j) {
                // max(não levar, levar + valor de quando tínhamos menos peso/itens)
                dp_table[i][j] = max(dp_table[i-1][j],
                                     itens[i-1].valor + dp_table[i-1][j - itens[i-1].peso]);
            } else {
                dp_table[i][j] = dp_table[i-1][j];
            }
        }
    }
    return dp_table[n][cap_total];
}

void imprimir_itens_escolhidos(int n, int cap_total, Item itens[]) {
    int j = cap_total; // Capacidade restante
    int valor_total = 0;
    int peso_total = 0;
    cout << "--- ITENS SELECIONADOS (PD ITERATIVA) ---" << endl;
    // Percorremos a tabela de trás para frente (do último item para o primeiro)
    for (int i = n; i > 0; i--) {
        // Se o valor mudou em relação à linha de cima, o item i-1 foi incluído
        if (dp_table[i][j] != dp_table[i - 1][j]) {
            cout << "Item " << itens[i - 1].id
                 << " [Peso: " << itens[i - 1].peso
                 << ", Valor: " << itens[i - 1].valor << "]" << endl;

            valor_total += itens[i - 1].valor;
            peso_total += itens[i - 1].peso;

            // Subtraímos o peso do item escolhido da capacidade atual
            j -= itens[i - 1].peso;
        }
    }
    cout << "-------------------------------------------" << endl;
    cout << "Resumo: Valor " << valor_total << " | Peso " << peso_total << "/" << cap_total << endl;
}

// --- FUNÇÃO PRINCIPAL ---
int main() {
    int capacidade = 10;
    int n = 4;

    // Array estático de itens
    Item itens[MAX_ITENS] = {
        {0, 5, 79},
        {1, 4, 70},
        {2, 4, 45},
        {3, 2, 35}
    };

    // Reset da memória para PD Top-Down (preencher com -1)
    for(int i=0; i<MAX_ITENS; i++)
        for(int j=0; j<MAX_CAPACIDADE; j++) memo[i][j] = -1;

    cout << "===========================================" << endl;
    cout << "   COMPARATIVO: MOCHILA 0/1 (ARRAYS PUROS) " << endl;
    cout << "===========================================" << endl;
    cout << "Capacidade: " << capacidade << " | Itens: " << n << endl;
    cout << "-------------------------------------------" << endl;

    cout << "1. FB Iterativa (Binaria):  " << fb_iterativa(n, capacidade, itens) << endl;
    cout << "2. FB Recursiva:            " << fb_recursiva(0, n, capacidade, itens) << endl;
    cout << "3. Algoritmo Guloso:        " << solucao_gulosa(n, capacidade, itens) << " (Pode falhar!)" << endl;
    cout << "4. PD Top-Down (Memo):      " << pd_top_down(0, n, capacidade, itens) << endl;
    cout << "5. PD Bottom-Up (Tabela):   " << pd_bottom_up(n, capacidade, itens) << endl;
    cout << "-------------------------------------------" << endl;

    return 0;
}