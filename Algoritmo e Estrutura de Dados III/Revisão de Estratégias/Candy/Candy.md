
# 🍬 Concurso Internacional de Coleta de Doces

> [!abstract] **Visão Geral do Problema**
> 
> Temos uma matriz de $M$ linhas e $N$ colunas de caixas com doces. Ao escolher uma caixa $(r, c)$:
> 
> 1. Todas as caixas das linhas adjacentes ($r-1$ e $r+1$) são eliminadas.
>     
> 2. As caixas vizinhas imediatas na mesma linha ($c-1$ e $c+1$) são eliminadas.
>     
> 
> O objetivo é encontrar a **quantidade máxima de doces** que Charlie pode coletar.

## 🎯 Análise Estratégica: Por que este paradigma?

> [!check] **Avaliação de Abordagens**
> 
> - ❌ **Força Bruta ($O(2^{M \times N})$):**
>     
>     Testar todas as configurações possíveis de caixas válidas geraria até $2^{100.000}$ estados. Para $M \times N \le 10^5$, isso causa estouro de tempo (**Time Limit Exceeded - TLE**) imediato.
>     
> - ❌ **Estratégia Gulosa (Greedy):**
>     
>     Escolher sempre a caixa com o maior valor de doces no tabuleiro destrói as vizinhas que, somadas, poderiam render um valor total muito maior (ex: escolher uma caixa central de valor $10$ elimina duas caixas vizinhas de valor $9$ cada, totalizando $18$). Escolhas míopes locais não garantem o ótimo global.
>     
> - ✅ **Paradigma Ideal: Programação Dinâmica Desacoplada em Duas Etapas ($O(M \times N)$):**
>     
>     O problema se decompõe de forma independente em duas instâncias do clássico **House Robber (Subsequência de Soma Máxima sem Elementos Adjacentes)**:
>     
>     1. **DP nas Colunas (1D):** Para cada linha $i$, calculamos o valor máximo de doces escolhendo caixas não adjacentes.
>         
>     2. **DP nas Linhas (1D):** Com o melhor resultado de cada linha em mãos, escolhemos as linhas não adjacentes que maximizam a soma final.
>         

## 🧠 Modelagem Matemática da Recorrência

Para um vetor unidimensional $V = [v_1, v_2, \dots, v_K]$ onde não se pode pegar elementos adjacentes:

$$dp[i] = \max(dp[i-1], \; dp[i-2] + v_i)$$

- **$dp[i-1]$:** Não pegamos o elemento $v_i$ (mantemos o melhor valor até a posição anterior).
    
- **$dp[i-2] + v_i$:** Pegamos o elemento $v_i$ (somamos seu valor ao melhor resultado obtido até duas posições atrás).
    

Plaintext

```
Passo 1 (Por Linha):
Linha 0: [ 1, 8, 2, 9 ]  ──► DP 1D ──► Melhor da Linha 0 = 17 (8 + 9)
Linha 1: [ 10, 1, 1, 10 ] ──► DP 1D ──► Melhor da Linha 1 = 20 (10 + 10)
Linha 2: [ 2, 5, 2, 5 ]  ──► DP 1D ──► Melhor da Linha 2 = 10 (5 + 5)

Passo 2 (Entre Linhas):
Vetor de Linhas: [ 17, 20, 10 ] ──► DP 1D Final ──► Max(17 + 10, 20) = 27
```

## 🔍 Explicação Detalhada de Cada Bloco e Linha de Código

### Bloco 1: Importação de Bibliotecas

Snippet de código

```C++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
```

- **`#include <iostream>`**: Permite usar os canais padrão de entrada e saída (`cin` e `cout`).
    
- **`#include <vector>`**: Permite a alocação dinâmica dos vetores `linha` e `maxPorLinha`.
    
- **`#include <algorithm>`**: Fornece a função `max(a, b)` para as tomadas de decisão da Programação Dinâmica.
    
- **`using namespace std;`**: Permite o uso direto das funções sem o prefixo `std::`.
    

### Bloco 2: Função Genérica de Programação Dinâmica 1D (`resolver1D`)

Snippet de código

```C++
int resolver1D(const vector<int>& v) {
    int n = (int)v.size();
    if (n == 0) return 0;
    if (n == 1) return v[0];

    int anterior2 = 0;
    int anterior1 = 0;

    for (int i = 0; i < n; i++) {
        int atual = max(anterior1, anterior2 + v[i]);
        anterior2 = anterior1;
        anterior1 = atual;
    }

    return anterior1;
}
```

- **`const vector<int>& v`**: Recebe o vetor por referência constante para evitar cópias desnecessárias na memória.
    
- **`int anterior2 = 0, anterior1 = 0;`**: Otimização de espaço para $O(1)$. Em vez de guardar uma matriz inteira, guardamos apenas o melhor resultado de dois passos atrás (`anterior2`) e de um passo atrás (`anterior1`).
    
- **`int atual = max(anterior1, anterior2 + v[i]);`**: Aplica a equação de Bellman: escolhe o maior valor entre não incluir a caixa atual (`anterior1`) ou incluir a caixa atual somada ao valor seguro de dois passos atrás (`anterior2 + v[i]`).
    
- **`anterior2 = anterior1; anterior1 = atual;`**: Desloca a janela temporal para a próxima iteração.
    
- **`return anterior1;`**: Retorna a pontuação máxima possível naquele arranjo linear.
    

### Bloco 3: Estrutura Principal e Leitura dos Casos de Teste

Snippet de código

```C++
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;

    while (cin >> M >> N && !(M == 0 && N == 0)) {
        vector<int> maxPorLinha(M);
```

- **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: Acelera a leitura dos dados para processar matrizes de até $10^5$ elementos com rapidez.
    
- **`while (cin >> M >> N && !(M == 0 && N == 0))`**: Laço que processa múltiplas instâncias e para ao encontrar a linha `0 0`.
    
- **`vector<int> maxPorLinha(M);`**: Vetor de tamanho $M$ que guardará o valor ótimo de cada uma das $M$ linhas da matriz.
    

### Bloco 4: Execução em Duas Etapas (Linhas e Tabuleiro)

Snippet de código

```C++
        for (int i = 0; i < M; i++) {
            vector<int> linha(N);
            for (int j = 0; j < N; j++) {
                cin >> linha[j];
            }
            maxPorLinha[i] = resolver1D(linha);
        }

        int respostaFinal = resolver1D(maxPorLinha);

        cout << respostaFinal << "\n";
    }

    return 0;
}
```

- **`for (int i = 0; i < M; i++)`**: Itera sobre cada linha da matriz.
    
- **`maxPorLinha[i] = resolver1D(linha);`**: Resolve a DP horizontalmente e condensa os $N$ números da linha $i$ em um único valor ótimo.
    
- **`int respostaFinal = resolver1D(maxPorLinha);`**: Reutiliza a mesma função para resolver a DP verticalmente, selecionando as linhas não adjacentes que produzem a maior soma.
    
- **`cout << respostaFinal << "\n";`**: Imprime a resposta final do caso de teste.
    

## ⚡ Tabela de Análise de Complexidade

|**Métrica**|**Complexidade**|**Justificativa**|
|---|---|---|
|**Tempo**|$O(M \times N)$|Cada uma das $M \times N$ caixas é lida e processada exatamente uma vez na DP horizontal, e o vetor de $M$ linhas é processado em $O(M)$ na DP vertical. Para $M \times N \le 10^5$, roda em menos de $0.02$s.|
|**Espaço**|$O(N)$|Mantém na memória apenas o vetor da linha atual de tamanho $N$ e o vetor condensado `maxPorLinha` de tamanho $M$.|