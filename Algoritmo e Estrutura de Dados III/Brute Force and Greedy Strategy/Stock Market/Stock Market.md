
## 📌 Detalhamento da Estrutura do Código

### 1. Inclusão de Bibliotecas

C++

```
#include <iostream>
#include <vector>
#include <algorithm> // Para usar a função max()

using namespace std;
```

> [!note] Bibliotecas Utilizadas
> 
> - `<iostream>`: Entrada e saída padrão (`cin`, `cout`, `endl`).
>     
> - `<vector>`: Armazenamento dinâmico do histórico de preços dos $N$ dias.
>     
> - `<algorithm>`: Fornece a função `max(a, b)` para calcular as escolhas ótimas de transição.
>     

### 2. Leitura dos Dados e Casos de Teste

C++

```
int main() {
    int N, C;

    while (cin >> N >> C) {
        vector<int> P(N);
        for (int i = 0; i < N; i++) {
            cin >> P[i];
        }
```

> [!info] Leitura Sequencial
> 
> - O `while (cin >> N >> C)` processa múltiplos casos de teste até o fim da entrada.
>     
> - O vetor `P` armazena todos os preços da ação do dia $0$ até $N-1$.
>     

### 3. Casos Iniciais (Dia 1 / Índice 0)

C++

```
        int sem_acao = 0;
        int com_acao = -P[0] - C;
```

- **`sem_acao = 0`**: No início, antes de comprar qualquer coisa, o lucro acumulado é $0$.
    
- **`com_acao = -P[0] - C`**: Se decidirmos comprar no 1º dia ($P[0]$), ficamos no negativo com o valor da ação mais a taxa $C$.
    

### 4. Laço de Transição de Estados (Dia 2 ao Dia N)

C++

```
        for (int i = 1; i < N; i++) {
            int sem_acao_anterior = sem_acao;
            int com_acao_anterior = com_acao;

            sem_acao = max(sem_acao_anterior, com_acao_anterior + P[i]);
            com_acao = max(com_acao_anterior, sem_acao_anterior - P[i] - C);
        }

        cout << sem_acao << endl;
    }

    return 0;
}
```

> [!tip] Importância das Variáveis Temporárias
> 
> Salvamos `sem_acao_anterior` e `com_acao_anterior` em variáveis auxiliares para garantir que o cálculo do estado `com_acao` use o valor **antigo** de `sem_acao` (do dia anterior, e não o recém-atualizado do dia de hoje).

## 💻 Código Completo Compilável

C++

```
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, C;

    while (cin >> N >> C) {
        // 1. Armazena os preços no vetor
        vector<int> P(N);
        for (int i = 0; i < N; i++) {
            cin >> P[i];
        }

        // 2. Condições Iniciais no Dia 1
        int sem_acao = 0;
        int com_acao = -P[0] - C;

        // 3. Processamento dos dias 2 em diante
        for (int i = 1; i < N; i++) {
            int sem_acao_anterior = sem_acao;
            int com_acao_anterior = com_acao;

            sem_acao = max(sem_acao_anterior, com_acao_anterior + P[i]);
            com_acao = max(com_acao_anterior, sem_acao_anterior - P[i] - C);
        }

        // 4. Saída do lucro máximo
        cout << sem_acao << endl;
    }

    return 0;
}
```

## ⚡ Análise de Complexidade

|**Métrica**|**Complexidade**|**Justificativa**|
|---|---|---|
|**Tempo**|$O(N)$|O vetor de preços é percorrido em laços simples de tamanho $N$.|
|**Espaço**|$O(N)$|Alocação do vetor `vector<int> P(N)` para armazenar os $N$ preços das ações.|