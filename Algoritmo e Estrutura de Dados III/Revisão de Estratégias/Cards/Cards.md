## 🎯 Análise Estratégica: Por que este paradigma?

> [!check] **Avaliação de Abordagens**
> 
> - ❌ **Força Bruta ($O(2^N)$):**
>     
>     Explorar a árvore completa de decisões geraria $2^N$ folhas. Para $N = 10^4$, $2^{10000}$ é um número astronômico que resultaria em estouro imediato de tempo (TLE).
>     
> - ❌ **Estratégia Gulosa (Greedy):**
>     
>     Alberto escolher simplesmente a maior carta visível na ponta naquele instante ($\max(A[i], A[j])$) é uma falha conhecida. Uma carta alta na ponta pode esconder uma carta ainda maior para Wanderley pegar logo em seguida, ou uma carta menor pode liberar uma carta gigantesca no turno seguinte para Alberto. Decisões míopes locais não garantem o ótimo global.
>     
> - ✅ **Paradigma Ideal: Programação Dinâmica de Intervalo com Otimização de Espaço ($O(N^2)$ Tempo, $O(N)$ Espaço):**
>     
>     Alberto joga como **Maximizador** (busca o maior ganho) e Wanderley joga como **Minimizador** (deixa o pior cenário para Alberto).
>     
>     Como a decisão de um intervalo de tamanho $tam$ só depende de subintervalos de tamanho $tam - 2$, podemos resolver em $O(N^2)$ e comprimir a matriz para apenas vetores lineares $O(N)$, cabendo com folga na memória para $N = 10^4$.
>     

## 🧠 Modelagem Teórica do Jogo (Minimax)

Seja $dp(i, j)$ a **pontuação máxima que Alberto consegue garantir** considerando as cartas restantes no intervalo $[i, j]$:

Quando é a vez de Alberto:

1. **Se Alberto escolhe a carta da esquerda ($A[i]$):**
    
    - Sobra o intervalo $[i+1, j]$.
        
    - Agora é o turno de Wanderley. Sabendo que Wanderley quer ferrar o Alberto (minimizar seus pontos futuros), Wanderley escolherá a melhor jogada dele, deixando para Alberto:
        
        $$\min(dp(i+2, j), \; dp(i+1, j-1))$$
        
    - Ganho total dessa escolha: $A[i] + \min(dp(i+2, j), \; dp(i+1, j-1))$.
        
2. **Se Alberto escolhe a carta da direita ($A[j]$):**
    
    - Sobra o intervalo $[i, j-1]$.
        
    - Wanderley joga e deixa para Alberto:
        
        $$\min(dp(i+1, j-1), \; dp(i, j-2))$$
        
    - Ganho total dessa escolha: $A[j] + \min(dp(i+1, j-1), \; dp(i, j-2))$.
        

Como Alberto quer maximizar, a relação de recorrência é:

$$dp(i, j) = \max \Big( A[i] + \min(dp(i+2, j), dp(i+1, j-1)), \; A[j] + \min(dp(i+1, j-1), dp(i, j-2)) \Big)$$

# 🃏 Jogo das Cartas Minimax (Alberto e Wanderley)

> [!abstract] **Visão Geral do Problema**
> 
> Um vetor com um número par $N$ de cartas é disposto em linha. Alberto joga primeiro e Wanderley joga em seguida. Em cada turno, o jogador retira uma carta de uma das duas extremidades.
> 
> Alberto joga para **maximizar** sua pontuação total e Wanderley joga para **minimizar** a pontuação final de Alberto. O objetivo é computar a pontuação máxima garantida por Alberto sob jogo ótimo de ambos.

## 🎯 Análise Estratégica: Por que este paradigma?

> [!check] **Avaliação de Abordagens**
> 
> - ❌ **Força Bruta ($O(2^N)$):**
>     
>     Explorar a árvore completa de decisões geraria $2^N$ combinações. Para $N = 10^4$, isso causaria **Time Limit Exceeded (TLE)** instantâneo.
>     
> - ❌ **Abordagem Gulosa (Greedy):**
>     
>     Escolher localmente $\max(A[i], A[j])$ falha, pois pode expor uma carta muito maior para o adversário no turno seguinte.
>     
> - ✅ **Paradigma Ideal: Programação Dinâmica de Intervalo ($O(N^2)$ Tempo, $O(N)$ Espaço):**
>     
>     A subestrutura ótima de jogos de soma zero permite calcular o valor ótimo de subintervalos crescentes. Otimizamos a memória de $O(N^2)$ para $O(N)$ mantendo apenas as camadas de tamanho $tam - 2$.
>     

## 🧠 Equação de Recorrência Minimax

Para qualquer subintervalo $[i, j]$:

