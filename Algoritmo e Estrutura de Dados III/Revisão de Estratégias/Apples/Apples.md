
# 🍎 Colheita de Maçãs (Beecrowd 1517)

> [!abstract] **Visão Geral do Problema**
> 
> Rafael está em um tabuleiro $N \times M$ na posição inicial $(X, Y)$ no tempo $T = 0$. Ele pode se mover $1$ unidade por segundo nas $8$ direções possíveis. $K$ maçãs cairão em coordenadas $(X_i, Y_i)$ em instantes de tempo $T_i$ não decrescentes.
> 
> O objetivo é encontrar o **número máximo de maçãs** que Rafael consegue coletar a tempo.

## 🧠 Modelagem Matemática e Transição de Estados

### Distância de Chebyshev (Movimento em 8 Direções)

O tempo mínimo para se deslocar entre dois pontos $(x_1, y_1)$ e $(x_2, y_2)$ em uma grade onde movimentos diagonais levam $1$ segundo é:

$$\text{distância} = \max(\vert{}x_1 - x_2\vert{}, \vert{}y_1 - y_2\vert{})$$

Uma transição da maçã $j$ para a maçã $i$ é válida se e somente se:

$$\max(\vert{}x_j - x_i\vert{}, \vert{}y_j - y_i\vert{}) \le T_i - T_j$$

## 🔍 Explicação Detalhada de Cada Bloco e Linha de Código

### Bloco 1: Importação de Bibliotecas e Estrutura de Dados

C++

```
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Maca {
    int x;
    int y;
    int t;
};
```

- **`#include <iostream>`**: Permite usar `cin` e `cout`.
    
- **`#include <vector>`**: Permite a alocação dinâmica dos vetores `macas` e `dp`.
    
- **`#include <algorithm>`**: Fornece a função `max()`.
    
- **`#include <cmath>`**: Fornece a função `abs()` para calcular as diferenças absolutas.
    
- **`struct Maca`**: Modela cada evento de queda de maçã com suas coordenadas espaciais `x`, `y` e temporal `t`.
    

### Bloco 2: Função de Verificação de Alcance

C++

```
bool alcancavel(const Maca& a, const Maca& b) {
    int dist = max(abs(a.x - b.x), abs(a.y - b.y));
    return dist <= (b.t - a.t);
}
```

- **`const Maca& a, const Maca& b`**: Passagem por referência constante para evitar cópias de memória desnecessárias.
    
- **`int dist = max(abs(a.x - b.x), abs(a.y - b.y));`**: Calcula o número mínimo de segundos necessários para se deslocar da posição de $a$ até a posição de $b$.
    
- **`return dist <= (b.t - a.t);`**: Retorna `true` se o tempo disponível entre os dois eventos for suficiente para cobrir o deslocamento.
    

### Bloco 3: Leitura e Condições Iniciais

C++

```
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, K;

    while (cin >> N >> M >> K && !(N == 0 && M == 0 && K == 0)) {
        vector<Maca> macas(K + 1);
        for (int i = 1; i <= K; i++) {
            cin >> macas[i].x >> macas[i].y >> macas[i].t;
        }

        Maca rafael;
        cin >> rafael.x >> rafael.y;
        rafael.t = 0;
        macas[0] = rafael;
```

- **`ios_base::sync_with_stdio(false); cin.tie(NULL);`**: Otimização de fluxo de E/S.
    
- **`while (cin >> N >> M >> K && !(N == 0 && M == 0 && K == 0))`**: Processa os múltiplos casos de teste até encontrar a condição de parada $0 \; 0 \; 0$.
    
- **`vector<Maca> macas(K + 1);`**: Armazena as $K$ maçãs nas posições $1$ até $K$.
    
- **`macas[0] = rafael;`**: Armazena o ponto inicial de Rafael no índice $0$ com instante $t = 0$, unificando a verificação de transições.
    

### Bloco 4: Programação Dinâmica ($O(K^2)$)

C++

```
        vector<int> dp(K + 1, -1);
        dp[0] = 0;

        int max_macas = 0;

        for (int i = 1; i <= K; i++) {
            if (alcancavel(macas[0], macas[i])) {
                dp[i] = 1;
            }

            for (int j = 1; j < i; j++) {
                if (dp[j] != -1 && alcancavel(macas[j], macas[i])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }

            if (dp[i] > max_macas) {
                max_macas = dp[i];
            }
        }

        cout << max_macas << "\n";
    }

    return 0;
}
```

- **`vector<int> dp(K + 1, -1);`**: Vetor DP onde `dp[i]` guarda o número máximo de maçãs que podem ser coletadas terminando na maçã $i$. Inicializado com $-1$ para indicar estados inalcançáveis.
    
- **`if (alcancavel(macas[0], macas[i])) dp[i] = 1;`**: Se a maçã $i$ puder ser alcançada diretamente a partir do ponto de partida de Rafael no instante $t = 0$, ela pode ser a primeira maçã coletada (acumulando $1$ maçã).
    
- **`for (int j = 1; j < i; j++)`**: Avalia todas as maçãs anteriores $j$.
    
- **`if (dp[j] != -1 && alcancavel(macas[j], macas[i]))`**: Se a maçã $j$ era alcançável e é possível se deslocar de $j$ até $i$ no intervalo de tempo $T_i - T_j$, atualizamos `dp[i] = max(dp[i], dp[j] + 1)`.
    
- **`max_macas`**: Rastreia o valor máximo encontrado no vetor `dp` e é impresso ao final do caso de teste.
    

## ⚡ Tabela de Análise de Complexidade

|**Métrica**|**Complexidade**|**Detalhes**|
|---|---|---|
|**Tempo**|$O(K^2)$|Dois laços aninhados de tamanho $K$. Para $K \le 1000$, realiza no máximo $\approx 5 \times 10^5$ operações simples por caso de teste (execução em $< 0.02$s).|
|**Espaço**|$O(K)$|Utiliza vetores unidimensionais `macas` e `dp` de tamanho $K + 1$.|