
# Produção de Vodka em São Petersburgo (Beecrowd 1210)

> [!abstract] Visão Geral do Problema
> 
> Determinar o **custo mínimo** para operar uma destilaria por $N$ anos, decidindo no início de cada ano se o destilador deve ser mantido ou substituído por um novo.
> 
> Deve-se imprimir o custo mínimo e a **lista de anos em que a máquina foi substituída**, priorizando trocas mais cedo em caso de empate.

## 🧠 Modelagem de Estados (Dynamic Programming)

### Definição do Estado

$dp[ano][idade]$: Menor custo acumulado do ano $ano$ até o ano final $N$, dado que o destilador possui idade $idade$ no início do ano.

Plaintext

```
Decisão no início do ano com idade atual 'idade':

                     ┌── SE idade == M ──► Obrigatório Trocar: (P - V[idade]) + C[0] + dp[ano+1][1]
dp[ano][idade] = ───┤
                     └── SE idade < M  ──► min {
                                             Trocar: (P - V[idade]) + C[0] + dp[ano+1][1],
                                             Manter: C[idade] + dp[ano+1][idade+1]
                                           }
```

## 📌 Detalhamento da Estrutura

### 1. Preenchimento Regressivo da Tabela DP

C++

```
for (int ano = N; ano >= 1; ano--) {
    for (int idade = 0; idade <= M; idade++) {
        int custo_troca = (P - V[idade]) + C[0] + dp[ano + 1][1];

        if (idade == M) {
            dp[ano][idade] = custo_troca;
        } else {
            int custo_manter = C[idade] + dp[ano + 1][idade + 1];
            dp[ano][idade] = min(custo_troca, custo_manter);
        }
    }
}
```

> [!note] Caso Base
> 
> Para todo $idade \in [0, M]$, $dp[N+1][idade] = 0$, pois após o ano $N$ o período de produção encerra sem custos adicionais.

### 2. Algoritmo de Reconstrução de Caminho

C++

```
vector<int> trocas;
int idade_atual = I;

for (int ano = 1; ano <= N; ano++) {
    int custo_troca = (P - V[idade_atual]) + C[0] + dp[ano + 1][1];
    int custo_manter = (idade_atual < M) ? (C[idade_atual] + dp[ano + 1][idade_atual + 1]) : 1e9;

    if (idade_atual == M || custo_troca <= custo_manter) {
        trocas.push_back(ano);
        idade_atual = 1;
    } else {
        idade_atual++;
    }
}
```

> [!tip] Regra de Desempate Estrita
> 
> O teste `custo_troca <= custo_manter` assegura a exigência de substituir o destilador o mais cedo possível sempre que os custos forem idênticos.

## ⚡ Análise de Complexidade

|**Métrica**|**Complexidade**|**Justificativa**|
|---|---|---|
|**Tempo**|$O(N \cdot M)$|A matriz possui dimensões $(N+2) \times (M+1)$ e cada transição é calculada em $O(1)$. Para $N, M \le 2000$, realiza cerca de $4 \times 10^6$ operações.|
|**Espaço**|$O(N \cdot M)$|Matriz bidimensional `dp` alocada com `vector<vector<int>>`.|