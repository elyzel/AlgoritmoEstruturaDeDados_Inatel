# Menor Soma de Subconjunto Inalcançável

> [!abstract] Visão Geral do Problema
> 
> Dado um conjunto de $N$ números inteiros positivos, determinar o **menor inteiro positivo** que **não** pode ser representado como a soma de nenhum subconjunto do vetor.

## 🧠 Teorema da Extensão de Intervalo

Se com os primeiros elementos conseguimos gerar **todas** as somas no intervalo contínuo $[1, S]$, ao adicionar um novo elemento $X$:

- Se $X \le S + 1 \implies$ Novo intervalo contínuo alcançável: $[1, S + X]$.
    
- Se $X > S + 1 \implies$ O valor $S + 1$ **nunca poderá ser formado**, pois todos os elementos seguintes serão $\ge X > S + 1$.
    

Plaintext

```
Intervalo atual: [1 -------------- S]
                                    ▲
                         Tentando cobrir: S + 1
                         
Caso X <= S + 1: [1 ------------------------- S + X]  (Sucesso!)
Caso X >  S + 1: [1 -------------- S]  ... [X ...]    (Buraco em S + 1!)
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

### 2. Algoritmo Guloso Linear com `sort`

C++

```
vector<long long> A(N);
for (int i = 0; i < N; i++) cin >> A[i];

sort(A.begin(), A.end());

long long menor_impossivel = 1;
for (int i = 0; i < N; i++) {
    if (A[i] > menor_impossivel) {
        break;
    }
    menor_impossivel += A[i];
}

cout << menor_impossivel << endl;
```

> [!tip] Critério de Parada
> 
> O laço encerra no primeiro elemento $A[i]$ que criar uma descontinuidade ($A[i] > \text{menor\_impossivel}$). Se todos os números forem consumidos, a resposta é a soma total de todos os elementos mais $1$.

## ⚡ Análise de Complexidade

| **Métrica** | **Complexidade** | **Justificativa**                                                                |
| ----------- | ---------------- | -------------------------------------------------------------------------------- |
| **Tempo**   | $O(N \log N)$    | O passo dominante é a ordenação com `sort()`. O laço seguinte executa em $O(N)$. |
| **Espaço**  | $O(N)$           | Vetor `vector<long long> A(N)` para armazenar a entrada.                         |