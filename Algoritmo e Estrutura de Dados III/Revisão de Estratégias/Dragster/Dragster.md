# 🏎️ Probabilidade do Torneio de Rubens (Mata-Mata em Árvore)

> [!abstract] **Visão Geral do Problema**
> 
> Em um torneio eliminatório (mata-mata) com $N$ pilotos, o competidor número **1 (Rubens)** deseja saber qual é a probabilidade exata dele ser o campeão do torneio.
> 
> Recebemos a matriz $M[i][j]$ com a chance de cada piloto vencer os outros em um confronto direto e a descrição das partidas que formam a chave do campeonato.

## 🧠 1. Como Funciona a Lógica em Árvore?

Um torneio eliminatório tem a estrutura de uma **Árvore Binária**:

Plaintext

```
                 [ Partida Final ] (Raiz)
                     /       \
           [ Partida A ]   [ Partida B ]
             /       \       /       \
          [Piloto 1] [2]   [3]       [4]  (Folhas)
```

1. **Os Pilotos ($1$ a $N$):** São as pontas iniciais (folhas). Cada piloto tem $100\%$ ($1.0$) de chance de disputar a sua própria posição inicial.
    
2. **As Corridas ($N+1$ a $2N-1$):** São os cruzamentos (nós internos). Cada corrida reúne o vencedor de um lado esquerdo (`esq`) contra o vencedor de um lado direito (`dir`).
    
3. **A Grande Final:** É a **única corrida que não alimenta nenhuma outra corrida** (ou seja, é o nó que não tem "pai").
    

## 📐 2. A Fórmula da Probabilidade

Para que o piloto $i$ vença uma partida $k$:

1. Ele precisa **vencer todas as etapas anteriores do lado esquerdo**.
    
2. O adversário dele será alguém $j$ vindo do lado direito. Como não sabemos quem vai vencer o lado direito, **somamos as chances de cada adversário possível $j$ multiplicado pela probabilidade de $i$ derrotar $j$ ($M[i][j]$)**:
    

$$P(i \text{ vence } k) = P(i \text{ vence } \text{esq}) \times \sum_{j \in \text{dir}} \Big( P(j \text{ vence } \text{dir}) \times M[i][j] \Big)$$

## 💻 3. Código Completo em C++

```cpp
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Variáveis globais para armazenar os dados do torneio
int N;
vector<vector<double>> M; // M[i][j]: chance do piloto i vencer o piloto j
vector<int> esq;          // Chave do lado esquerdo de cada partida
vector<int> dir;          // Chave do lado direito de cada partida

// Função recursiva que calcula as chances de vitória de cada competidor no nó atual
vector<double> calcular(int no) {
    // Vetor de tamanho (N + 1) onde cada posição guarda a probabilidade do piloto vencer
    vector<double> prob(N + 1, 0.0);

    // CASO BASE: O nó é um piloto individual (folha da árvore de 1 a N)
    if (no <= N) {
        prob[no] = 1.0; // O piloto tem 100% de chance de estar na sua posição inicial
        return prob;
    }

    // PASSO RECURSIVO: Calcula primeiro as probabilidades dos dois lados (filhos)
    vector<double> probEsq = calcular(esq[no]);
    vector<double> probDir = calcular(dir[no]);

    // 1. Calcula a chance dos competidores do lado ESQUERDO vencerem este confronto
    for (int i = 1; i <= N; i++) {
        if (probEsq[i] > 0.0) {
            double chanceContraDireita = 0.0;
            for (int j = 1; j <= N; j++) {
                if (probDir[j] > 0.0) {
                    chanceContraDireita += probDir[j] * M[i][j];
                }
            }
            prob[i] = probEsq[i] * chanceContraDireita;
        }
    }

    // 2. Calcula a chance dos competidores do lado DIREITO vencerem este confronto
    for (int j = 1; j <= N; j++) {
        if (probDir[j] > 0.0) {
            double chanceContraEsquerda = 0.0;
            for (int i = 1; i <= N; i++) {
                if (probEsq[i] > 0.0) {
                    chanceContraEsquerda += probEsq[i] * M[j][i];
                }
            }
            prob[j] = probDir[j] * chanceContraEsquerda;
        }
    }

    return prob;
}

int main() {
    // Repete a leitura enquanto N for diferente de 0
    while (cin >> N && N != 0) {
        
        // 1. Cria e preenche a matriz de probabilidades M com tamanho (N+1) x (N+1)
        M.assign(N + 1, vector<double>(N + 1, 0.0));
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                cin >> M[i][j];
            }
        }

        int total = 2 * N;
        esq.assign(total, 0);
        dir.assign(total, 0);
        vector<bool> temPai(total, false);

        // 2. Lê as N - 1 partidas do torneio
        for (int k = N + 1; k <= 2 * N - 1; k++) {
            int A, B;
            cin >> A >> B;
            esq[k] = A;
            dir[k] = B;
            temPai[A] = true; // O nó A disputa uma partida, logo tem um "pai"
            temPai[B] = true; // O nó B disputa uma partida, logo tem um "pai"
        }

        // 3. Descobre a Grande Final (a única partida que não tem pai)
        int partidaFinal = 0;
        for (int k = N + 1; k <= 2 * N - 1; k++) {
            if (!temPai[k]) {
                partidaFinal = k;
                break;
            }
        }

        // 4. Dispara a recursão a partir da partida final
        vector<double> resultado = calcular(partidaFinal);

        // 5. Exibe a chance de Rubens (piloto 1) ser o campeão com 6 casas decimais
        cout << fixed << setprecision(6) << resultado[1] << endl;
    }

    return 0;
}
```

