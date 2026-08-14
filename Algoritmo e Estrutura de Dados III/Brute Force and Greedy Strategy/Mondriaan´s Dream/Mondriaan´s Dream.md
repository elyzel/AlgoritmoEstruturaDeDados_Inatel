
# O Sonho de Mondriaan (Pavimentação de Retângulo com Dominós)

> [!abstract] Visão Geral do Problema
> 
> Calcular o número de maneiras de preencher completamente uma grade $H \times W$ utilizando dominós de tamanho $2 \times 1$ e $1 \times 2$.
> 
> Como $H, W \le 11$, a solução padrão é a **Programação Dinâmica com Máscara de Bits (Bitmask Profile DP)**, processando o tabuleiro linha por linha.

## 🧠 Modelagem de Estados (Bitmask DP)

Cada linha possui um estado representado por um número binário de $W$ bits:

- Bit `0`: Célula desocupada na linha atual.
    
- Bit `1`: Célula preenchida por um dominó vertical que veio da linha anterior.
    

Plaintext

```
Linha i:     [ 0 ] [ 1 ] [ 0 ] [ 0 ]   (bit 1 = ocupado da linha i-1)
               │     │     └───┴─── Coloca dominó horizontal (2x1)
               ▼     └── Já ocupado: avança para a próxima coluna
      Coloca dominó vertical (projeta bit 1 para Linha i+1)
```

## 📌 Detalhamento da Estrutura

### 1. Inclusão de Bibliotecas

C++

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
```

### 2. Busca em Profundidade (DFS) para Transições de Linha

C++

```
void gerarTransicoes(int c, int mascaraAtual, int proximaMascara, vector<long long>& proximoDp, long long qtdManeiras) {
    if (c == W) {
        proximoDp[proximaMascara] += qtdManeiras;
        return;
    }

    if ((mascaraAtual & (1 << c)) != 0) {
        gerarTransicoes(c + 1, mascaraAtual, proximaMascara, proximoDp, qtdManeiras);
    } else {
        gerarTransicoes(c + 1, mascaraAtual, proximaMascara | (1 << c), proximoDp, qtdManeiras);

        if (c + 1 < W && ((mascaraAtual & (1 << (c + 1))) == 0)) {
            gerarTransicoes(c + 2, mascaraAtual, proximaMascara, proximoDp, qtdManeiras);
        }
    }
}
```

> [!tip] Vantagem da DFS de Transições
> 
> Em vez de testar todas as $2^W \times 2^W$ combinações possíveis entre duas linhas com laços, a DFS gera **somente as transições geometricamente válidas**, tornando a execução instantânea.

### 3. Laço Principal e Atualização da DP

C++

```
int totalMascaras = (1 << W);
vector<long long> dpAtual(totalMascaras, 0);
dpAtual[0] = 1;

for (int r = 0; r < H; r++) {
    vector<long long> proximoDp(totalMascaras, 0);
    for (int mask = 0; mask < totalMascaras; mask++) {
        if (dpAtual[mask] > 0) {
            gerarTransicoes(0, mask, 0, proximoDp, dpAtual[mask]);
        }
    }
    dpAtual = proximoDp;
}

cout << dpAtual[0] << endl;
```

> [!note] Interpretação da Resposta Final
> 
> O resultado final está em `dpAtual[0]` após processar a linha $H-1$, pois nenhuma peça pode ficar projetando para fora do tabuleiro (máscara $0$).

## ⚡ Análise de Complexidade

|**Métrica**|**Complexidade**|**Justificativa**|
|---|---|---|
|**Tempo**|$O(H \cdot 2^W)$|Para $W \le 11$, $2^{11} = 2048$. O laço executa $11 \times 2048$ transições no pior caso.|
|**Espaço**|$O(2^W)$|Mantém apenas dois vetores de tamanho $2^W$ para a linha atual e a próxima linha.|