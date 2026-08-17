# Estratégia de Brute Force

## Brute Force __Iterativa__

Para descobrir qual o maior valor possivel, o Brute Force testa todas as possibilidades até achar o melhor caminho possível.

| __Possibilidade__ | __Item 1__ | __Item 2__ | __Item 3__ | __Item 4__ |
| ----------------- | ---------- | ---------- | ---------- | ---------- |
| 1                 | 0          | 0          | 0          | 0          |
| 2                 | 1          | 0          | 0          | 0          |
| 3                 | 0          | 1          | 0          | 0          |
| N                 | ...        | ...        | ...        | ...        |

### Estrutura do Brute Force em Código

```cpp
#include<iostream>
#include<cmath>

//--  - Força bruta iterativa (Binária)
int fb_iterativa(int n, int cap, Item)

```
##  Brute Force Recursividade

Para descobrir o maior valor possível, o caminho é efetuado ao mesmo tempo por diversas ramificações, porém, consome mais desempenho do hardware utilizado.

![[Recursividade.canvas]]
# Estratégia de Greedy

A estratégia gulosa executa a operação através de juntar os maiores valores primeiramente e depois testando a compatibilidade até o menor possível.


# Programação Dinâmica

Utilizada uma matriz bidimensional para comparar os valores de forma iterativa ou recursiva também. Exclusiva para **análise combinatória**. 

>[!INFO]
>A programação dinâmica é mais econômica em seu processamento do que a força bruta iterativa.

## Iterativa


| 0   | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 10  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   | 0   |
| 0   | 0   | 0   | 0   | 0   | 35  | 35  | 35  | 35  | 35  | 35  |
| 0   | 0   | 0   | 25  | 25  | 35  | 35  | 35  | 60  | 60  | 60  |
|     |     |     |     |     |     |     |     |     |     |     |
|     |     |     |     |     |     |     |     |     |     |     |