## 🔍 4. Explicação Detalhada Bloco por Bloco

### Bloco 1: Bibliotecas Utilizadas

- `<iostream>`: Entrada (`cin`) e saída (`cout`).
    
- `<vector>`: Estrutura de lista dinâmica flexível para tabelas e matrizes.
    
- `<iomanip>`: Fornece os comandos `fixed` e `setprecision(6)` para formatar a saída com exatamente $6$ casas decimais.
    
- `<algorithm>`: Biblioteca de utilitários matemáticos e ordenação.
    

### Bloco 2: A Função Recursiva `calcular(no)`

C++

```
if (no <= N) {
    prob[no] = 1.0;
    return prob;
}
```

> [!note] **Caso Base (Folhas)**
> 
> Se o número do nó for menor ou igual a $N$, significa que ele não é uma corrida, mas sim um piloto individual. A chance dele "ganhar" sua própria vaga inicial é $100\%$ ($1.0$).

C++

```
vector<double> probEsq = calcular(esq[no]);
vector<double> probDir = calcular(dir[no]);
```

> [!tip] **Passo Recursivo**
> 
> Antes de calcular a partida atual, o programa chama a si mesmo para resolver completamente a subchave esquerda (`probEsq`) e a subchave direita (`probDir`). Isso resolve as dependências automaticamente, mesmo se o arquivo de entrada fornecer as partidas fora de ordem.

### Bloco 3: Identificação da Grande Final (`temPai`)

C++

```
for (int k = N + 1; k <= 2 * N - 1; k++) {
    int A, B;
    cin >> A >> B;
    esq[k] = A;
    dir[k] = B;
    temPai[A] = true;
    temPai[B] = true;
}
```

- Marcamos `temPai[A] = true` e `temPai[B] = true`.
    
- Toda partida intermediária e todo piloto será filho de alguma outra corrida. **Apenas a grande final nunca será marcada como filha de ninguém**. O laço seguinte encontra esse nó raiz e inicia o cálculo por ele.
    

## ⚡ 5. Análise de Complexidade

|**Métrica**|**Complexidade**|**Explicação Prática**|
|---|---|---|
|**Tempo**|$O(N^2)$|Cada par de pilotos $(i, j)$ só se cruza na árvore uma única vez. Para $N = 300$, executa cerca de $45.000$ operações, rodando em menos de $0.01$ segundos.|
|**Espaço**|$O(N^2)$|Matriz $M$ de tamanho $(N+1) \times (N+1)$ para guardar as probabilidades dos pilotos.|