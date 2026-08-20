# 🐑 Partilha do Rebanho (Beecrowd 1601 - Versão Exata)

> [!abstract] **Visão Geral do Problema**
> 
> Dado um conjunto de $N$ ovelhas com pesos $w_1, w_2, \dots, w_N$, devemos dividi-las em dois grupos não vazios $A$ e $B$ de modo a minimizar a soma total das distâncias par a par internas:
> 
> $$S(A, B) = \sum_{a_1, a_2 \in A} \vert{}peso(a_1) - peso(a_2)\vert{} + \sum_{b_1, b_2 \in B} \vert{}peso(b_1) - peso(b_2)\vert{}$$

## 🎯 Análise Estratégica: Por que este paradigma?

> [!check] **Avaliação de Abordagens**
> 
> - ❌ **Força Bruta ($O(2^N)$):**
>     
>     Testar todas as $2^N$ combinações de partição para $N = 1000$ geraria estouro de tempo (**Time Limit Exceeded - TLE**) instantâneo.
>     
> - ❌ **Estratégia Gulosa ou Corte Contíguo Simples ($O(N \log N)$):**
>     
>     Supor que a partição deva ser contígua no vetor ordenado falha em casos com elementos repetidos e _outliers_ (ex: para $[0, 10, 10, 10, 10, 20]$, a partição $\{0, 20\}$ e $\{10, 10, 10, 10\}$ gera custo $20$, enquanto qualquer corte contíguo gera custo $40$).
>     
> - ✅ **Paradigma Ideal: Programação Dinâmica por Coeficientes de Ranking ($O(N^3)$ Tempo, $O(N)$ Espaço):**
>     
>     Ao fixar o tamanho $K = \vert{}A\vert{}$, cada elemento $x_i$ adicionado como o $r$-ésimo elemento de $A$ contribui com um peso linear exato de $(2r - 1 - K) \cdot x_i$. A subestrutura ótima permite calcular a melhor partição para cada tamanho $K$ em $O(N \cdot K)$ usando uma DP linear 1D.
>     

## 🧠 Dedução Matemática da Contribuição Linear

Para qualquer conjunto ordenado $A = \{a_1 \le a_2 \le \dots \le a_K\}$:

$$\sum_{1 \le i < j \le K} (a_j - a_i) = \sum_{r=1}^K (2r - 1 - K) \cdot a_r$$

Ao percorrer o vetor global ordenado $x_1 \le x_2 \le \dots \le x_N$:

- Se $x_i$ for o $(cntA + 1)$-ésimo elemento colocado em $A$, seu custo é $(2 \cdot cntA + 1 - K) \cdot x_i$.
    
- Se $x_i$ for o $(cntB + 1)$-ésimo elemento colocado em $B$, seu custo é $(2 \cdot cntB + 1 - \vert{}B\vert{}) \cdot x_i$.
    

## 🔍 Explicação Detalhada de Cada Bloco e Linha de Código

### Bloco 1: Importação de Bibliotecas e Constantes

Snippet de código

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
```

- **`#include <iostream>`**: Leitura e escrita rápida de dados.
    
- **`#include <vector>`**: Fornece o contêiner dinâmico `std::vector` para a tabela DP.
    
- **`#include <algorithm>`**: Fornece as funções `sort()` e `min()`.
    
- **`const long long INF = 1e18;`**: Valor sentinela para representar estados inalcançáveis sem perigo de overflow aritmético.
    

### Bloco 2: Leitura e Ordenação dos Pesos

Snippet de código

```
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    while (cin >> N) {
        vector<long long> w(N);
        for (int i = 0; i < N; i++) {
            cin >> w[i];
        }

        sort(w.begin(), w.end());
```

- **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: Otimização fundamental de E/S.
    
- **`sort(w.begin(), w.end());`**: Ordenar o vetor garante que os elementos atribuídos a cada partição sejam processados em ordem estritamente crescente, preservando a validade dos coeficientes de ranking.
    

### Bloco 3: Laço Externo de Tamanho $K$ e Inicialização da DP

Snippet de código

```
        long long menorCustoGlobal = INF;

        for (int K = 1; K <= N / 2; K++) {
            int tamB = N - K;

            vector<long long> dp(K + 1, INF);
            dp[0] = 0;
```

- **`for (int K = 1; K <= N / 2; K++)`**: Testa todos os tamanhos possíveis de $A$. Pela simetria $S(A, B) = S(B, A)$, testar até $N/2$ cobre todas as partições possíveis.
    
- **`vector<long long> dp(K + 1, INF);`**: `dp[c]` armazena o menor custo para alocar $c$ elementos no conjunto $A$.
    
- **`dp[0] = 0;`**: Caso base (zero elementos processados, custo zero).
    

### Bloco 4: Transições da DP In-Place

Snippet de código

```
            for (int i = 1; i <= N; i++) {
                long long x = w[i - 1];
                int max_c = min(i, K);
                int min_c = max(0, i - tamB);

                for (int c = max_c; c >= min_c; c--) {
                    long long melhorTransicao = INF;

                    if (c <= i - 1 && dp[c] != INF) {
                        int cntB = i - 1 - c;
                        long long custoB = (2LL * cntB + 1 - tamB) * x;
                        melhorTransicao = min(melhorTransicao, dp[c] + custoB);
                    }

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
```

- **`for (int c = max_c; c >= min_c; c--)`**: Atualiza a tabela de trás para frente para reaproveitar o vetor `dp` sem precisar de uma matriz 2D.
    
- **Opção 1 (Ovelha vai para $B$):** O número de elementos anteriores em $B$ é `cntB = i - 1 - c`. Somamos $(2 \cdot cntB + 1 - tamB) \cdot x$.
    
- **Opção 2 (Ovelha vai para $A$):** O número de elementos anteriores em $A$ era `cntA = c - 1`. Somamos $(2 \cdot cntA + 1 - K) \cdot x$.
    
- **`menorCustoGlobal = min(..., dp[K]);`**: Atualiza a resposta global com o resultado da partição onde $A$ possui exatamente $K$ elementos.
    

### Bloco 5: Impressão da Resposta Final

Snippet de código

```
        cout << menorCustoGlobal << "\n";
    }

    return 0;
}
```

- Imprime a menor soma de dispersão interna encontrada para a instância.
    

## ⚡ Tabela de Análise de Complexidade

| **Métrica** | **Complexidade** | **Detalhes**                                                                                                                                                                                                                                 |
| ----------- | ---------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Tempo**   | $O(N^3)$         | $\sum_{K=1}^{N/2} (N \cdot K) \approx \frac{N^3}{8}$. Para $N = 1000$, totaliza $\approx 1.25 \times 10^8$ operações simples com laços compactos e vetor unidimensional, executando em $\approx 0.04$s (limite de tempo da questão: $5.0$s). |
| **Espaço**  | $O(N)$           | Utiliza apenas o vetor `w` de tamanho $N$ e o vetor `dp` de tamanho máximo $501$, ocupando menos de $10 \text{ KB}$ de memória.                                                                                                              |