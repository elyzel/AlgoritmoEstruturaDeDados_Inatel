
# 🐱 O Gato do Zelador do Armazém (Beecrowd 1600)

> [!abstract] **Visão Geral do Problema**
> 
> Controlamos um gato (`j`) em um armazém de $N$ linhas e $M$ colunas que deve empurrar um bloco de terra (`b`) até a posição de destino (`x`).
> 
> O mapa contém até $5$ portas (`#`). Uma porta se abre no momento em que o gato pisa nela. O bloco **não pode** ser empurrado para uma porta fechada.
> 
> O objetivo é encontrar o **número mínimo de portas abertas** para completar a tarefa e, como critério de desempate, o **menor número de movimentos do gato**. Se for impossível, imprimir `-1`.

## 🎯 Análise Estratégica: Por que este paradigma?

> [!check] **Avaliação de Abordagens**
> 
> - ❌ **Força Bruta / Backtracking com DFS ($O(4^{\text{movimentos}})$):**
>     
>     Como o gato pode revisitar posições para manobrar em volta da caixa, uma busca em profundidade pura entraria em ciclos infinitos ou exploraria um número impraticável de ramificações, resultando em **Time Limit Exceeded (TLE)**.
>     
> - ❌ **Estratégia Gulosa (Greedy):**
>     
>     Tentar sempre diminuir a distância Manhattan do bloco até o alvo ou evitar abrir portas a qualquer custo falha completamente. Frequentemente é necessário dar voltas no armazém e abrir portas distantes para conseguir posicionar o gato atrás do bloco e empurrá-lo no sentido correto. Decisões míopes locais não funcionam em Sokoban.
>     
> - ✅ **Paradigma Ideal: Busca em Largura (BFS) no Grafo de Estados com Bitmask ($O(N^2 \cdot M^2 \cdot 2^P)$):**
>     
>     Como cada movimento tem custo $1$ e há no máximo $5$ portas ($2^5 = 32$ máscaras de bits possíveis), o espaço total de estados $(gx, gy, bx, by, \text{mask})$ é finito. A BFS em conjunto com uma matriz plana de distâncias garante o menor número de movimentos para cada configuração de portas abertas.
>     

## 🧠 Modelagem de Estados (Grafo Implícito)

Cada configuração única do jogo é um vértice no grafo:

$$\text{Estado} = (gx, gy, bx, by, \text{mask})$$

- $(gx, gy)$: Coordenadas do gato ($0 \le gx < N$, $0 \le gy < M$).
    
- $(bx, by)$: Coordenadas do bloco ($0 \le bx < N$, $0 \le by < M$).
    
- $\text{mask} \in [0, 31]$: Inteiro cujos bits de $0$ a $4$ indicam quais das portas estão abertas ($1$) ou fechadas ($0$).
    

Plaintext

```
Movimento do Gato para (ngx, ngy):
 ├─ Se (ngx, ngy) == (bx, by) ──► EMPURRÃO DO BLOCO para (nbx, nby)
 │                                 Válido se (nbx, nby) não for parede ('*')
 │                                 e não for porta com bit correspondente 0.
 └─ Se (ngx, ngy) != (bx, by) ──► MOVIMENTO SIMPLES
                                   Se (ngx, ngy) for porta '#', ativa bit na mask.
```

## 🔍 Explicação Detalhada de Cada Bloco e Linha de Código

### Bloco 1: Estruturas Globais e Matriz Estática

Snippet de código

```
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

struct Estado {
    int gx, gy;
    int bx, by;
    int mask;
};

int dist_map[25][25][25][25][32];
```

- **`#include <...>`**: Apenas as bibliotecas fundamentais de fluxos, vetores e manipulação de strings.
    
- **`const int dx[4], dy[4]`**: Vetores de deslocamento ortogonal para simular os 4 passos possíveis (Cima, Baixo, Esquerda e Direita).
    
- **`struct Estado`**: Modela a tupla $(gx, gy, bx, by, \text{mask})$.
    
- **`int dist_map[25][25][25][25][32]`**: Matriz 5D estática alocada na memória BSS ($\approx 48 \text{ MB}$). Elimina milhares de alocações dinâmicas na pilha por caso de teste.
    

### Bloco 2: Função Auxiliar `contarPortas`

Snippet de código

```
int contarPortas(int mask) {
    int cont = 0;
    while (mask > 0) {
        if (mask & 1) cont++;
        mask >>= 1;
    }
    return cont;
}
```

- **`mask & 1`**: Avalia o bit menos significativo.
    
- **`mask >>= 1`**: Desloca a representação binária à direita.
    
- Retorna quantas portas estão ativas no estado atual.
    

### Bloco 3: Leitura dos Dados e Mapeamento dos Elementos

Snippet de código

```
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;

    while (cin >> N >> M) {
        vector<string> grid(N);
        int gx = 0, gy = 0, bx = 0, by = 0, fx = 0, fy = 0;
        vector<pair<int, int>> portas;

        for (int i = 0; i < N; i++) {
            cin >> grid[i];
            for (int j = 0; j < M; j++) {
                if (grid[i][j] == 'j') { gx = i; gy = j; grid[i][j] = '.'; }
                else if (grid[i][j] == 'b') { bx = i; by = j; grid[i][j] = '.'; }
                else if (grid[i][j] == 'x') { fx = i; fy = j; grid[i][j] = '.'; }
                else if (grid[i][j] == '#') { portas.push_back({i, j}); }
            }
        }
```