$$dp[i][j] = \max \begin{cases} A[i] + \min(dp[i+2][j], \; dp[i+1][j-1]) & \text{(Alberto escolhe a esquerda)} \\ A[j] + \min(dp[i+1][j-1], \; dp[i][j-2]) & \text{(Alberto escolhe a direita)} \end{cases}$$

## 🔍 Explicação Detalhada de Cada Bloco e Linha de Código

### Bloco 1: Importação de Bibliotecas e Otimização de E/S

C++

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
```

- **`#include <iostream>`**: Entrada e saída rápida de dados.
    
- **`#include <vector>`**: Fornece os vetores unidimensionais dinâmicos `dp2` e `dp0`.
    
- **`#include <algorithm>`**: Fornece as funções `max()` e `min()`.
    

### Bloco 2: Leitura dos Dados e Casos de Teste

C++

```
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    while (cin >> N) {
        vector<long long> A(N);
        for (int i = 0; i < N; i++) {
            cin >> A[i];
        }
```

- **`while (cin >> N)`**: Processa as instâncias de teste até o fim do arquivo (EOF).
    
- **`vector<long long> A(N)`**: Armazena as cartas como inteiros de 64 bits para prevenir qualquer overflow durante a soma de valores de cartas grandes.
    

### Bloco 3: Inicialização da DP e Caso Base ($tam = 2$)

C++

```
        vector<long long> dp2(N, 0);
        vector<long long> dp0(N, 0);

        for (int i = 0; i < N - 1; i++) {
            dp2[i] = max(A[i], A[i + 1]);
        }
```

- **`vector<long long> dp2(N, 0)`**: Guarda os resultados calculados para subintervalos de tamanho $tam - 2$.
    
- **`vector<long long> dp0(N, 0)`**: Guarda os resultados para o tamanho $tam$ atual.
    
- **`dp2[i] = max(A[i], A[i + 1])`**: Quando restam apenas $2$ cartas consecutivas $[i, i+1]$, Alberto escolhe a maior delas e Wanderley fica obrigatoriamente com a menor.
    

### Bloco 4: Laços de Programação Dinâmica por Tamanho do Intervalo

C++

```
        for (int tam = 4; tam <= N; tam += 2) {
            for (int i = 0; i <= N - tam; i++) {
                int j = i + tam - 1;

                long long op1 = A[i] + min(dp2[i + 2], dp2[i + 1]);
                long long op2 = A[j] + min(dp2[i + 1], dp2[i]);

                dp0[i] = max(op1, op2);
            }

            dp2 = dp0;
        }
```

- **`for (int tam = 4; tam <= N; tam += 2)`**: Itera apenas sobre tamanhos pares, pois cada rodada completa consome exatamente 2 cartas (uma de Alberto e uma de Wanderley).
    
- **`int j = i + tam - 1;`**: Define a extremidade direita do subintervalo atual $[i, j]$.
    
- **`long long op1 = A[i] + min(...)`**:
    
    - Alberto leva $A[i]$.
        
    - A sobra $[i+1, j]$ é jogada por Wanderley.
        
    - O termo $dp2[i+2]$ representa o intervalo $[i+2, j]$ (Wanderley pegou a esquerda).
        
    - O termo $dp2[i+1]$ representa o intervalo $[i+1, j-1]$ (Wanderley pegou a direita).
        
    - Como Wanderley joga para prejudicar Alberto, pegamos o $\min$.
        
- **`long long op2 = A[j] + min(...)`**: Lógica análoga caso Alberto decida pegar a carta da ponta direita $A[j]$.
    
- **`dp2 = dp0`**: Atualiza a camada anterior para ser reaproveitada na próxima iteração de tamanho maior.
    

### Bloco 5: Impressão do Resultado Final

C++

```
        if (N == 2) {
            cout << dp2[0] << "\n";
        } else {
            cout << dp0[0] << "\n";
        }
    }

    return 0;
}
```

- Imprime a pontuação do intervalo completo $[0, N-1]$, que está armazenada no índice $0$.
    

## ⚡ Tabela de Análise de Complexidade

| **Métrica** | **Complexidade** | **Detalhes**                                                                                                                                                                       |
| ----------- | ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Tempo**   | $O(N^2)$         | Dois laços aninhados percorrendo os subintervalos pares. Para $N = 10^4$, executa cerca de $\frac{N^2}{4} \approx 2.5 \times 10^7$ operações simples (executa em $\approx 0.15$s). |
| **Espaço**  | $O(N)$           | Reduzido de $O(N^2)$ para $O(N)$ usando apenas dois vetores (`dp2` e `dp0`) de tamanho $N$. Consome menos de $1 \text{ MB}$ de memória.                                            |