- **`cin >> N >> M`**: Lê $N$ (linhas) e $M$ (colunas) corretamente.
    
- **`grid[i][j] = '.'`**: Transforma as posições ocupadas pelos elementos móveis em casas livres no mapa para que a navegação seja controlada pelo vetor `fila`.
    
- **`portas.push_back({i, j})`**: Atribui a cada porta `#` um índice de $0$ a $4$, correspondente ao seu bit na máscara binária.
    

### Bloco 4: Execução da BFS e Poda de Portas

Snippet de código

```
        int inicioFila = 0;

        while (inicioFila < (int)fila.size()) {
            Estado atual = fila[inicioFila++];
            int d = dist_map[atual.gx][atual.gy][atual.bx][atual.by][atual.mask];
            int pAbertas = contarPortas(atual.mask);

            if (atual.bx == fx && atual.by == fy) {
                if (pAbertas < melhorPortas) {
                    melhorPortas = pAbertas;
                    melhorPassos = d;
                } else if (pAbertas == melhorPortas && d < melhorPassos) {
                    melhorPassos = d;
                }
                continue;
            }

            if (pAbertas > melhorPortas) continue;
```

- **`inicioFila++`**: Consome os estados da fila em ordem FIFO.
    
- **`if (pAbertas < melhorPortas)`**: Atualiza o menor número de portas e a menor quantidade de passos necessários para atingir o objetivo $(fx, fy)$.
    
- **`if (pAbertas > melhorPortas) continue;`**: Poda ramos da busca que já abriram mais portas que uma solução completa já encontrada.
    

### Bloco 5: Transições de Movimento e Validação de Portas

Snippet de código

```
            for (int dir = 0; dir < 4; dir++) {
                int ngx = atual.gx + dx[dir];
                int ngy = atual.gy + dy[dir];

                if (ngx < 0 || ngx >= N || ngy < 0 || ngy >= M || grid[ngx][ngy] == '*') continue;

                int nbx = atual.bx;
                int nby = atual.by;
                int nmask = atual.mask;

                if (ngx == atual.bx && ngy == atual.by) {
                    nbx += dx[dir];
                    nby += dy[dir];

                    if (nbx < 0 || nbx >= N || nby < 0 || nby >= M || grid[nbx][nby] == '*') continue;

                    bool portaBloqueada = false;
                    for (int p = 0; p < totalPortas; p++) {
                        if (nbx == portas[p].first && nby == portas[p].second) {
                            if (!(nmask & (1 << p))) {
                                portaBloqueada = true;
                                break;
                            }
                        }
                    }
                    if (portaBloqueada) continue;
                }

                for (int p = 0; p < totalPortas; p++) {
                    if (ngx == portas[p].first && ngy == portas[p].second) {
                        nmask |= (1 << p);
                    }
                }

                if (dist_map[ngx][ngy][nbx][nby][nmask] == -1) {
                    dist_map[ngx][ngy][nbx][nby][nmask] = d + 1;
                    fila.push_back({ngx, ngy, nbx, nby, nmask});
                }
            }
```

- **`portaBloqueada`**: O bloco só pode entrar em uma porta se o bit correspondente já estiver ativo (`nmask & (1 << p)`).
    
- **`nmask |= (1 << p)`**: Se o gato entra na coordenada de uma porta, o bit correspondente é ativado (abrindo a porta permanentemente).
    

### Bloco 6: Impressão e Reset em Tempo Linear $O(\text{visitados})$

Snippet de código

```
        if (melhorPortas == 999) {
            cout << -1 << "\n";
        } else {
            cout << melhorPortas << " " << melhorPassos << "\n";
        }

        for (size_t i = 0; i < fila.size(); i++) {
            dist_map[fila[i].gx][fila[i].gy][fila[i].bx][fila[i].by][fila[i].mask] = -1;
        }
    }

    return 0;
}
```

- **`cout << melhorPortas << " " << melhorPassos`**: Exibe o par mínimo ótimo formatado.
    
- **Limpeza em $O(\text{visitados})$**: Restaura as posições modificadas em `dist_map` de volta para `-1`, permitindo que cada caso de teste subsequente execute em tempo quase nulo sem `memset` em 48 MB.
    

## ⚡ Tabela de Análise de Complexidade

| **Métrica** | **Complexidade**             | **Detalhes**                                                                                                                                                    |
| ----------- | ---------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Tempo**   | $O(N^2 \cdot M^2 \cdot 2^P)$ | Para $N, M \le 25$ e $P \le 5$, cada estado é visitado no máximo uma vez. O tempo total de execução fica abaixo de $0.05$s, muito inferior ao limite de $5.0$s. |
| **Espaço**  | $O(N^2 \cdot M^2 \cdot 2^P)$ | Matriz estática `dist_map` de $48 \text{ MB}$ e vetor `fila` alocado estritamente na memória principal.                                                         |